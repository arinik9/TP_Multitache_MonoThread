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
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>

//------------------------------------------------------ Include personnel
#include "Clavier.h"
#include "Configuration.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques
static int id_bal;
static int numMatricule=1;
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
void Clavier (int id_bal_param)
// Algorithme :
//
{
	id_bal = id_bal_param;
	for(;;) {
		Menu();
	}
} //----- fin de Clavier

void Commande ( char code, unsigned int valeur ){
// Algorithme :
//
Voiture voiture;
messageSortie voitureSortante;
	switch (code) {
		case 'Q' :
			exit(0);
		case 'P' :
			if(valeur==1){
				voiture.numPorte=1;
				voiture.usager=PROF;
				voiture.heureArrivee=time(NULL);
				voiture.matricule=(numMatricule%999);
				numMatricule++;
				msgsnd(id_bal, &voiture, sizeof(struct Voiture), 0);
				break;
			}
			else if(valeur==2){
				voiture.numPorte=3;
				voiture.usager=PROF;
				voiture.heureArrivee=time(NULL);
				voiture.matricule=(numMatricule%999);
				numMatricule++;
				msgsnd(id_bal, &voiture, sizeof(struct Voiture), 0);
				break;
			}
		case 'A' :
			if(valeur==1){
				voiture.numPorte=2;
				voiture.usager=AUTRE;
				voiture.heureArrivee=time(NULL);
				voiture.matricule=(numMatricule%999);
				numMatricule++;
				msgsnd(id_bal, &voiture, sizeof(struct Voiture), 0);
				break;
			}
			else if(valeur==2){
				voiture.numPorte=3;
				voiture.usager=AUTRE;
				voiture.heureArrivee=time(NULL);
				voiture.matricule=(numMatricule%999);
				numMatricule++;
				msgsnd(id_bal, &voiture, sizeof(struct Voiture), 0);
				break;
			}
		case 'S' :
			voitureSortante.numPorte=4;
			voitureSortante.numPlace = valeur;
			msgsnd(id_bal, &voitureSortante, sizeof(struct messageSortie), 0);
			break;
			
	}
	
} //----- fin de Commande
