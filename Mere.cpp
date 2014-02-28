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
#include<stdio.h>
#include<stdlib.h>
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Clavier.h"
#include "Entree.h"
#include "Configuration.h"

	

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
	//-----Initialisation affichage
	//InitialiserApplication(XTERM);
	//pid_t pidHeure = ActiverHeure();
	char *mem ;
 
	int flag = 0 ; // un drapeau attache au segment
	MemEtat memEtat;//struct	

  	char *name = (char *) malloc(sizeof(memEtat)*sizeof(char)) ;
  	//char* name = new char(sizeof(memEtat))
	name = "Configuration.cpp" ;

	shmid = creerSegment(sizeof(memEtat),name,1) ;
	printf("Je commence par m'attacher le segment de memoire Mere.cpp\n") ;
	mem = (char*) shmat(shmid,0,flag) ;

	if (mem ==(char*)-1){
	perror("attachement impossible") ;
	exit(1) ;
	}
	//printf("je vais ecrire un message que papa va afficher\n") ;
	strcpy(mem,"Turquie, ele est belle, magnifique!! Oh la la!!");
	printf("Bon, c'est pas tout ca mais il est temps de mourrir\n") ;
        //printf("avant tout detachons le segment partagee\n") ;
        if(shmdt(mem)==-1){
        perror("detachement impossible") ;
        exit(1) ;
        }
        //printf("maintenant que c'est fait, bye bye\n") ;


	
	//afficherInfoSegment(shmid) ;
	//detruireSegment(shmid) ;

	//-----Initialisation des boîtes aux lettres
	/*key_t cleEntree;
	key_t cleSortie;
	int tailleEntree, writeEntree, id_fileEntree;
	int tailleSortie, writeSortie, id_fileSortie;
	cleEntree = ftok("fileEntree",1);
	cleSortie = ftok("fileSortie",1);
	id_fileEntree = msgget(cleEntree, 0666|IPC_CREAT);
	id_fileSortie = msgget(cleSortie, 0666|IPC_CREAT);
	if(id_fileEntree==-1){
		perror("Erreur creation boite aux lettres entree");
		exit(EXIT_FAILURE);
	}
	if(id_fileSortie==-1){
		perror("Erreur creation boite aux lettres sortie");
		exit(EXIT_FAILURE);
	}
	Msgbuf messageEntree;
	messageEntree.type=1;
	strcpy(messageEntree.texte, "OH");
	tailleEntree=strlen(messageEntree.texte);
	msgsnd(id_fileEntree, &messageEntree, tailleEntree+1, 0);
	//msgsnd(id_fileEntree, &messageEntree, tailleEntree+1, 0);)*/

	//-----Initialisation de la tache Entree
		pid_t pidEntree = fork();
		if (pidEntree == -1){
			cout << "fail" << endl;
			exit(EXIT_FAILURE);
		}
		if (pidEntree== 0){
			Entree();
		}
		else{
			//Synchronisation de fin normale entre le père et le fils
			waitpid(pidEntree, NULL, 0);
		}

	//-----Initialisation du clavier
	/*pid_t pidClavier = fork();
	if (pidClavier == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pidClavier == 0){
		Clavier();
	}
	else{
		//Synchronisation de fin normale entre le père et le fils
		waitpid(pidClavier, NULL, 0);
	}*/	
	//kill(pidHeure, SIGUSR2);
	//TerminerApplication(true);
	return 0;
} //----- fin de main
