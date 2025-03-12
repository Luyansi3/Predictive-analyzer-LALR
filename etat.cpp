#include "etat.h"
#include "automate.h"

/* -------------------------------------------------------------------
   Etat E0 : Etat initial de l'automate
-------------------------------------------------------------------*/
bool E0::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3); // entier => décalage vers l'état E3.
            break;
        case OPENPAR:
            automate.decalage(s, new E2); // parenthèse ouvrante => décalage vers l'état E2.
            break;
        case EXPR:
            automate.transitionsimple(s, new E1); // expression => transition simple vers E1.
            break;
        default:
            automate.ignore();
            break;
    }
    return false; // analyse continue
}

/* -------------------------------------------------------------------
   Etat E1 : Etat d'attente après une expression
   Gère les opérateurs ou la fin de l'expression.
-------------------------------------------------------------------*/
bool E1::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        case PLUS:
            automate.decalage(s, new E4); // plus => décalage vers l'état E4 (préparation à l'addition).
            break;
        case MULT:
            automate.decalage(s, new E5); // multiplication => décalage vers l'état E5 (préparation à la multiplication).
            break;
        case FIN:
            return true; // fin => arrêt de l'analyse
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E2 : Etat gérant l'ouverture d'une parenthèse
   Permet de démarrer une nouvelle analyse d'expression dans 
   une parenthèse.
-------------------------------------------------------------------*/
bool E2::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3); // entier => décalage vers l'état E3.
            break;
        case OPENPAR:
            automate.decalage(s, new E2); // parenthèse ouvrante => décalage vers l'état E2 (traiter parenthèse imbriquée).
            break;
        case EXPR:
            automate.transitionsimple(s, new E6); // expression (résultat d'une réduction) => transition simple vers E6.
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E3 : Etat de réduction d'un entier
   Cet état intervient lorsque le symbole lu est un entier et que 
   la prochaine entrée doit déclencher une réduction.
-------------------------------------------------------------------*/
bool E3::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        // Pour les symboles qui ne font pas partie de l'entier (opérateur, parenthèse fermante ou FIN)
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
        {
            // Retirer l'entier de la pile
            Entier* s1 = (Entier*) automate.popSymbol();
            // Effectuer une réduction d'un symbole en créant une expression entière
            automate.reduction(1, new ExprEnt(s1));
            break;
        }
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E4 : Etat après lecture d'un opérateur '+'
   Prépare l'addition en attendant le second opérande.
-------------------------------------------------------------------*/
bool E4::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3); // entier => décalage vers l'état E3.
            break;
        case OPENPAR:
            automate.decalage(s, new E2); // parenthèse ouvrante => décalage vers l'état E2 (traiter parenthèse imbriquée).
            break;
        case EXPR:
            automate.transitionsimple(s, new E7); // expression (résultat d'une réduction) => transition simple vers E7 (réduction d'addition).
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E5 : Etat après lecture d'un opérateur '*'
   Prépare la multiplication en attendant le second opérande.
-------------------------------------------------------------------*/
bool E5::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        case INT:
            automate.decalage(s, new E3); // entier => décalage vers l'état E3.
            break;
        case OPENPAR:
            automate.decalage(s, new E2); // parenthèse ouvrante => décalage vers l'état E2.
            break;
        case EXPR:
            automate.transitionsimple(s, new E8); // expression (résultat d'une réduction) => transition simple vers E8 (réduction de multiplication).
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E6 : Etat en cours de traitement d'une parenthèse
   Cet état attend la fermeture de la parenthèse ou la continuation 
   de l'expression avec un opérateur.
-------------------------------------------------------------------*/
bool E6::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        case PLUS:
            automate.decalage(s, new E4); // plus => décalage vers l'état E4 (préparation à l'addition).
            break;
        case MULT:
            automate.decalage(s, new E5); // multiplication => décalage vers l'état E5 (préparation à la multiplication).
            break;
        case CLOSEPAR:
            automate.decalage(s, new E9); // parenthèse fermante => décalage vers l'état E9 (préparation à la réduction de l'expression entre parenthèses).
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E7 : Etat de réduction pour l'addition
   Gère la réduction d'une expression de la forme expr + expr.
-------------------------------------------------------------------*/
bool E7::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        // Lorsque le symbole suivant est un plus, une parenthèse fermante ou FIN,
        // cela indique la fin de l'expression d'addition.
        case PLUS:
        case CLOSEPAR:
        case FIN:
        {
            // Récupérer le second opérande (à droite du '+')
            Expr* s1 = (Expr*) automate.popSymbol();
            // Supprimer le symbole représentant l'opérateur '+'
            automate.popAndDestroySymbol();
            // Récupérer le premier opérande (à gauche du '+')
            Expr* s2 = (Expr*) automate.popSymbol();
            // Réduire les trois éléments (opérande, opérateur, opérande) en une expression d'addition
            automate.reduction(3, new ExprAdd(s2, s1));
            break;
        }
        case MULT:
            automate.decalage(s, new E5); // multiplication => décalage vers l'état E5 (préparation à la multiplication).
            break;
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E8 : Etat de réduction pour la multiplication
   Réduit une séquence de symboles pour former une expression de multiplication.
-------------------------------------------------------------------*/
bool E8::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        // Pour les symboles indiquant la fin de l'expression (plus, parenthèse fermante, FIN ou multiplication),
        // réaliser la réduction de la multiplication.
        case PLUS:
        case CLOSEPAR:
        case FIN:
        case MULT:
        {
            // Récupérer le second opérande (à droite du '*')
            Expr* s1 = (Expr*) automate.popSymbol();
            // Supprimer le symbole de l'opérateur '*'
            automate.popAndDestroySymbol();
            // Récupérer le premier opérande (à gauche du '*')
            Expr* s2 = (Expr*) automate.popSymbol();
            // Réduire les trois éléments en une expression de multiplication
            automate.reduction(3, new ExprMult(s2, s1));
            break;
        }
        default:
            automate.ignore();
            break;
    }
    return false;
}

/* -------------------------------------------------------------------
   Etat E9 : Etat de réduction pour la parenthèse fermante
   Réduit une expression entre parenthèses en retirant les symboles 
   de délimitation et en ne gardant que l'expression.
-------------------------------------------------------------------*/
bool E9::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
        // Pour les symboles indiquant la fin ou la continuation de l'expression,
        // réaliser la réduction de la parenthèse.
        case PLUS:
        case CLOSEPAR:
        case FIN:
        case MULT:
        {
            // Supprimer la parenthèse ouvrante ou un symbole inutile
            automate.popAndDestroySymbol();
            // Récupérer l'expression à l'intérieur des parenthèses
            Expr* s1 = (Expr*) automate.popSymbol();
            // Supprimer la parenthèse fermante ou le symbole séparateur
            automate.popAndDestroySymbol();
            // Réduire les trois symboles en une expression parenthésée
            automate.reduction(3, new ExprPar(s1));
            break;
        }
        default:
            automate.ignore();
            break;
    }
    return false;
}