// un bibliotheque pour jouer avec les anagrammes
#include <vector>
#include <string>
#include "mAnagrammes.hpp"
#include "mDictionnaire.hpp"

using namespace std;


#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/**
 * retire une lettre
 * @param string vrac: une suite de lettres
 * @param char lettre: une lettre
 * @return string: '-' si la lettre n'apparaît dans `vrac` et sinon
 * `vrac` après avoir y retiré la première occurence de la lettre
 */
string retire(string vrac, char lettre){
    string vracFinal;
    int occurence = 0;
    for(int i=0; i<vrac.size(); i++){
        if(vrac[i] == lettre and occurence == 0){
            occurence++;
            continue;
        }
    vracFinal += vrac[i];
    }
    if(vracFinal == vrac){
        return "-";
    }else{
        return vracFinal;
    }
}


/**
 * retire un mot
 * @param string vrac: une suite de lettres
 * @param string mot: un mot
 * renvoie vrac après lui avoir retiré une occurence de chaque lettre du mot
 * et la chaîne "-" si l'opération est impossible.
 */
string retire(string vrac, string mot){
    string vracFinal = vrac;
    for(int i=0; i<mot.size(); i++){
        vracFinal = retire(vracFinal,mot[i]);
    }
    return vracFinal;
}


/**
 * est anagramme
 * @param string mot1: un mot
 * @param string mot2: un mot
 * renvoie vrai si les deux mots sont des anagrammes l'un de l'autre et faux sinon
*/
bool est_anagramme(string mot1, string mot2){
    if(retire(mot1,mot2) == ""){
        return true;
    }else{
        return false;
    }
}


/**
 * calcul la liste des anagrammes d'un mot qui figurent dans le dico
 */
vector<string> listeDesAnagrammesDuDico(string mot, string dico){
    ifstream fichier;
    fichier.open(dico);
    string l;
    vector<string>t={};
    while(fichier >> l){
        if(est_anagramme (l, mot)){
            t.push_back(l);
        }
    }
    fichier.close();
    return t;
}
        