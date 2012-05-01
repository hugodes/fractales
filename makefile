comp : main.c utilitaires.c display.c
	gcc -std=c99 -lm -o mandel main.c utilitaires.c display.c -lglut -lGLU -lGL
