#include "symbole.h"
#include <iostream>

void Symbole::Affiche() {
   cout<<Etiquettes[ident];
}

void Entier::Affiche() {
   Symbole::Affiche();
   cout<<"("<<valeur<<")";
}

void Expr::Affiche() {
   Symbole::Affiche();
}

double ExprMult::eval(const map<string, double> &valeurs){
   return e1->eval() * e2->eval();
}

double ExprAdd::eval(const map<string, double> &valeurs){
   return e1->eval() + e2->eval();
}

double ExprEnt::eval(const map<string, double> &valeurs){
   return (double) val->getVal();
}

double ExprPar::eval(const map<string, double> &valeurs){
   return e->eval();
}