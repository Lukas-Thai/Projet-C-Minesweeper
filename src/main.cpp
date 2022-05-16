#include"Demineur.h"

int main() {
	srand(time(NULL)); //initialise la gestion du hasard
	Demineur jeu;
	unsigned int commande;
	cin >> commande;
	switch (commande) {
	case 1:
		cin >> jeu.ligne >> jeu.colonne >> jeu.nb_mines;
		initialiser_jeu(jeu);
	case 2:
		cin >> jeu.ligne >> jeu.colonne >> jeu.nb_mines;
		initialiser_deja_fait(jeu);
		afficher(jeu);
		break;
	case 3:
		cin >> jeu.ligne >> jeu.colonne >> jeu.nb_mines;
		initialiser_deja_fait(jeu);
		verif_victoire(jeu);
		break;
	case 4:
		cin >> jeu.ligne >> jeu.colonne >> jeu.nb_mines;
		initialiser_deja_fait(jeu);
		verif_defaite(jeu);
		break;
	case 5:
		cin >> jeu.ligne >> jeu.colonne;
		initialiser_grille(jeu);
		break;
	}
	detruire(jeu);
	return 0;
}
