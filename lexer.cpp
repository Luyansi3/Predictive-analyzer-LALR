#include "lexer.h"

// La méthode Consulter() renvoie le symbole (token) courant sans avancer dans le flux.
// Si le tampon est déjà rempli, le symbole pré-analysé est retourné.
// Sinon, la méthode analyse le flux à partir de la position "tete" pour créer le prochain symbole.
Symbole * Lexer::Consulter() {
   // Si aucun symbole n'a été stocké dans le tampon
   if (!tampon) {
      // Si la position "tete" atteint la fin du flux, on crée un symbole FIN
      if (tete == (int) flux.length()) tampon = new Symbole(FIN);
      else
      {
         switch (flux[tete]) {
            case '(':
               tampon = new Symbole(OPENPAR);
               tete++;
               break;
            case ')':
               tampon = new Symbole(CLOSEPAR);
               tete++;
               break;
            case '*':
               tampon = new Symbole(MULT);
               tete++;
               break;
            case '+':
               tampon = new Symbole(PLUS);
               tete++;
               break;
            default:
               if (flux[tete] <= '9' && flux[tete] >= '0') {
                  // Conversion du caractère en entier (par exemple, '3' devient 3)
                  int resultat = flux[tete] - '0';
                  int i = 1;
                  while (flux[tete + i] <= '9' && flux[tete + i] >= '0') {
                     resultat = resultat * 10 + (flux[tete + i] - '0');
                     i++;
                  }
                  // Avance la tête de lecture de i positions (pour ignorer tous les chiffres composant le nombre)
                  tete = tete + i;
                  // Crée un symbole de type Entier avec la valeur calculée
                  tampon = new Entier(resultat);
               }
               else {
                  // Si le caractère ne correspond à aucun symbole reconnu, on crée un symbole d'erreur et on avance d'un caractère
                  tampon = new Symbole(ERREUR);
                  tete++;
               }
         }
      }
   }
   // Retourne le symbole actuellement stocké dans le tampon
   return tampon;
}

// La méthode Avancer() vide le tampon afin de forcer la lecture du prochain symbole lors de l'appel suivant de Consulter().
// Cela permet de "consommer" le symbole courant une fois qu'il a été traité.
void Lexer::Avancer() {
   tampon = nullptr;
}
