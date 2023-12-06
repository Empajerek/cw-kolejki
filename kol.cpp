#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "kol.h"

// inicjujemy urząd w postaci wektora
std::vector<interesant*> kolejki;
int numerki = 0;

void otwarcie_urzedu(int m){
    for(int i = 0; i < m; i++){
        interesant* new_interesant = (interesant*) malloc(sizeof(interesant));
        new_interesant->przed = new_interesant;
        new_interesant->po = new_interesant;
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
    kolejki[k]->przed->po = new_interesant;
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
    kolejki[k]->po = obsluzony->po;
    kolejki[k]->po->przed = kolejki[k];
    return obsluzony;
}

void zmiana_okienka(interesant *i, int k){
    i->przed->po = i->po;
    i->po->przed = i->przed;
    kolejki[k]->przed->po = i;
    kolejki[k]->przed = i;
}

void zamkniecie_okienka(int k1, int k2){
    kolejki[k2]->przed->po = kolejki[k1]->po;
    kolejki[k2]->przed = kolejki[k1]->przed;
    kolejki[k1]->przed = kolejki[k1];
    kolejki[k1]->po = kolejki[k1];
}

std::vector<interesant *> fast_track(interesant *i1, interesant *i2){
    std::vector<interesant*> obsluzeni;
    interesant* temp = i1->przed;
    while(i1->przed != i2){
        obsluzeni.push_back(i1);
        i1 = i1->po;
    }
    i1->przed = temp;
    temp->po = i2;
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