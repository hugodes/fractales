#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "global.h"
#include "affichage.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

couleur* tabCouleur;
int nbCouleur = 10;
int nbCouleurDegrade = 9*128;

void initColorTab(){
  couleur* couleursDegrade=malloc(nbCouleur*sizeof(couleur));  
  couleur noir = {0.0,0.0,0.0};
  couleur blanc = {1.0,1.0,1.0};
  couleur bleu = {0.0,0.0,1.0};
  couleur jaune = {1.0,1.0,0.0};
  couleur rouge = {1.0,0.0,0.0};
  couleur vert = {0.0,1.0,0.0};
  couleur cyan = {0.0,1.0,1.0};
  couleur magenta = {1.0,0.0,1.0};

  couleur bleuFonce = {0.0,0.0,0.25};
  couleur orange = {1.0,0.5,0.0};
  
  couleursDegrade[0] = rouge;
  couleursDegrade[1] = bleuFonce;
  couleursDegrade[2] = blanc;
  couleursDegrade[3] = rouge;
  couleursDegrade[4] = bleuFonce;
  couleursDegrade[5] = blanc;
  couleursDegrade[6] = rouge;
  couleursDegrade[7] = bleuFonce;
  couleursDegrade[8] = rouge;
  couleursDegrade[9] = bleuFonce;

  tabCouleur=malloc((nbCouleurDegrade+2)*sizeof(couleur));
  tabCouleur[0]=noir;
  tabCouleur[1]=blanc;
  for(int i=0;i<nbCouleur-1;i++){
    for(int j=0;j<128;j++){
      tabCouleur[128*i+j+2]=degrade(couleursDegrade[i],couleursDegrade[i+1],(float)j/(float)127);
    }  
  }
  free(couleursDegrade);
}

int getIndColor(int n){
  int indC;
  if(n==nMax){
    return 0;
  }else{
    indC = 2+nbCouleurDegrade*(float)n/nMax;
    return indC;
  }
}

couleur getColor(int n){
    switch(modeCouleur){
    case 1:
      return tabCouleur[getIndColor(n)];
      break;
    case 2 :
      if(n==nMax){
	return tabCouleur[0];
      }else if(n%2==0){
	return tabCouleur[200];
      }else{
	return tabCouleur[50];
      }
      break;
    }
}

void draw(){
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

couleur degrade(couleur c1, couleur c2, float rapport){
  couleur c = {c1.rouge+rapport*(c2.rouge-c1.rouge),c1.vert+rapport*(c2.vert-c1.vert),c1.bleu+rapport*(c2.bleu-c1.bleu)};
  return c;
} 

void drawCouleur(int x, int y, couleur c){
  glColor3f(c.rouge,c.vert,c.bleu);
  glVertex2i(x,y);
}
