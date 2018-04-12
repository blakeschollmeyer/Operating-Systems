#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "concol.h" // Get from http://www.cplusplus.com/articles/2ywTURfi/
                            // For gotoXY get from http://www.cplusplus.com/forum/beginner/88558/

int main()
{
      char c=0;
      int x, y;
      int increment,$;
      srand( (unsigned)time( NULL ) );
      setcolor(green,black);
          
      while (TRUE) //boucle infinie
      {
            c = (rand() % 250) + 11;
            x = rand() % 80;
            y = rand() % 25;
            
            if (c == 14)
            {
                  for (increment=0; increment <= 24; increment++)
                  {
                        GotoXY(x, increment);
                        printf("%c", 219);
                        if (increment >= 20 & increment <= 15){ GotoXY(x, increment - 5); printf("%c", 176); }
                        if (increment >= 15 & increment <= 10){ GotoXY(x, increment - 5); printf("%c", 177); }
                        if (increment >= 10 & increment <= 3) { GotoXY(x, increment - 7); printf("%c", 178); }
                        for($=0;$<24000000;$++)
                        {
                              $=$;
                        }
                  }
            }
            GotoXY(x, y);
            printf("%c", c);
      }
}
