
#ifndef GRAPHE2023_ALGORITHME_H
#define GRAPHE2023_ALGORITHME_H
#include <vector>
#include "Graphe.h"
//#include "Arc.h"


class Algorithme {

private:
    int MAXPOIDS = 100;
public:
    std::vector<int> demi_degre_interieur(std::vector<int> FS, std::vector<int> APS);
    std::vector<int> demi_degre_exterieur(std::vector<int> FS, std::vector<int> APS);
    std::vector<int> descente_largeur(int r, std::vector<int> fs, std::vector<int> aps);
    void calcul_distance(Graphe *g);
    void empiler(int x, std::vector<int>& pilch);
    vector<int> rang(vector<int> FS, vector<int> APS);
    void Prufer_decode(vector<int> t);
    void prufer_encode(vector<int>& prf, Graphe& G);
    /**
    * Applique l'algorithme de Dijkstra sur le graphe G à partir du sommet s
    * @param s Le sommet de départ
    * @param G Le graphe sur lequel appliquer l'algorithme
    * @param predecesseur La liste des prédécesseurs de chaque sommet
    * @param distance La liste des distances minimales entre le sommet de départ et chaque sommet du graphe
    */
    void Dijkstra(int s, Graphe *G, vector<int>& predecesseur, vector<int>& distance);

    void affiche_tab(std::vector<int> v);
    void affiche_tab_b(std::vector<bool> v);
    void Dantzig(vector<vector<int>> c);
    void traverse(int s, int p, int k, Graphe& g, vector<int>& num, vector<int>& ro, vector<bool>& entarj,
             vector<int>& tarj, vector<int>& pred, vector<int>& prem, vector<int>& pilch, vector<int>& cfc);

    void Tarjan(Graphe & g);
    void Kruskal(Graphe & G, vector<pair<int, pair<int, int>>>& arbreCouvrant) ;

    void graphe_reduit(vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& fs,
            vector<int>& aps, vector<int>& fsr, vector<int>& apsr);

    void base_Greduit(vector<int>& apsr, vector<int>& fsr, vector<int>& br);
    void edition_bases(vector<int>& prem, vector<int>& pilch, vector<int>& br);
    void ordonnancementt(vector<int>& fp, vector<int>& app, vector<int>& d, vector<int>& fpc, vector<int>& appc, vector<int>& lc);
    void fusionner(int i, int j, vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& nbElem);

    // Algorithme de Kruskal
   // void Kruskal(Graphe& g);
    //vector<pair<int, pair<int, int>>> trierAretes(Graphe& g);
    //int trouverComposante(vector<vector<int>>& foret_couvrante, int sommet);
    //bool cycle(vector<vector<int>>& foret_couvrante, int sommetA, int sommetB);


};




#endif //GRAPHE2023_ALGORITHME_H
