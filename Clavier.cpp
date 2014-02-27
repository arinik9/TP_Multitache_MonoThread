/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/
//---------- Réalisation de la tâche <Clavier> (fichier Clavier.cpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <Menu.h>
#include <stdlib.h>
//
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
	switch (code) {
		case 'Q' : exit(0);
		//case 'P' : 
	}
} //----- fin de Commande
