#include <iostream>
#include "automate.h"


int main(void) {
   // string chaine("(1+34)*123");
   // string chaine("(1+34)*123");
   // string chaine("1+34*++(1+1))+(+)ff23");
<<<<<<< HEAD
   
   Automate a = Automate(chaine);
=======
   string input;
   cout << "entrer une expression: ";
   cin >> input;

   Automate a = Automate(input);
>>>>>>> 3f28310 (add a prompt)

   a.lecture();

   return 0;
}

