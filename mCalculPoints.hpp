#include <vector>
#include <string>
using namespace std;


/*******************************************************
 *
 * M    M    OOO    TTTTT   EEEEE   U   U    RRRR
 * MM  MM   O   O     T     E       U   U    R   R
 * M MM M   O   O     T     EEE     U   U    RRR
 * M    M   O   O     T     E       U   U    R  R
 * M    M    OOO      T     EEEEE    UUU     R   R
************************************/

/**
 * calculPoints
 * @param vector<string> plateauJoueur: un plateau de jeu
 * @param int nbMaxLettres: la nombre maximal de lettres d'un mot
 *    autrement dit la largeur du plateau
 * @param int nbFinalMots: le nombre maximal de mots dans le plateau
 * @return le nombre de points rapportés par les mots du plateau
 *   rappel: le vrac est ignoré, de même que les mots à une lettre
 *   ou qui ne rentrent pas complètement dans le plateau.
*/
int calculPoints(vector<string> plateauJoueur, int nbMaxLettres,
                 int nbFinalMots);
