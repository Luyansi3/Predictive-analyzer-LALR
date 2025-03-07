#pragma once

#include <string>
#include <map>
using namespace std;

enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR, EXPR };

const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR", "EXPR" };

class Symbole {
   public:
      Symbole(int i) : ident(i) {  }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();

   protected:
      int ident;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }
      void Affiche();
      int getVal() {return valeur;}
   protected:
      int valeur;
};



class Expr : public Symbole
{
   public:
      Expr() : Symbole(EXPR) {}
      ~Expr() {}
      virtual double eval(const map<string, double> &valeurs = {}) = 0;
      void Affiche();
};


class ExprMult : public Expr
{
private:
   Expr* e1;
   Expr* e2;
public:
   ExprMult(Expr* expr1, Expr* expr2) : Expr(), e1(expr1), e2(expr2) {};
   ~ExprMult() {delete e1; delete e2;}
   double eval(const map<string, double> &valeurs = {});
};

class ExprAdd : public Expr
{
private:
   Expr* e1;
   Expr* e2;
public:
   ExprAdd(Expr* expr1, Expr* expr2) : Expr(), e1(expr1), e2(expr2) {};
   ~ExprAdd() {delete e1; delete e2;}
   double eval(const map<string, double> &valeurs = {});
};

class ExprPar : public Expr
{
private:
   Expr* e;
public:
   ExprPar(Expr* expr) : Expr(), e(expr) {};
   ~ExprPar() {delete e;}
   double eval(const map<string, double> &valeurs = {});
};

class ExprEnt : public Expr
{
private:
   Entier* val;
public:
   ExprEnt(Entier* v) : Expr(), val(v) {};
   ~ExprEnt() {delete val;}
   double eval(const map<string, double> &valeurs= {});
};

