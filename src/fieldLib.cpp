/*! ****************************************************************************
 *
 * \file    fieldLib.cpp
 * \brief   Main program of the project sicherDigger
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/

// FIXME: add obj type (physic, gfx(txt output) ) as a member of objFieldEntry

#include "objFieldEntry.h"
#include "objField.h"

#include "config.h"
#include "textEngine.h"
#include "timeEngine.h"
#include "physicsEngine.h"

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
//    objField field(24, 16);
    objField field(cfg);

    textEngine txt;
    timeEngine time(250000);    // 250 ms trigger value
    physicsEngine phy;

    txt.draw(field, textEngine::firstdraw);
    for (int i = 0; i < 10; i++)
    {
        char str[256];

        time.wait4Trigger();

        phy.run(field);

        snprintf(str, 256, "%.2f", time.getTriggerTime()/1000000.0);
        txt.draw(field, textEngine::redraw, str);
    }
    printf("\n\n\n");

    printf("iterations: %d\n", phy.getIterNum());

#if 0
    field.str(objField::list);
//    field.str(objField::array);
#endif

    return 0;

/* error handling */
out:
    return -1;
}

