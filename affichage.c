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


couleur* tabCouleur;
couleur* couleursDegrade;
int nbCouleur=0;
int nbCouleurDegrade=0;
couleur noir = {0.0,0.0,0.0};
couleur blanc = {1.0,1.0,1.0};
couleur bleu = {0.0,0.0,1.0};
couleur jaune = {1.0,1.0,0.0};
couleur rouge = {1.0,0.0,0.0};
couleur vert = {0.0,1.0,0.0};
couleur cyan = {0.0,1.0,1.0};
couleur magenta = {1.0,0.0,1.0};
couleur bleuFonce = {0.0,0.0,0.25};

void initColorTab(){
  couleursDegrade=malloc(100*sizeof(couleur));  
  
  addCouleur(rouge);
  addCouleur(bleuFonce);
  addCouleur(blanc);
  addCouleur(rouge);
  addCouleur(bleuFonce);
  addCouleur(blanc);
  addCouleur(rouge);
  addCouleur(bleuFonce);
  addCouleur(blanc);

  tabCouleur=malloc((nbCouleurDegrade)*sizeof(couleur));
  for(int i=0;i<nbCouleur-1;i++){
    for(int j=0;j<128;j++){
      tabCouleur[128*i+j]=degrade(couleursDegrade[i],couleursDegrade[i+1],(float)j/(float)127);
    }  
  }
  free(couleursDegrade);
}

couleur getColor(int n){
  int indC;
  if(n==nMax){
    return noir;
  }else{
    switch(modeCouleur){
    case 1:
      indC = nbCouleurDegrade*(float)n/nMax;
      return tabCouleur[indC];
      break;
    case 2 :
      indC = n*nbCouleurDegrade/500;
      return tabCouleur[indC];
      break;
    case 3 :
      if(n%2==0){
	return bleuFonce;
      }else{
	return blanc;
      }
      break;
    }
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

void addCouleur(couleur c){
  couleursDegrade[nbCouleur]=c;
  nbCouleur++;
  nbCouleurDegrade=(nbCouleur-1)*128;
}
