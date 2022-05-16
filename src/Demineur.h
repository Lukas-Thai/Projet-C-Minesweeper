#ifndef _demineur_
#define _demineur_
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#define nb_case_adja 8
#pragma warning(disable : 4996)
using namespace std;

typedef struct {
	bool mine; //Variable qui indique si la case est une mine
	bool revele; //Variable qui indique si la case a été révélée
	bool marque; //Variable qui indique si la case a été marqué 
	char detection; //Variable qui indique le nombre de mine autour de la case
} Case;

typedef enum { IN_PROGRESS = 1, GAME_LOST = 0, GAME_WON = 2 }State; //défini les états possible du jeu

typedef struct {
	int ligne; //Indique le nombre de ligne du tableau
	int colonne; //Indique le nombre de colonne du tableau
	int taille; //indique le nombre de case dans le démineur
	unsigned int nb_mines; //indique le nombre de mine dans le jeu
	State etat_jeu; //indique si la partie est en cours, gagné ou perdu
	Case* tableau; //Tableau de case qui sera assigné dynamiquement 
} Demineur;

/*
  @brief Permet de déposer des mines aléatoirement dans le jeu
  @param[in,out] jeu Le démineur
*/
void deposer_mine(Demineur& jeu);
/*
  @brief Permet de jouer un coup qui démasque une case
  @param[in,out] jeu Le démineur
  @param[in] position La position où le coup est joué
*/
void revele(Demineur& jeu, unsigned int position);

/*
  @brief Permet d'attribuer le nombre de mines adjacente à une case
  @param[in,out] jeu Le démineur
*/
void detection_mine(Demineur& jeu);

/*
  @brief Permet de jouer un coup dans le démineur
  @param[in,out] jeu Le démineur
  @param[in] type_coup Le type du coup qu'on fait
  @param[in] position La position où l'on souhaite jouer le coup
*/
void jouer_coup(Demineur& jeu, char type_coup, int position);

/*
  @brief Initialise une grille de démineur
  @param[in,out] jeu Le démineur
*/
void initialiser_jeu(Demineur& jeu);

/*
  @brief Permet de d'initialiser une grille de démineur à partir d'input de l'utilisateur
  @param[in,out] jeu Le démineur
*/
void initialiser_deja_fait(Demineur& jeu);

/*
  @brief Affiche si la partie est gagnée
  @param[in,out] jeu Le démineur
*/
void verif_victoire(Demineur& jeu);

/*
  @brief Affiche si la partie est perdue
  @param[in] jeu Le démineur
*/
void verif_defaite(const Demineur& jeu);

/*
  @brief Permet de savoir quel symbole affiché lors de l'affichage
  @param[in] jeu Le démineur
  @param[in] position La position du symbole a déterminé dans la grille
  @param[out] str le symbole à afficher
*/
void choix_affichage(const Demineur& jeu, unsigned int position, char str[]);
/*
  @brief Permet d'afficher la grille du démineur
  @param[in] jeu Le démineur
*/
void afficher(const Demineur& jeu);
/*
  @brief Permet de compter les cases non révélé et les mines trouvé autour d'une case
  @param[in] jeu le demineur
  @param[in] position la case
  @param[out] nb_detecte le nombre de case non révélé
  @param[out] nb_mine le nombre de mine repéré autour de la case
  @param[in] position_adjacente le tableau avec la position relative des cases adjacente
*/
void passe1(const Demineur& jeu, const int position, unsigned int& nb_detecte, unsigned int& nb_mine, const int position_adjacente[]);

/*
  @brief Permet de voir si un marquage est possible et affiche la position ou elle est possible
  @param[in] jeu le demineur
  @param[in] position la case
  @param[in] nb_detecte le nombre de case non révélé
  @param[in] nb_mine le nombre de mine repéré autour de la case
  @param[in] position_adjacente le tableau avec la position relative des cases adjacente
  @param[out] coup_fait Un marquage a-t-il été trouvé
*/
void passe2_marquage(Demineur& jeu, const int position, const unsigned int nb_detecte, const unsigned int nb_mine, const int position_adjacente[], bool& coup_fait);

/*
  @brief Permet de voir si un démasquage est possible et affiche la position ou elle est possible
  @param[in] jeu le demineur
  @param[in] position la case
  @param[in] nb_detecte le nombre de case non révélé
  @param[in] nb_mine le nombre de mine repéré autour de la case
  @param[in] position_adjacente le tableau avec la position relative des cases adjacente
  @param[out] coup_fait Un démasquage a-t-il été trouvé
*/
void passe2_demasquage(Demineur& jeu, const int position, const unsigned int nb_detecte, const unsigned int nb_mine, const int position_adjacente[], bool& coup_fait);
/*
  @brief Permet de jouer un coup intelligent si possible sinon aléatoirement
  @param[in] jeu Le démineur
*/
void coup_intelligent(const Demineur& jeu);

/*
  @brief Permet de lire une grille et de la transformer sous forme de tablea
  @param[out] jeu Le demineur
*/
void lire_grille(Demineur& jeu);
/*
  @brief Permet d'initialiser un jeu à partir d'une grille
  @param[out] le jeu Le demineur
*/
void initialiser_grille(Demineur& jeu);
/*
  @brief Permet de restituer la mémoire prise par le tableau
  @param[out] Le demineur
*/
void detruire(Demineur& jeu);
#endif