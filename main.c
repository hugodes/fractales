#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "interactions.h"
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

#include <math.h>

int** t;          //Tableau
int largeur;      //Largeur de la fenêtre
int hauteur;      //Hauteur de la fenêtre
char* nom;        //Nom de la fenêtre

int nMax = 100;    //Itérations maximales du calcul récursif

//Bornes de l'ensemble de complexe à traiter
long double minRe = -2.0;
long double maxRe = 2.0;
long double minIm = -2.0;
long double maxIm = 2.0;
//Complexe associé à l'ensemble de Julia
long double juliaRe = 0.0;
long double juliaIm = 0.0;

int fractale = 1; //variable d'état (1 pour Mandelbrot, 2 pour Julia)
int modeCouleur = 1; //variable d'état (1 pour RVB, 2 pour LSM/M)

float pasZoom = 1.5;//puissance du zoom;
int pasPrecision = 25;//modification de la précision (nMax)

void afficheAscii(){
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


int main(int argc, char **argv, char **env) {
  if ((argc == 2) && (atoi(argv[1])==0)){
    afficheAscii();
  }else if (argc == 3) {

    //Dimensions de l'image en pixels
    largeur = atoi(argv[1]);
    hauteur = atoi(argv[2]);
    //Nom de la fenêtre
    nom="Mandelbrot";
    if(largeur>hauteur){
      GLdouble ecart = (maxRe-minRe)*((double)largeur/(double)hauteur-1)/2;
      minRe -= ecart;
      maxRe += ecart;
    }else if(largeur<hauteur){
      GLdouble ecart = (maxIm-minIm)*((double)hauteur/(double)largeur-1)/2;
      minIm-= ecart;
      maxIm+= ecart;
    }


    t=initTab(largeur, hauteur);

    rempliTab();//Remplissage du tableau

    //------------------------------------INITIALISATION OPENGL---------------------------------------
	
    glutInit(&argc,argv);
    glutInitWindowPosition(0,0);//initialisation de la fenêtre
    glutInitWindowSize(largeur,hauteur);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(nom);
    glutDisplayFunc(draw);
    glutReshapeFunc(draw);
    glutSpecialFunc(GestionSpecial);
    glutMouseFunc(GestionSouris);
    glutKeyboardFunc(GestionClavier);
    initColorTab();
    glutMainLoop();
	
    //---------------------------------------------------------------------------------------

    freeTab(largeur, hauteur);//Libération de la mémoire allouée -- fin du programme
    freeTabColor();
  }
  else {
    printf("Il faut lancer le programme avec 2 arguments:\n1)La largeur de l'image en pixels\n2)La longueur de l'image en pixels\n");
    printf("Arrêt du programme\n");
  }
  return 0;
}
