#include "automate.h"
#include <unistd.h> // Pour certaines fonctions POSIX (ex.: sleep) utiliser pour les test (lors de boucle infinis :))

/* -------------------------------
   Constructeur et Destructeur
---------------------------------*/

Automate::Automate(string flux)
{   
    // Stockage du flux de caractères à analyser
    this->flux = flux;
    // Flag d'erreur initialisé à false (aucune erreur détectée)
    bugFlag = false;
    // Instanciation du lexer qui découpera le flux en symboles
    lexer = new Lexer(flux);
}

Automate::~Automate()
{
    // Suppression de l'objet lexer
    delete lexer;
    
    // Libération de la mémoire pour tous les états stockés dans stackstate (doit normalement être vide)
    for (unsigned int i = 0; i < stackstate.size(); i++) {
        delete stackstate[i];
    }
    // Libération de la mémoire pour tous les symboles stockés dans stacksymbole
    for (unsigned int i = 0; i < stacksymbole.size(); i++) {
        delete stacksymbole[i];
    }
}

/* -------------------------------
   Affichage des piles d'états et de symboles
---------------------------------*/

void Automate::printStacks(){
    cout << "state : ";
    for (unsigned int i = 0; i < stackstate.size(); i++) {
        stackstate[i]->print();
        cout << " ";
    }
    cout << endl;

    cout << "symbols : ";
    for (unsigned int i = 0; i < stacksymbole.size(); i++) {
        stacksymbole[i]->Affiche();
        cout << " ";
    }
    cout << endl;
}

/* -------------------------------
   Analyse et transitions
---------------------------------*/

// Méthode principale d'analyse du flux (lecture syntaxique)
void Automate::lecture(void){

    Etat* e0 = new E0;
    stackstate.push_back(e0); // Push de l'axiome de la grammaire dans la stack

    Symbole * s;
    // Boucle de lecture des symboles jusqu'à la fin ou jusqu'à une erreur
    while(true) {
        // Consulter le symbole courant sans avancer dans le flux
        s = lexer->Consulter();

        // Tentative de transition de l'état courant avec le symbole
        // Si la transition retourne true, on sort de la boucle car nous sommes arrivé au caractère de fin
        if (stackstate.back()->transition(*this, s)) break;

        // Si le lexer a atteint la fin du flux et que bugFlag est activé, on sort également
        if (lexer->getTete() == (int) flux.length() && bugFlag) break;
    }
    // Si aucune erreur n'a été détectée (bugFlag reste false)
    if (!bugFlag) {
        // Suppression du symbole courant (déjà traité)
        delete s;
        // Le symbole final de la pile doit être une expression ; on le récupère
        Expr* E = (Expr*) stacksymbole.back();
        // Évaluation de l'expression finale et affichage du résultat
        cout << "Résultat : " << E->eval() << endl;
    }
}

// Méthode appelée en cas d'erreur de syntaxe pour ignorer le symbole erroné
void Automate::ignore() {
    // Active le flag d'erreur et l'affiche
    bugFlag = true;
    cout << flux << endl;
    
    // Affiche une ligne de tirets jusqu'à la position de l'erreur
    for (int i = 0; i < lexer->getTete()-1; i++) {
        cout << "-";
    }
    // Affiche un caret (^) pour indiquer la position exacte de l'erreur
    cout << "^";

    for (unsigned int i = lexer->getTete(); i < flux.length(); i++) {
        cout << "-";
    }
    cout << endl;
    cout << "Error !" << endl;
    
    // Suppression du symbole courant erroné et passage au suivant
    delete lexer->Consulter();
    lexer->Avancer();
}

/* -------------------------------
   Méthodes de gestion de piles
---------------------------------*/

// Décalage (shift) : ajoute un symbole et un état dans leurs piles respectives
// et avance dans le flux.
void Automate::decalage(Symbole * s, Etat * e) {
    stacksymbole.push_back(s);
    stackstate.push_back(e);
    lexer->Avancer();
}

// Transition simple : ajoute un symbole et un état dans leurs piles sans avancer dans le flux.
void Automate::transitionsimple(Symbole * s, Etat * e) {
    stacksymbole.push_back(s);
    stackstate.push_back(e);
}

// Réduction : effectue une réduction syntaxique en supprimant n états de la pile,
// puis effectue une transition avec le symbole de réduction.
void Automate::reduction(int n, Symbole * s) {
    for (int i = 0; i < n; i++) {
        delete(stackstate.back()); // détruit l'instance de l'état pointé
        stackstate.pop_back(); // retire le pointeur de la pile
    }
    // Applique une transition sur le nouvel état en haut de la pile avec le symbole de réduction
    stackstate.back()->transition(*this, s);
}

// Extrait le symbole en haut de la pile sans le détruire (la gestion de la mémoire est externe)
Symbole* Automate::popSymbol(void){
    Symbole* s = stacksymbole.back();
    stacksymbole.pop_back();
    return s;
}

// Extrait et détruit le symbole en haut de la pile
void Automate::popAndDestroySymbol(){
    delete (stacksymbole.back()); // détruit l'instance du Symbole pointée
    stacksymbole.pop_back(); // retire le pointeur de la pile
}