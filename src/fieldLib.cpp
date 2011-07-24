/*! ****************************************************************************
 *
 * \file    fieldLib.cpp
 * \brief   Main program of the project sicherDigger
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/

// FIXME: add obj type (physic, gfx(txt output) ) as a member of baseObj

#include "baseObj.h"
#include "baseObjField.h"

#include "config.h"
#include "textEngine.h"
#include "timeEngine.h"

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

/* load configurations */
#include "configData.h"

using namespace std;




/*
 * main
 */
int main(void)
{

    config cfg(field_a);
    //baseObjField field(24, 16);
    baseObjField field(cfg);

    textEngine txt;
    timeEngine time(250000);    // 250 ms trigger value

    txt.draw(field, textEngine::firstdraw);
    for (int i = 0; i < 10; i++)
    {
        char str[256];

        time.wait4Trigger();

        snprintf(str, 256, "%.2f", time.getTriggerTime()/1000000.0);
        txt.draw(field, textEngine::redraw, str);
    }
    printf("\n\n\n");

#if 1
//    field.str(baseObjField::list);
    field.str(baseObjField::array);
#endif

    return 0;

/* error handling */
out:
    return -1;
}

