#ifndef GLOBAL_H
#define GLOBAL_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

extern int** t;          //Tableau
extern int largeur;      //Largeur de la fenêtre
extern int hauteur;      //Hauteur de la fenêtre
extern char* nom;        //Nom de la fenêtre

extern int nMax;    //Itérations maximales du calcul récursif

//Bornes de l'ensemble de complexe à traiter
extern long double minRe;
extern long double maxRe;
extern long double minIm;
extern long double maxIm;
//Complexe associé à l'ensemble de Julia
extern long double juliaRe;
extern long double juliaIm;

extern int fractale; //variable d'état (1 pour Mandelbrot, 2 pour Julia)
extern int modeCouleur; //variable d'état (1 pour RVB, 2 pour LSM/M)

extern float pasZoom;//puissance du zoom
extern int pasPrecision;//modification de la précision (nMax)

#endif

