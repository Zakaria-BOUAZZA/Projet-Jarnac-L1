#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "vueEnModeTexte.hpp"
#include "mDictionnaire.hpp"
#include "mAnagrammes.hpp"
#include "mCalculPoints.hpp"
#include "mEquivalence.hpp"

string create_pioche(){
    vector<char>alphabet = {};
    for(int i=97; i<123; i++){
        alphabet.push_back(i);
    }
    vector<int>valeurs = {14,4,7,5,19,2,4,2,11,1,1,6,5,9,8,4,1,10,7,9,8,2,1,1,1,2};
    string pioche = "";
    for(int i=0; i<alphabet.size(); i++){
        for(int j=0; j<valeurs[i]; j++){
            pioche.push_back(alphabet[i]);
        }
    }
    return pioche;
}


char lettre_hasard(string pioche){
    return pioche[rand() %pioche.size()];
}

string pioche_3lettre(string pioche){
    string mot;
    for (int i=0; i<3;i++){
        mot.push_back(lettre_hasard(pioche));
    }
    return mot;
}


char pioche_lettre(string pioche,string nomJoueur){
    cout << nomJoueur << ", vous avez gagné une lettre !, cette lettre est: ";
    char lettre = lettre_hasard(pioche);
    return lettre;
}


string createvrac(string pioche){
    vector<char>voyelle = {'a','e','i','o','u','y'};
    string vrac = "";
    for(int i=0; i<6; i++){
        vrac.push_back(pioche[rand() %144]);
    }
    for(int i=0; i<vrac.size(); i++){
        for(int j=0; j<voyelle.size(); j++){
            if(voyelle[j] == vrac[i]){
                return vrac;
            }
        }
    }
    vrac.erase(5,1);
    int indice = rand() % voyelle.size();
    vrac.push_back(voyelle[indice]);
    return vrac;
}


/************************
 * choisit une action parmi les actions possibles proposées dans possibilités
 * @param possibilites une liste de chaine de caractères
 * @param nomJoueur
 * @return une des chaines de caractères de possibilités,
 * laquelle aura été choisie par définition par le joueur nommé nomJoueur.
 **/
char choisirAction(vector<string> possibilites, string nomJoueur){
    afficheLaDemandeDeReponseParmi(possibilites,nomJoueur);
    char choix;
    cin >> choix;
    for(string pos:possibilites){
        if (pos[0]==choix) return choix;}
     return choisirAction(possibilites,nomJoueur);
}

/************************
 * choisit un mot parmis les mots du dictionnaire dans le fichier dico
 * @param plateau un plateau de jeu (voir définition:
 * le premier mot represente des lettres en vrac, les suivants des mots.)
 * @param nomJoueur le nom du joueur concerné par le choix
 * @param l'adresse du dictionnaire à consulter
 * @return la chaine de caractère "-" si le joueur (n'a pas voulu choisir)
 * ou un des mots du dictionnaire
 * lequel aura été choisi en principe par le joueur nommé nomJoueur.
 **/
string choisirMot(vector<string> plateau, string nomJoueur, string dico){
    afficheLaDemandeDeTaperUnMot(nomJoueur);
    string reponse;
    cin >> reponse;
    if(reponse == "P"){
        return "-";
    }
    while( not(trouve(reponse,importeDico(dico))) or retire(plateau[0],reponse) == "-"){
        signaleMotNonValide(reponse);
        cin >> reponse;
        if(reponse == "P"){
            return "-";
        }
    }
    return reponse;
}

string modifie_mot(vector<string> plateau, string nomJoueur, string dico){
    cout << nomJoueur << ", veuillez taper le mot que souhaitez modifier ou seulement la lettre P pour passer votre tour:";
    string mot;
    cin >> mot;
    if(mot == "P"){
        return"-";
    }
    while(not trouve(mot,plateau)){
        signaleMotNonValide(mot);
        cin >> mot;
        if(mot == "P"){
            return "-";
        }
    }
    cout << "Veuillez taper le mot apres modification:";
    string nv_mot;
    cin >> nv_mot;
    string vrac = plateau[0];
    if(nv_mot == "P"){
        return"-";
    }
    while(not trouve(nv_mot,importeDico(dico)) or retire(nv_mot,mot)=="-" or retire(vrac,retire(nv_mot,mot))=="-"){
        signaleMotNonValide(nv_mot);
        cin >> nv_mot;
        if(nv_mot == "P"){
            return"-";
        }
    }
    return nv_mot;
}


vector<string> tour_choix_modifie_mot(vector<string> plateau_principal, string nomJoueur_principal, string dico, string pioche){
    string nv_mot = modifie_mot(plateau_principal, nomJoueur_principal, dico);
    if(nv_mot == "-"){
        return plateau_principal;
    }
    string mot_original;
    int indice;
    for(int i=1; i<plateau_principal.size(); i++){
        if(retire(nv_mot, plateau_principal[i]) != "-"){
            mot_original = plateau_principal[i];
            indice = i;
        }
    }
    plateau_principal[indice] = nv_mot;
    plateau_principal[0] = retire(plateau_principal[0], retire(nv_mot,mot_original));
    return plateau_principal;
}


vector<string> retire_element(string elt, vector<string> tableau){
    vector<string>nv_tableau = {};
    for(int i=0; i<tableau.size(); i++){
        if(tableau[i] != elt){
            nv_tableau.push_back(tableau[i]);
        }
    }
    return nv_tableau;
}

    
vector<string> tour_choix_choisir_mot(vector<string> plateau_principal, string nomJoueur_principal, string dico, string pioche){
    string mot = choisirMot(plateau_principal, nomJoueur_principal, dico);
    if(mot == "-"){ 
        return plateau_principal;
    }else{
        plateau_principal[0] = retire(plateau_principal[0], mot);
        plateau_principal.push_back(mot);
        return plateau_principal;
    }
}


vector<vector<string>> cri_jarnac(vector<string> plateau_principal,vector<string> plateau_victime,string nomJoueur_principal, string dico, string pioche){
    cout << nomJoueur_principal << "--> vous avez crié Jarnac, vous devez maintenant saisir le mot du tableau de l'adversaire que vous souhaitez completer !" << endl;
    string nv_mot = modifie_mot(plateau_victime,nomJoueur_principal, dico);
    if(nv_mot == "-"){
        return {plateau_principal,plateau_victime};
    }else{
        plateau_principal.push_back(nv_mot);
    }
        int indice;
        string mot_original;
    for(int i=1; i<plateau_victime.size(); i++){
        if(retire(nv_mot, plateau_victime[i]) != "-"){
            mot_original = plateau_victime[i];
            indice = i;
        }
    }
    cout << nv_mot << mot_original << endl;
    plateau_victime.erase(plateau_victime.begin() + indice);
    plateau_victime[0] = retire(plateau_victime[0], retire(nv_mot, mot_original));
    return {plateau_principal,plateau_victime};
}


string vrac_change_3lettres(vector<string> plateau, string nomJoueur, string pioche){
    afficheLaDemandeDeChoisir3lettres(nomJoueur);
    string lettres_debarras;
    cin >> lettres_debarras;
    string vrac = plateau[0];
    while(retire(vrac, lettres_debarras) == "-"){
        cout << lettres_debarras << "<--- cette saisie est invalide" << endl;
        cout << "Veuillez réessayer" << endl;
        cin >> lettres_debarras;
    }
    vrac = retire(vrac,lettres_debarras);
    vrac = vrac + pioche_3lettre(pioche);
    return vrac;
}
        
    

vector<vector<string>> tour_choix_mot_complet(vector<string>plateauJoueur1,vector<string>plateauJoueur2,string nomJoueur1,string nomJoueur2, string dico, string pioche,string nomJoueur_principal,vector<string> possibilite){
    vector<string>plateau_principal;
    vector<string>plateau_victime;
    if(nomJoueur_principal == nomJoueur1){
        plateau_principal = plateauJoueur1;
        plateau_victime = plateauJoueur2;
        affichePlateaux(plateau_principal, plateauJoueur2, 8, 9, "Jarnac", nomJoueur1, nomJoueur2);
    }
    if(nomJoueur_principal == nomJoueur2){
        plateau_victime = plateauJoueur1; 
        plateau_principal = plateauJoueur2;
        affichePlateaux(plateauJoueur1, plateau_principal, 8, 9, "Jarnac", nomJoueur1, nomJoueur2);
    }
    char choix = choisirAction(possibilite, nomJoueur_principal);
    if(choix == 'P'){
        return {plateau_principal,plateau_victime};
    }
    if(choix == 'A'){
        plateau_principal[0] = "perdant";
        plateau_victime[0] = "gagnant";
        return {plateau_principal,plateau_victime};
    }
    if(choix == 'E'){
        string nv_vrac = vrac_change_3lettres(plateau_principal, nomJoueur_principal, pioche);
        plateau_principal[0] = nv_vrac;
        if(nomJoueur_principal == nomJoueur1){
            return tour_choix_mot_complet(plateau_principal, plateau_victime, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, {"Continuer en choisissant un mot","Passer son tour","Abandonner la Partie","Modifier un mot"});
        }
        if(nomJoueur_principal == nomJoueur2){
            return tour_choix_mot_complet(plateau_victime, plateau_principal, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, {"Continuer en choisissant un mot","Passer son tour","Abandonner la Partie","Modifier un mot"});
        }
    }
    if(choix == 'T'){
        string vrac = plateau_principal[0];
        vrac.push_back(pioche_lettre(pioche, nomJoueur_principal));
        plateau_principal[0] = vrac;
        if(nomJoueur_principal == nomJoueur1){
            return tour_choix_mot_complet(plateau_principal, plateau_victime, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, {"Continuer en choisissant un mot","Passer son tour","Abandonner la Partie","Modifier un mot"});
        }
        if(nomJoueur_principal == nomJoueur2){
            return tour_choix_mot_complet(plateau_victime, plateau_principal, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, {"Continuer en choisissant un mot","Passer son tour","Abandonner la Partie","Modifier un mot"});
        }
    }
    //si crier jarnac
    if(choix == 'J'){
        vector<vector<string>> jarnac=cri_jarnac(plateau_principal,plateau_victime,nomJoueur_principal,dico,pioche);
        plateau_principal = jarnac[0];
        plateau_victime = jarnac[1];
        if(nomJoueur_principal == nomJoueur1){
            return tour_choix_mot_complet(plateau_principal, plateau_victime, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
        }
        if(nomJoueur_principal == nomJoueur2){
            return tour_choix_mot_complet(plateau_victime, plateau_principal, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
        }
    }
    //rendre jarnac disponible seulement apres le passage de l'adversaire
    if(trouve("Jarnac", possibilite)){
        possibilite = retire_element("Jarnac", possibilite);
    }
    //si choisir mot
    if(choix == 'C'){
        vector<string>tab = tour_choix_choisir_mot(plateau_principal, nomJoueur_principal, dico, pioche);
        if(plateau_principal == tab){
            return {plateau_principal,plateau_victime};
            char lettre = pioche_lettre(pioche, nomJoueur_principal);
            tab[0].push_back(lettre);
        }
        if(nomJoueur_principal == nomJoueur1){
            return tour_choix_mot_complet(tab, plateau_victime, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
        }
        if(nomJoueur_principal == nomJoueur2){
            return tour_choix_mot_complet(plateau_victime, tab, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
        }
    }
    //si modifie mot
    if(choix == 'M'){
        vector<string>tab=tour_choix_modifie_mot(plateau_principal,  nomJoueur_principal,  dico,  pioche);
        if(plateau_principal == tab){ 
            return {plateau_principal, plateau_victime};
            char lettre = pioche_lettre(pioche, nomJoueur_principal);
            tab[0].push_back(lettre);
        }
        if(nomJoueur_principal == nomJoueur1){
            return tour_choix_mot_complet(tab, plateau_victime, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
        }
        if(nomJoueur_principal == nomJoueur2){
            return tour_choix_mot_complet(plateau_victime, tab, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
        }
    }
    return tour_choix_mot_complet(plateauJoueur1, plateauJoueur2, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur_principal, possibilite);
}




bool jeu_est_fini(vector<string>plateauJoueur1, vector<string>plateauJoueur2, string nomJoueur1, string nomJoueur2){
    if(plateauJoueur1[0] == "gagnant"){
        signaleGagnant(nomJoueur1);
        return true;
    }
    if(plateauJoueur2[0] == "gagnant"){
        signaleGagnant(nomJoueur2);
        return true;
    }
    if((plateauJoueur1.size() == 8) or (plateauJoueur2.size() == 8)){
        if(calculPoints(plateauJoueur1, 9, 8) > calculPoints(plateauJoueur2, 9, 8)){
            signaleGagnant(nomJoueur1);
        }
        if(calculPoints(plateauJoueur1, 9, 8) < calculPoints(plateauJoueur2, 9, 8)){
            signaleGagnant(nomJoueur2);
        }
        if(calculPoints(plateauJoueur1, 9, 8) == calculPoints(plateauJoueur2, 9, 8)){
            if(plateauJoueur1.size() == 8){
                signaleGagnant(nomJoueur1);
            }
            if(plateauJoueur2.size() == 8){
                signaleGagnant(nomJoueur2);
            }
        }     
        return true;
    }
    return false;
}

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
bool lanceLeJeu(string joueur0, string joueur1){
     //vector<string> possibilites_reference={"Abandonner la Partie","Continuer en choisissant un mot", "Echanger trois Lettres", "Jarnac", "Passer son tour", "Tirer une lettre","Modifier un mot"};
    
    cout << "saisissez votre dictionnaire commun, le dictionnaire de français est './dictionnaire.txt'" << endl;
    string dico;
    cin >> dico;
    string pioche = create_pioche();
    cout << pioche << endl;
    string vracJoueur1 = createvrac(pioche);
    string vracJoueur2 = createvrac(pioche);
    pioche = retire(pioche, vracJoueur1);
    pioche = retire(pioche, vracJoueur2);
    vector<string> plateauJoueur1 = {vracJoueur1};
    vector<string> plateauJoueur2 = {vracJoueur2};
    string nomJoueur1 = joueur0;
    string nomJoueur2 = joueur1;
    vector<string> possibilites = {"Continuer en choisissant un mot","Passer son tour","Abandonner la Partie"};
    string joueur_qui_debute = nomJoueur1;
    int nombre_tour = 0;
    while(not jeu_est_fini(plateauJoueur1, plateauJoueur2, nomJoueur1, nomJoueur2)){
        nombre_tour++;
        if(joueur_qui_debute == nomJoueur1){
            joueur_qui_debute = nomJoueur2;
        }else{ 
            joueur_qui_debute = nomJoueur1;
        }
        if(joueur_qui_debute == nomJoueur1){
            vector<vector<string>>tour1 = tour_choix_mot_complet(plateauJoueur1, plateauJoueur2, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur1, possibilites);
            plateauJoueur1 = tour1[0];
            plateauJoueur2 = tour1[1];
        }
        if(joueur_qui_debute == nomJoueur2){
            vector<vector<string>>tour2 = tour_choix_mot_complet(plateauJoueur1, plateauJoueur2, nomJoueur1, nomJoueur2, dico, pioche, nomJoueur2, possibilites);
            plateauJoueur1 = tour2[1];
            plateauJoueur2 = tour2[0];
        }
        possibilites.push_back("Jarnac");
        if(nombre_tour > 1){
            possibilites = {"Continuer en choisissant un mot","Modifier un mot","Passer son tour","Jarnac","Abandonner la Partie","Tirer une lettre","Echanger trois Lettres"};
        }
    }
    if(plateauJoueur1[0] == "gagnant" or plateauJoueur2[0] == "gagnant"){
        return false;
    }else{
        return true;
    }
}
           
    
int main(){
    lanceLeJeu("Zakaria","Younes");
}