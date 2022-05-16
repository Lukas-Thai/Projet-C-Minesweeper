#include "Demineur.h"

void deposer_mine(Demineur& jeu) {
	for (unsigned int i = 0; i < jeu.nb_mines; ++i) {
		jeu.tableau[i].mine = true;
	}
	for (int i = 0; i < jeu.taille * 3; ++i) {
		Case temp;
		unsigned int a = rand() % jeu.taille;
		unsigned int b = rand() % jeu.taille;
		temp = jeu.tableau[b];
		jeu.tableau[b] = jeu.tableau[a];
		jeu.tableau[a] = temp;
	}
	for (int i = 0; i < jeu.taille; ++i) {
		if (jeu.tableau[i].mine == true) {
			cout << " " << i;
		}
	}
	cout << endl;
}


void revele(Demineur& jeu, unsigned int position) {
	int position_adjacente[nb_case_adja] = { -jeu.colonne - 1,-jeu.colonne,-jeu.colonne + 1,-1,+1,jeu.colonne - 1,jeu.colonne,jeu.colonne + 1 };
	if (jeu.tableau[position].mine == true) {
		jeu.etat_jeu = GAME_LOST;
	}
	else if (jeu.tableau[position].detection == 0 && jeu.tableau[position].revele == false) {
		jeu.tableau[position].revele = true;
		for (unsigned int j = 0; j < nb_case_adja; ++j) {
			int place_chercher = position + position_adjacente[j];
			if (jeu.tableau[place_chercher].revele == true) {
				continue;
			}
			else if (position % jeu.colonne == 0 && (j == 0 || j == 3 || j == 5)) {
				continue;
			}
			else if (((position + 1) % jeu.colonne == 0) && (j == 2 || j == 4 || j == 7)) {
				continue;
			}
			if (place_chercher >= 0 && place_chercher < jeu.taille) {
				revele(jeu, place_chercher);
			}
		}
	}
	else {
		jeu.tableau[position].revele = true;
	}
}


void detection_mine(Demineur& jeu) {
	int position_adjacente[nb_case_adja] = { -jeu.colonne - 1,-jeu.colonne,-jeu.colonne + 1,-1,+1,jeu.colonne - 1,jeu.colonne,jeu.colonne + 1 };
	for (int i = 0; i < jeu.taille; ++i) {
		unsigned char nb_detecte = 0;
		if (jeu.tableau[i].mine == false) {
			for (unsigned int j = 0; j < nb_case_adja; ++j) {
				int place_chercher = i + position_adjacente[j];
				if (place_chercher >= 0 && place_chercher < jeu.taille) {
					if (i % jeu.colonne == 0 && (j == 0 || j == 3 || j == 5)) {
						continue;
					}
					else if (((i + 1) % jeu.colonne == 0) && (j == 2 || j == 4 || j == 7)) {
						continue;
					}
					if (jeu.tableau[place_chercher].mine == true) {
						nb_detecte++;
					}
				}
			}
		}
		jeu.tableau[i].detection = nb_detecte;
	}
}


void jouer_coup(Demineur& jeu, char type_coup, int position) {
	if (type_coup == 'D') {
		if (position < jeu.taille && jeu.tableau[position].revele == false) {
			revele(jeu, position);
		}
	}
	else if (type_coup == 'M') {
		if (position < jeu.taille && jeu.tableau[position].mine == false) {
			jeu.etat_jeu = GAME_LOST;
			jeu.tableau[position].marque = true;
		}
		else if (position < jeu.taille && jeu.tableau[position].mine == true) {
			jeu.tableau[position].marque = true;
		}
	}
}

void initialiser_jeu(Demineur& jeu) {
	jeu.taille = jeu.colonne * jeu.ligne;
	jeu.etat_jeu = IN_PROGRESS;
	Case* tab = new Case[jeu.taille];
	Case tuile;
	tuile.mine = false;
	tuile.revele = false;
	tuile.marque = false;
	for (int i = 0; i < jeu.taille; ++i) {
		tab[i] = tuile;
	}
	jeu.tableau = tab;
	cout << jeu.ligne << " " << jeu.colonne << " " << jeu.nb_mines;
	deposer_mine(jeu);
	detection_mine(jeu);
}


void initialiser_deja_fait(Demineur& jeu) {
	jeu.etat_jeu = IN_PROGRESS;
	jeu.taille = jeu.ligne * jeu.colonne;
	unsigned int nb_coup;
	unsigned int position;
	char type_coup;
	Case* tab = new Case[jeu.taille];
	Case tuile;
	tuile.mine = false;
	tuile.revele = false;
	tuile.marque = false;
	for (int i = 0; i < jeu.taille; ++i) {
		tab[i] = tuile;
	}
	jeu.tableau = tab;
	unsigned int pos_mine;
	for (unsigned int i = 0; i < jeu.nb_mines; ++i) {
		cin >> pos_mine;
		jeu.tableau[pos_mine].mine = true;
	}
	detection_mine(jeu);
	cin >> nb_coup;
	for (unsigned int i = 0; i < nb_coup; ++i) {
		cin >> type_coup >> position;
		jouer_coup(jeu, type_coup, position);
	}
}


void verif_victoire(Demineur& jeu) {
	for (int i = 0; i < jeu.taille; ++i) {
		if (jeu.tableau[i].mine == false && jeu.tableau[i].revele == false) {
			break;
		}
		else if (i == jeu.taille - 1) {
			jeu.etat_jeu = GAME_WON;
		}
	}
	if (jeu.etat_jeu == GAME_WON) {
		cout << "game won" << endl;
	}
	else {
		cout << "game not won" << endl;
	}
}


void verif_defaite(const Demineur& jeu) {
	if (jeu.etat_jeu == GAME_LOST) {
		cout << "game lost" << endl;
	}
	else {
		cout << "game not lost" << endl;
	}
}


void choix_affichage(const Demineur& jeu, unsigned int position, char str[]) {
	if (jeu.etat_jeu != IN_PROGRESS && jeu.tableau[position].mine == true) {
		strcpy(str, "m");
	}
	else if (jeu.tableau[position].marque == true) {
		strcpy(str, "x");
	}
	else if (jeu.tableau[position].revele == true && jeu.tableau[position].detection != 0) {
		sprintf(str, "%d", jeu.tableau[position].detection);
	}
	else if (jeu.tableau[position].revele == false) {
		strcpy(str, ".");
	}
	else {
		strcpy(str, " ");
	}
}


void afficher(const Demineur& jeu) {
	unsigned int nb_ligne_console = (jeu.ligne * 2) + 1;
	unsigned int compteur = 0;
	cout << jeu.ligne << " " << jeu.colonne << endl;
	for (unsigned int i = 0; i < nb_ligne_console; ++i) {
		if (i % 2 == 1) {
			cout << "|";
		}
		for (int j = 0; j < jeu.colonne; ++j) {
			if (i % 2 == 0) {
				cout << " ---";
			}
			else {
				char affichage[2];
				choix_affichage(jeu, compteur, affichage);
				++compteur;
				cout << " " << affichage << " ";
				cout << "|";
			}
		}
		cout << endl;
	}
}


void passe1(Demineur& jeu, const int position, unsigned int& nb_detecte, unsigned int& nb_mine, const int position_adjacente[]) {
	for (int j = 0; j < 8; ++j) {
		if (position % jeu.colonne == 0 && (j == 0 || j == 3 || j == 5)) {
			continue;//La case n'existe pas
		}
		else if (((position + 1) % jeu.colonne == 0) && (j == 2 || j == 4 || j == 7)) {
			continue;//La case n'existe pas
		}
		if (position + position_adjacente[j] < jeu.taille && position + position_adjacente[j] >= 0) {
			if (jeu.tableau[position + position_adjacente[j]].revele == false) { //Si les cases autours n'ont pas été révélées. On rajoute 1 au nombre de case détecté
				nb_detecte += 1;
			}
			if (jeu.tableau[position + position_adjacente[j]].marque == true) { //Si les cases autours ont été marqué par des mines. On rajoute 1 au nombre de mine détecté. 
				nb_mine += 1;
			}
		}
	}
}

void passe2_marquage(Demineur& jeu, const int position, const unsigned int nb_detecte, const unsigned int nb_mine, const int position_adjacente[], bool& coup_fait) {
	for (int l = 0; l < 8; ++l) {
		if (nb_detecte == jeu.tableau[position].detection) { //Si le nombre de cases détectés est égal au nombre de mine autour de la case, on marque la case non révélée.
			for (unsigned int k = 0; k < 8; k++) {
				if (position % jeu.colonne == 0 && (k == 0 || k == 3 || k == 5)) {
					continue;//La case n'existe pas
				}
				else if (((position + 1) % jeu.colonne == 0) && (k == 2 || k == 4 || k == 7)) {
					continue;//La case n'existe pas
				}
				if (jeu.tableau[position + position_adjacente[k]].revele == false && jeu.tableau[position + position_adjacente[k]].marque == false) {
					if (position + position_adjacente[k] < jeu.taille && position + position_adjacente[k] >= 0) {
						cout << "M";
						cout << position + position_adjacente[k] << endl;
						jouer_coup(jeu, 'M', position + position_adjacente[k]);
						coup_fait = true;
						return;
					}
				}
			}
		}
	}
}

void passe2_demasquage(Demineur& jeu, const int position, const unsigned int nb_detecte, const unsigned int nb_mine, const int position_adjacente[], bool& coup_fait) {
	if (nb_mine == jeu.tableau[position].detection) {
		for (unsigned int k = 0; k < 8; k++) {
			if (position % jeu.colonne == 0 && (k == 0 || k == 3 || k == 5)) {
				continue;//La case n'existe pas
			}
			else if (((position + 1) % jeu.colonne == 0) && (k == 2 || k == 4 || k == 7)) {
				continue;//La case n'existe pas
			}
			if (jeu.tableau[position + position_adjacente[k]].revele == false && jeu.tableau[position + position_adjacente[k]].marque == false) {
				if (position + position_adjacente[k] < jeu.taille && position + position_adjacente[k] >= 0) {
					cout << "D";
					cout << position + position_adjacente[k] << endl;
					coup_fait = true;
					return;
				}
			}
		}
	}
}

void coup_intelligent(Demineur& jeu) {
	if (jeu.etat_jeu == GAME_LOST || jeu.etat_jeu == GAME_WON) { //Vérification de l'état du jeu, s'il est gagné ou perdu.
		cout << "Pas de coup intelligent possible.";
	}
	else {
		int position_adjacente[nb_case_adja] = { -jeu.colonne - 1,-jeu.colonne,-jeu.colonne + 1,-1,+1,jeu.colonne - 1,jeu.colonne,jeu.colonne + 1 };
		for (int i = 0; i < jeu.taille; i++) {
			if (jeu.tableau[i].revele == true) {
				unsigned int nb_detecte = 0;
				unsigned int nb_mine = 0;
				bool coup_fait = false;
				passe1(jeu, i, nb_detecte, nb_mine, position_adjacente);
				passe2_marquage(jeu, i, nb_detecte, nb_mine, position_adjacente, coup_fait);
				if (coup_fait) { return; }
				passe2_demasquage(jeu, i, nb_detecte, nb_mine, position_adjacente, coup_fait);
				if (coup_fait) { return; }
			}
		}
		unsigned int numero_case = rand() % jeu.taille;
		while (jeu.tableau[numero_case].revele == true || jeu.tableau[numero_case].marque == true) {
			numero_case = rand() % jeu.taille;
		}
		cout << "D" << numero_case << endl;
	}
}


void lire_grille(Demineur& jeu) {
	unsigned int nb_separateur = jeu.colonne + 1;
	int compteur = 0;
	unsigned int compteur_separateur = 0;
	char case_a_lire;
	Case tuile;
	tuile.mine = false;
	tuile.revele = true;
	tuile.marque = false;
	tuile.detection = 0;
	while (compteur < jeu.taille) {
		cin >> case_a_lire;
		if (case_a_lire == '-' || case_a_lire == '_') {
			;
			continue;
		}
		if (case_a_lire == '|') {
			compteur_separateur++;
			if ((compteur_separateur % nb_separateur) - 1 != 0) {
				jeu.tableau[compteur] = tuile;
				compteur++;
				tuile.mine = false;
				tuile.revele = true;
				tuile.marque = false;
				tuile.detection = 0;
			}
		}
		else if (case_a_lire == 'x') {
			tuile.mine = true;
			tuile.marque = true;
			tuile.revele = false;
		}
		else if (case_a_lire == '.') {
			tuile.revele = false;
		}
		else {
			char temp[2];
			int temp2;
			sprintf(temp, "%c", case_a_lire);
			sscanf(temp, "%d", &temp2);
			tuile.detection = temp2;
		}
	}
}

void initialiser_grille(Demineur& jeu) {
	jeu.taille = jeu.ligne * jeu.colonne;
	jeu.etat_jeu = IN_PROGRESS;

	Case* tab = new Case[jeu.taille];
	Case tuile;
	tuile.mine = false;
	tuile.revele = true;
	tuile.marque = false;
	tuile.detection = 0;
	for (int i = 0; i < jeu.taille; ++i) {
		tab[i] = tuile;
	}
	jeu.tableau = tab;
	lire_grille(jeu);
	coup_intelligent(jeu);
}
void detruire(Demineur& jeu) {
	delete[] jeu.tableau;
	jeu.tableau = NULL;
}
