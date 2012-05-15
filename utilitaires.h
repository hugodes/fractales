/*-----------------------------------------------------------------------------------------------
Nom : utilitaires.h
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient la définition des fonctions du fichier source utilitaires.c
 ---------------------------------------------------------------------------------------------- */

#ifndef UTILITAIRES_H
#define UTILITAIRES_H
//On alloue dynamiquement l'espace pour ce tableau.
int** initTab(int, int);
//On rempli le tableau avec le rang n pour le quel Zn > 2
void rempliTab();
//Affiche un tableau 2D dans le terminal
void afficheTab();
//Calcule pour un immaginaire donné le n pour lequel Zn >2
int calculNLim(long double, long double, long double, long double, int);
//Libere l'espace alloué pour le tableau
void freeTab(int, int);
//reinitialise les bornes à leur valeur initiale
void init(int);
void *CalculNCol(void *threadid);
#endif
