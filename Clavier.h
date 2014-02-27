/*************************************************************************
                           Clavier.h  -  description
                             -------------------
<<<<<<< HEAD
    début                : Mardi 21 Février 2014  
=======
    début                : Mardi 21 Février 2014
>>>>>>> Lecture-Ecriture Dans la Memoire Partagée
    copyright            : (C) 2014 par B3329
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Clavier> (fichier Clavier.h) -------
#if ! defined ( Clavier_H )
#define Clavier_H

//------------------------------------------------------------------------
// Rôle de la tâche <Clavier>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
void Clavier();
void Commande ( char code, unsigned int valeur );

#endif // Clavier_H
