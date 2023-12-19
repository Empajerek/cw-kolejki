#include <iostream>
#include <vector>
#include "kol.h"

// inicjujemy urząd w postaci wektora i zmienną na numerki
static std::vector<interesant*> kolejki;
static int numerki;

// pare funkcji pomocniczych

/**
 * @brief Szuka nastepnego interesanta znając poprzedniego
 * 
 * @param current aktualny interesant
 * @param previous poprzedni interesant
 * @return interesant* szukany interesant
 */
static interesant* nastepny(interesant* current, interesant* previous){
    if(current->przed == previous)
        return current->po;
    return current->przed;
}

/**
 * @brief Skleja kolejke z pomocą czterech interesantów
 * 
 * Sklejamy intersanta i2 z i3, tak żeby powstał łańcuch: i1 -- i2 -- i3 -- i4
 * 
 * @param i1 interesant przed sklejonym
 * @param i2 interesant sklejany przed
 * @param i3 interesant sklejany za
 * @param i4 interesant za sklejonymi
 */
static void sklej(interesant* i1, interesant* i2, interesant* i3, interesant* i4){
    // kolejka zero-osobowa
    if(i2 == i3){
        i2->po = i2;
        i2->przed = i2;
        return;
    }
    // gdy sklejamy kolejke jednoosobową
    if(i2 == i4){
        i2->przed = i3;
        i2->po = i3;
        i3->przed = i2;
        i3->po = i2;
        return;
    }
    // pozostałe przypadki
    if(i2->przed == i1)
        i2->po = i3;
    else
        i2->przed = i3;

    if(i3->po == i4)
        i3->przed = i2;
    else
        i3->po = i2;
}

/**
 * @brief Usuwa interesanta z kolejki
 *
 * @param i usuwany interesant
 */
static void wyjdz(interesant* i){
    interesant* poprz = i->przed;
    interesant* nast = i->po;
    sklej(nastepny(poprz, i), poprz, nast, nastepny(nast, i));
}

/**
 * @brief Dodaje interesanta do kolejki
 * 
 * @param i dodawany interesant
 * @param k kolejka do której jest dodawany
 */
static void wejdz(interesant* i, int k){
    interesant* l2 = nastepny(kolejki[k]->przed, kolejki[k]);
    interesant* l1 = kolejki[k]->przed;
    kolejki[k]->przed = i;
    i->po = kolejki[k];
    sklej(l2, l1, i, kolejki[k]);
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

void otwarcie_urzedu(int m){
    // kolejki reprezentujemy jako interesantów o numerku -1, dla których "po" jest pierwszy interesant, a "przed" jest ostatnim
    for(int i = 0; i < m; i++){
        interesant* straznik = (interesant*) malloc(sizeof(interesant));
        straznik->przed = straznik;
        straznik->po = straznik;
        straznik->numerek = -1;
        kolejki.push_back(straznik);
    }
    numerki = 0;
}

interesant* nowy_interesant(int k){
    interesant* new_interesant = (interesant*) malloc(sizeof(interesant));
    new_interesant->numerek = numerki++;
    wejdz(new_interesant, k);
    return new_interesant;
}

int numerek(interesant *i){
    return i->numerek;
}

interesant* obsluz(int k){
    if(kolejki[k]->po == kolejki[k])
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
    // kolejka k1 nie ma elementów, można pominąć
    if(kolejki[k1]->po == kolejki[k1])
        return;
    // sklejamy najpierw koniec k2 z początkiem k1, a potem koniec k1, z początkiem k2
    sklej(nastepny(kolejki[k2]->przed, kolejki[k2]), kolejki[k2]->przed, kolejki[k1]->po, nastepny(kolejki[k1]->po, kolejki[k1]));
    sklej(nastepny(kolejki[k1]->przed, kolejki[k1]), kolejki[k1]->przed, kolejki[k2], kolejki[k2]->po);
    kolejki[k2]->przed = kolejki[k1]->przed;
    // zerujemy k1
    kolejki[k1]->przed = kolejki[k1];
    kolejki[k1]->po = kolejki[k1];
}

std::vector<interesant*> fast_track(interesant *i1, interesant *i2){
    // fast_track dla jednej osoby
    if(i1 == i2){
        wyjdz(i1);
        std::vector<interesant*> wyjscie = {i1};
        return wyjscie;
    }
    // IDEA: bierzemy lewo i prawo naszego i1, i idziemy w obydwu kierunkach aż znajdziemy i2
    interesant* lewy1 = i1;
    interesant* lewy2 = i1->przed;
    interesant* prawy1 = i1;
    interesant* prawy2 = i1->po;
    std::vector<interesant*> obsluzeni_l;
    std::vector<interesant*> obsluzeni_p;
    obsluzeni_l.push_back(lewy1);
    obsluzeni_p.push_back(prawy1);
    while(lewy1 != i2 && prawy1 != i2){
        // nie chcemy przejść przez początek kolejki
        if(lewy1->numerek != -1){
            interesant* temp_l = lewy1;
            lewy1 = nastepny(lewy1, lewy2);
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
    // wycinamy przedział, i zwracamy jego zawartość
    if(obsluzeni_l.back() == i2){
        interesant* l1 = nastepny(obsluzeni_l[0], obsluzeni_l[1]);
        interesant* l2 = nastepny(l1, obsluzeni_l[0]);
        interesant* p1 = nastepny(lewy1, lewy2);
        interesant* p2 = nastepny(p1, lewy1);
        sklej(l2, l1, p1, p2);
        return obsluzeni_l;
    }else{
        interesant* l1 = nastepny(obsluzeni_p[0], obsluzeni_p[1]);
        interesant* l2 = nastepny(l1, obsluzeni_p[0]);
        interesant* p1 = nastepny(prawy1, prawy2);
        interesant* p2 = nastepny(p1, prawy1);
        sklej(l2, l1, p1, p2);
        return obsluzeni_p;
    }
}

void naczelnik(int k){
    // przepinamy wskaźniki i to wystarczy
    interesant* temp = kolejki[k]->po;
    kolejki[k]->po = kolejki[k]->przed;
    kolejki[k]->przed = temp;
}

std::vector<interesant *> zamkniecie_urzedu(){
    std::vector<interesant*> obsluzeni;
    int n = (int) kolejki.size();
    for(int i = 0; i < n; i++){
        // obsuługujemy wszystkich pozostałych
        while(kolejki[i]->po->numerek != -1)
            obsluzeni.push_back(obsluz(i));
        free(kolejki[i]);
    }      
    kolejki.clear();
    kolejki.shrink_to_fit();
    return obsluzeni;
}