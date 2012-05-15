/*-----------------------------------------------------------------------------------------------
Nom : main.c
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient la fonction main de l'application. Il initialise OpenGl et 
fait appel aux différents module du programme afin de générer l'affichage initial.
 ---------------------------------------------------------------------------------------------- */

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

//-------------------------------------------------------------------
/* Les 2 fonctions suivantes servent à afficher un mandelbrot en ascii art sur le terminal */

void afficheAsciiMandel(){
  fractale = 1;
  afficheTab();
}

void afficheAsciiJulia(){
  fractale=2;
  juliaRe = -0.5;
  juliaIm = 0.5;
  afficheTab();
}
//-----------------------------------------------------------------------

int main(int argc, char **argv, char **env) {
  //selon les arguments, ascii ou affichage 
  if ((argc == 2) && (atoi(argv[1])==0)){
    afficheAsciiMandel();
  }
  else if ((argc == 2) && (atoi(argv[1])==1)){
    afficheAsciiJulia();
  }
  else if (argc == 3) {

    //Dimensions de l'image en pixels
    largeur = atoi(argv[1]);
    hauteur = atoi(argv[2]);
    //Nom de la fenêtre
    nom="Mandelbrot";
    //le code suivant permet de modifier les bornes pour garder un affichage proportionné de l'ensemble dans le cas où largeur et hauteur sont différentes.
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
