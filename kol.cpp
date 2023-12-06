#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "kol.h"

// inicjujemy urząd w postaci wektora
std::vector<interesant*> kolejki;
int numerki = 0;

interesant* nastepny(interesant* current, interesant* previous){
    if(current->przed == previous)
        return current->po;
    return current->przed;
}

void otwarcie_urzedu(int m){
    for(int i = 0; i < m; i++){
        interesant* new_interesant = (interesant*) malloc(sizeof(interesant));
        new_interesant->przed = new_interesant;
        new_interesant->po = new_interesant;
        new_interesant->numerek = 0;
        kolejki.push_back(new_interesant);
    }
}

/*
                     _ _.-'`-._ _
                    ;.'________'.;
         _________n.[____________].n_________
        |""_""_""_""||==||==||==||""_""_""_""]
        |"""""""""""||..||..||..||"""""""""""|
        |LI LI LI LI||LI||LI||LI||LI LI LI LI|
        |.. .. .. ..||..||..||..||.. .. .. ..|
        |LI LI LI LI||LI||LI||LI||LI LI LI LI|
     ,,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,
    ;;jgs;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*/

interesant *nowy_interesant(int k){
    interesant* new_interesant = (interesant*) malloc(sizeof(interesant));    
    new_interesant->numerek = numerki++;
    new_interesant->przed = kolejki[k]->przed;
    new_interesant->po = kolejki[k];

    if(kolejki[k]->przed->po == kolejki[k])
        kolejki[k]->przed->po = new_interesant;
    else
        kolejki[k]->przed->przed = new_interesant;
    kolejki[k]->przed = new_interesant;
    return new_interesant;
}

int numerek(interesant *i){
    return i->numerek;
}

interesant *obsluz(int k){
    if(kolejki[k]->po == kolejki[k]->przed)
        return NULL;
    interesant* obsluzony = kolejki[k]->po;
    interesant* nast = nastepny(obsluzony, kolejki[k]);
    if(nast->po != obsluzony)
        nast->przed = kolejki[k];
    else
        nast->po = kolejki[k];
    kolejki[k]->po = nast;
    return obsluzony;
}

void zmiana_okienka(interesant *i, int k){
    interesant* poprzedni = i->przed;
    interesant* nastepny = i->po;

    if(nastepny->przed == i)
        nastepny->przed = poprzedni;
    else
        nastepny->po = poprzedni;

    if(poprzedni->po == i)
        nastepny->po = poprzedni;
    else
        nastepny->przed = poprzedni;

    if(kolejki[k]->przed->po == kolejki[k])
        kolejki[k]->przed->po = i;
    else
        kolejki[k]->przed->przed = i;
    kolejki[k]->przed = i;
}

void zamkniecie_okienka(int k1, int k2){
    if(kolejki[k2]->przed->po == kolejki[k2])
        kolejki[k2]->przed->po = kolejki[k1]->po;
    else
        kolejki[k2]->przed->przed = kolejki[k1]->po;

    kolejki[k2]->przed = kolejki[k1]->przed;
    kolejki[k1]->przed = kolejki[k1];
    kolejki[k1]->po = kolejki[k1];
}

// -------------------------------------------------
std::vector<interesant *> fast_track(interesant *i1, interesant *i2){
    interesant* lewy1 = i1->przed;
    interesant* lewy2 = i1;
    interesant* prawy1 = i1->po;
    interesant* prawy2 = i1;
    std::vector<interesant*> obsluzeni;
    obsluzeni.push_back(i1);

    while(lewy1 != i2 && prawy1 != i2){
        interesant* temp = lewy1;
        lewy1 = nastepny(lewy2, lewy1);
        lewy2 = temp;

        temp = prawy1;
        prawy1 = nastepny(prawy1, prawy2);
        prawy2 = temp;
    }
    if(lewy1 == i2){
        lewy2 = i1;
        lewy1 = i1->przed;
        while(lewy1 != i2){
            interesant* temp = lewy1;
            lewy1 = nastepny(lewy2, lewy1);
            lewy2 = temp;
            obsluzeni.push_back(lewy2);
        }
    }else{
        prawy1 = i1->po;
        prawy2 = i1;
        while(prawy1 != i2){
            interesant* temp = prawy1;
            prawy1 = nastepny(prawy1, prawy2);
            prawy2 = temp;
            obsluzeni.push_back(prawy2);
        }
    }
    obsluzeni.push_back(i2);
    return obsluzeni;
}

void naczelnik(int k){
    interesant* temp = kolejki[k]->po;
    kolejki[k]->po = kolejki[k]->przed;
    kolejki[k]->przed = temp;
}

std::vector<interesant *> zamkniecie_urzedu(){
    std::vector<interesant*> obsluzeni;
    long long n = kolejki.size();
    for(int i = 0; i < n; i++)
        while(kolejki[i]->po != kolejki[i]->przed)
            obsluzeni.push_back(obsluz(i));
    kolejki.clear();
    return obsluzeni;
}