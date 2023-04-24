#include "Arc.h"
#include <iostream>
#include <sstream>
#include <string>

// Constructeurs
Arc::Arc(Sommet* s1, Sommet* s2, int poids, bool oriente)
        : d_poids(poids), d_s1(s1), d_s2(s2), d_oriente(oriente)
{
}

Arc::Arc(Sommet* s1, Sommet* s2, int poids)
        : Arc(s1, s2, poids, true)
{
}

Arc::Arc(Sommet* s1, Sommet* s2, bool oriente)
        : Arc(s1, s2, 0, oriente)
{
}

Arc::Arc(Sommet* s1, Sommet* s2)
        : Arc(s1, s2, 0, true)
{
}

// Getters
int Arc::getPoids() const
{
    return d_poids;
}

Sommet* Arc::getS1() const
{
    return d_s1;
}

Sommet* Arc::getS2() const
{
    return d_s2;
}

bool Arc::isOriente() const
{
    return d_oriente;
}

// Setters
void Arc::setPoids(int poids)
{
    d_poids = poids;
}

void Arc::setS1(Sommet* s1)
{
    d_s1 = s1;
}

void Arc::setS2(Sommet* s2)
{
    d_s2 = s2;
}

void Arc::setOriente(bool oriente)
{
    d_oriente = oriente;
}

// Opérateurs
bool Arc::operator==(const Arc& other) const
{
    return (d_s1 == other.d_s1 && d_s2 == other.d_s2 && d_poids == other.d_poids && d_oriente == other.d_oriente);
}

bool Arc::operator!=(const Arc& other) const
{
    return !(*this == other);
}

// Fonction d'affichage
std::string Arc::toString() const {
    std::stringstream ss;
    ss << "[" << d_s1->toString() << ", " << d_s2->toString() << "] : " << d_poids;
    if (d_oriente) {
        ss << ", d_oriente";
    } else {
        ss << ", non d_oriente";
    }
}
