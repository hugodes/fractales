/*-----------------------------------------------------------------------------------------------
Nom : affichage.c
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient les différentes fonctions du module d'affichage
de l'ensemble de Mandelbrot.
 --------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "global.h"
#include "affichage.h"

#ifdef __linux__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <glut/glut.h>
#endif

couleur* tabCouleur;//tableau contenant les couleurs disponibles dans le dégradé
couleur* couleursDegrade;//tableau temporaire utilisé pour créé le précédent
int nbCouleur=0;//nombre de couleurs utilisées pour définir le dégradé final
int nbCouleurDegrade=128;//nombre de couleurs définie par un dégradé entre deux couleurs
int nMaxAffiche=1000;//précision de la méthode d'affichage linéaire

//ici, on a définit les couleurs basiques et celles utilisées
couleur noir = {0.0,0.0,0.0};
couleur blanc = {1.0,1.0,1.0};
couleur bleu = {0.0,0.0,1.0};
couleur jaune = {1.0,1.0,0.0};
couleur rouge = {1.0,0.0,0.0};
couleur vert = {0.0,1.0,0.0};
couleur cyan = {0.0,1.0,1.0};
couleur magenta = {1.0,0.0,1.0};
couleur bleuFonce = {0.0,0.0,0.25};

void initColorTab(){//fonction qui initialise et rempli le tableau de dégradé
  couleursDegrade=malloc(100*sizeof(couleur));  
  
  //----------------------------------------
  /*ici on utilise addCouleur pour chaque couleur que l'on souhaite utiliser
    pour définir le dégradé final*/
  addCouleur(bleuFonce);
  addCouleur(jaune);
  addCouleur(rouge);

  //------------------------------------------

  tabCouleur=malloc(((nbCouleur-1)*nbCouleurDegrade)*sizeof(couleur));
  for(int i=0;i<nbCouleur-1;i++){
    for(int j=0;j<nbCouleurDegrade;j++){
      tabCouleur[nbCouleurDegrade*i+j]=degrade(couleursDegrade[i],couleursDegrade[i+1],(float)j/(float)127);
    }  
  }
  free(couleursDegrade);
}

couleur getColor(int n){//cette fonction retourne la couleur associée à n
  int indC;
  if(n==nMax){
    return noir;
  }else{
    switch(modeCouleur){
    case 1://mode d'affichage proportionnel
      indC = (nbCouleur-1)*(float)nbCouleurDegrade*(float)n/nMax;
      return tabCouleur[indC];
      break;
    case 2 ://mode d'affichage linéaire
      if(n>nMaxAffiche){
	indC=(nbCouleur-1)*nbCouleurDegrade-1;
      }else{
	indC = n*(nbCouleur-1)*nbCouleurDegrade/nMaxAffiche;
      }
      return tabCouleur[indC];
      break;
    case 3 :// LSM/M
      if(n%2==0){
	return bleuFonce;
      }else{
	return blanc;
      }
      break;
    }
  }
}

void draw(){//enclenche le tracé
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0,largeur,0,hauteur, 0, 1);
  glPointSize(1.0);
  glBegin(GL_POINTS);
  for(int i=0;i<largeur;i++){
    for(int j=0;j<hauteur;j++){
      float n=t[i][j];
      drawCouleur(i,j,getColor(n));
    }
  }	
  glEnd();
  glutSwapBuffers();
}

void freeTabColor(){
  free(tabCouleur);
}

couleur degrade(couleur c1, couleur c2, float rapport){//renvoit le dégradé de deux couleurs en fonction du rapport
  couleur c = {c1.rouge+rapport*(c2.rouge-c1.rouge),c1.vert+rapport*(c2.vert-c1.vert),c1.bleu+rapport*(c2.bleu-c1.bleu)};
  return c;
} 

void drawCouleur(int x, int y, couleur c){//dessine un point de couleur c
  glColor3f(c.rouge,c.vert,c.bleu);
  glVertex2i(x,y);
}

void addCouleur(couleur c){//ajoute une couleur c aux tableau définissant le dégradé final
  couleursDegrade[nbCouleur]=c;
  nbCouleur++;
}

void addCouleurf(float rouge, float vert, float bleu){//même, mais avec les composantes RGB directement
  couleur c={rouge,vert,bleu};
  addCouleur(c);
}
