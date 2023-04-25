#include "Graphe.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Algorithme.h"

using namespace std;

Graphe::Graphe() {
    // Initialisation des attributs de l'objet Graphe
    d_est_oriente = false;
    d_avec_Poids = false;
    d_matrice[0][0]=0;
    d_matrice_cout [0][0]= 0;
    d_listeSommet [0]= nullptr;
}
Graphe::Graphe(std::vector<std::vector<int>> matrice, bool est_oriente, bool avec_Poids): d_matrice(matrice),
d_est_oriente(est_oriente), d_avec_Poids(avec_Poids) {
    int ligne = matrice.size();
    int colonne = matrice[0].size();
    this->d_matrice.resize(ligne, std::vector<int>(colonne));
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            this->d_matrice[i][j] = matrice[i][j];
        }
    }
    d_listeSommet.push_back(nullptr);
}

// Constructeur prenant des vecteurs d_aps et d_fs ainsi qu'un booléen d_est_oriente
Graphe::Graphe(std::vector<int> aps, std::vector<int> fs, bool est_oriente): d_aps(aps), d_fs(fs), d_est_oriente(est_oriente),
d_avec_Poids(false){
    int tailleFs = fs.size();
    int tailleAps = aps.size();

    this->d_aps.reserve(tailleAps);
    this->d_fs.reserve(tailleFs);

    for(int i=0; i<tailleFs; i++){
        this->d_fs.push_back(fs[i]);
    }

    for(int i=0; i<tailleAps; i++){
        this->d_aps.push_back(aps[i]);
    }

    this->d_listeSommet.push_back(nullptr);

    fs_apsToMatrice();
}

// Constructeur prenant deux booléens d_est_oriente et avec_poids
Graphe::Graphe(bool est_oriente, bool avec_poids) : d_est_oriente(est_oriente), d_avec_Poids(avec_poids){
    Generer_matrice(0, d_avec_Poids);
    Matrice_to_fs_aps();
}

//------- Methodes de la d_matrice  ---------------------------

void Graphe::Generer_matrice(int n, bool avec_Poids) {
    int taille_matrice = n + 2;
    d_matrice.resize(taille_matrice, vector<int>(taille_matrice));

    d_matrice[0][0] = n;

    int val = 0;
    if (n > 0)
        d_matrice[0][1] = 0;

    for (int i = 2; i < taille_matrice; i++)
        d_matrice[0][i] = val;
    for (int i = 1; i < taille_matrice; i++)
        d_matrice[i][0] = val;

    for (int i = 1; i < taille_matrice; i++) {
        for (int j = 1; j < taille_matrice; j++) {
            d_matrice[i][j] = val;
        }
    }
    if (avec_Poids == true)
        Generer_Matrice_Cout(n);
}

void Graphe::Generer_Matrice_Cout(int n) {
    int taille_matrice = n + 2;

    d_matrice_cout.resize(taille_matrice, vector<int>(taille_matrice));

    d_matrice_cout[0][0] = n;

    if (n > 0) {
        d_matrice_cout[0][1] = 0;
    }

    for (int i = 2; i < taille_matrice; i++) {
        d_matrice_cout[0][i] = d_valeur_interdite;
    }

    for (int i = 1; i < taille_matrice; i++) {
        for (int j = 0; j < taille_matrice; j++) {
            d_matrice_cout[i][j] = d_valeur_interdite;
        }
    }
}

void Graphe::genere_fsAps(int n) {
    int tailleFs = n + 1;
    int tailleAps = n + 1;
    d_fs.resize(tailleFs);
    d_aps.resize(tailleAps);

    d_fs[0] = n;
    d_aps[0] = n;

    int val = 0;
    for (int i = 1; i < tailleFs; i++) {
        d_fs[i] = val;
    }

    for (int i = 1; i < tailleAps; i++) {
        d_aps[i] = val;
    }
}

int Graphe::Numero_Sommet(Sommet* s) {
    for (int i = 0; i < d_listeSommet.size(); i++) {
        if (d_listeSommet[i] == s) {
            return i+1;
        }
    }
    return -1;
}

void Graphe::ajouterArc(Sommet* s, Sommet* t, int val) {
    int indiceS = Numero_Sommet(s);
    int indiceT = Numero_Sommet(t);
    if (indiceS == -1 || indiceT == -1) {
        return;
    }

    d_matrice[0][1]++;
    d_matrice[indiceS][indiceT] = 1;

    if (d_est_oriente == false) {
        d_matrice[indiceT][indiceS] = 1;
        d_matrice[0][1]++;
    }

    if (d_avec_Poids) {
        d_matrice_cout[indiceS][indiceT] = val;
        d_matrice_cout[0][1] = d_matrice[0][1];
        if (d_est_oriente == false) {
            d_matrice_cout[indiceT][indiceS] = val;
        }
    }
    Matrice_to_fs_aps();
}

void Graphe::ajouterSommet(Sommet* s) {
    int taille = nombre_sommets_matrice() + 1;
    taille++;
    d_listeSommet.push_back(s);

    vector<vector<int>> N_matrice(taille, vector<int>(taille));
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - 1; j++) {
            N_matrice[i][j] = d_matrice[i][j];
        }
    }
    N_matrice[0][0]++;
    d_matrice = N_matrice;

    if (d_avec_Poids) {
        MiseAJourAjoutMatriceCout();
    }

    Matrice_to_fs_aps();
}

void Graphe::supprimerSommet(Sommet* s) {
    int indiceS = Numero_Sommet(s);
    vector<vector<int>> mat(d_matrice.size() - 1, vector<int>(d_matrice[0].size() - 1, 0));

    if (indiceS == -1) {
        return;
    }

    MiseAJourSuppMatriceCout(indiceS);
    d_listeSommet.erase(d_listeSommet.begin() + indiceS - 1);

    for (int i = 0; i < indiceS; ++i) {
        for (int j = 0; j < indiceS; ++j) {
            mat[i][j] = d_matrice[i][j];
        }
        for (int j = indiceS + 1; j < d_matrice.size(); ++j) {
            mat[i][j - 1] = d_matrice[i][j];
        }
    }
    for (int i = indiceS + 1; i < d_matrice.size(); ++i) {
        for (int j = 0; j < indiceS; ++j) {
            mat[i - 1][j] = d_matrice[i][j];
        }
        for (int j = indiceS + 1; j < d_matrice.size(); ++j) {
            mat[i - 1][j - 1] = d_matrice[i][j];
        }
    }
    mat[0][0]--;
    d_matrice = mat;
    d_matrice[0][1] = miseAJourArc();
    d_matrice_cout[0][1] = d_matrice[0][1];

    Matrice_to_fs_aps();
}

bool Graphe::existeArc(Sommet* s, Sommet* t) {
    int indiceS = Numero_Sommet(s);
    int indiceT = Numero_Sommet(t);

    if (indiceS == -1 || indiceT == -1) {
        return false;
    }

    if (d_avec_Poids) {
        return (d_matrice[indiceS][indiceT] != d_valeur_interdite);
    } else {
        return (d_matrice[indiceS][indiceT] != 0);
    }
}

void Graphe::enleverArc(Sommet* s, Sommet* t){
    int indiceS = Numero_Sommet(s) ;
    int indiceT = Numero_Sommet(t) ;

    if( indiceS== -1  ||  indiceT == -1  )
    {
        return  ;
    }
    else
    {
        d_matrice[0][1]-- ;
        d_matrice[indiceS][indiceT] = 0   ;
        if (d_avec_Poids)
            d_matrice_cout[indiceS][indiceT] = d_valeur_interdite   ;

        d_matrice_cout[0][1]-- ;
    }
    Matrice_to_fs_aps();
}

//---------------methodes FS APS d_matrice------------------------------

void Graphe::Matrice_to_fs_aps() {
    int n = nombre_sommets_matrice();
    int m = nombre_arcs_matrice();

    d_fs.clear();
    d_aps.clear();

    if (n > 0) {
        d_aps.push_back(n);
        d_fs.push_back(n + m);

        int k = 1;

        for (int i = 1; i <= n; i++) {
            d_aps.push_back(k);

            for (int j = 1; j <= n; j++) {
                if (d_matrice[i][j] != 0) {
                    d_fs.push_back(j);
                    k++;
                }
            }

            d_fs.push_back(0);
            k++;
        }
    }
}

void Graphe::fs_apsToMatrice() {
    int n = nombre_sommets_aps();
    d_matrice = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
    d_matrice[0][0] = n;
    d_matrice[0][1] = nombre_arcs_fs();

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            d_matrice[i][j] = 0;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int k = d_aps[i]; d_fs[k] != 0; k++) {
            d_matrice[i][d_fs[k]] = 1;
        }
    }
}

//------------------------------Getters-----------------------------------------
bool Graphe::isAvecPoids() const{
    return d_avec_Poids;
}

bool Graphe::isOriente() const{
    return d_est_oriente;
}

int Graphe::getFsElem(int i)const {
    return d_fs[i];
}

int Graphe::getApsElem(int i) const{
    return d_aps[i];
}

int Graphe::getMatriceElem(int i,int j)const {
    return d_matrice[i][j];
}

int Graphe::getCout(int i,int j) const{
    return d_matrice_cout[i][j];
}

Sommet* Graphe::getListeSommetElem(int i) const{
    return d_listeSommet[i];
}

vector<int> Graphe::getFs() const{
    return d_fs;
}

vector<int> Graphe::getAps() const {
    return d_aps;
}

vector<vector<int>> Graphe::getMatCout() const{
    return d_matrice_cout;
}

int Graphe::nombre_successeur(Sommet* s) {
    int indiceS = Numero_Sommet(s);
    int co = 0;
    int i = d_aps[indiceS];
    while (i < d_fs.size() && d_fs[i] != 0) {
        i++;
        co++;
    }
    return co;
}

int Graphe::miseAJourArc() {
    int co = 0;
    for (int i = 0; i < d_matrice.size(); i++) {
        for (int j = 0; j < d_matrice[0].size(); j++) {
            if (d_matrice[i][j] == 1) {
                co++;
            }
        }
    }
    return co;
}

int Graphe::nombre_sommets_aps(){
    return getApsElem(0);
}

int Graphe::nombre_arcs_fs(){
    return getFsElem(0)-nombre_sommets_aps();
}

int Graphe::nombre_arcs_matrice(){
    return d_matrice[0][1];
}

int Graphe::nombre_sommets_matrice() {
    return d_matrice[0][0];
}

//------------------------------------Setters ---------------------------------

void Graphe::setFsElem(int i, int val ) {
    d_fs[i] = val;
}

void Graphe::setApsElem(int i, int val) {
    d_aps[i] = val;
}

void Graphe::setMatriceElem(int i, int j, int val ) {
    d_matrice[i][j] = val;
}

void Graphe::setCoutElem(int i, int j, int val) {
    d_matrice_cout[i][j] = val;
}

//----------------------------  Methodes affichage  ---------------------------

void Graphe::affiche_successeur(int indiceS)
{
    std::cout << "successeur de " << indiceS << "|";
    int i = getApsElem(indiceS);
    while ((i < getFsElem(0)) && (getFsElem(i) != 0))
    {
        std::cout << getFsElem(i) << "|";
        i++;
    }
    std::cout << std::endl;
}

void Graphe::afficher_matrice()
{
    if (isOriente())
        std::cout << "votre graphe est d_oriente \n";
    std::cout << toString() << std::endl;
}


void Graphe::afficher_fs_aps() {
    std::string str = "-------------------- d_fs & d_aps ------------------- \n";

    str += "FS : |";
    for(int i = 1; i < d_fs.size(); i++){
        str += std::to_string(d_fs[i]) + "|";
    }

    str += "\nAPS : |";

    for(int i = 1; i < d_aps.size(); i++){
        str += std::to_string(d_aps[i]) + "|";
    }
    std::cout << str << std::endl;
}

void Graphe::afficher_cout()
{
    std::cout << " cout  \n ";

    std::string Smatrice = "-------------------d_matrice --------------------- \n " ;

    for(int i = 0 ; i < d_matrice_cout.size() ; i++ ) {
        Smatrice += "| " ;
        for(int j = 0 ; j < d_matrice_cout[i].size() ; j++)
        {
            Smatrice += std::to_string(d_matrice_cout[i][j]) + "\t" ;
        }
        Smatrice += "|\n " ;
    }
    std::cout << Smatrice << std::endl;
}

string Graphe::toString(){
    string Total = "Grphe ";
    if(d_est_oriente)
        Total += "Oriente";

    else
        Total += "Non Oriente";
    if(d_avec_Poids)
        Total += " Contient des d_poids";
    string str = "--------d_fs & d_aps ---------- \n";
    str += "FS : |";
    for(int i = 1; i < d_fs.size(); i++){
        str += to_string(d_fs[i]) + "|";
    }
    str += "\nAPS : |";
    for(int i = 1; i < d_aps.size(); i++){
        str += to_string(d_aps[i]) + "|";
    }
    string Smatrice = "--------d_matrice ---------- \n ";

    for(int i = 0; i < d_matrice.size(); i++){
        Smatrice += "|";
        for(int j = 0; j < d_matrice[i].size(); j++){
            Smatrice += "\t" + to_string(d_matrice[i][j]);
        }
        Smatrice += "|\n";
    }
    string ListeSommets = "\n ------Liste des sommets------ \n ";
    for(int i = 1; i < d_listeSommet.size(); i++){
        ListeSommets += d_listeSommet[i]->toString() + "|";
    }
    return Total + "\n " + str + Smatrice + ListeSommets;
}

// --------------------------- Methode cout -----------------------------

void Graphe::MiseAJourAjoutMatriceCout() {
    int taille = nombre_sommets_matrice();
    taille++;
    vector<vector<int>> N_matrice(taille, vector<int>(taille, d_valeur_interdite));

    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - 1; j++) {
            N_matrice[i][j] = d_matrice_cout[i][j];
        }
    }

    int indice = Numero_Sommet(d_listeSommet.back());

    for (int j = 0; j < taille; j++) {
        N_matrice[indice][j] = d_valeur_interdite;
        N_matrice[j][indice] = d_valeur_interdite;
    }

    if (indice > 0)
        N_matrice[0][1] = d_matrice_cout[0][1];

    N_matrice[0][0]++;
    d_matrice_cout = N_matrice;
}

void Graphe::MiseAJourSuppMatriceCout(int indiceS) {
    if (indiceS == -1) {
        return;
    }

    std::vector<std::vector<int>> mat(d_matrice_cout.size() - 1, std::vector<int>(d_matrice_cout[0].size() - 1));

    for (int i = 0; i < indiceS; ++i) {
        for (int j = 0; j < indiceS; ++j) {
            mat[i][j] = d_matrice_cout[i][j];
        }
        for (int j = indiceS + 1; j < d_matrice_cout.size(); ++j) {
            mat[i][j - 1] = d_matrice_cout[i][j];
        }
    }
    for (int i = indiceS + 1; i < d_matrice_cout.size(); ++i) {
        for (int j = 0; j < indiceS; ++j) {
            mat[i - 1][j] = d_matrice_cout[i][j];
        }
        for (int j = indiceS + 1; j < d_matrice_cout.size(); ++j) {
            mat[i - 1][j - 1] = d_matrice_cout[i][j];
        }
    }
    mat[0][0]--;
    d_matrice_cout = mat;
}

//--------------------------sauvgarde/charger-----------------------------

void Graphe::sauvgarde() {
    ofstream file("writerFile.txt");
    if(file.is_open()) {
        file << toString();
        file.close();
    } else {
        cout << "Unable to locate the fileName." << endl;
    }
}

void Graphe::menu_algorithme()
{
    int option = 0;
    do {
        cout << " Choisissez un algorithme a appliquer ? " << endl;

        cout << "1. Dantzig  " << endl;
        cout << "2. Dikjstra  " << endl;
        cout << "3. Kruskal   " << endl;
        cout << "4. Ordonnancement   " << endl;
        cout << "5. Prufer codage /decodage   " << endl;
        cout << "6. Rang  " << endl;
        cout << "7. Tarjan  " << endl;
        cout << "8. Demi degre interieur  " << endl;
        cout << "9. Demi degre exterieur  " << endl;
        cout << "10. Calcul des distances " << endl;
        cout << "11. Sortir " << endl;

        cout << "-----------------------------------------------------------------------" << endl;

        cout << "VEUILLEZ ENTREZ VOTRE CHOIX: ";
        cin >> option;
        cout << "-----------------------------------------------------------------------" << endl;

        switch (option) {
            case 1: {

                //Dantzig

                if(!d_avec_Poids && !d_est_oriente)
                {
                    cout << "votre graphe n'est pas compatible avec cet algorithme!" << endl;
                }
                else {
                    Algorithme aDantzig;
                    aDantzig.Dantzig(getMatCout());
                }
                break ;
            }
            case 2:
            {
                //dikjstra

                if(!d_avec_Poids && !d_est_oriente)
                {
                    cout << "votre graphe n'est pas compatible avec cet algorithme!" << endl;
                }
                else {

                    afficher_matrice();
                    afficher_cout();
                    afficher_fs_aps();
                    Algorithme A_Dikjstra;
                    int n = getApsElem(0) ;
                    int m = getFsElem(0)-n  ;
                    vector<int> predecesseur(n+2) ;
                    vector<int> distance(n+2) ;
                    A_Dikjstra.Dijkstra(1,this,predecesseur,distance) ;

                    //DessinGraphe dessinGraphe(this) ;
                    //Djikstra djikstra(this) ;
                }
                break;
            }

            case 3:
            {
                //KRUSKAL
              //  Algorithme algo;
              //  algo.Kruskal(*this);
              //  cout << "L'algorithme de Kruskal a été exécuté avec succès." << endl;
              //  cout << "Voici l'arbre couvrant construit :" << endl;

                break;
            }

            case 4 :
            {
                //Ordonnancement
                break;
            }

            case 5 :
            {
                //Prufer
                if(d_est_oriente == true)
                {
                    cout << "votre graphe n'est pas compatible avec cet algorithme! " << endl;
                }
                else
                {
                    Algorithme aprufer;
                }
                break;
            }
            case 6:

            {
                //Rang
                if(d_est_oriente == false)
                {
                    cout << "votre graphe n'est pas compatible avec cet algorithme! " << endl;
                }
                else
                {
                    afficher_fs_aps();
                    Algorithme a;
                    vector<int> r = a.rang(getFs(), getAps());
                    string str;
                    str += "-----------Rang------------\n|";
                    for(int i : r){
                        str += to_string(i) + "|";
                    }
                    str += "\n";
                    cout << str;
                }
                break;
            }
            case 7:
            {
                //Tarjan
                cout << "desole cet algorithme ne fonctionne pas :(" << endl;
                break;
            }
            case 8:
            {
                //Demi degre interieur
                if(d_est_oriente == false)
                {
                    cout << "votre graphe n'est pas compatible avec cet algorithme! " << endl;
                }
                else
                {
                    afficher_fs_aps();

                    Algorithme addi;

                    vector<int> ddi = addi.demi_degre_interieur(getFs(), getAps());

                    string str1;
                    str1 += "-----------Demi Degre Interieur------------\n|";
                    for(int i : ddi){
                        str1 += to_string(i) + "|";
                    }
                    str1 += "\n";
                    cout << str1;
                }
                break;
            }
            case 9:
            {
                //Demi degre exterieur
                if(d_est_oriente == false)
                {
                    cout << "votre graphe n'est pas compatible avec cet algorithme! " << endl;
                }
                else
                {
                    afficher_fs_aps();

                    Algorithme adde;

                    vector<int> dde = adde.demi_degre_exterieur(getFs(), getAps());

                    string str2;
                    str2 += "-----------Demi Degre Exterieur-----------\n|";
                    for(int i : dde){
                        str2 += to_string(i) + "|";
                    }
                    str2 += "\n";

                    cout << str2;
                }
                break;
            }
            case 10:
            {
                //calcul des distances

                Algorithme aDistance;
                aDistance.calcul_distance(this);

                break;
            }
            case 11:{
                cout<<"Vous êtes sortie. ETAPE PRECEDENTE :"<<endl;
                break;
            }
            default: {
                cout << "Cette option n'existe pas" << endl;
                cout<<"Entrez quelque chose de valide :"<<endl;
                cin>>option;
            }
        }
    }while(option != 11);
}

void Graphe::actions(vector<Sommet*>& liste) {
    int option = 0;

    cout << "-----------------------------------------------------------------------" << endl;
    do {
        cout << " que voulez vous faire  ? " << endl;

        cout << "1. ajouter un sommet  " << endl;
        cout << "2. ajouter un arc  " << endl;
        cout << "3. supprimer un sommet    " << endl;
        cout << "4. supprimer un arc    " << endl;
        cout << "5. appliquer un algorithme   " << endl;
        cout << "6. affichage graphique  " << endl;
        cout << "7. sortir " << endl;
        cout << "-----------------------------------------------------------------------" << endl;

        cout << "VEUILLEZ ENTREZ VOTRE CHOIX: ";
        cin >> option;
        cout << "-----------------------------------------------------------------------" << endl;

        switch (option) {
            case 1: {
                //ajouter sommet
                string contenu = "";
                cout << "entrez le nom du sommet : ";
                cin >> contenu;
                cout << "veuiller saisir un point :";
                int x, y;
                cout << "d_x : ";
                cin >> x;
                cout << "d_y : ";
                cin >> y;
                Point p(x, y);
                Sommet* s = new Sommet (contenu,&p,1);
                liste.push_back(s);
                ajouterSommet(liste.back());
                afficher_matrice();
                break;
            }
            case 2: {
                //ajouter arc
                cout << "veuillez saisir le 1ere sommet( pas de sommets 0 )  : ";

                int i, j;
                cin >> i;
                cout << "veuillez saisir le 2eme sommet ( pas de sommets 0 ) : ";
                cin >> j;
                int p;
                if (d_avec_Poids == true) {
                    cout << "entrez le d_poids de votre nouvel arc : ";
                    cin >> p;
                    ajouterArc(liste[i - 1], liste[j - 1], p);
                } else
                    ajouterArc(liste[i - 1], liste[j - 1], 0);
                afficher_matrice();
                break;
            }
            case 3: {
                //supprimer sommet
                cout << "veuillez saisir le  sommet( pas de sommets 0 ) : ";
                int i;
                cin >> i;
                supprimerSommet(liste[i-1 ]); // a revoir si prb !!!
                liste.erase(liste.begin() + i -1);
                afficher_matrice();
                break;
            }
            case 4: {
                //supprimer arc
                cout << "veuillez saisir le 1ere sommet( pas de sommets 0 )  : ";
                int i, j;
                cin >> i;
                cout << "veuillez saisir le 2eme sommet ( pas de sommets 0 ) : ";
                cin >> j;
                enleverArc(liste[i - 1], liste[j - 1]);
                afficher_matrice();
                break;
            }
            case 5: {
                //algorithme

                menu_algorithme();
                break;
            }
            case 6: {
                //affichage graphique
                //new DessinGrape(this);
                break;
            }
            case 7:{
                cout<<"Vous êtes sortie, ETAPE PRECEDENTE :"<<endl;
                    break;
            }
            default: {
                    cout << "Cette option n'existe pas" << endl;
                    cout<<"Entrez quelque chose de valide :"<<endl;
                    cin>>option;
            }

                afficher_matrice();

        }
    }while (option != 7);

}

