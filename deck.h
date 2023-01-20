#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structuri lista simplu inlantuita 
typedef struct Card{
    char suit, value;
    struct Card *next;
} Card;
typedef struct Deck{
    Card *top, *bottom;
    int size;
} Deck;
//Structura jucatori de rollingstone (camp pentru pachet overall + camp pentru fiecare suita)
typedef struct Jucatori{
    Deck *playerdeck;
    Deck *S;
    Deck *H;
    Deck *C;
    Deck *D;
} Jucatori;
//Structura pentru jucatorii de scarabeu (indicele care ne arata daca a fost sau nu eliminat + pachetul overall)

typedef struct Scarab{
    int maijoaca;
    Deck *playerdeck;
} Scarab;
//Functie de alocare a unei carti
Card* alloccard(){
    Card *card=(Card*)malloc(sizeof(Card));
    return card;
}
//Functie de alcoare a unui pachet
Deck *allocdeck(){
    Deck *deck=(Deck*)malloc(sizeof(Deck));
    deck->bottom=NULL;
    deck->top=NULL;
    deck->size=0;
    if(deck!=NULL){
        return deck;
    }
}
//Functie de creare a unei carti
Card *createcard(char value, char suit){
    Card *card=alloccard();
    card->suit=suit;
    card->value=value;
    card->next=NULL;
    return card;
}
//Functie care verifica daca un pachet este gol
int isempty(Deck *deck){
    return (deck->top==NULL|| deck==NULL);
}
//Functia push pentru stive (adaugare la inceput)
void push(Deck *deck, Card *card){
    if(isempty(deck)==1){
		deck->top=deck->bottom=card;
		deck->size++;
	}
    else{
	card->next=deck->top;
	deck->top=card;
	deck->size++;
    }
}
//Functia enqueue pentru cozi (adaugare la final)
void enqueue(Deck *deck, Card *carte){
	if(isempty(deck)==1){
		deck->top=deck->bottom=carte;
		deck->size++;
	}
	else{
		deck->bottom->next=carte;
		deck->bottom=carte;
		deck->size++;
	}
}
//Functie de initializare a unui pachet stock (As, Ah, Ac, Ad ...) 
Deck *initdeck(){
    Deck *deck=allocdeck();
    char *suits="shcd";
    int size;
    for(int i=15; i>=2; i--){
        for(int j=0; j<strlen(suits); j++){
            if(i>=2 && i<10){
                Card *card=createcard('0'+i, suits[j]);
                size=deck->size+1;
                enqueue(deck, card);
            }
            if(i==10){
                Card *card=createcard('T', suits[j]);
                size=deck->size+1;
                enqueue(deck, card);
            }
            if(i==12){
                Card *card=createcard('J', suits[j]);
                size=deck->size+1;
                enqueue(deck, card);
            }
            if(i==13){
                Card *card=createcard('Q', suits[j]);
                size=deck->size+1;
                enqueue(deck, card);
            }
            if(i==14){
                Card *card=createcard('K', suits[j]);
                size=deck->size+1;
                enqueue(deck, card);
            }
            if(i==15){
                Card *card=createcard('A', suits[j]);
                size=deck->size+1;
                enqueue(deck, card);
            }
        }
    }
    return deck;
}
//Functia pop pentru stive(eliminare de la inceput)
void pop(Deck *deck){
	if(isempty(deck)==0){
		Card *aux;
		aux=deck->top;
		deck->top=deck->top->next;
		deck->size--;
		free(aux);
	}
}
//Functie de eliberare a unui pachet
void emptydeck(Deck *deck){
    if(deck!=NULL){
        while(deck->top!=NULL){
            pop(deck);
        }
    free(deck);
	}
}
//Functie de afisare in terminal a unui pachet (debugging tool)
void printdeck(Deck *deck){
    if(isempty(deck)==0){
    Card *card=deck->top;
    while(card!=NULL){
        printf("%c%c ", card->value, card->suit);
        card=card->next;
    }
    printf("\n");}
    else printf("Pachetul este gol!\n");
}
//Functie de afisare a unui pachet in fisier
void printdecktofile(Deck *deck, FILE *fp){
        if(isempty(deck)==0){
    Card *card=deck->top;
    for(int i=1; i<=51; i++){
        fprintf(fp, "%c%c ", card->value, card->suit);
        card=card->next;
    }
    fprintf(fp, "%c%c", card->value, card->suit);
    fprintf(fp, "\n");}
    else printf("Pachetul este gol!\n");
}
//Functia de inversare a unui pachet
void reversedeck(Deck *deck){
    Card *prev=NULL, *next=NULL, *curr=deck->top;
    deck->bottom=deck->top;
    while(curr!=NULL){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    deck->top=prev;
}
//Functia pentru n-piles
void npiles(Deck *deck, FILE *fp){
    int nrpachete, order[52];
    fscanf(fp, "%d", &nrpachete);
    for(int j=0; j<nrpachete; j++){
    fscanf(fp, "%d", &order[j]);
    }
    int size=deck->size/nrpachete;
    Deck *v[nrpachete];
    for(int i=1; i<=nrpachete; i++){
        v[i]=allocdeck();
    }
    Card *aux=deck->top;
    int j;
    for(int i=1; i<=nrpachete; i++){
        j=1;
        while(j<=52/nrpachete){
            enqueue(v[i], aux);
            aux=aux->next;
            j++;
        }
    }
    for(int i=1; i<nrpachete; i++){
        v[order[i-1]]->bottom->next=v[order[i]]->top;
    }
    deck->top=v[order[0]]->top;
    deck->bottom=v[order[nrpachete-1]]->bottom;
    deck->size=52;
    deck->bottom->next=NULL;
    for(int i=1; i<=nrpachete; i++){
        free(v[i]);
    }
}
//Functia pentru intercalare
void intercalare(Deck *deck){
    Deck *h1, *h2, *result;
    h1=allocdeck();
    h2=allocdeck();
    result=allocdeck();
    for(int i=1; i<=deck->size; i++){
        if(i<=deck->size/2){
            enqueue(h1, deck->top);
            deck->top=deck->top->next;
        }
        else{
            enqueue(h2, deck->top);
            deck->top=deck->top->next;
        }
    }
    for(int i=1; i<=deck->size; i++){
        if(i%2==1){
            enqueue(result, h1->top);
            h1->top=h1->top->next;
        }
        else{
            enqueue(result, h2->top);
            h2->top=h2->top->next;
        }
    }
    deck->top=result->top;
    deck->bottom=result->bottom;
    deck->bottom->next=NULL;
    deck->size=52;
    free(result);
    free(h1);
    free(h2);
}
//Functia pentru Monge's shuffle
void mongean(Deck *deck){
    Card *prev=NULL, *curr=NULL;
    curr=deck->top->next;
    prev=deck->top;
    int i=0;
    while(curr->next!=NULL){
        if(i%2==1){
            prev->next=curr->next;
            curr->next=deck->top;
            deck->top=curr;
            curr=prev;
            prev=curr->next;
            curr=prev->next;
        }
        i++;
    }
    deck->bottom=prev;
    deck->bottom->next=NULL;
    curr->next=deck->top;
    deck->top=curr;
}
//Functie care intoare valoarea cartii in functie de char-ul pus in structura
int cardvalue(Card *card){
    if(card->value>='2' && card->value<='9'){
        return card->value-'0';
    }
    if(card->value=='T'){
        return 10;
    }
    if(card->value=='J'){
        return 12;
    }
    if(card->value=='Q'){
        return 13;
    }
    if(card->value=='K'){
        return 14;
    }
    if(card->value=='A'){
        return 15;
    }
}
//Functie care calculeaza minimul de carti intoarse la razboi
int calcmin(int razboi, int s1, int s2){
    int m1, m2;
    if(razboi<s1){
        m1=razboi;
    }
    else{
        m1=s1;
    }
    if(razboi<s2){
        m2=razboi;
    }
    else{
        m2=s2;
    }
    if(m1<=m2){
        return m1;
    }
    else{
        return m2;
    }
}
//Inversul functiei cardvalue
char returnvalue(int x){
    if(x==15){
        return 'A';
    }
    if(x==14){
        return 'K';
    }
    if(x==13){
        return 'Q';
    }
    if(x==12){
        return 'J';
    }
    if(x==10){
        return 'T';
    }
    if(x>=2 && x<=9){
        return '0'+x;
    }
}
//Functie care verifica daca o carte este sau nu scarabeu
int escarabeu(Card *card){
    if(cardvalue(card)>=12 && cardvalue(card)<=15){
        return 1;
    }
    return 0;
}
//Enqueue, doar ca face copia unei carti si apoi adauga copia (yep, am dat rage cand umblam cu aceleasi carti din pachetul original la razboi)
void copyandenqueue(Card *card, Deck *lista){
    Card *newcard=createcard(card->value, card->suit);
    enqueue(lista, newcard);
    lista->bottom->next=NULL;
}
//Push, doar ca face copie si adauga copia
void copyandpush(Card *card, Deck *lista){
    Card *newcard=createcard(card->value, card->suit);
    push(lista, newcard);
    lista->bottom->next=NULL;
}
//Functie care adauga la final cartile in cadrul rolling stone
void copypiletoplayer(Deck *pile, Jucatori *player){
    while(pile->top!=NULL){
        copyandenqueue(pile->top, player->playerdeck);
        if(pile->top->suit=='s'){
            copyandenqueue(pile->top, player->S);
        }
        if(pile->top->suit=='h'){
            copyandenqueue(pile->top, player->H);
        }
        if(pile->top->suit=='c'){
            copyandenqueue(pile->top, player->C);
        }
        if(pile->top->suit=='d'){
            copyandenqueue(pile->top, player->D);
        }
        pop(pile);
    }
}
//Analogul lui copypiletoplayer, doar ca pentru scarabei
void copypilev2(Deck *pile, Scarab *player){
    while(pile->top!=NULL){
        copyandenqueue(pile->top, player->playerdeck);
        pop(pile);
    }
}