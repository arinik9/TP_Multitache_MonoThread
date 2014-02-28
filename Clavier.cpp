/*************************************************************************
                           Clavier.cpp  -  description
                             -------------------
    début                : Mardi 21 Février 2014  
    copyright            : (C) 2014 par B3329
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/
//---------- Réalisation de la tâche <Clavier> (fichier Clavier.cpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <Menu.h>
#include <stdlib.h>

//------------------------------------------------------ Include personnel
#include "Clavier.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques
//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier ()
// Algorithme :
//
{
	for(;;) {
		Menu();
	}
} //----- fin de Clavier

void Commande ( char code, unsigned int valeur ){
// Algorithme :
//
	switch (code) {
		case 'Q' : exit(0);
		//case 'P' : 
	}
} //----- fin de Commande
