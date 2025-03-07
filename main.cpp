#include <iostream>
#include "automate.h"


int main(void) {
   // string chaine("(1+34)*123");
   string chaine("(1+34)*123");
   // string chaine("1+34*++(1+1))+(+)ff23");

   Automate a = Automate(chaine);

   a.lecture();

   return 0;
}

