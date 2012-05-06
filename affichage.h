#include <openGL/gl.h>
#include <openGL/glu.h>
#include <glut/glut.h>

typedef struct {
  GLfloat rouge;
  GLfloat vert;
  GLfloat bleu;
} couleur;

void initColorTab();
int getIndColor(int);
couleur getColor(int);
void draw();
void freeTabColor();
couleur degrade(couleur,couleur,float);
void drawCouleur(int,int,couleur);
