/*************************************************************************
                           Mere.h  -  description
                             -------------------
    début                : Mardi 21 Février 2014  
    copyright            : (C) 2014 par B3329
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Mere> (fichier Mere.h) -------
#if ! defined ( Mere_H )
#define Mere_H

//------------------------------------------------------------------------
// Rôle de la tâche <Mere>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <sys/sem.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
//////////////////////////////////////////////////////////////////  PUBLIC

bool plein;




//---------------------------------------------------- Fonctions publiques
int creerMemoirePartagee(int size,char *name,int cle);
void afficherInfoMemoirePartagee(int shmid);
void detruireMemoirePartagee(int shmid);

// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
int main();

#endif // Mere_H

