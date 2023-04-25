
#include "MyWindow.h"
MyWindow::MyWindow(QWidget *parent) : QMainWindow(parent) {
    /*label = new QLabel("Hello World", this);
    button = new QPushButton("Click Me", this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);

    setLayout(layout);*/

    //d_graphe = Graphe();
    // Création des 8 boutons
    dessinButton = new QPushButton("Dessin", this);
    chargerButton = new QPushButton("Charger", this);
    ajouterSommetButton = new QPushButton("Ajouter Sommet", this);
    supprimerSommetButton = new QPushButton("Supprimer Sommet", this);
    ajouterArcButton = new QPushButton("Ajouter Arc", this);
    supprimerArcButton = new QPushButton("Supprimer Arc", this);
    creerGrapheButton = new QPushButton("Creer Graphe", this);
    sauvegarderButton = new QPushButton("Sauvegarder", this);

// Création des QLineEdit pour la suppression de sommet et ajout de sommet
    numSommetASupprimer = new QLineEdit(this);
    nomSommet = new QLineEdit(this);
    positionX = new QLineEdit(this);
    positionY = new QLineEdit(this);

// Création des QLineEdit pour la suppression et l'ajout d'arc
    departArcASupprimer = new QLineEdit(this);
    arriveeArcASupprimer = new QLineEdit(this);
    poidsArcASupprimer = new QLineEdit(this);
    departArcAjouter = new QLineEdit(this);
    arriveeArcAjouter = new QLineEdit(this);
    poidsArcAjouter = new QLineEdit(this);

// Création des labels pour chaque QLineEdit
    QLabel* labelNumSuppr = new QLabel("Numéro du sommet à supprimer :", this);
    QLabel* labelNomSommet = new QLabel("Nom du sommet :", this);
    QLabel* labelPosX = new QLabel("Position X :", this);
    QLabel* labelPosY = new QLabel("Position Y :", this);
    QLabel* labelDepartSuppr = new QLabel("Départ de l'arc à supprimer :", this);
    QLabel* labelArriveeSuppr = new QLabel("Arrivée de l'arc à supprimer :", this);
    QLabel* labelPoidsSuppr = new QLabel("Poids de l'arc à supprimer :", this);
    QLabel* labelDepartAjout = new QLabel("Départ de l'arc à ajouter :", this);
    QLabel* labelArriveeAjout = new QLabel("Arrivée de l'arc à ajouter :", this);
    QLabel* labelPoidsAjout = new QLabel("Poids de l'arc à ajouter :", this);

// Positionnement des widgets
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(dessinButton, 0, 0);
    layout->addWidget(chargerButton, 0, 1);
    layout->addWidget(ajouterSommetButton, 1, 0);
    layout->addWidget(supprimerSommetButton, 1, 1);
    layout->addWidget(ajouterArcButton, 2, 0);
    layout->addWidget(supprimerArcButton, 2, 1);
    layout->addWidget(creerGrapheButton, 3, 0);
    layout->addWidget(sauvegarderButton, 3, 1);

    layout->addWidget(labelNumSuppr, 4, 0);
    layout->addWidget(numSommetASupprimer, 4, 1);
    layout->addWidget(labelNomSommet, 5, 0);
    layout->addWidget(nomSommet, 5, 1);
    layout->addWidget(labelPosX, 6, 0);
    layout->addWidget(positionX, 6, 1);
    layout->addWidget(labelPosY, 7, 0);
    layout->addWidget(positionY, 7, 1);

    layout->addWidget(labelDepartSuppr, 4, 2);
    layout->addWidget(departArcASupprimer, 4, 3);
    layout->addWidget(labelArriveeSuppr, 5, 2);
    layout->addWidget(arriveeArcASupprimer, 5, 3);
    layout->addWidget(labelPoidsSuppr, 6, 2);
    layout->addWidget(poidsArcASupprimer, 6, 3);

    layout->addWidget(labelDepartAjout, 8, 2);
    layout->addWidget(departArcAjouter, 8, 3);
    layout->addWidget(labelArriveeAjout, 9, 2);
    layout->addWidget(arriveeArcAjouter, 9, 3);
    layout->addWidget(labelPoidsAjout, 10, 2);
    layout->addWidget(poidsArcAjouter, 10, 3);
// Ajout des marges entre les boutons et les QLineEdit
    layout->setColumnMinimumWidth(0, 50);
    layout->setColumnMinimumWidth(1, 50);
    layout->setColumnMinimumWidth(2, 250);
    layout->setColumnMinimumWidth(3, 100);
    layout->setRowMinimumHeight(4, 50);
    layout->setRowMinimumHeight(7, 50);
    layout->setRowMinimumHeight(11, 50);

    // Création de la liste de choix pour les algorithmes
    algoListe = new QComboBox(this);
    algoListe->addItem("Calcul des distances");
    algoListe->addItem("Dantzig");
    algoListe->addItem("Demi degré intèrieur");
    algoListe->addItem("Demi degré extèrieur");
    algoListe->addItem("Dijkstra");
    algoListe->addItem("Kruskal (arbre couvrant minimum)");
    algoListe->addItem("Ordonnancement");
    algoListe->addItem("Rang");
    algoListe->addItem("Tarjan");
    algoListe->addItem("Prufer codage / decodage");

    QHBoxLayout* layoutH5 = new QHBoxLayout();
    layoutH5->addWidget(algoListe);
    layout->addLayout(layoutH5, 8, 0, 1, 2);

    // Création des QCheckBox pour le type de graphe
    isOriented = new QCheckBox("Graphe orienté", this);
    isWeighted = new QCheckBox("Graphe pondéré", this);

// Positionnement des QCheckBox
    isOriented->setGeometry(QRect(QPoint(10, 330), QSize(150, 25)));
    isWeighted->setGeometry(QRect(QPoint(10, 360), QSize(150, 25)));

// Ajout des QCheckBox au layout
    layout->addWidget(isOriented, 9, 0);
    layout->addWidget(isWeighted, 9, 1);


    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

  // QObject::connect(supprimerSommetButton, SIGNAL(clicked()), this, SLOT(supprimerSommet()));


}

/*void MyWindow::supprimerSommet()
{
    int numSommet = numSommetASupprimer->text().toInt();
    Sommet* sommetASupprimer = d_graphe.getListeSommetElem(numSommet);
    d_graphe.supprimerSommet(sommetASupprimer);
}
*/

