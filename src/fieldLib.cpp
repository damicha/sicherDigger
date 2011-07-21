/***************************************************************************//**
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

#include "txtEngine.h"
#include "timeEngine.h"

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
using namespace std;





/*
 * main
 */
int main(void)
{


    baseObjField field(24, 16);

    txtEngine txt;
    timeEngine time(250000);    // 250 ms trigger value

    txt.draw(field, txtEngine::firstdraw);
    for (int i = 0; i < 20; i++)
    {
        char str[256];

        time.wait4Trigger();

        snprintf(str, 256, "%.2f", time.getTriggerTime()/1000000.0);
        txt.draw(field, txtEngine::redraw, str);
        // wait until 0.25 seconds are gone
#if 0
        while(1) {
            // sleep for 10 milliseconds
            usleep(10000);

            gettimeofday(&end, 0); 
            double end_t = end.tv_sec + 1e-6*end.tv_usec;
            if (end_t > start_t + 0.25) {
                break;
            }
        };
#endif
//        printf("%f %f\n", end.tv_sec + 1e-6*end.tv_usec,
//                          end.tv_sec - start.tv_sec + 1e-6*(end.tv_usec - start.tv_usec));
    }

#if 0
    for(int i = 0; i < field.objs.size(); i++) {
        printf("position: %2d, data: %s\n", i, field.objs[i].str().c_str()); 
    }
//    field.str(baseObjField::list);
    field.str(baseObjField::array);
#endif
    printf("\n\n\n");
    return 0;

/* error handling */
out:
    return -1;
}

