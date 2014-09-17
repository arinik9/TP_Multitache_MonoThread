/*************************************************************************
                           Entree.cpp  -  description
                             -------------------
    début                : Mardi 25 Février 2014
    copyright            : (C) 2014 par B3329  
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/
//---------- Réalisation de la tâche <Entree> (fichier Entree.cpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <Menu.h>
#include <stdlib.h>
#include <unistd.h>
#include <Outils.h>
#include <Heure.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <sys/sem.h>
#include <map>


//------------------------------------------------------ Include personnel
#include "Sortie.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques
//------------------------------------------------------ Fonctions privées
static int id_mem;
static int id_sem;
static int id_bal;
static struct MemoirePartagee* memoire;
static std::map<pid_t, Voiture> voituriers; //Liste des voituriers en activité
static std::map<pid_t, Voiture>::iterator itMap;
static struct sembuf reserver = {0, -1, 0};
static struct sembuf liberer = {0, 1, 0};

static int definirPrioritaire(){
		int p=0;
		if(memoire->demandes[0].usager != AUCUN){
			p=1;
			Voiture voiture;
			voiture=memoire->demandes[0];
			if(memoire->demandes[2].usager == PROF){
				if(memoire->demandes[2].heureArrivee > voiture.heureArrivee){
					p=3;
				}
			}		
		}
		else{
			if(memoire->demandes[2].usager != AUCUN){			
				Voiture voiture = memoire->demandes[2];
				if(voiture.usager == PROF){
					p=3;
				}
				else{ // voiture.TYPE == AUTRE
					p=3;
					if(memoire->demandes[1].usager != AUCUN){
					if( voiture.heureArrivee > memoire->demandes[1].heureArrivee){
					p=2;
					}
					}
				}
			}
			else if(memoire->demandes[1].usager != AUCUN){
				p=2;
			}
			
		}
return p;
}

void HandleSignalSortie(int sig)
//handler du signal SIGUSR2
{
//Actualisation du nombre de places	
	semop(id_sem, &reserver, 1); //Reservation de la ressource critique
	memoire->placesDispos++;
	semop(id_sem, &liberer, 1); //Liberation de la ressource critique
		
	//Recuperation de la voiture sortie
	int numPlace;
	pid_t pidVoiturier = waitpid((pid_t)(-1),&numPlace, WNOHANG);
	numPlace=WEXITSTATUS(numPlace);
	itMap=voituriers.find(pidVoiturier);
	Voiture voiture = itMap->second;

	//Actualisation de la memoire partagee
	semop(id_sem, &reserver, 1); //Reservation de la ressource critique
	memoire->parking[numPlace-1].usager = AUCUN;
	semop(id_sem, &liberer, 1); //Liberation de la ressource critique

	voituriers.erase(itMap);
	//analyse des requetes
	int prioritaire = definirPrioritaire();
	if(prioritaire != 0){
		semop(id_sem, &reserver, 1); //Reservation de la ressource critique
		memoire->demandes[prioritaire-1].usager = AUCUN;
		semop(id_sem, &liberer, 1); //Liberation de la ressource critique
		struct sembuf libererEntree = {prioritaire, 1, 0};
		int s = semop(id_sem, &libererEntree, 1); //deblocage de l'entree autorise
	}

	//actualisation de l'affichage
	switch(numPlace){
		case 1:
			Effacer(ETAT_P1);
			break;
		case 2:
			Effacer(ETAT_P2);
			break;
		case 3:
			Effacer(ETAT_P3);
			break;
		case 4:
			Effacer(ETAT_P4);
			break;
		case 5:
			Effacer(ETAT_P5);
			break;
		case 6:
			Effacer(ETAT_P6);
			break;
		case 7:
			Effacer(ETAT_P7);
			break;
		case 8:
			Effacer(ETAT_P8);
			break;
	}

	switch(prioritaire){
		case 1:
			Effacer(REQUETE_R1);
			break;
		case 2:
			Effacer(REQUETE_R2);
			break;
		case 3:
			Effacer(REQUETE_R3);
			break;
	}
	
	AfficherSortie(voiture.usager, voiture.matricule, voiture.heureArrivee, time(NULL));
	//heure de sortie calculée au dernier moment afin de gagner plus d'argent
}

void HandlerFinProgrammeSortie(int sig){
	shmdt(memoire);
	for(itMap=voituriers.begin(); itMap!=voituriers.end(); ++itMap){
		kill(itMap->first, SIGUSR2);
	}
	exit(0);
}


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


void Sortie(int id_mem_param, int id_sem_param, int id_bal_param)
// Algorithme :
//
{
//Recuperation des identifiants
	id_mem = id_mem_param;
	id_sem = id_sem_param;
	id_bal = id_bal_param;

	pid_t pidVoiturier;
	messageSortie voitureSortante;
	
	memoire = (MemoirePartagee*) shmat(id_mem,NULL,0);
	Voiture voiture;

	struct sigaction saChild; //pour le signal SIGCHLD
		sigemptyset(&saChild.sa_mask);
		saChild.sa_handler = HandleSignalSortie;
		saChild.sa_flags = 0;
		sigaction(SIGCHLD, &saChild, NULL);
	struct sigaction saUsr2; //pour le signal SIGUSR2
		sigemptyset(&saUsr2.sa_mask);
		saUsr2.sa_handler = HandlerFinProgrammeSortie;
		saUsr2.sa_flags = 0;
		sigaction(SIGUSR2, &saUsr2, NULL);

	for(;;){
		while(msgrcv( id_bal, &voitureSortante,sizeof(struct messageSortie), 4, 0) == -1);
		if(memoire->parking[voitureSortante.numPlace-1].usager != AUCUN){// si une voiture est présente sur la place
		voiture = memoire->parking[voitureSortante.numPlace-1];
		pidVoiturier = SortirVoiture(voitureSortante.numPlace);

			if(pidVoiturier!=-1){
				voituriers.insert(std::pair<pid_t, Voiture>(pidVoiturier, voiture));
			}
		}
	}
        	
} //----- fin de Sortie

