Salut, aici este readme-ul facut de mine (Poață Andrei-Cătălin, 313CD, nu Ponta, nu Popa, Poantă sau orice alta variantă).

Functiile de baza le-am facut ca la laborator.

Reversedeck -> am facut asemanator cu ce era in curs, doar ca am schimbat variabilele parca (am facut-o acum ceva timp)
npiles -> citeste din fisier numarul de pachete si ordinea, apoi face n pachete pe care la final le reuneste in ordine;
intercalare -> face 2 pachete si apoi efectiv pune 1 si 1 in functie de paritate.
mongean -> am facut o manevra la asta, am vazut ca practic amestecarea e echivalentul adaugarii la final cartilor de pe
           pozitii impare de dupa varf (sper sa se inteleaga). Am facut schema asta pentru ca dadeam rage la adaugat sub
           adaugat deasupra samd.
cardvalue, cardmin, returnvalue -> cred ca e evident ce fac
escarabeu -> daca valoarea cartii e intre 12 si 15 returneaza 1 (adica e de la J la A), altfel 0
copyanddequeue, copyandpush -> functiile de baza, doar ca fac o copie si o adauga pe aceea
copypiletoplayer, copypilev2 -> adauga ce e in pile (adica gramada de pe masa) in mana jucatorului (varianta pt rollingstone,
                                si varianta pentru scarabei)
shuffle si amestecare -> citesc din fisier tipul si verifica mot-a-mot ce trebuie sa faca. Diferenta e ca prima returneaza, 
                        cealalta scrie in fisier
razboi -> face pachetul stock, il sparge in 2, pune cartile in "mainile" jucatorilor (players[1], respectiv players[2]), 
        initializeaza matricea de aparitii pentru fiecare tip de carte din mana unui jucator, iar pentru 100 de maini, salveaza
        in v1 valoarea cartii jucatorului 1, in v2 valoarea cartii jucatorului 2, apoi ia pe cazuri. Daca v1<v2, ia cele 2 carti
        si le muta la finalul lui 2, daca v1>v2, se pun la finalul lui v1, daca e egalitate, se plimba n pozitii in cele 2 pachete
        si in functie de valori (v11 si v22) se alege la finalul pachetului carui jucator se adauga cartile. In caz ca se ajunge la
        100 de maini, se verifica matricea de aparitii.
rolling stone -> ah yes, asa rage am dat. Am vrut sa folosesc liste circulare, dar pana la urma am ramas la Z4 (clasa resturilor mod 4)
                Sparge pachetele in 4, le imparte la jucatori, salveaza in struct cartile in functie de tip, iar apoi literalmente fiecare
                caz este luat in parte. V-am zis ca am dat rage si m-am dat batut cu varianta inteligenta. + Ca pierdeam timp mult facand
                debugging. Daca are s, adauga in pile si sterge din mana, altfel adauga in mana tot ce e pe masa si actualizeaza valoarea
                care trebuie pusa in continuare, ia o carte de genul, o pune si tot asa. Daca n-are S, cauta H, daca n-are nici H, cauta C,
                daca n-are nici C, cauta D, iar daca nu are S, nu are nici D, nu este luat in considerare pentru ca intra in if-ul de la final,
                care incheie jocul. Am folosit while inifinit pentru ca mna, that's the practice in game design si asa am facut si pe sem 1 la II
                (ma rog, acolo era musai while infinit)
scarabeii egipteni -> another rage inducing thing. Idem ca la rollingstone, dar rip. Am ajuns sa fac aceeasi chestie. Merg cu ajutorul Z4, iar daca
                    se joaca 8 dupa o carte normala, se trece la indice+3, pt ca in Z4, ce sa vezi, daca adaugi 3, se ajunge la termenul de dinaintea
                    celui la care te afli. Avem indexul winner care se updateaza de fiecare data cand cineva joaca un scarabeu. El determina indexul 
                    unui posibil castigator. Daca acesta castiga si ia toate cartile de pe masa, se actualizeaza indicele pentru sfarsitul rundei, se
                    updateaza castigatorul si apoi indicele pentru finalul rundei se actualizeaza cu 0. (runda = serie de adaugat de carti fara a le ridica
                    cineva de jos). In cazuri, fie adaugam carte pe jos si o scoteam din pachet, fie luam cartile de pe jos si le puneam in pachet in functie,
                    fie schimbam sensul in functie de ce se intampla. In caz ca ramanea vreun player fara carti, indicele "maijoaca" (nume creativ, csz), devenea
                    0 si acel jucator nu mai era luat in calcul la desfasurarea jocului. Din nou, am folosit un while infinit din care se iese in cazul in care 
                    un singur jucator mai are carti in mana.
int main -> cred ca e evident, citeste de la tastatura tipul jocului si acceseaza functiile conform acelui tip.

My coding style is horrendous, ik.