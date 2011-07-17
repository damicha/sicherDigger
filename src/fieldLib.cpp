/***************************************************************************//**
 *
 * \file    fieldLib.cpp
 * \brief   Main program of the project sicherDigger
 *
 * \author  damicha of defect
 * \data    2011
 *
 ******************************************************************************/

// FIXME: add obj type (physic, gfx(txt output) ) as a member of baseObj

#include "baseObj.h"
#include "baseObjField.h"

#include "txtEngine.h"

#include <stdio.h>
using namespace std;



/*
 * main
 */
int main(void)
{
    baseObjField field(7, 5);

    txtEngine txt_engine;

    txt_engine.draw(field, txtEngine::firstdraw);
    for (int i = 0; i < 3; i++) {
        txt_engine.draw(field);
    }

#if 0
    for(int i = 0; i < field.objs.size(); i++) {
        printf("position: %2d, data: %s\n", i, field.objs[i].str().c_str()); 
    }
//    field.str(baseObjField::list);
    field.str(baseObjField::array);
#endif
    return 0;

/* error handling */
out:
    return -1;
}

