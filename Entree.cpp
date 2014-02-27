/*************************************************************************
                           Entree.cpp  -  description
                             -------------------
    début                : Mardi 25 Février 2014
<<<<<<< HEAD
    copyright            : (C) 2014 par B3329  
=======
    copyright            : (C) 2014 par B3329
>>>>>>> Lecture-Ecriture Dans la Memoire Partagée
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
#include "Configuration.h"

//
//------------------------------------------------------ Include personnel
#include "Entree.h"
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

void Entree ()
// Algorithme :
//
{
	extern int shmid;
	char *mem ;
	int flag = 0 ;
	printf("Je commence par m'attacher le segment de memoire Entree.cpp\n") ;
	mem = (char*)shmat(shmid,0,flag) ;
    
	if (mem ==(char*)-1){
	perror("attachement impossible") ;
	exit(1) ;
	}
	printf("je vais afficher un message que mon fils a ecrit\n") ;
	printf("%s\n",mem) ;
	
	detruireSegment(shmid) ;


	/*int id_file, read, nb;
	key_t cle;
	//Création d'une clé
	cle= ftok("fileEntree",1);
 
	//Création d'une file (avec IPC_CREAT: crée si la clé n'existe pas déja)
	id_file= msgget(cle, 0666|IPC_CREAT);

    	if (id_file == -1){
        	cout << "Erreur creation de file\n" << endl;
		exit(EXIT_FAILURE);
	}
 
	nb=0;
	msgbuff message;
        read= msgrcv(id_file, &message, 1000, 1, 0);

	if (read == -1){
        	perror("Erreur de lecture dans la file\n");
		exit(EXIT_FAILURE);
	}
        nb++;
        printf("Message %d: (type=%ld) %s\n",nb, message.type, message.texte); 

	*/
} //----- fin de Entree
