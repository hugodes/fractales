/*-----------------------------------------------------------------------------------------------
Nom : interactions.c
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient les différentes fonctions du module d'interactions avec l'image.
 ---------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "global.h"

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


void zoom(double degree, long double centreRe, long double centreIm){
  //permet de zoomer sur un point défini par les deux derniers paramètres
    long double ecartRe = (maxRe-minRe)/2;
    long double ecartIm = (maxIm-minIm)/2;
    minRe = centreRe-ecartRe*degree;
    maxRe = centreRe+ecartRe*degree;
    minIm = centreIm-ecartIm*degree;
    maxIm = centreIm+ecartIm*degree;
    if(degree<1){
      nMax+=pasPrecision;
    }else{
      if(nMax>=55){//on limite le retrait de précision (précision négative = erreur de segmentation)
	nMax-=pasPrecision;
      }
    }
    rempliTab();
    glutPostRedisplay();
}

void deplacer(long double pasRe, long double pasIm){//deplacement multidirectionnel
  minRe = minRe+pasRe;
  maxRe = maxRe+pasRe;
  minIm = minIm+pasIm;
  maxIm = maxIm+pasIm;
  rempliTab();
  glutPostRedisplay();
}

void GestionSpecial(int key, int x, int y){
    long double centreRe = (minRe+maxRe)/2;
    long double centreIm = (minIm+maxIm)/2;
    long double pasRe = (maxRe-minRe)*100/largeur;
    long double pasIm = (maxIm-minIm)*100/hauteur;
  switch(key){
  case GLUT_KEY_PAGE_UP : //zoom avant		  
    zoom(1/pasZoom,centreRe,centreIm);
    break;
  case GLUT_KEY_PAGE_DOWN :  //zoom arrière 
    zoom(pasZoom,centreRe,centreIm);
    break;
  case GLUT_KEY_LEFT : //déplacement gauche
    deplacer(-pasRe,0);
    break;
  case GLUT_KEY_RIGHT : //déplacement droite
    deplacer(pasRe,0);
    break;
  case GLUT_KEY_UP : //déplacement haut
    deplacer(0,-pasIm);
    break;
  case GLUT_KEY_DOWN : // déplacement bas
    deplacer(0,pasIm);
    break;
  case GLUT_KEY_F2 : //Affichage de l'ensemble de Julia du point visé par la souris
    juliaRe = minRe + (maxRe-minRe)*x/largeur;
    juliaIm = minIm + (maxIm-minIm)*y/hauteur;
    init(2);
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_F1 : //affichage par défaut du programme
    init(1);
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_END : //réinitialisation du zoom de la fractale en cours
    init(fractale);
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_F5 : //couleur proportionnelle
    modeCouleur = 1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F6 : //couleur linéaire
    modeCouleur = 2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F7 : //LSM/M - couleur selon la parité de l'itération
    modeCouleur = 3;
    glutPostRedisplay();
    break;
  }
}

void GestionClavier(unsigned char key, int x, int y){
  //modification manuelle de la précision
  if(key=='+'){
    nMax+=50;
    rempliTab();
    glutPostRedisplay();
  }else{
    if(nMax>=80){
      nMax-=50;
      rempliTab();
      glutPostRedisplay();
    }
  }
}

void GestionSouris(int button, int state, int x, int y){
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    //zoom avant
    long double centreRe = minRe + (maxRe-minRe)*x/largeur;
    long double centreIm = minIm + (maxIm-minIm)*y/hauteur;
    zoom(1/pasZoom,centreRe,centreIm);
  }else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    //zoom arrière
    long double centreRe = minRe + (maxRe-minRe)*x/largeur;
    long double centreIm = minIm + (maxIm-minIm)*y/hauteur;
    zoom(pasZoom,centreRe,centreIm);
  }
}
