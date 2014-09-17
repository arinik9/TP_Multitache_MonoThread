/*************************************************************************
                           Configuration.h  -  description
                             -------------------
    début                : Mardi 25 Février 2014  
    copyright            : (C) 2014 par B3329
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Configuration> (fichier Configuration.h) -------
#if ! defined ( Configuration_H )
#define Configuration_H

//------------------------------------------------------------------------
// Rôle de la tâche <Configuration>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <time.h>
#include "Outils.h"

//------------------------------------------------------------- Constantes
#define DROITS 0660 // Droits d'accès

//------------------------------------------------------------------ Types


struct Voiture{
	long numPorte;
	enum TypeUsager usager;
	time_t heureArrivee;
	int matricule;
};

struct messageSortie{
	long numPorte;
	int numPlace;
};

struct MemoirePartagee{
	int placesDispos;
	Voiture parking[8];
	Voiture demandes[3];
};
	

//////////////////////////////////////////////////////////////////  PUBLIC



//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

#endif // Configuration_H


