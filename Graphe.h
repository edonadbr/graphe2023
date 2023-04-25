#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include "Sommet.h"

//#include "Arc.h"


class Graphe {
public:
    Graphe();
    Graphe(vector<vector<int>>matrice, bool est_oriente, bool avec_Poids);
    Graphe(std::vector<int> aps, std::vector<int> fs, bool est_oriente);
    Graphe(bool est_oriente, bool avec_Poids);
    void ajouterSommet(Sommet s);
    int Numero_Sommet(Sommet* s);
    void ajouterArc(Sommet* s, Sommet *t, int val);
    void ajouterSommet(Sommet* s);
    void supprimerSommet(Sommet* s);
    bool existeArc(Sommet* s, Sommet* t);
    void enleverArc(Sommet* s, Sommet* t);
    void Matrice_to_fs_aps();
    void fs_apsToMatrice();
    int nombre_successeur(Sommet* s);
    int nombre_arcs_fs();
    int nombre_sommets_aps();
    int nombre_sommets_matrice();
    int nombre_arcs_matrice();

    bool isAvecPoids()const;
    bool isOriente()const;
    int getFsElem(int i)const;
    int getApsElem(int i)const;
    int getMatriceElem(int i,int j)const;
    int getCout(int i,int j)const;
    Sommet* getListeSommetElem(int i)const;
    vector<int> getFs()const;
    vector<int> getAps()const;
    vector<vector<int>> getMatCout()const;

    // Modificateurs
    void setFsElem(int i, int val);
    void setApsElem(int i, int val);
    void setMatriceElem(int i, int j, int val);
    void setCoutElem(int i, int j, int val);

    void affiche_successeur(int indiceS);
    void afficher_matrice();
    void afficher_fs_aps();
    void afficher_cout();
    string toString();

    void sauvgarde();
    void menu_algorithme();

    void actions(vector<Sommet*>& liste);
private:
    std::vector<std::vector<int>> d_matrice;
    std::vector<std::vector<int>> d_matrice_cout;
    std::vector<Sommet*> d_listeSommet;
    std::vector<int> d_fs;
    std::vector<int> d_aps;
    bool d_avec_Poids;
    bool d_est_oriente;
    int d_valeur_interdite = 999;

    void Generer_matrice(int n, bool avec_Poids);
    void Generer_Matrice_Cout(int n);
    void genere_fsAps(int n);
    void MiseAJourAjoutMatriceCout();
    void MiseAJourSuppMatriceCout(int indiceS);
    int miseAJourArc();
};

#endif // GRAPHE_H
