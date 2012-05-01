#ifndef UTILITAIRES_H
#define UTILITAIRES_H
//On alloue dynamiquement l'espace pour ce tableau.
int** initTab(int, int);
//On rempli le tableau avec le rang n pour le quel Zn > 2
void rempliTab(int**, int, int, long double, long double, long double, long double, int);
//Calcule pour un immaginaire donné le n pour lequel Zn >2
int calculNLim(long double, long double, long double, long double, int, int);
//Libere l'espace alloué pour le tableau
void freeTab(int**, int, int);
//affiche un tableau à deux dimensions
void affichTab2D(int**, int, int);
#endif
