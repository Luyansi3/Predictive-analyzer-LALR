#pragma once

#include <iostream>
#include <vector>
#include <stack>

#include "symbole.h"
#include "lexer.h"
#include "etat.h"


using namespace std;

class Automate
{
    private:
        vector<Symbole*> stacksymbole;
        vector<Etat*> stackstate;
        Lexer *lexer;
        string flux;
        bool bugFlag;

    public:
        Automate(string flux);
        ~Automate();
        void decalage(Symbole * s, Etat * e);
        void transitionsimple(Symbole * s, Etat * e);
        void lecture(void);
        void reduction(int n,Symbole * s);
        Symbole* popSymbol(void);
        void popAndDestroySymbol();
        void printStacks();
        void ignore();

};


