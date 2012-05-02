#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "display.h"
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <glut/glut.h>
#include <math.h>

int** t;//tableau
int largeur;//largeur de l'image
int hauteur;//longueur de l'image
char* nom;//nom de la fenêtre
int nMax=60;//nmax (le commentaire utile xD)
int preci=2;
long double minRe = -2.5;
long double maxRe = 1.5;
long double minIm = -2.0;
long double maxIm = 2.0; 
long double pas = 0.5;

//-------------FONCTION DRAW + getColor A SEPARER DANS UN AUTRE FICHIER-------------
GLfloat* getColor(float n){
  GLfloat* vect= malloc(3);
  GLfloat nMaxf = nMax;
  if(n==nMaxf){
    for(int i=0;i<3;i++){
      vect[i]=0.0;
    }
  } else if(n<=nMaxf/2){
    vect[0]=n*2/nMaxf;
    vect[1]=n*2/nMaxf;
    vect[2]=1 - n*2/nMaxf;
  } else {
    vect[0]=1.0;
    vect[1]=1-(n-nMaxf/2)*2/nMaxf;
    vect[2]=0.0;
  }
  return vect;
}


void draw(){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(minRe, maxRe, minIm, maxIm, 0, 0);
  glPointSize(1.0);
  glBegin(GL_POINTS);
  glColor3f(0.0,0.0,0.0);
  float miLarg=largeur;
  float miHaut=hauteur;
  miLarg/=2;
  miHaut/=2;
  for(int i=0;i<largeur;i++){
    for(int j=0;j<hauteur;j++){
      float x;
      float y;
      x=(i-miLarg)/miLarg;
      y=(j-miHaut)/miHaut;
      float n=t[i][j];
      GLfloat* vect =getColor(n);
      glColor3fv(vect);
      glVertex2f(x,y);
      free(vect);
    }	
  }
  glEnd();
  glutSwapBuffers();
}

void GestionClavier(int key, int x, int y){
    long double centreRe = (minRe+maxRe)/2;
    long double centreIm = (minIm+maxIm)/2;
    long double ecartRe = maxRe-minRe;
    long double ecartIm = maxIm-minIm;
    long double pasRe = (maxRe-minRe)*100/largeur;
    long double pasIm = (maxIm-minIm)*100/hauteur;
  switch(key){
  case GLUT_KEY_PAGE_UP : 		  
    minRe = centreRe-(ecartRe)/3;
    maxRe = centreRe+(ecartRe)/3;
    minIm = centreIm-(ecartIm)/3;
    maxIm = centreIm+(ecartIm)/3;
    preci+=1;
    nMax+=preci;
    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
				
    glutPostRedisplay();
    break;
  case GLUT_KEY_PAGE_DOWN :   
    minRe = centreRe-(ecartRe)*0.75;
    maxRe = centreRe+(ecartRe)*0.75;
    minIm = centreIm-(ecartIm)*0.75;
    maxIm = centreIm+(ecartIm)*0.75;
    preci-=1;
    nMax+=preci;
    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);

    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT :
    minRe = minRe-pasRe;
    maxRe = maxRe-pasRe;
    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT :
    minRe = minRe+pasRe;
    maxRe = maxRe+pasRe;
    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
    glutPostRedisplay();
    break;
  case GLUT_KEY_UP :
    minIm = minIm-pasIm;
    maxIm = maxIm-pasIm;
    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN :
    minIm = minIm+pasIm;
    maxIm = maxIm+pasIm;
    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
    glutPostRedisplay();
    break;
  }
}

  void GestionSouris(int button, int state, int x, int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
      long double midZoomRe = minRe + (maxRe-minRe)*x/largeur;
      long double midZoomIm = minIm + (maxIm-minIm)*y/hauteur;
      long double ecartRe = maxRe-minRe;
      long double ecartIm = maxIm-minIm;

      minRe = midZoomRe-(ecartRe)/3;
      maxRe = midZoomRe+(ecartRe)/3;
      minIm = midZoomIm-(ecartIm)/3;
      maxIm = midZoomIm+(ecartIm)/3;
      preci+=1;
      nMax+=preci;
      rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
				
    glutPostRedisplay();
    }else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
      long double midZoomRe = minRe + (maxRe-minRe)*x/largeur;
      long double midZoomIm = minIm + (maxIm-minIm)*y/hauteur;
      long double ecartRe = maxRe-minRe;
      long double ecartIm = maxIm-minIm;

      minRe = midZoomRe-(ecartRe)*0.75;
      maxRe = midZoomRe+(ecartRe)*0.75;
      minIm = midZoomIm-(ecartIm)*0.75;
      maxIm = midZoomIm+(ecartIm)*0.75;
      preci-=1;
      nMax+=preci;
      rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);
    }
  }
  
//----------------------------------------------------------------------

int main(int argc, char **argv, char **env) {

  if (argc == 3) {

    //Dimensions de l'image en pixels
    largeur = atoi(argv[1]);
    hauteur = atoi(argv[2]);
    //Nom de la fenêtre
    nom="Mandelbrot";
    long double hauteurf = hauteur;
    long double largeurf = largeur;
    if(largeur>hauteur){
      long double ecart = (maxRe-minRe)*(largeurf/hauteurf-1)/2;
      minRe -= ecart;
      maxRe += ecart;
    }else if(largeur<hauteur){
      long double ecart = (maxIm-minIm)*(hauteurf/largeurf-1)/2;
      minIm-= ecart;
      maxIm+= ecart;
    }


    t=initTab(largeur, hauteur);

    rempliTab(t, largeur, hauteur, minRe, maxRe, minIm, maxIm, nMax);//Remplissage du tableau

    //------------------------------------TESTS OPENGL---------------------------------------
	
    glutInit(&argc,argv);
    glutInitWindowPosition(0,0);//initialisation de la fenêtre
    glutInitWindowSize(largeur,hauteur);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(nom);
    glutDisplayFunc(draw);
    glutReshapeFunc(draw);
    glutSpecialFunc(GestionClavier);
    glutMouseFunc(GestionSouris);
    glutMainLoop();
    glFlush();
	
    //---------------------------------------------------------------------------------------

    freeTab(t, largeur, hauteur);//Libération de la mémoire allouée -- fin du programme
  }
  else {
    printf("Il faut lancer le programme avec 2 arguments:\n1)La largeur de l'image en pixels\n2)La longueur de l'image en pixels\n");
    printf("Arrêt du programme\n");
  }
  return 0;
}
