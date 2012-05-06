mac : main.c utilitaires.c
	gcc -std=c99 -lm -framework OpenGL -framework Cocoa -framework GLUT -o mandel main.c utilitaires.c affichage.c interactions.c
linux : main.c utilitaires.c interactions.c affichage.c
	gcc -std=c99 -lm -o mandel main.c utilitaires.c affichage.c interactions.c -lglut -lGLU -lGL
