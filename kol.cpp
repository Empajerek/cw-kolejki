#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "kol.h"

// inicjujemy urząd w postaci wektora kolejek
std::vector<std::deque<interesant*>> kolejki;
int numerki = 0;

void otwarcie_urzedu(int m){
    for(int i = 0; i < m; i++)
        kolejki.push_back(std::deque<interesant*>());
}

interesant *nowy_interesant(int k){
    interesant* new_interesant = new interesant;
    new_interesant->numerek = numerki++;
    new_interesant->kolejka = k;
    kolejki[k].push_back(new_interesant);
    return new_interesant;
}

int numerek(interesant *i){
    return i->numerek;
}

interesant *obsluz(int k){
    // jeśli pusta to NULL
    if(kolejki[k].empty())
        return NULL;
    // jeśli nie to obsługujemy
    interesant* obsluzony = kolejki[k].front();
    kolejki[k].pop_front();
    return obsluzony;
}

void zmiana_okienka(interesant *i, int k){
    // wyrzucamy iteresanta z kolejki
    kolejki[i->kolejka].erase(std::remove(kolejki[i->kolejka].begin(),
                                          kolejki[i->kolejka].end(), i),
                              kolejki[i->kolejka].end());
    // i dorzucamy do nowej
    kolejki[k].push_back(i);
    i->kolejka = k;             
}

void zamkniecie_okienka(int k1, int k2){
    // doklejamy kolejke k1 do k2
    kolejki[k2].insert(kolejki[k2].end(), 
                             kolejki[k1].begin(), 
                             kolejki[k1].end());
    // i czyścimy k1
    kolejki[k1].clear();
}


std::vector<interesant *> fast_track(interesant *i1, interesant *i2){
    std::vector<interesant*> obsluzeni;
    // wyszukujemy i1 i i2
    auto indexI1 = std::find(kolejki[i1->kolejka].begin(), 
                             kolejki[i1->kolejka].end(), i1);
    auto indexI2 = std::find(kolejki[i2->kolejka].begin(), 
                             kolejki[i2->kolejka].end(), i2);
    // i obsługujemy interesantów z przedziału i1 - i2
    for(auto obsluzony = indexI1; obsluzony <= indexI2; obsluzony++)
        obsluzeni.push_back(*obsluzony);
    kolejki[i1->kolejka].erase(indexI1, indexI2 + 1);
    return obsluzeni;
}


void naczelnik(int k){
    std::reverse(kolejki[k].begin(),kolejki[k].end());
}


std::vector<interesant *> zamkniecie_urzedu(){
    // obsługujemy pozostałych interesantów
    std::vector<interesant*> obsluzeni;
    for(auto kolejka : kolejki)
        for(auto obsluzony : kolejka)
            obsluzeni.push_back(obsluzony);
    // i czyścimy wektor
    kolejki.clear();
    return obsluzeni;
}