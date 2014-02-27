/*************************************************************************
                           Configuration.cpp  -  description
                             -------------------
<<<<<<< HEAD
    début                : Mardi 25 Février 2014  
=======
    début                : Mardi 25 Février 2014
>>>>>>> Lecture-Ecriture Dans la Memoire Partagée
    copyright            : (C) 2014 par B3329
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Configuration.cpp> (fichier Configuration.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "Configuration.h"
//
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
int creerSegment(int size, char *name, int cle){
// Algorithme :
//
	int shmid ; // l'identificateur de la memoire partagee 
	key_t clef ; // la clef associee au segment

	/* L'instruction ftok(name,(key_t) cle) permet de construire 
	une cle identifiant le segment */
	clef = ftok(name,(key_t) cle) ;
  

	/* L'instruction IPC_CREAT|IPC_EXCL|SHM_R|SHM_W permet d'indiquer 
	les droits d'acces de ce segment de memoire */


	shmid = shmget( clef, size, IPC_CREAT|IPC_EXCL|SHM_R|SHM_W ) ;
	if ( shmid== -1 ) {
		perror("La creation du segment de memoire partage a echouee") ;
		exit(1) ; // on laisse tout tomber et on sort du programme
	}

	printf("l'identificateur du segment est %d \n",shmid) ;
	printf("ce segment est associe a la clef %d \n",clef) ;

	return shmid ;
}//----- fin de creerSegment

void afficherInfoSegment(int shmid) {
// Algorithme :
//
	struct shmid_ds buf ;

	if (shmctl(shmid,IPC_STAT,&buf) == -1){
		perror("Erreur lors de l'utilsation de infoSegment") ;
		exit(1) ;
	}

	printf("Affichage des champs de controles\n") ;
	printf("identificateur du proprietaire : %d\n",buf.shm_perm.uid) ;
	printf("identificateur du groupe du proprietaire : %d\n",buf.shm_perm.gid) ;
	printf("identificateur du createur : %d\n",buf.shm_perm.cuid) ;
	printf("identificateur du groupe du createur : %d\n",buf.shm_perm.cgid) ;
	printf("mode d'acces : %d\n",buf.shm_perm.mode) ;
	printf("taille du segment : %d\n",buf.shm_segsz) ;
}//----- fin de afficherInfoSegment

void detruireSegment(int shmid) {
// Algorithme :
//
	if (shmctl(shmid,IPC_RMID,NULL) == -1){
		perror("Erreur lors de la destruction") ;
		exit(1) ;
	}
}//----- fin de detruireSegment
<<<<<<< HEAD
=======

>>>>>>> Lecture-Ecriture Dans la Memoire Partagée
