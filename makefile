comp : main.c utilitaires.c interactions.c affichage.c
	gcc -std=c99 -lm -o mandel main.c utilitaires.c affichage.c interactions.c -lglut -lGLU -lGL
