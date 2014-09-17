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
#include "Entree.h"
#include "Configuration.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques
static int id_mem;
static int id_sem;
static int id_bal;
static struct MemoirePartagee* memoire;
static std::map<pid_t, Voiture> voituriers; //Liste des voituriers en activité
static std::map<pid_t, Voiture>::iterator itMap;
static struct sembuf reserver = {0, -1, 0};
static struct sembuf liberer = {0, 1, 0};

//------------------------------------------------------ Fonctions privées




void HandlerFinVoiturier(int sig){
	int numPlace;
	pid_t pidVoiturier = waitpid((pid_t)(-1),&numPlace, WNOHANG);
	numPlace=WEXITSTATUS(numPlace);
	itMap=voituriers.find(pidVoiturier);
	Voiture voiture = itMap->second;
	semop(id_sem, &reserver, 1); //Reservation de la ressource critique
	memoire->parking[numPlace-1]=voiture;
	semop(id_sem, &liberer, 1); //Liberation de la ressource critique
	voituriers.erase(itMap);
}

void HandlerFinProgramme(int sig){
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


void Entree (int numPorte, enum TypeBarriere barriere, int id_mem_param, int id_sem_param, int id_bal_param)
// Algorithme :
//
{
	id_mem=id_mem_param;
	id_sem=id_sem_param;
	id_bal=id_bal_param;
	memoire = (MemoirePartagee*) shmat(id_mem,NULL,0);
	pid_t pidVoiturier;
	Voiture voiture;
	struct sigaction saChild;
		sigemptyset(&saChild.sa_mask);
		saChild.sa_handler = HandlerFinVoiturier;
		saChild.sa_flags = 0;
	sigaction(SIGCHLD, &saChild, NULL);
	struct sigaction saUsr2;
		sigemptyset(&saUsr2.sa_mask);
		saUsr2.sa_handler = HandlerFinProgramme;
		saUsr2.sa_flags = 0;
	sigaction(SIGUSR2, &saUsr2, NULL);

	struct sembuf reserver = {0, -1, 0};
	struct sembuf liberer = {0, 1, 0};

	for(;;){
		while(msgrcv(id_bal, &voiture, sizeof(struct Voiture), numPorte, 0) == -1);
		DessinerVoitureBarriere(barriere, voiture.usager);
		if(memoire->placesDispos == 0){ // si le parking est plein
			semop(id_sem, &reserver, 1); // reservation de la ressource critique
			memoire->demandes[numPorte-1] = voiture;
			semop(id_sem, &liberer, 1); //liberation de la ressource critique
			AfficherRequete(barriere, voiture.usager, time(NULL));
			struct sembuf bloquerEntree = {numPorte, -1, 0};
			while(semop(id_sem, &bloquerEntree, 1) == -1); //blocage de la tache Entre
		}
		semop(id_sem, &reserver, 1); //reservation de la ressource critique
		memoire->placesDispos--;
		semop(id_sem, &liberer, 1); //liberation de la ressource critique
		pidVoiturier = GarerVoiture(barriere);
		if(pidVoiturier != -1){
			voituriers.insert(std::pair<pid_t, Voiture>(pidVoiturier, voiture));
		}
		sleep(1);
	}
} //----- fin de Entree

