
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "vueEnModeTexte.hpp"
#include "mPoseMotJarnac-correction.hpp"

/***********************************************************************
 *
 *  CCC     OOO   N   N  TTTTT RRRR    OOO   L      EEEEE  U    U  RRRR
 * C       O   O  NN  N    T   R   R  O   O  L      E      U    U  R   R
 * C       O   O  N N N    T   RRRR   O   O  L      EEEE   U    U  RRRR
 * C       O   O  N  NN    T   R  R   O   O  L      E      U    U  R  R
 *  CCC     OOO   N   N    T   R   R   OOO   LLLLL  EEEEE   UUUU   R   R
 *
 * **********************************************************************/

/*****************
Crée la pioche du jeu jarnac tout en respectant les règles de cette dernière
@return la pioche sous forme de string
*/
string create_pioche();

/*****************
Génère au hasard une lettre présente dans la pioche
@param la pioche
@return la lettre sous forme de char
*/
char lettre_hasard(string pioche);

/*****************
Génère au hasard 3 lettres presentes dans la pioche
@param la pioche
@return les 3 lettres sous forme de string
*/
string pioche_3lettre(string pioche);

/*****************
Affiche au joueur un message lui indiquant qu'il peut piocher une lettre puis génère au hasard 1 lettre présente dans la pioche
@param la pioche
@param le nom du joueur qui pioche
@return la lettre piochée
*/
char pioche_lettre(string pioche,string nomJoueur);

/*****************
Créer le vrac en remplaçant la derniere lettre par une voyelle au hasard si il est uniquement composé de consonnes.
@param la pioche
@return le vrac sous forme de string
*/

string createvrac(string pioche);

/************************
 * choisit une action parmi les actions possibles proposées dans possibilités
 * @param possibilites une liste de chaine de caractères
 * @param nomJoueur
 * @return une des chaines de caractères de possibilités,
 * laquelle aura été choisie par définition par le joueur nommé nomJoueur.
 **/
string choisirAction(vector<string> possibilites, string nomJoueur);

/************************
 * choisit un mot parmis les mots du diconnaire dans le fichier dico
 * @param plateau un plateau de jeu (voir définition:
 * le premier mot represente des lettres en vrac, les suivants des mots.)
 * @param nomJoueur le nom du joueur concerné par le choix
 * @param l'adresse du dictionnaire à consulter
 * @return la chaine de caractère "-" si le joueur (n'a pas voulu choisir)
 * ou un des mots du dictionnaire
 * lequel aura été choisi en principe par le joueur nommé nomJoueur.
 **/
string choisirMot(vector<string> plateau, string nomJoueur, string dico);

/*****************
Demande au joueur de modifier un mot de son plateau
@param le plateau du joueur
@param le nom du joueur
@param le dictionnaire commun
@return le mot modifié s'il respecte toutes les conditions : le nouveau mot doit faire parti du dictionnaire, il doit uniquement etre constitué du mot original qu'il souhaite modifier ainsi que de son vrac.
*/
string modifie_mot(vector<string> plateau, string nomJoueur, string dico);

/*****************
demande au joueur de modifier un mot de son plateau puis renvoie le tableau modifié
@param le plateau du joueur
@param le nom du joueur
@param le dictionnaire commun
@param la pioche
@return le tableau modifié avec le mot modifié ainsi que le vrac sans lettres ajoutées au mot.
*/
vector<string> tour_choix_modifie_mot(vector<string> plateau_principal, string nomJoueur_principal, string dico, string pioche);

/*****************
Retire un element d'un tableau
@param la chaîne de caractères à retirer
@param le plateau du joueur
@return le plateau sans l'élèment.
*/
vector<string> retire_element(string elt,vector<string> tableau);

/*****************
Demande au joueur de choisir un mot puis l'ajoute dans son plateau si le mot est valide: si il est fait a partir de lettres de son vrac et si le mot est présent dans le dictionnaire commun
@param le plateau du joueur
@param le nom du joueur
@param le dictionnaire
@param la pioche
@return le plateau avec le mot choisi.
*/
vector<string> tour_choix_choisir_mot(vector<string> plateau_principal, string nomJoueur_principal, string dico, string pioche);

/*****************
demande au joueur quelle mot du plateau adverse il souhaite modifier, lui demande le mot modifié. Si ces deux saisies sont valides, la fonction va modifier le plateau du joueur qui a lancé le jarnac en lui ajoutant le mot qu'il a suggéré, la fonction va egalement modifier le plateau du joueur adverse en lui enlevant le mot que le joueur principal a souhaité completer ainsi que la ou les lettre(s) du vrac qu'il a ajouté au mot
@param le plateau du joueur qui cri jarnac
@param le plateau du joueur adverse
@param le nom du joueur qui cri jarnac
@param le dictionnaire
@param la pioche
@return un tableau 2D, soit un tableau contenant les plateaux de chaques joueurs apres l'operation jarnac
*/
vector<vector<string>> cri_jarnac(vector<string> plateau_principal,vector<string> plateau_victime,string nomJoueur_principal, string dico, string pioche);

/*****************
change le vrac du joueur ayant actionné la possibilité d'echanger 3 lettres de son vrac.
demande au joueur de quelles lettres il souhaite se debarrasser puis lui ajoute 3 lettres au hasard 
@param le plateau du joueur
@param le nom du joueur
@param la pioche
@return le nouveau vrac
*/
string vrac_change_3lettres(vector<string> plateau, string nomJoueur, string pioche);

/*****************
Moteur du jeu, propose des actions au joueur, gere les actions que le joueur a decidé d'effectuer tout en modifiant les plateau suivant les actions choisi
si un joueur abandonne la partie: son vrac est remplacé par 'perdant' et celui de l'adversaire par 'gagnant'
@param le plateau du joueur1
@param le plateau du joueur2
@param le nom du joueur1
@param le nom du joueur2
@param le dictionnaire
@param la pioche
@param le nom du joueur à qui c'est le tour de jouer
@param les possibilités, soit les actions que l'on va proposer au joueur
@return un tableau 2D, soit le tableau des plateaux des deux joueurs
*/
vector<vector<string>> tour_choix_mot_complet(vector<string>plateauJoueur1,vector<string>plateauJoueur2,string nomJoueur1,string nomJoueur2, string dico, string pioche,string nomJoueur_principal,vector<string> possibilite);

/*****************
 * Permet à deux joueurs de s'affronter
 * au Jarnac de l'installation à la notification du gagnant,
 * ils auront au cour du jeu à choisir
 *  - leur dictionnaire commun
 *  - leur interface et leur mode de jeu
 *  - leur actions et leurs coups respectifs
 * @param les prenoms de chacun deux joueurs
 * @retour vrai si le jeu s'est terminé normalement
 * avec un vainqueur (supériorité en nombre de points lors de la pose du 8eme mot)
 * et un perdant notifiés
 * (en cas d'égalité au points
 * c'est le joueur qui a fini
 * le tour qui gagne
 * de ce fait il y a toujours
 * un gagnant qui est notifé lors que le jeu va jusqu'au bout),
 * faux si le jeu a fait l'objet d'un abandon.
 */
bool lanceLeJeu(string joueur0, string joueur1);
