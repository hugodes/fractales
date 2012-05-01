#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

int** initTab(int largeur, int hauteur)//Allocation mémoire du tableau
{
	int** t;
	t= malloc(largeur*sizeof(int*));
	for (int i=0; i<largeur; i++) {
		t[i]= malloc(hauteur*sizeof(int));
	}
	return t;
}
void rempliTab(int **t, int largeur, int hauteur, long double minRe, long double maxRe, long double minIm, long double maxIm, int nMax){
//Application du calcul de n pour toutes les cases du tableau

	//Rapports d'échelle en fonction de la taille de l'image
	long double facteur_Re = (maxRe-minRe)/largeur; 
	long double facteur_Im =  (maxIm-minIm)/hauteur;
	//http://stackoverflow.com/questions/7479194/how-to-run-two-child-processes-simultaneously-in-c
	for (int i=0; i<largeur; i++) {
	  long double c_Re=minRe+i*facteur_Re;//partie réelle de c
	  for(int j=0; j<hauteur; j++) {
	    long double c_Im=maxIm+-j*facteur_Im;//partie imaginaire de c
	      t[i][j]=calculNLim(c_Re, c_Im, c_Re, c_Im, 1, nMax);
	  }
	}
}
int calculNLim(long double c_Re, long double c_Im, long double z_Re, long double z_Im, int n, int nLim)
{
  long double z_Re2=z_Re*z_Re;//z_Re²
  long double z_Im2=z_Im*z_Im;//z_Im²

	//la condition est < 4 car on ne prend pas la racine carree
	if (n>nLim-1 || (z_Re2+z_Im2) >4) {
		return n;
	}
	else {
	  long double z1_Re=z_Re2-z_Im2+c_Re;//partie réelle de z(n+1)
	  long double z1_Im=2*z_Re*z_Im+c_Im;//partie imaginaire de z(n+1)
		return calculNLim(c_Re, c_Im, z1_Re, z1_Im, ++n, nLim);
	}
}
void freeTab(int** t, int largeur, int hauteur)
{
	for (int i=0; i<largeur; i++) {
		free(t[i]);
	}
	free(t);
}
