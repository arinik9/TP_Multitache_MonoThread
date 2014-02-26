/*************************************************************************
                           Configuration  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
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


 struct MemHabituel{
	unsigned int numPlace;
	char occupation;
	const char* heureEntree;
	bool plein;
};

struct MemEnCasPlein{
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

