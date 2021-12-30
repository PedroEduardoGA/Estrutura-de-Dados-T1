#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sorteador.h"

char* Sorteio()
{
    int x;

    x=  rand() % 11;//x eh sorteado de 0 a 10: 0,1,2,3,4,5,6,7,8,9,10
    switch (x)
    {
        case 1 :
            return "red";
    
    
        case 2 :
            return "green";
    
    
        case 3 :
            return "yellow";
    
    
        case 4 :
            return "aquamarine";
    
    
        case 5 :
            return "indigo";
    
    
        case 6 :
            return "khaki";
    
    
        case 7 :
            return "orangered";
    
        case 8 :
            return "violet";

        case 9 :
            return "goldenrod";

        case 10 :
            return "aqua";
            
        case 11 :
            return "black";
    
    }
    return "white";
}