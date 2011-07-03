/* fieldLib.cpp */

// FIXME: add obj type (physic, gfx(txt output) ) as a member of baseObj

#include "baseObj.h"
#include "baseObjField.h"

#include <stdio.h>
using namespace std;



/*
 * main
 */
int main(void)
{
    baseObjField field(5, 5);

    for(int i = 0; i < field.objs.size(); i++) {
        printf("position: %2d, data: %s\n", i, field.objs[i].str().c_str()); 
    }
    return 0;

/* error handling */
out:
    return -1;
}

