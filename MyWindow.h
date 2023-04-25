//
// Created by Edona Dibra on 25/04/2023.
//

#ifndef GRAPHE2023_MYWINDOW_H
#define GRAPHE2023_MYWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "Graphe.h"

class MyWindow : public QMainWindow{
public :
        MyWindow(QWidget *parent = nullptr);
        void supprimerSommet();
private:
    //Graphe d_graphe;
    QLabel *label;
    QPushButton *dessinButton;
    QPushButton *chargerButton;
    QPushButton* supprimerSommetButton;
    QPushButton* ajouterSommetButton;
    QPushButton* ajouterArcButton;
    QPushButton* supprimerArcButton;
    QPushButton* creerGrapheButton ;
    QPushButton* sauvegarderButton ;

    QLineEdit* numSommetASupprimer;
    QLineEdit* nomSommet;
    QLineEdit* positionX;
    QLineEdit* positionY;
    QLineEdit* departArcASupprimer;
    QLineEdit* arriveeArcASupprimer;
    QLineEdit* poidsArcASupprimer ;
    QLineEdit* departArcAjouter ;
    QLineEdit* arriveeArcAjouter ;
    QLineEdit* poidsArcAjouter ;
    QComboBox* algoListe;
    QCheckBox* isOriented;
    QCheckBox* isWeighted;
};


#endif //GRAPHE2023_MYWINDOW_H
