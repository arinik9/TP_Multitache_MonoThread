/*************************************************************************
                           Entree  -  description
                             -------------------
    début                : Mardi 25 Février 2014
    copyright            : (C) 2014 par B3329  
    e-mail               : william.vitali@insa-lyon.fr; nejat.arinik@insa-lyon.fr; niamh.lawlor@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <Entree> (fichier Entree.h) -------
#if ! defined ( Sortie_H )
#define Sortie_H

//------------------------------------------------------------------------
// Rôle de la tâche <Entree>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Configuration.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types



//int numPlaceRecuperee;
//pid_t pidVoiturier;

//extern  int id_fileEntree;
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

	
/*switch(sig){
case SIGINT:
printf("\nControl-C was pressed: mypid = %d, mypgid = %d\n",
getpid(), getpgid(getpid()));
_exit(0);
break;
case SIGCHLD:
printf("\nSIGCHLD. mypid = %d, mypgid = %d\n",
getpid(), getpgid(getpid()));
if(si->si_code == CLD_EXITED || si->si_code == CLD_KILLED){
printf("Process %d is done!\n", si->si_pid);
}
break;
}
*/
//}


// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//
void Sortie(int id_mem, int id_sem, int id_bal);
//
#endif // Sortie_H

