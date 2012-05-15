/*-----------------------------------------------------------------------------------------------
Nom : interactions.h
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient les définitions des fonctions du fichier source interactions.c
 --------------------------------------------------------------------------------------------- */
#ifndef INTERACTIONS_H
#define INTERACTIONS_H

void zoom(double, long double, long double);
void deplacer(long double, long double);
void GestionSpecial(int,int,int);
void GestionClavier(unsigned char, int, int);
void GestionSouris(int,int,int,int);

#endif
