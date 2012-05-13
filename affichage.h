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


typedef struct {
  GLfloat rouge;
  GLfloat vert;
  GLfloat bleu;
} couleur;

void initColorTab();
couleur getColor(int);
void draw();
void freeTabColor();
couleur degrade(couleur,couleur,float);
void drawCouleur(int,int,couleur);
void addCouleur(couleur);
void addCouleurf(float,float,float);
