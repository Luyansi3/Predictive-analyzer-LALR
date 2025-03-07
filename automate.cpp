#include "automate.h"
#include <unistd.h>

Automate::Automate(string flux)
{   
    this->flux = flux;
    bugFlag = false;
    lexer = new Lexer(flux);
}
Automate::~Automate()
{
    delete lexer;
    for(unsigned int i=0; i<stackstate.size(); i++){
        delete stackstate[i];
    }
    for( unsigned int i=0; i<stacksymbole.size(); i++){
        delete stacksymbole[i];
    }
}

void Automate::printStacks(){
    cout << "state : ";
    for(unsigned int i=0; i<stackstate.size(); i++){
        stackstate[i]->print();
        cout << " ";
    }
    cout << endl;

    cout << "symbols : ";
    for(unsigned int i=0; i<stacksymbole.size(); i++){
        stacksymbole[i]->Affiche();
        cout << " ";
    }
    cout << endl;
}

void Automate::lecture(void){

    Etat* e0 = new E0;
    stackstate.push_back(e0); // initialiser la stack avec l'état E0
    Symbole * s;
    // printStacks();
    // cout << endl;
    while(true) {
        s=lexer->Consulter();
        // s->Affiche();
        // cout<<endl;
        // printStacks();
        // cout<<endl;

        if(stackstate.back()->transition(*this, s)) break;
        if(lexer->getTete() == (int) flux.length()&& bugFlag) break;
        
    }
    if(!bugFlag){
        delete s;
        Expr* E = (Expr*) stacksymbole.back();
        cout << "Résultat : " << E->eval() << endl;
    }
    
}

void Automate::ignore() {
    bugFlag = true;
    cout << flux << endl;
    for (int i = 0; i < lexer->getTete()-1; i++)
    {
        cout << "-";
    }
    cout << "^";
    for (unsigned int i = lexer->getTete(); i < flux.length() ; i++)
    {
        cout << "-";
    }
    cout <<endl;
    cout << "Error !" << endl;
    delete lexer->Consulter();
    lexer->Avancer();
    
    
}

void Automate::decalage(Symbole * s, Etat * e) {
    stacksymbole.push_back(s);
    stackstate.push_back(e);
    lexer->Avancer();
}

void Automate::transitionsimple(Symbole * s, Etat * e) {
    stacksymbole.push_back(s);
    stackstate.push_back(e);
}

void Automate::reduction(int n, Symbole * s) {
    for (int i=0;i<n;i++)
    {
        delete(stackstate.back());
        stackstate.pop_back();
    }
    stackstate.back()->transition(*this,s);
}

Symbole* Automate::popSymbol(void){
    Symbole* s = stacksymbole.back();
    // delete(stacksymbole.back());
    stacksymbole.pop_back();
    return s;
}

void Automate::popAndDestroySymbol(){
    delete (stacksymbole.back());
    stacksymbole.pop_back();
}
