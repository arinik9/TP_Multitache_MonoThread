/*************************************************************************
                           Configuration.h  -  description
                             -------------------
<<<<<<< HEAD
    début                : Mardi 25 Février 2014  
=======
    début                : Mardi 25 Février 2014
>>>>>>> Lecture-Ecriture Dans la Memoire Partagée
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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Msgbuf {
	long type;
	char texte[3];
};

//
 struct MemEtat{
	unsigned int numPlace;
	char occupation;
	const char* heureEntree;
	bool plein;
};

struct MemDemandes{
	char porte;
	char usager;
	const char* Heure;
	unsigned int matricule;
};
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

int creerSegment(int size,char *name,int cle);
void afficherInfoSegment(int shmid);
void detruireSegment(int shmid);
#endif // Configuration_H
