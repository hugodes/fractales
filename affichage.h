/*-----------------------------------------------------------------------------------------------
Nom : affichage.h
Auteurs : Pierre-Alexandre Cimbé, Hugo des Longchamps, Ahmed Rafik
Projet : Coloration, fractales, ensemble de Mandelbrot
-------------------------------------------------------------------------------------------------
Spécificités : Ce fichier contient les définitions des fonctions du fichier source affichage.h
 --------------------------------------------------------------------------------------------- */

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

//structure couleur utilisée pour l'affichage
typedef struct {
  float rouge;
  float vert;
  float bleu;
} couleur;

void initColorTab();
couleur getColor(int);
void draw();
void freeTabColor();
couleur degrade(couleur,couleur,float);
void drawCouleur(int,int,couleur);
void addCouleur(couleur);
void addCouleurf(float,float,float);
