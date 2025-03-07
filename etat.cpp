#include "etat.h"
#include "automate.h"


bool E0::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        case EXPR:
            automate.transitionsimple(s, new E1);
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E1::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case PLUS:
            automate.decalage(s, new E4);
            break;
        case MULT:
            automate.decalage(s, new E5);
            break;
        case FIN:
            return true;
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E2::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        case EXPR:
            automate.transitionsimple(s, new E6);
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E3::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            {Entier* s1 = (Entier*) automate.popSymbol();
            automate.reduction(1,new ExprEnt(s1));
            break;}
        default :
            automate.ignore();
            break;

    }
    return false;
}

bool E4::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        case EXPR:
            automate.transitionsimple(s, new E7);
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E5::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3);
            break;
        case OPENPAR:
            automate.decalage(s, new E2);
            break;
        case EXPR:
            automate.transitionsimple(s, new E8);
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E6::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case PLUS:
            automate.decalage(s, new E4);
            break;
        case MULT:
            automate.decalage(s, new E5);
            break;
        case CLOSEPAR:
            automate.decalage(s, new E9);
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E7::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case PLUS:
        case CLOSEPAR:
        case FIN:
            {Expr* s1 = (Expr*) automate.popSymbol();
            automate.popAndDestroySymbol();
            Expr* s2 = (Expr*) automate.popSymbol();
            automate.reduction(3, new ExprAdd(s2, s1));
            break;}
        case MULT:
            automate.decalage(s, new E5);
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

bool E8::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case PLUS:
        case CLOSEPAR:
        case FIN:
        case MULT:
            {Expr* s1 = (Expr*) automate.popSymbol();
            automate.popAndDestroySymbol();
            Expr* s2 = (Expr*) automate.popSymbol();
            automate.reduction(3,new ExprMult(s2, s1));
            break;}

        default:
            automate.ignore();
            break;
    }
    return false;
}


bool E9::transition(Automate &automate,Symbole *s)
{
    switch (*s)
    {
        case PLUS:
        case CLOSEPAR:
        case FIN:
        case MULT:
            {automate.popAndDestroySymbol();
            Expr* s1 = (Expr*) automate.popSymbol();
            automate.popAndDestroySymbol();
            automate.reduction(3,new ExprPar(s1));
            break;}
        default:
            automate.ignore();
            break;
    }
    return false;
}
