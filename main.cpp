#include <QApplication>
#include <QApplication>
#include "MyWindow.h"

#include <iostream>
#include <vector>
#include "Sommet.h"
#include "Point.h"
#include "Graphe.h"
#include "Algorithme.h"

using namespace std;

int main(int argc, char *argv[]) {

    vector<Sommet*> liste;

    bool avec_Poids = true;
    bool est_oriente = true;
    Point* p1 = new Point(100, 200);
    Point* p2 = new Point(400, 260);
    Point* p3 = new Point(100, 500);
    Point* p4 = new Point(500, 450);
    Point* p5 = new Point(100, 450);

    Sommet* s = new Sommet("S",p1 , 1);
    Sommet* t = new Sommet("T",p2 , 1);
    Sommet* w = new Sommet("P", p3, 1);
    Sommet* k = new Sommet("K",p4 , 1);
    Sommet* L = new Sommet("L",p5 , 1);

    int choix = 0;
    int option = 0;
    int affichage = 0;

    do {
        std::cout << "--------------------------------MENU---------------------------------------" << std::endl;

        std::cout << "1. cree un graphe " << std::endl;
        std::cout << "2. exemple d'algorithme  " << std::endl;
        std::cout << "3. application " << std::endl;
        std::cout << "4. sortir " << std::endl;

        std::cout << "---------------------------------------------------------------------------" << std::endl;

        std::cout << "VEUILLEZ ENTREZ VOTRE CHOIX: ";
        std::cin >> choix;

        std::cout << "-----------------------------------------------------------------------" << std::endl;

        switch (choix) {
            case 1: {
                do {
                    std::cout << "--------------------------------cree un graphe---------------------------------------"
                              << std::endl;

                    std::cout << "1. generer un graphe d_oriente avec 5 sommets" << std::endl;
                    std::cout << "2. generer un graphe non  d_oriente avec 5 sommets" << std::endl;
                    std::cout << "3. generer un graphe d_oriente sans d_poids" << std::endl;
                    std::cout << "4. generer un graphe non orieente sans d_poids" << std::endl;
                    std::cout << "5. generer un graphe d_oriente avec d_poids" << std::endl;
                    std::cout << "6. generer un graphe non d_oriente avec d_poids" << std::endl;
                    std::cout << "7. sortir" << std::endl;

                    std::cout << "---------------------------------------------------------------------------"
                              << std::endl;

                    std::cout << "VEUILLEZ ENTREZ VOTRE CHOIX: ";
                    std::cin >> choix;
                    switch (choix) {
                        case 1: {    //generer un graphe d_oriente avec 5 sommets
                            Graphe G(est_oriente, avec_Poids);

                            G.ajouterSommet(s);
                            G.ajouterSommet(t);
                            G.ajouterSommet(w);
                            G.ajouterSommet(k);

                            liste.push_back(s);
                            liste.push_back(t);
                            liste.push_back(w);
                            liste.push_back(k);

                            G.ajouterArc(s, t, 1);
                            G.ajouterArc(s, k, 2);
                            G.ajouterArc(t, k, 3);
                            G.ajouterArc(w, t, 5);
                            G.ajouterArc(w, w, 5);
                            G.ajouterArc(k,t, 5);
                            G.ajouterArc(k, k, 5);

                            std::cout << " quel type d'affichage voulez vous ? " << std::endl;
                            std::cout << "1. Console   " << std::endl;
                            std::cout << "2. Graphique  " << std::endl;

                            std::cout << "---------------------------------------------------------------------------"
                                      << std::endl;

                            std::cout << "VEUILLEZ ENTREZ VOTRE CHOIX: ";
                            std::cin >> affichage;
                            if (affichage == 1) {
                                G.afficher_fs_aps();
                                std::cout << "Save   " << std::endl;

                                G.sauvgarde();
                            } else {
                                //DessinGraphe dessin(G);
                            }
                            G.actions(liste);
                            break;
                        }
                        case 2: {
                            //generer un graphe non d_oriente avec 5 sommets
                            est_oriente = false;
                            Graphe NonG = Graphe(est_oriente, avec_Poids);

                            NonG.ajouterSommet(s);
                            NonG.ajouterSommet(t);
                            NonG.ajouterSommet(w);
                            NonG.ajouterSommet(k);

                            NonG.ajouterArc(s, t, 1);
                            NonG.ajouterArc(s, k, 2);
                            NonG.ajouterArc(t, k, 3);
                            NonG.ajouterArc(w, t, 5);
                            NonG.ajouterArc(w, w, 5);
                            NonG.ajouterArc(k, t, 5);
                            NonG.ajouterArc(k, k, 5);

                            std::cout << " quel type d'affichage voulez vous ? " << std::endl;
                            std::cout << "1. Console " << std::endl;
                            std::cout << "2. Graphique  " << std::endl;

                            std::cout << "---------------------------------------------------------------------------"
                                      << std::endl;

                            std::cout << "VEUILLEZ ENTREZ VOTRE CHOIX: ";
                            std::cin >> affichage;
                            if (affichage == 1) {
                                NonG.afficher_matrice();
                            } else {
                                //new DessinGraphe(NonG);
                            }
                            break;
                        }

                        case 3: {
                            //genere un graphe d_oriente sans d_poids

                            avec_Poids = false;
                            est_oriente = true;
                            Graphe GsP = Graphe(est_oriente, avec_Poids);

                            GsP.actions(liste);
                            break;
                        }
                        case 4: {
                            //genere un graphe non d_oriente sans d_poids

                            avec_Poids = false;
                            est_oriente = false;
                            Graphe Gnp = Graphe(est_oriente, avec_Poids);

                            Gnp.actions(liste);
                            break;
                        }

                        case 5: {
                            //genere un graphe d_oriente avec d_poids
                            avec_Poids = true;
                            est_oriente = true;
                            Graphe Gop = Graphe(est_oriente, avec_Poids);
                            Gop.actions(liste);
                            break;

                        }
                        case 6: {
                            //genere un graphe non d_oriente avec d_poids
                            avec_Poids = true;
                            est_oriente = false;
                            Graphe GnP = Graphe(est_oriente, avec_Poids);

                            GnP.actions(liste);
                            break;
                        }

                        case 7 :{
                            cout <<"Vous êtes sortie, ETAPE PRECEDENTE :"<<endl;
                            break;
                        }

                        default:
                            std::cout << "cette option n'existe pas" << std::endl;
                            cout<<"Entrez quelque chose de valide :"<<endl;
                            cin>>option;
                            break;
                    }
                } while (choix != 7);

                break;
            }
            case 2: {
                //exemple d algorithme

                int algo = 0;
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
                    cin >> algo;
                    cout << "-----------------------------------------------------------------------" << endl;

                    switch (algo) {
                        case 1: {

                            //Dantzig

                            Graphe gDantzig = Graphe(true, true);

                            cout << "---------Ajout de sommets ------------" << endl;
                            gDantzig.ajouterSommet(s);
                            gDantzig.ajouterSommet(t);
                            gDantzig.ajouterSommet(w);
                            gDantzig.ajouterSommet(k);

                            cout << "---------Ajout de arc  ------------" << endl;
                            gDantzig.ajouterArc(s, t, 1);
                            gDantzig.ajouterArc(s, k, 2);
                            gDantzig.ajouterArc(t, w, 3);

                            Algorithme aDantzig;

                            aDantzig.Dantzig(gDantzig.getMatCout());

                            break;
                        }
                        case 2: {
                            std::cout << " algo de dikjstra" << std::endl;
                            Graphe *gDikjstra = new Graphe(avec_Poids, est_oriente);

                            // -------------- Class.Sommet --------------
                            Point *p1 = new Point(100, 400);
                            Point *p2 = new Point(400, 300);
                            Point *p3 = new Point(400, 600);
                            Point *p4 = new Point(700, 400);
                            Point *p5 = new Point(700, 100);
                            Point *p6 = new Point(700, 700);
                            Point *p7 = new Point(100, 700);

                            Sommet *s1 = new Sommet("Reims", p1, 1); //sommets 0 et marque 1
                            Sommet *s2 = new Sommet("Nice", p2, 1);  //sommets 1 et marque 1
                            Sommet *s3 = new Sommet("Paris", p3, 1);  //sommets 2 et marque 1
                            Sommet *s4= new Sommet("Brest", p4, 1);  //sommets 2 et marque 1
                            Sommet *s5= new Sommet("Tours", p5, 1);  //sommets 2 et marque 1
                            Sommet *s6= new Sommet("Lille", p6, 1);  //sommets 2 et marque 1
                            Sommet *s7= new Sommet("Lyon", p7, 1);  //sommets 2 et marque 1

                            std::cout << "---------Ajout de sommets ------------" << std::endl;
                            gDikjstra->ajouterSommet(s1);
                            gDikjstra->ajouterSommet(s2);
                            gDikjstra->ajouterSommet(s3);
                            gDikjstra->ajouterSommet(s4);
                            gDikjstra->ajouterSommet(s5);
                            gDikjstra->ajouterSommet(s6);
                            gDikjstra->ajouterSommet(s7);

                            cout << "---------Ajout de arc  ------------" << endl;
                            gDikjstra->ajouterArc(s1, s2, 1);
                            gDikjstra->ajouterArc(s1, s5, 2);
                            gDikjstra->ajouterArc(s1, s3, 3);
                            gDikjstra->ajouterArc(s1, s7, 1);

                            gDikjstra->ajouterArc(s2, s5, 1);
                            gDikjstra->ajouterArc(s2, s3, 4);
                            gDikjstra->ajouterArc(s3, s5, 3);
                            gDikjstra->ajouterArc(s3, s6, 1);
                            gDikjstra->ajouterArc(s4, s3, 1);
                            gDikjstra->ajouterArc(s5, s4, 1);
                            gDikjstra->ajouterArc(s6, s4, 1);
                            gDikjstra->ajouterArc(s7, s3, 1);
                            gDikjstra->ajouterArc(s7, s6, 3);

                            gDikjstra->afficher_matrice();
                            gDikjstra->afficher_cout();
                            gDikjstra->afficher_fs_aps();
                            Algorithme A_Dikjstra;

                            int n = gDikjstra->getApsElem(0);
                            int m = gDikjstra->getFsElem(0) - n;
                            vector<int> predecesseur(n + 2);
                            vector<int> distance(n + 2);
                            A_Dikjstra.Dijkstra(1, gDikjstra, predecesseur, distance);
                            cout << "Affichage du pred ";
                            for (int i = 0; i < predecesseur.size(); i++)
                                cout << predecesseur[i] << "| ";
                            cout << endl;

                            //DessinGraphe(gDikjstra);
                            //Djikstra(gDikjstra);
                            break;

                        }
                        case 3: {
                            //Kruskal
                            break;
                        }
                        case 4 : {
                            //Ordonnancement
                            break;
                        }
                        case 5 : {
                            //Prufer
                            Graphe gprufer(est_oriente, avec_Poids);
                            gprufer.ajouterSommet(s);
                            gprufer.ajouterSommet(t);
                            gprufer.ajouterSommet(w);
                            gprufer.ajouterSommet(k);
                            gprufer.ajouterArc(s, t, 1);
                            gprufer.ajouterArc(s, k, 2);
                            gprufer.ajouterArc(t, w, 3);

                            gprufer.afficher_fs_aps();
                            int n = gprufer.nombre_sommets_matrice();
                            vector<int> pref(n - 2);
                            Algorithme A_prufer;
                            A_prufer.prufer_encode(pref, gprufer);

                            //new DessinGraphe(gprufer);
                            cout << "Affichage du pref " << endl;
                            for (int i = 0; i < pref.size(); i++)
                                cout << pref[i] << "| ";
                            cout << endl;

                            break;

                        }
                        case 6: {
                            //Rang
                            Graphe *gRang = new Graphe(true, true);

                            gRang->ajouterSommet(s);
                            gRang->ajouterSommet(t);
                            gRang->ajouterSommet(w);
                            gRang->ajouterSommet(k);

                            gRang->ajouterArc(s, t, 1);
                            gRang->ajouterArc(s, k, 2);
                            gRang->ajouterArc(t, w, 3);

                            gRang->afficher_fs_aps();

                            Algorithme *a = new Algorithme();

                            std::vector<int> r = a->rang(gRang->getFs(), gRang->getAps());

                            std::string str = "-----------Rang------------\n|";
                            for (int i: r) {
                                str += std::to_string(i) + "|";
                            }
                            str += "\n";

                            std::cout << str;
                            break;
                        }
                        case 7: {
                            //Tarjan
                            std::cout << "Désolé, cet algorithme ne fonctionne pas..." << std::endl;
                            break;
                        }
                        case 8: {
                            // Demi degre interieur
                            Graphe gDdi(true, true);

                            cout << "---------Ajout de sommets ------------" << endl;
                            gDdi.ajouterSommet(s);
                            gDdi.ajouterSommet(t);
                            gDdi.ajouterSommet(w);
                            gDdi.ajouterSommet(k);

                            cout << "---------Ajout de arc  ------------" << endl;
                            gDdi.ajouterArc(s, t, 1);
                            gDdi.ajouterArc(s, k, 2);
                            gDdi.ajouterArc(t, w, 3);

                            gDdi.afficher_fs_aps();

                            Algorithme addi;
                            vector<int> ddi = addi.demi_degre_interieur(gDdi.getFs(), gDdi.getAps());

                            string str1 = "-----------Demi Degre Interieur------------\n|";
                            for (int i: ddi) {
                                str1 += to_string(i) + "|";
                            }
                            str1 += "\n";
                            cout << str1;

                            break;
                        }
                        case 9: {
                            // Demi degre exterieur
                            Graphe gDde(true, true);

                            std::cout << "---------Ajout de sommets ------------" << std::endl;
                            gDde.ajouterSommet(s);
                            gDde.ajouterSommet(t);
                            gDde.ajouterSommet(w);
                            gDde.ajouterSommet(k);

                            std::cout << "---------Ajout de arc  ------------" << std::endl;
                            gDde.ajouterArc(s, t, 1);
                            gDde.ajouterArc(s, k, 2);
                            gDde.ajouterArc(t, w, 3);

                            gDde.afficher_fs_aps();

                            Algorithme adde;
                            std::vector<int> dde = adde.demi_degre_exterieur(gDde.getFs(), gDde.getAps());

                            std::string str2 = "-----------Demi Degre Exterieur-----------\n|";
                            for (int i: dde) {
                                str2 += std::to_string(i) + "|";
                            }
                            str2 += "\n";
                            std::cout << str2 << std::endl;

                            break;
                        }

                        case 10: {
                            //Calcul de distance

                            Graphe gdist(true, true);

                            cout << "---------Ajout de sommets ------------" << endl;
                            gdist.ajouterSommet(s);
                            gdist.ajouterSommet(t);
                            gdist.ajouterSommet(w);
                            gdist.ajouterSommet(k);

                            cout << "---------Ajout de arc  ------------" << endl;
                            gdist.ajouterArc(s, t, 1);
                            gdist.ajouterArc(s, k, 2);
                            gdist.ajouterArc(t, w, 3);

                            gdist.afficher_fs_aps();

                            Algorithme distance;
                            distance.calcul_distance(&gdist);

                            break;
                        }
                    }
                } while (algo != 11);
            }
            case 3: {
                /* try {
                     UIManager::setLookAndFeel(new NimbusLookAndFeel());
                 } catch (UnsupportedLookAndFeelException e) {
                     e.printStackTrace();
                 }
                 */

                QApplication app(argc, argv);
                MyWindow window;
                window.show();
                return app.exec();

                Graphe G(est_oriente, avec_Poids);


                G.ajouterSommet(s);
                G.ajouterSommet(t);
                G.ajouterSommet(w);
                G.ajouterSommet(k);

                vector<Sommet> liste;
                liste.push_back(*s);
                liste.push_back(*t);
                liste.push_back(*w);
                liste.push_back(*k);

                G.ajouterArc(s, t, 1);
                G.ajouterArc(s, k, 2);
                G.ajouterArc(t, k, 3);
                G.ajouterArc(w, t, 5);
                G.ajouterArc(w, w, 5);
                G.ajouterArc(k, t, 5);
                G.ajouterArc(k, k, 5);

                //MyWindow Fenetre(G);
                //Fenetre.setVisible(true);
                break;
            }
            case 4:{
                cout<<"FINI, Vous êtes sortie ."<<endl;
                break;
            }
            default :
                cout << "Cette option n'existe pas" << endl;
                cout<<"Entrez quelque chose de valide :"<<endl;
                cin>>option;
                break;
        }
    }while(choix!=4);
}

