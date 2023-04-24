//
// Created by Edona Dibra on 20/04/2023.
//

#ifndef GRAPHE2023_ARC_H
#define GRAPHE2023_ARC_H

#ifndef ARC_H
#define ARC_H

#include "Sommet.h"
#include <string>

class Arc {
private:
    int d_poids;
    Sommet *d_s1;
    Sommet *d_s2;
    bool d_oriente;

public:
    // Constructeurs
    Arc(Sommet* s1, Sommet* s2, int poids, bool oriente);
    Arc(Sommet* s1, Sommet* s2, int poids);
    Arc(Sommet* s1, Sommet* s2, bool oriente);
    Arc(Sommet* s1, Sommet* s2);

    // Getters
    int getPoids() const;
    Sommet* getS1() const;
    Sommet* getS2() const;
    bool isOriente() const;

    // Setters
    void setPoids(int poids);
    void setS1(Sommet* s1);
    void setS2(Sommet* s2);
    void setOriente(bool oriente);

    // Opérateurs
    bool operator==(const Arc& other) const;
    bool operator!=(const Arc& other) const;

    // Fonction d'affichage
    std::string toString() const;
};

#endif // ARC_H



#endif //GRAPHE2023_ARC_H
