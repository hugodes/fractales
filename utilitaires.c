/*-----------------------------------------------------------------------------------------------
Nom : utilitaires.c
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient les différentes fonctions du module de calcul
de l'ensemble de mandelbrot.
 ---------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "global.h"

int** initTab(int largeur, int hauteur)//Allocation mémoire du tableau
{
	int** t;
	t= malloc(largeur*sizeof(int*));
	for (int i=0; i<largeur; i++) {
		t[i]= malloc(hauteur*sizeof(int));
	}
	return t;
}
void rempliTab(){//Rempli le tableau en fonction de la fractale souhaitée

  long double facteur_Re = (maxRe-minRe)/largeur; 
  long double facteur_Im =  (maxIm-minIm)/hauteur;
  long double px_Re;
  long double px_Im;

  switch(fractale){
  case 1 :
    for (int i=0; i<largeur; i++) {
      px_Re=minRe+i*facteur_Re;//partie réelle de c
      for(int j=0; j<hauteur; j++) {
	px_Im=maxIm+-j*facteur_Im;//partie imaginaire de c
	t[i][j]=calculNLim(px_Re, px_Im,px_Re, px_Im, 1);
      }
    }
    break;
  case 2 :
     for (int i=0; i<largeur; i++) {
      px_Re=minRe+i*facteur_Re;//partie réelle de c
      for(int j=0; j<hauteur; j++) {
	px_Im=maxIm+-j*facteur_Im;//partie imaginaire de c
	t[i][j]=calculNLim(juliaRe, juliaIm,px_Re, px_Im, 0);
      }
    }
     break;
  }
}
//Affiche un tableau 2D dans le terminal
void afficheTab(){
  largeur = 20;
  hauteur = 20;
  t=initTab(largeur,hauteur);
  nMax=99;
  rempliTab();
  printf("\n");
  for(int i=0;i<largeur;i++){
    for(int j=0;j<hauteur;j++){
      if(t[j][i]<=9){
	printf("%i  ",t[j][i]);
      }else{
	printf("%i ",t[j][i]);
      }
    }
    printf("\n");
  }
}

int calculNLim(long double c_Re, long double c_Im, long double z_Re, long double z_Im, int n)
{
  long double z_Re2=z_Re*z_Re;//z_Re²
  long double z_Im2=z_Im*z_Im;//z_Im²

	//la condition est < 4 car on ne prend pas la racine carree
	if (n>nMax-1 || (z_Re2+z_Im2) >4) {
		return n;
	}
	else {
	  long double z1_Re=z_Re2-z_Im2+c_Re;//partie réelle de z(n+1)
	  long double z1_Im=2*z_Re*z_Im+c_Im;//partie imaginaire de z(n+1)
		return calculNLim(c_Re, c_Im, z1_Re, z1_Im, ++n);
	}
}

void freeTab(int largeur, int hauteur)//libere l'espace alloué au tableau
{
	for (int i=0; i<largeur; i++) {
		free(t[i]);
	}
	free(t);
}

void init(int frac){//reinitialise les bornes, la precision, pour la fractale demandée
  minRe = -2.0;
  maxRe = 2.0;
  minIm = -2.0;
  maxIm = 2.0;
  //les bornes sont de nouveaux modifiés en fonction du rapport des dimensions de la fenêtre
  if(largeur>hauteur){
    long double ecart = (maxRe-minRe)*((float)largeur/(float)hauteur-1)/2;
    minRe -= ecart;
    maxRe += ecart;
  }else if(largeur<hauteur){
    long double ecart = (maxIm-minIm)*((float)hauteur/(float)largeur-1)/2;
    minIm-= ecart;
    maxIm+= ecart;
  }
  nMax = 100;
  fractale = frac;
}
