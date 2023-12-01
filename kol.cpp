#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "kol.h"

typedef struct{
    std::vector<std::deque<interesant*>> kolejki;
} urzad_t;

urzad_t urzad;
int numerki = 0;

void otwarcie_urzedu(int m){
    for(int i = 0; i < m; i++)
        urzad.kolejki.push_back(std::deque<interesant*>());
}

interesant *nowy_interesant(int k){
    interesant* new_interesant = (interesant*) malloc(sizeof(interesant));
    new_interesant->numerek = ++numerki;
    new_interesant->kolejka = k;
    urzad.kolejki[k].push_back(new_interesant);
    return new_interesant;
};

int numerek(interesant *i){
    return i->numerek;
}

interesant *obsluz(int k){
    if(urzad.kolejki[k].front() != nullptr){
        interesant* obsluzony = urzad.kolejki[k].front();
        urzad.kolejki[k].pop_front();
        return obsluzony;
    }
    return NULL;
}

void zmiana_okienka(interesant *i, int k){
    urzad.kolejki[i->kolejka].erase(std::remove(
                                        urzad.kolejki[i->kolejka].begin(), 
                                        urzad.kolejki[i->kolejka].end(), i
                                    ),
                                    urzad.kolejki[i->kolejka].end());
    urzad.kolejki[k].push_back(i);
    i->kolejka = k;             
}

void zamkniecie_okienka(int k1, int k2);


std::vector<interesant *> fast_track(interesant *i1, interesant *i2);


void naczelnik(int k);


std::vector<interesant *> zamkniecie_urzedu(){
    std::vector<interesant*> obsluzeni;
    for(auto kolejka : urzad.kolejki)
        for(interesant* obsluzony : kolejka)
            obsluzeni.push_back(obsluzony);

    urzad.kolejki.clear();
    delete &urzad;
}