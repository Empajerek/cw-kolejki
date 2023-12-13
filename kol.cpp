#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include "kol.h"

// inicjujemy urząd w postaci wektora
static std::vector<interesant*> kolejki;
static int numerki = 0;

/**
 * @brief Szuka nastepnego interesanta znająć poprzedniego
 * 
 * @param current aktualny interesant
 * @param previous poprzedni interesant
 * @return interesant* szukany interesant
 */
interesant* nastepny(interesant* current, interesant* previous){
    if(current->przed == previous)
        return current->po;
    return current->przed;
}

/**
 * @brief Usuwa interesanta z kolejki
 *
 * @param i usuwany iteresant
 */
static void wyjdz(interesant* i){
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
    i->po = nullptr;
    i->przed = nullptr;
}

/**
 * @brief Dodaje interesanta do kolejki
 * 
 * @param i dodawany interesant
 * @param k kolejka do której jest dodawany
 */
static void wejdz(interesant* i, int k){
    if(kolejki[k]->przed->po == kolejki[k])
        kolejki[k]->przed->po = i;
    else
        kolejki[k]->przed->przed = i;
    kolejki[k]->przed = i;
    i->po = kolejki[k];
    i->przed = kolejki[k]->przed;
}

void printUrzad(){
    printf("-------------------------------------------------------------------------------\n");
    for(int i = 0; i < (int)kolejki.size(); i++){
        interesant* ludzik = kolejki[i]->po;
        interesant* ludzikprzed = kolejki[i];
        printf("%d : ", i);
        while(ludzik != kolejki[i]){
            printf("%d ", ludzik->numerek);
            interesant* temp = ludzik;
            ludzik = nastepny(ludzik, ludzikprzed);
            ludzikprzed = temp;
        }
        printf("\n");
    }
}

void otwarcie_urzedu(int m){
    for(int i = 0; i < m; i++){
        interesant* new_interesant = (interesant*) malloc(sizeof(interesant));
        new_interesant->przed = new_interesant;
        new_interesant->po = new_interesant;
        new_interesant->numerek = -1;
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
    wejdz(new_interesant, k);
    printUrzad();
    return new_interesant;
}

int numerek(interesant *i){
    return i->numerek;
}

interesant *obsluz(int k){
    if(kolejki[k]->po == kolejki[k]->przed)
        return NULL;
    interesant* obsluzony = kolejki[k]->po;
    wyjdz(obsluzony);
    return obsluzony;
}

void zmiana_okienka(interesant *i, int k){
    wyjdz(i);
    wejdz(i, k);
}

void zamkniecie_okienka(int k1, int k2){
    if(kolejki[k2]->przed->po == kolejki[k2])
        kolejki[k2]->przed->po = kolejki[k1]->po;
    else
        kolejki[k2]->przed->przed = kolejki[k1]->po;

    if(kolejki[k1]->po->przed == kolejki[k1])
        kolejki[k1]->po->przed = kolejki[k2]->przed;
    else
        kolejki[k1]->po->po = kolejki[k2]->przed;

    kolejki[k2]->przed = kolejki[k1]->przed;
    kolejki[k1]->przed = kolejki[k1];
    kolejki[k1]->po = kolejki[k1];
}

std::vector<interesant *> fast_track(interesant *i1, interesant *i2){
    interesant* lewy1 = i1->przed;
    interesant* lewy2 = i1;
    interesant* prawy1 = i1->po;
    interesant* prawy2 = i1;
    std::vector<interesant*> obsluzeni_l;
    std::vector<interesant*> obsluzeni_p;

    obsluzeni_l.push_back(lewy2);
    obsluzeni_l.push_back(lewy1);
    obsluzeni_p.push_back(prawy2);
    obsluzeni_p.push_back(prawy1);

    while(lewy1 != i2 && prawy1 != i2){
        if(lewy1->numerek != -1){
            interesant* temp_l = lewy1;
            lewy1 = nastepny(lewy2, lewy1);
            lewy2 = temp_l;
            obsluzeni_l.push_back(lewy1);
        }
        if(prawy1->numerek != -1){
            interesant* temp_p = prawy1;
            prawy1 = nastepny(prawy1, prawy2);
            prawy2 = temp_p;
            obsluzeni_p.push_back(prawy1);
        }
    }
    if(obsluzeni_l.back() == i2)
        return obsluzeni_l;
    return obsluzeni_p;
}

void naczelnik(int k){
    interesant* temp = kolejki[k]->po;
    kolejki[k]->po = kolejki[k]->przed;
    kolejki[k]->przed = temp;
    printUrzad();
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