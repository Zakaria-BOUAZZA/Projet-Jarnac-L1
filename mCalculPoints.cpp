#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "mCalculPoints.hpp"
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

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

int calculPoints(vector<string> plateauJoueur, int nbMaxLettres, int nbFinalMots){
    int taille = plateauJoueur.size();
    int points = 0;
    if(taille > nbFinalMots){
        taille = nbFinalMots + 1;
    }
    for(int i = 1; i < taille; i++){
        if(plateauJoueur[i].size() <= nbMaxLettres and plateauJoueur[i].size() >= 3){
            points += plateauJoueur[i].size() * plateauJoueur[i].size();
        }
    }
    return points;             
}
    
    

