#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "kol.h"

// struktura urzędu, musimy globalizować 
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
    interesant* new_interesant = new interesant;
    new_interesant->numerek = numerki++;
    new_interesant->kolejka = k;
    urzad.kolejki[k].push_back(new_interesant);
    return new_interesant;
}

int numerek(interesant *i){
    return i->numerek;
}

interesant *obsluz(int k){
    // jeśli pusta to NULL
    if(urzad.kolejki[k].empty())
        return NULL;
    // jeśli nie to obsługujemy
    interesant* obsluzony = urzad.kolejki[k].front();
    urzad.kolejki[k].pop_front();
    return obsluzony;
}

void zmiana_okienka(interesant *i, int k){
    // wyrzucamy iteresanta z kolejki
    urzad.kolejki[i->kolejka].erase(std::remove(
                                        urzad.kolejki[i->kolejka].begin(), 
                                        urzad.kolejki[i->kolejka].end(), i),
                                    urzad.kolejki[i->kolejka].end());
    // dorzucamy do nowej
    urzad.kolejki[k].push_back(i);
    i->kolejka = k;             
}

void zamkniecie_okienka(int k1, int k2){
    // doklejamy kolejke k1 do k2
    urzad.kolejki[k2].insert(urzad.kolejki[k2].end(), 
                             urzad.kolejki[k1].begin(), 
                             urzad.kolejki[k1].end());
    // i czyścimy k1
    urzad.kolejki[k1].clear();
}


std::vector<interesant *> fast_track(interesant *i1, interesant *i2){
    std::vector<interesant*> obsluzeni;
    // wyszukujemy i1 i i2
    auto indexI1 = std::find(urzad.kolejki[i1->kolejka].begin(), 
                             urzad.kolejki[i1->kolejka].end(), i1);
    auto indexI2 = std::find(urzad.kolejki[i1->kolejka].begin(), 
                             urzad.kolejki[i1->kolejka].end(), i2);
    // obsługujemy interesantów z przedziału i1 - i2
    for(auto obsluzony = indexI1; obsluzony <= indexI2; obsluzony++)
        obsluzeni.push_back(*obsluzony);
    urzad.kolejki[i1->kolejka].erase(indexI1, indexI2 + 1);
    return obsluzeni;
}


void naczelnik(int k){
    std::reverse(urzad.kolejki[k].begin(),urzad.kolejki[k].end());
}


std::vector<interesant *> zamkniecie_urzedu(){
    // obsługujemy pozostałych interesantów
    std::vector<interesant*> obsluzeni;
    for(auto kolejka : urzad.kolejki)
        for(auto obsluzony : kolejka)
            obsluzeni.push_back(obsluzony);
    // czyścimy wektor
    urzad.kolejki.clear();
    return obsluzeni;
}