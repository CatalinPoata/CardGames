#include <stdio.h>
#include "deck.h"

//Functia care determina tipul de amestecare si scrie in fisier(task 1)
void amestecare(FILE *fp, FILE *out){
    Deck *deck=initdeck();
    char type[100];
    int nr;
    fscanf(fp, "%d\n", &nr);
    for(int i=1; i<=nr; i++){
        fscanf(fp, "%s\n", type);
        if(strcmp(type, "\0")==0){
            fscanf(fp, "%s\n", type);
        }
        type[strlen(type)]='\0';
        if(strcmp(type, "inversare")==0){
            reversedeck(deck);
        }
        if(strcmp(type, "intercalare")==0){
            intercalare(deck);
        }
        if(strcmp(type, "npiles")==0){
            npiles(deck, fp);
        }
        if(strcmp(type, "mongean")==0){
            mongean(deck);
        }
    }
    printdecktofile(deck, out);
    emptydeck(deck);
}
//Analogul amestecare, doar ca returneaza pachetul in loc sa il scrie in fisier(task 2-4)
Deck* shuffle(FILE* fp){
    Deck *deck=initdeck();
    char type[100];
    int nr;
    fscanf(fp, "%d\n", &nr);
    for(int i=1; i<=nr; i++){
        fscanf(fp, "%s", type);
        while(strcmp(type, "\0")==0){
            fscanf(fp, "%s", type);
        }
        type[strlen(type)]='\0';
        if(strcmp(type, "inversare")==0){
            reversedeck(deck);
        }
        if(strcmp(type, "intercalare")==0){
            intercalare(deck);
        }
        if(strcmp(type, "npiles")==0){
            npiles(deck, fp);
        }
        if(strcmp(type, "mongean")==0){
            mongean(deck);
        }
    }
    return deck;
}
//Functia pentru razboi
void razboi(FILE* fp, FILE* out){

    Deck *deck=shuffle(fp);
    Deck *players[3];
    
    for(int i=1; i<=2; i++){
        players[i]=allocdeck();

    }
    
    Card *aux=deck->top;
    int k; 
    int carti[3][16]={};
    for(int i=1; i<=2; i++){
        k=1;
        while(k<=52/2){
            copyandenqueue(aux, players[i]);
            aux=aux->next;
            k++;
        }
    }
    emptydeck(deck);
    for(int i=1; i<=2; i++){
        players[i]->bottom->next=NULL;
    }
    for(int i=1; i<=2; i++){
        for(Card *iter=players[i]->top; iter!=NULL; iter=iter->next){
            carti[i][cardvalue(iter)]++;
        }
    }
    Deck *auxdeck=allocdeck();
    for(int mana=1; mana<=100; mana++){
        if(isempty(players[1])==1){
            fprintf(out, "%d", 2);
            break;
        }
        if(isempty(players[2])==1){
            fprintf(out, "%d", 1);
            break;
        }
        int v1=cardvalue(players[1]->top);
        int v2=cardvalue(players[2]->top);
        
        if(v1>v2){
            Card* aux=players[1]->top->next;
            players[1]->bottom->next=players[1]->top;
            players[1]->bottom=players[1]->top;
            players[1]->top->next=NULL;
            players[1]->top=aux;
            carti[1][cardvalue(players[2]->top)]++;
            carti[2][cardvalue(players[2]->top)]--;
            enqueue(players[1], players[2]->top);
            players[2]->top=players[2]->top->next;
            players[1]->bottom->next=NULL;
            players[2]->size--;
        }
        if(v2>v1){
            Card* aux=players[2]->top->next;
            players[2]->bottom->next=players[2]->top;
            players[2]->bottom=players[2]->top;
            players[2]->top->next=NULL;
            players[2]->top=aux;
            carti[2][cardvalue(players[1]->top)]++;
            carti[1][cardvalue(players[1]->top)]--;
            enqueue(players[2], players[1]->top);
            players[1]->top=players[1]->top->next;
            players[2]->bottom->next=NULL;
            players[1]->size--;
        }
        if(v1==v2){
            int N=calcmin(v1, players[1]->size, players[2]->size);
            Card *aux1=players[1]->top, *aux2=players[2]->top;
            for(int k=1; k<N; k++){
                aux1=aux1->next;
                aux2=aux2->next;
            }
            if(aux1->next!=NULL && N!=players[1]->size && aux2->next!=NULL){
                aux1=aux1->next;
            }
            if(aux2->next!=NULL && N!=players[2]->size && aux1->next!=NULL){
                aux2=aux2->next;
            }
            if(N==players[1]->size){
                aux1=players[1]->top;
                for(int k=1; k<N-1; k++){
                    aux1=aux1->next;
                }
            }
            if(N==players[2]->size){
                aux2=players[2]->top;
                for(int k=1; k<N-1; k++){
                    aux2=aux2->next;
                }
            }
            int v11, v22;
            v11=cardvalue(aux1);
            v22=cardvalue(aux2);

            if(v11>v22){
                Card *prev=players[1]->top, *iter;
                for(Card *iter=players[2]->top; iter!=aux2; iter=iter->next){
                    carti[2][cardvalue(iter)]--;
                    carti[1][cardvalue(iter)]++;
                }
                players[1]->top=aux1->next;
                auxdeck->top=prev;
                auxdeck->bottom=aux1;
                auxdeck->bottom->next=NULL;
                reversedeck(auxdeck);
                players[1]->bottom->next=auxdeck->top;
                players[1]->bottom=auxdeck->bottom;
                prev=players[2]->top;
                players[2]->top=aux2->next;
                auxdeck->top=prev;
                auxdeck->bottom=aux2;
                auxdeck->bottom->next=NULL;
                reversedeck(auxdeck);
                players[1]->bottom->next=auxdeck->top;
                players[1]->bottom=auxdeck->bottom;
                players[1]->size=players[1]->size+N+1;
                players[2]->size=players[2]->size-N-1;
            }
            else{
                Card *prev=players[2]->top;
                for(Card *iter=players[1]->top; iter!=aux1; iter=iter->next){
                    carti[2][cardvalue(iter)]++;
                    carti[1][cardvalue(iter)]--;
                }
                players[2]->top=aux2->next;
                auxdeck->top=prev;
                auxdeck->bottom=aux2;
                auxdeck->bottom->next=NULL;
                reversedeck(auxdeck);
                players[2]->bottom->next=auxdeck->top;
                players[2]->bottom=auxdeck->bottom;
                prev=players[1]->top;
                if(players[1]->size!=N){
                players[1]->top=aux1->next;}
                else players[1]->top=aux1;
                auxdeck->top=prev;
                auxdeck->bottom=aux1;
                auxdeck->bottom->next=NULL;
                reversedeck(auxdeck);
                players[2]->bottom->next=auxdeck->top;
                players[2]->bottom=auxdeck->bottom;
                players[2]->size=players[2]->size+N+1;
                players[1]->size=players[1]->size-N-1;
            }
        }
        if(mana==100){
            for(int l=15; l>=2; l--){
                if(carti[1][l]<carti[2][l]){
                    fprintf(out, "%d %c", 2, returnvalue(l));
                    break;
                }
                if(carti[1][l]>carti[2][l]){
                    fprintf(out, "%d %c", 1, returnvalue(l));
                    break;
                }
                
            }
        }
    }
    for(int i=1; i<=2; i++){
        emptydeck(players[i]);
    }
    free(auxdeck);
}
//Functia pentru rollingstone
void rollingstone(FILE *fp, FILE *out){
    Deck *deck=shuffle(fp);
    Deck *pile=NULL;
    pile=allocdeck();
    Card *aux=deck->top;
    int k;
    Jucatori *players[5];
    for(int i=1; i<=4; i++){
        players[i]=(Jucatori*)malloc(sizeof(Jucatori));
    }
    for(int i=1; i<=4; i++){
        players[i]->playerdeck=allocdeck();
        players[i]->S=allocdeck();
        players[i]->H=allocdeck();
        players[i]->C=allocdeck();
        players[i]->D=allocdeck();
    }
    for(int i=1; i<=4; i++){
        k=1;
        while(k<=52/4){
            copyandenqueue(aux, players[i]->playerdeck);
            if(aux->suit=='s'){
                copyandenqueue(aux, players[i]->S);
                players[i]->S->bottom->next=NULL;
            }
            if(aux->suit=='h'){
                copyandenqueue(aux, players[i]->H);
                players[i]->H->bottom->next=NULL;
            }
            if(aux->suit=='c'){
                copyandenqueue(aux, players[i]->C);
                players[i]->C->bottom->next=NULL;
            }
            if(aux->suit=='d'){
                copyandenqueue(aux, players[i]->D);
                players[i]->D->bottom->next=NULL;
            }
            aux=aux->next;
            k++;
        }
        players[i]->playerdeck->bottom->next=NULL;
    }
    int runda=0, count;
    char valoare='s';
    while(-1<3){
        count=runda%4+1;
        if(valoare=='s'){
            if(isempty(players[count]->S)==0){
                copyandpush(players[count]->S->top, pile);
                pop(players[count]->S);
            }
            else{
                copypiletoplayer(pile, players[count]);
                if(isempty(players[count]->H)==0){
                    valoare='h';
                    copyandpush(players[count]->H->top, pile);
                    pop(players[count]->H);
                }
                else if(isempty(players[count]->C)==0){
                    valoare='c';
                    copyandpush(players[count]->C->top, pile);
                    pop(players[count]->C);
                }
                else if(isempty(players[count]->D)==0){
                    valoare='d';
                    copyandpush(players[count]->D->top, pile);
                    pop(players[count]->D);
                }
            }
        }
        else if(valoare=='h'){
            if(isempty(players[count]->H)==0){
                copyandpush(players[count]->H->top, pile);
                pop(players[count]->H);
            }
            else{
                copypiletoplayer(pile, players[count]);
                if(isempty(players[count]->C)==0){
                    valoare='c';
                    copyandpush(players[count]->C->top, pile);
                    pop(players[count]->C);
                }
                else if(isempty(players[count]->D)==0){
                    valoare='d';
                    copyandpush(players[count]->D->top, pile);
                    pop(players[count]->D);
                }
                else if(isempty(players[count]->S)==0){
                    valoare='s';
                    copyandpush(players[count]->S->top, pile);
                    pop(players[count]->S);
                }
            }
        }
        else if(valoare=='c'){
            if(isempty(players[count]->C)==0){
                copyandpush(players[count]->C->top, pile);
                pop(players[count]->C);
            }
            else{
                copypiletoplayer(pile, players[count]);
                if(isempty(players[count]->D)==0){
                    valoare='d';
                    copyandpush(players[count]->D->top, pile);
                    pop(players[count]->D);
                }
                else if(isempty(players[count]->S)==0){
                    valoare='s';
                    copyandpush(players[count]->S->top, pile);
                    pop(players[count]->S);
                }
                else if(isempty(players[count]->H)==0){
                    valoare='h';
                    copyandpush(players[count]->H->top, pile);
                    pop(players[count]->H);
                }
            }
        }
        else if(valoare=='d'){
            if(isempty(players[count]->D)==0){
                copyandpush(players[count]->D->top, pile);
                pop(players[count]->D);
            }
            else{
                copypiletoplayer(pile, players[count]);
                if(isempty(players[count]->S)==0){
                    valoare='s';
                    copyandpush(players[count]->S->top, pile);
                    pop(players[count]->S);
                }
                else if(isempty(players[count]->H)==0){
                    valoare='h';
                    copyandpush(players[count]->H->top, pile);
                    pop(players[count]->H);
                }
                else if(isempty(players[count]->C)==0){
                    valoare='c';
                    copyandpush(players[count]->C->top, pile);
                    pop(players[count]->C);
                }
            }
        }
        if(isempty(players[count]->S)==1 && isempty(players[count]->H)==1 && isempty(players[count]->C)==1 && isempty(players[count]->D)==1){
            fprintf(out, "%d\n", count);
            break;
        }
        runda++;
    }
    emptydeck(deck);
    emptydeck(pile);
    for(int i=1; i<=4; i++){
        emptydeck(players[i]->playerdeck);
        emptydeck(players[i]->S);
        emptydeck(players[i]->H);
        emptydeck(players[i]->C);
        emptydeck(players[i]->D);
    }
    for(int i=1; i<=4; i++){
        free(players[i]);
    }
}
//Functia pentru scarabei
void scarabei(FILE* fp, FILE* out){
    Deck *deck=shuffle(fp);
    Deck *pile=allocdeck();
    Card *aux=deck->top;
    int k;
    Scarab *players[5];
    for(int i=0; i<=3; i++){
        players[i]=(Scarab*)malloc(sizeof(Scarab));
        players[i]->maijoaca=1;
    }
    for(int i=0; i<=3; i++){
        players[i]->playerdeck=allocdeck();
    }
    for(int i=0; i<=3; i++){
        k=1;
        while(k<=52/4){
            copyandenqueue(aux, players[i]->playerdeck);
            aux=aux->next;
            k++;
        }
    }
    int ordine=0, runda=0;
    int count=-1;
    int winner=0;
    int sfrunda=0;
    while(-1<3){
        if(sfrunda==1){
            count=winner;
        }
        else{
            if(ordine%2==0){
            count=(count+1)%4;
            }
            else{
                count=(count+3)%4;
            }
        }
        sfrunda=0;
        if(players[count]->maijoaca==1){
            if(isempty(pile)==1){
                if(escarabeu(players[count]->playerdeck->top)==1){
                    winner=count;
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                }
                else if(escarabeu(players[count]->playerdeck->top)==0 && cardvalue(players[count]->playerdeck->top)!=8){
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                }
                else if(escarabeu(players[count]->playerdeck->top)==0 && cardvalue(players[count]->playerdeck->top)==8){
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                    ordine+=1;
                }
                
            }
            else if(escarabeu(pile->top)==0){
                if(escarabeu(players[count]->playerdeck->top)==1){
                    winner=count;
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                }
                else if(escarabeu(players[count]->playerdeck->top)==0 && cardvalue(players[count]->playerdeck->top)!=8){
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                }
                else if(escarabeu(players[count]->playerdeck->top)==0 && cardvalue(players[count]->playerdeck->top)==8){
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                    ordine+=1;
                }
            }
            else{
                if(escarabeu(players[count]->playerdeck->top)==1){
                    winner=count;
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                }
                else if(escarabeu(players[count]->playerdeck->top)==0 && cardvalue(players[count]->playerdeck->top)==8){
                    copyandpush(players[count]->playerdeck->top, pile);
                    pop(players[count]->playerdeck);
                }
                else if(escarabeu(players[count]->playerdeck->top)==0 && cardvalue(players[count]->playerdeck->top)!=8){
                    copyandpush(players[count]->playerdeck->top, pile);
                    copypilev2(pile, players[winner]);
                    pop(players[count]->playerdeck);
                    sfrunda=1;
                }
            }
            if(isempty(players[count]->playerdeck)==1){
                players[count]->maijoaca=0;
            }
        }
        if(players[0]->maijoaca==0 && players[1]->maijoaca==0 && players[2]->maijoaca==0 && players[3]->maijoaca==1){
            fprintf(out, "%d\n", 4);
            break;
        }
        if(players[0]->maijoaca==0 && players[1]->maijoaca==0 && players[2]->maijoaca==1 && players[3]->maijoaca==0){
            fprintf(out, "%d\n", 3);
            break;
        }
        if(players[0]->maijoaca==0 && players[1]->maijoaca==1 && players[2]->maijoaca==0 && players[3]->maijoaca==0){
            fprintf(out, "%d\n", 2);
            break;
        }
        if(players[0]->maijoaca==1 && players[1]->maijoaca==0 && players[2]->maijoaca==0 && players[3]->maijoaca==0){
            fprintf(out, "%d\n", 1);
            break;
        }
    }
    emptydeck(deck);
    for(int i=0; i<=3; i++){
        emptydeck(players[i]->playerdeck);
    }
    for(int i=0; i<=3; i++){
        free(players[i]);
    }
    emptydeck(pile);
}
int main()
{
    FILE *fp=fopen("in", "r+");
    FILE *out=fopen("out", "wr");
    char task[120];
    fgets(task, 100, fp);
    task[strlen(task)-2]='\0';
    if(strcmp(task, "amestecare")==0){
        amestecare(fp, out);
        fclose(fp);
        fclose(out);
    }
    if(strcmp(task, "razboi")==0){
        razboi(fp, out);
        fclose(fp);
        fclose(out);
    }
    if(strcmp(task, "rollingstone")==0){
        rollingstone(fp, out);
        fclose(fp);
        fclose(out);
    }
    if(strcmp(task, "scarabei")==0){
        scarabei(fp, out);
        fclose(fp);
        fclose(out);
    }
}