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
#include "SDig_TextEngine.h"
#include "SDig_TimeEngine.h"
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

    SDig::TextEngine txt;
    SDig::TimeEngine time(250000);      // 250 ms trigger value
//    SDig::TimeEngine time(500000);      // trigger value
    physicsEngine phy;

    txt.drawField(field);
    txt.drawDebugInfo(time);

    bool stop = false;
    while(stop == false) 
    {
        char str[256];

        time.wait4Trigger();

        // FIXME:
        //  add SDigGameEngine
        //  get keys more than 4 times a second (60 times) <- game engine

        SDig::TextEngine::ButtonType    button = txt.getButton();
        physicsEngine::movement_t       moveDirection = physicsEngine::mtNone;
        
        switch(button)
        {
            case SDig::TextEngine::BT_LEFT:
                moveDirection = physicsEngine::mtLeft; 
                break;
            case SDig::TextEngine::BT_RIGHT:
                moveDirection = physicsEngine::mtRight;
                break;
            case SDig::TextEngine::BT_START:
                stop = true;                // leave the loop
                break;
        }

        phy.run(field, moveDirection);

        snprintf(str, 256, "%.2f", time.getTriggerTime()/SDig::TimeEngine::mTimeBase);
        txt.drawField(field, str);
        txt.drawDebugInfo(time);
    }
    printf("\n\n\n");

    printf("iterations: %d\n", phy.getIterNum());

#if 0
    txt.drawFieldList(field);
#endif
    return 0;
}

