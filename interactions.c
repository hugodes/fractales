#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "global.h"
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <glut/glut.h>

void zoom(double degree, long double centreRe, long double centreIm){
    long double ecartRe = (maxRe-minRe)/2;
    long double ecartIm = (maxIm-minIm)/2;
    minRe = centreRe-ecartRe*degree;
    maxRe = centreRe+ecartRe*degree;
    minIm = centreIm-ecartIm*degree;
    maxIm = centreIm+ecartIm*degree;
    if(degree<1){
      nMax+=pasPrecision;
    }else{
      nMax-=pasPrecision;
    }
    rempliTab();
    glutPostRedisplay();
}

void deplacer(long double pasRe, long double pasIm){
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
  case GLUT_KEY_PAGE_UP : 		  
    zoom(1/pasZoom,centreRe,centreIm);
    break;
  case GLUT_KEY_PAGE_DOWN :   
    zoom(pasZoom,centreRe,centreIm);
    break;
  case GLUT_KEY_LEFT :
    deplacer(-pasRe,0);
    break;
  case GLUT_KEY_RIGHT :
    deplacer(pasRe,0);
    break;
  case GLUT_KEY_UP :
    deplacer(0,-pasIm);
    break;
  case GLUT_KEY_DOWN :
    deplacer(0,pasIm);
    break;
  case GLUT_KEY_F2 :
    juliaRe = minRe + (maxRe-minRe)*x/largeur;
    juliaIm = minIm + (maxIm-minIm)*y/hauteur;
    init(2);
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_F1 :
    init(1);
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_END :
    init(fractale);
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_F5 :
    modeCouleur = 1;
    rempliTab();
    glutPostRedisplay();
    break;
  case GLUT_KEY_F6 :
    modeCouleur = 2;
    rempliTab();
    glutPostRedisplay();
    break;
  }
}

void GestionClavier(unsigned char key, int x, int y){
  if(key=='+'){
    nMax+=100;
    rempliTab();
    glutPostRedisplay();
  }else{
    nMax-=100;
    rempliTab();
    glutPostRedisplay();
  }
}

void GestionSouris(int button, int state, int x, int y){
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    long double centreRe = minRe + (maxRe-minRe)*x/largeur;
    long double centreIm = minIm + (maxIm-minIm)*y/hauteur;
    zoom(1/pasZoom,centreRe,centreIm);
  }else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    long double centreRe = minRe + (maxRe-minRe)*x/largeur;
    long double centreIm = minIm + (maxIm-minIm)*y/hauteur;
    zoom(pasZoom,centreRe,centreIm);
  }
}
