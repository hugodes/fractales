#ifndef UTILITAIRES_H
#define UTILITAIRES_H
//On alloue dynamiquement l'espace pour ce tableau.
int** initTab(int, int);
//On rempli le tableau avec le rang n pour le quel Zn > 2
void rempliTab();
//Calcule pour un immaginaire donné le n pour lequel Zn >2
int calculNLim(long double, long double, long double, long double, int);
//Libere l'espace alloué pour le tableau
void freeTab(int, int);
void init(int);
void *CalculNCol(void *threadid);
#endif
