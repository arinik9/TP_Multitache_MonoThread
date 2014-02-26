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
//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Clavier.h"
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
	InitialiserApplication(XTERM);
	pid_t pidHeure = ActiverHeure();
	pid_t pidClavier = fork();
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
	}	
	kill(pidHeure, SIGUSR2);
	TerminerApplication(true);
	return 0;
} //----- fin de main

