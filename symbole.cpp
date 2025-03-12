#include "symbole.h"
#include <iostream>

// Méthode d'affichage de la classe de base Symbole
// Affiche l'étiquette correspondant à l'identifiant du symbole.
void Symbole::Affiche() {
   cout << Etiquettes[ident];
}

// Méthode d'affichage de la classe Entier qui hérite de Symbole
// Affiche d'abord l'étiquette du symbole (par exemple "INT") puis,
// affiche la valeur entière contenue dans l'objet.
void Entier::Affiche() {
   Symbole::Affiche();
   cout << "(" << valeur << ")";
}

// Méthode d'affichage pour la classe Expr (expression)
// Comme Expr hérite de Symbole, on utilise ici l'affichage défini dans la classe de base.
void Expr::Affiche() {
   Symbole::Affiche();
}

// Méthode d'évaluation pour la multiplication d'expressions (ExprMult)
// Évalue les deux sous-expressions (e1 et e2) et retourne leur produit.
double ExprMult::eval(const map<string, double> &valeurs){
   return e1->eval() * e2->eval();
}

// Méthode d'évaluation pour l'addition d'expressions (ExprAdd)
// Évalue les deux sous-expressions (e1 et e2) et retourne leur somme.
double ExprAdd::eval(const map<string, double> &valeurs){
   return e1->eval() + e2->eval();
}

// Méthode d'évaluation pour une expression représentant un entier (ExprEnt)
// Retourne la valeur entière (convertie en double) contenue dans l'objet.
double ExprEnt::eval(const map<string, double> &valeurs){
   return (double) val->getVal();
}

// Méthode d'évaluation pour une expression parenthésée (ExprPar)
// Retourne simplement l'évaluation de l'expression encapsulée dans les parenthèses.
double ExprPar::eval(const map<string, double> &valeurs){
   return e->eval();
}
