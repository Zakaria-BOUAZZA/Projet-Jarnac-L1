#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/**************************************
 *
 * DDDD    IIIII     CCC    OOO
 *  D  D     I      C      O   O
 *  D  D     I     C       O   O
 *  D  D     I      C      O   O
 * DDDD    IIIII     CCC    OOO
 *
 ***************************************/

/** Convertit en majuscule
 * @param char lettre
 * @return lettre en majuscule, ou '-' si lettre n'est pas une lettre dans 'a-z, A-Z'.
 *
*/
char majuscule(char lettre){
    if(lettre >= 97 and lettre <= 122){
        return lettre - 32;
    }else if (lettre >= 65 and lettre <= 90){
        return lettre;        
    }else{
        return '-';
    }
}

/** «Purifie» un mot en retirant espaces et caractères spéciaux
 *  et en le mettant en majuscules
 * @param string mot
 * @return string: le mot purifié
*/


string purifie(string mot){
    string motPurifie;
    for(int i=0; i <= mot.size(); i++){
        if(mot[i] >= 97 and mot[i] <= 122){
            motPurifie += majuscule(mot[i]) ;
        }else if(mot[i] >= 65 and mot[i] <= 90){
            motPurifie += mot[i];
        }
    }
    return motPurifie;
}

        
/**importeDico
* @param string l'adresse d'un fichier contenant une liste de mots correctes.
* @return vector<string> un tableau de chaines de caracteres contenant les memes mots.
**/

vector<string> importeDico(string Dico){
    ifstream fichier;
    fichier.open(Dico);
    string mot;
    vector<string>t={};
    while(fichier >> mot){
        t.push_back(mot);
    }
    return t;
    fichier.close();
}


/** Teste si un mot est dans le dictionnaire
 *  Note: on comparera deux mots en testant si leurs purifications sont égales
 * @param string mot: le mot recherché
 * @param vector<string> dico: un dictionnaire sous forme de tableau
 * @return bool: vrai si le mot est dans le dictionnaire, faux sinon
*/

bool trouve(string mot, vector<string> dico){
    for(int i=0; i < dico.size(); i++){
        if(purifie(mot) == purifie(dico[i])){
            return true;
        }
    }
    return false;
}


