#include <vector>
#include "Sommet.h"



int Sommet::d_compteur = 0;

Sommet::Sommet(string contenu, Point* position, int marquee) : d_contenu(contenu), d_position(position),
    d_marquee(marquee), d_id(d_compteur){
   // this->d_contenu = contenu;
   // this->d_position = position;
    //this->d_marquee = marquee;
    d_compteur++;
    //this->d_id = d_compteur;
}

Sommet::Sommet(string contenu, int marquee): d_contenu(contenu), d_position(nullptr), d_marquee(marquee),  d_id(d_compteur) {
   // this->d_contenu = contenu;
    //this->d_position = nullptr;
    //this->d_marquee = marquee;
    d_compteur++;
    //this->d_id = d_compteur;
}

Sommet::Sommet() : d_contenu(""), d_position(nullptr), d_marquee(0), d_id(d_compteur){
    //this->d_contenu = "";
    //this->d_position = nullptr;
    //this->d_marquee = 0;
    d_compteur++;
    //this->d_id = d_compteur;
}

Point* Sommet::getPosition() {
    return d_position;
}

string Sommet::getContenu() {
    return d_contenu;
}

int Sommet::getMarquee() {
    return d_marquee;
}

int Sommet::getId() {
    return d_id;
}

Sommet* Sommet::getSommet() {
    return this;
}

void Sommet::setContenu(string contenu) {
    d_contenu = contenu;
}

void Sommet::ChangePosition(Point* position) {
    d_position = position;
}

void Sommet::setMarquee(int marquee) {
    d_marquee = marquee;
}

bool Sommet::operator==(Sommet &s) {
    return (s.getContenu() == this->d_contenu);
}

string Sommet::toString() {
    if(d_position == nullptr)
        return d_contenu;
    else
        return d_contenu + " ( " + to_string(d_position->getX()) + "," + to_string(d_position->getY()) + ")";
}