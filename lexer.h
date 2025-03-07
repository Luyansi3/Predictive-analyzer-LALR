#pragma once

#include <string>
#include "symbole.h"
using namespace std;

class Lexer {

   public:
      Lexer(string s) : flux(s), tete(0), tampon(nullptr) { }
      ~Lexer() { }

      Symbole * Consulter();
      void Avancer();
      int getTete() const {return tete;};

   protected:
      string flux;
      int tete;
      Symbole * tampon;
};
