#pragma once


#include<iostream>
#include "symbole.h"


class Automate;

class Etat
{
    public:
        Etat(string name) : name(name) { }
        virtual ~Etat() { }
        virtual void print() const {cout << name;}
        virtual bool transition(Automate &automate, Symbole *s) = 0;
        string getName() const {return name;}
    protected:
        string name;
};

class E0: public Etat
{
    public:
        E0() : Etat("E0") { }
        ~E0() { }
    
        bool transition(Automate &automate, Symbole *s);

};

class E1: public Etat
{
    public:
        E1() : Etat("E1") { }
        ~E1() { }
        bool transition(Automate &automate, Symbole *s);

};

class E2: public Etat
{
    public:
        E2() : Etat("E2") { }
        ~E2() { }
        bool transition(Automate &automate, Symbole *s);

};

class E3: public Etat
{
    public:
        E3() : Etat("E3") { }
        ~E3() { }
        bool transition(Automate &automate, Symbole *s);

};

class E4: public Etat
{
    public:
        E4() : Etat("E4") { }
        ~E4() { }
        bool transition(Automate &automate, Symbole *s);

};

class E5: public Etat
{
    public:
        E5() : Etat("E5") { }
        ~E5() { }
        bool transition(Automate &automate, Symbole *s);

};

class E6: public Etat
{
    public:
        E6() : Etat("E6") { }
        ~E6() { }
        bool transition(Automate &automate, Symbole *s);

};
class E7: public Etat
{
    public:
        E7() : Etat("E7") { }
        ~E7() { }
        bool transition(Automate &automate, Symbole *s);

};
class E8: public Etat
{
    public:
        E8() : Etat("E8") { }
        ~E8() { }
        bool transition(Automate &automate, Symbole *s);

};
class E9: public Etat
{
    public:
        E9() : Etat("E9") { }
        ~E9() { }
        bool transition(Automate &automate, Symbole *s);

};