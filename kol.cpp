#include <iostream>
#include <vector>
#include "kol.h"

// inicjujemy urząd w postaci wektora
static std::vector<interesant*> kolejki;
static int numerki;

/**
 * @brief Szuka nastepnego interesanta znająć poprzedniego
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
 * @param i1 interesant przed sklejonym
 * @param i2 interesant doklejany przed
 * @param i3 interesant dokklejany za
 * @param i4 iteresant za sklejonymi
 */
static void sklej(interesant* i1, interesant* i2, 
                  interesant* i3, interesant* i4){
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
    if(kolejki[k]->po == kolejki[k]){
        kolejki[k]->po = i;
        kolejki[k]->przed = i;
        i->po = kolejki[k];
        i->przed = kolejki[k];
        return;
    }
    interesant* l2 = nastepny(kolejki[k]->przed, kolejki[k]);
    interesant* l1 = kolejki[k]->przed;
    kolejki[k]->przed = i;
    i->po = kolejki[k];
    sklej(l2, l1, i, kolejki[k]);
}

void printUrzad(){
    printf("-------------------------------------------------------------------------------\n");
    for(int i = 0; i < (int)kolejki.size(); i++){
        interesant* ludzik = kolejki[i]->po;
        interesant* ludzikprzed = kolejki[i];
        printf("%d : ", i);
        while(ludzik->numerek != kolejki[i]->numerek){
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
        numerki = 0;
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
    return new_interesant;
}

int numerek(interesant *i){
    return i->numerek;
}

interesant *obsluz(int k){
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
    if(kolejki[k2]->po == kolejki[k2])
        return;

    if(kolejki[k2]->po == kolejki[k2])
        kolejki[k2]->po = kolejki[k1]->po;
    else
        sklej(nastepny(kolejki[k2]->przed, kolejki[k2]), kolejki[k2]->przed, kolejki[k1]->po, nastepny(kolejki[k1]->po, kolejki[k2]));
    sklej(nastepny(kolejki[k1]->przed, kolejki[k1]), kolejki[k1]->przed, kolejki[k2], kolejki[k2]->po);
    kolejki[k2]->przed = kolejki[k1]->przed;
    kolejki[k1]->przed = kolejki[k1];
    kolejki[k1]->po = kolejki[k1];
}

std::vector<interesant *> fast_track(interesant *i1, interesant *i2){
    if(i1 == i2){
        wyjdz(i1);
        std::vector<interesant*> wyjscie = {i1};
        return wyjscie;
    }
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
    interesant* temp = kolejki[k]->po;
    kolejki[k]->po = kolejki[k]->przed;
    kolejki[k]->przed = temp;
}

std::vector<interesant *> zamkniecie_urzedu(){
    std::vector<interesant*> obsluzeni;
    long long n = kolejki.size();
    for(int i = 0; i < n; i++){
        while(kolejki[i]->po->numerek != -1){
            obsluzeni.push_back(obsluz(i)); 
        }
        free(kolejki[i]);
    }      
    kolejki.clear();
    return obsluzeni;
}