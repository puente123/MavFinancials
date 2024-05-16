//This file was created to test the display of the logo

#include <stdio.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int main(){

    
printf(RED"   *                (                                         \n");
printf(" (  `               )\\ )                                (     \n");
printf(" )\\))(     )  )    (()/( (           )          (     ) )\\    \n");
printf("((_)()\\ ( /( /((    /(_)))\\  (    ( /(  (     ( )\\ ( /(((_|   \n");
printf("(_()((_))(_)|_))\\  (_))_((_) )\\ ) )(_)) )\\ )  )((_))(_))_ )\\  \n");
printf(BLUE"|  \\/  ((_)__)((_) | |_  (_)_(_/(((_)_ _(_/( ((_|_|(_)_| ((_) \n");
printf("| |\\/| / _` \\ V /  | __| | | ' \\)) _` | ' \\)) _|| / _` | (_-< \n");
printf("|_|  |_\\__,_|\\_/   |_|   |_|_||_|\\__,_|_||_|\\__||_\\__,_|_/__/ \n"RESET);
                                                              

}