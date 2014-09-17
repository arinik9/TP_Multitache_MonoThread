/*************************************************************************
                           Mere.cpp  -  description
                             -------------------
    début                : Mardi 21 Février 2014
    copyright            : (C) 2014 par B3329  
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/
//---------- Réalisation de la tâche <Mere> (fichier Mere.cpp) ---
/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
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
#include<stdlib.h>
#include <errno.h>

//------------------------------------------------------ Include personnel

#include "Configuration.h"
#include "Mere.h"
#include "Clavier.h"
#include "Entree.h"
#include "Sortie.h"

	

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

int main()
// Algorithme :
//
{

	//----------Initialisation memoire partagee----------
	int id_mem = shmget(IPC_PRIVATE, sizeof(MemoirePartagee), IPC_CREAT | DROITS);
	MemoirePartagee* memoire;
	memoire = (MemoirePartagee *) shmat(id_mem, NULL,0);//attachement du segment de memoire
	memoire->placesDispos=8;
	for(int i=0;i<8;i++){
		memoire->parking[i].usager=AUCUN;	
	}
	for(int j=0;j<3;j++){
		memoire->demandes[j].usager=AUCUN;	
	}
	shmdt(memoire);
	

	//----------Initialisation semaphore----------
	int id_sem = semget(IPC_PRIVATE, 4, IPC_CREAT | DROITS);
	semctl(id_sem, 0, SETVAL, 1);
		//semaphores elementaires
		// 0 : Memoire partagée
		// 1 : Porte Prof_Blaise_Pascal
		// 2 : Porte Autre_Blaise_Pascal
		// 3 : Porte Entree_Gaston_Berger

	//----------Initialisation boîte aux lettres----------
	int id_bal = msgget(IPC_PRIVATE, IPC_CREAT | DROITS);

	//-----Initialisation de la tache Entree
		InitialiserApplication(XTERM);
		pid_t pidHeure = ActiverHeure();
		pid_t pidEntree1, pidEntree2, pidEntree3;
		pid_t pidSortie;
		pid_t pidClavier;
		if ((pidEntree1=fork()) == 0){
			Entree(1, PROF_BLAISE_PASCAL, id_mem, id_sem, id_bal);
		}
		else if ((pidEntree2=fork()) == 0){
			Entree(2, AUTRE_BLAISE_PASCAL, id_mem, id_sem, id_bal);
		}
		else if ((pidEntree3=fork()) == 0){
			Entree(3, ENTREE_GASTON_BERGER, id_mem, id_sem, id_bal);
		}
		else if((pidSortie=fork()) == 0){
			Sortie(id_mem, id_sem, id_bal);
		}
		else if ((pidClavier=fork()) == 0){
			Clavier(id_bal);
		}
		else{
			//point triple
			waitpid(pidClavier, NULL, 0);
			//-----Destruction des taches-----
			kill(pidSortie, SIGUSR2);					
			kill(pidEntree1, SIGUSR2);					
			kill(pidEntree2, SIGUSR2);					
			kill(pidEntree3, SIGUSR2);					
			kill(pidClavier, SIGUSR2);					
			kill(pidHeure, SIGUSR2);					

			for(int i=0; i<6; i++){
				waitpid(-1, NULL, 0);
			}		

			semctl(id_sem, 0, IPC_RMID, 0); //Destruction du sémaphore
			msgctl(id_bal, IPC_RMID, 0); //Destruction de la boite aux lettres
			shmctl(id_mem, IPC_RMID, NULL);//destruction de la mémoire partagée
			//fin de l'application
			TerminerApplication(true);
		}
	return 0;
} //----- fin de main

