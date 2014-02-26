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
//------------------------------------------------------ Include personnel
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
pid_t Heure = ActiverHeure();
sleep(5);
kill(Heure, SIGUSR2);
TerminerApplication(true);
return 0;
} //----- fin de main

