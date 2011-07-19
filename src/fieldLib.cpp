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


    baseObjField field(12, 8);

    txtEngine txt;
    timeEngine time(250000);

    txt.draw(field, txtEngine::firstdraw);
    for (int i = 0; i < 20; i++)
    {
        time.wait4Trigger();

        // get the current time
        timeval start, end;
        gettimeofday(&start, 0);
        double start_t = start.tv_sec + 1e-6*start.tv_usec;

        usleep(10000);


//        txt.draw(field);
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
    
    return 0;

/* error handling */
out:
    return -1;
}

