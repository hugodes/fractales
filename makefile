comp : main.c utilitaires.c display.c
	gcc -std=c99 -lm -framework OpenGL -framework Cocoa -framework GLUT -o mandel main.c utilitaires.c display.c
