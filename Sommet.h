//
// Created by Edona Dibra on 19/04/2023.
//

#ifndef GRAPHE2023_SOMMET_H
#define GRAPHE2023_SOMMET_H



#ifndef SOMMET_H
#define SOMMET_H

#include<iostream>
#include"Point.h"

using namespace std;

class Sommet {
private:
    string d_contenu;
    Point* d_position;
    int d_marquee;
    int d_id;
    static int d_compteur;

public:
    Sommet(string contenu, Point* position, int marquee);

    Sommet(string contenu, int marquee);

    Sommet();

    Point* getPosition();

    string getContenu();

    int getMarquee();

    int getId();

    Sommet* getSommet();

    void setContenu(string contenu);

    void ChangePosition(Point* position);

    void setMarquee(int marquee);

    bool operator==(Sommet &s);

    string toString();


};

#endif /* SOMMET_H */




#endif //GRAPHE2023_SOMMET_H
