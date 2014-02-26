/*************************************************************************
                           XXX  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
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
#include <sys/msg.h>
#include <string.h>
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Clavier.h"
#include "Entree.h"
//#include "Configuration.h"
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
{	//-----Initialisation affichage
	//InitialiserApplication(XTERM);
	//pid_t pidHeure = ActiverHeure();
	
	//-----Initialisation des boîtes aux lettres
	struct msgbuf {
	long type;
	char texte[3];
};
	key_t cleEntree;
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
	msgbuf messageEntree;
	messageEntree.type=1;
	strcpy(messageEntree.texte, "OH");
	tailleEntree=strlen(messageEntree.texte);
	msgsnd(id_fileEntree, &messageEntree, tailleEntree+1, 0);
	//msgsnd(id_fileEntree, &messageEntree, tailleEntree+1, 0);

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

