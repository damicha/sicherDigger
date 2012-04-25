/*! ****************************************************************************
 *
 * \file    SDig_TimeEngine.cpp
 * \brief   Implementation of the TimeEngine class
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/


#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

#include <string>

#include "SDig_TimeEngine.h"


using namespace std;
using namespace SDig;

/*!
 * \brief  Waits until the next trigger event occures.
 */
void TimeEngine::wait4TriggerEvent() const
{
    /* get current time */
    uint64_t    currentTime = getTime();

    /* calculate the time of the next trigger event */
    uint64_t    nextTriggerTime;
    nextTriggerTime = currentTime + mTriggerInterval - currentTime % mTriggerInterval;

    /* calculate the time to sleep */
    uint64_t    sleepTime = nextTriggerTime - currentTime;

    /* sleep until the trigger event is reached */
    usleep(sleepTime);
}

/*!
 * \brief   Get time from system.
 * \return  Return with a class internal representation.
 */
uint64_t TimeEngine::getSystemTime(void) const
{
    /* get time from system */
    timeval t_val;
    gettimeofday(&t_val, NULL);

    /* convert into class internal representation */
    uint64_t t = timeval2us(&t_val);

    return t;
}

/*!
 * \brief   Converts the values of a timeval structure into a 64 bit value
 *          in micro seconds.
 * \param   t
 *  The timeval structure.
 * \return  64 bit time value in micro seconds. 
 */
uint64_t TimeEngine::timeval2us(const timeval *pTimeVal) const
{
    return ((uint64_t)pTimeVal->tv_sec*1000000 +
            (uint64_t)pTimeVal->tv_usec);
}


/*!
 * \brief   Print the values of the class members into a string.
 * \param pLineNum
 *  Number of lines that are used in the string.
 * \return  Created string.
 */
string SDig::TimeEngine::getDebugInfo(int *pLineNum) const
{
    const int len = 128;
    char s[len] = "";
    snprintf(s, len, "current time: %ld  \n", getTime());
    
    if (pLineNum != NULL) {
        *pLineNum = 1;
    }

    return string(s);
}

/* set time base value */
const uint64_t SDig::TimeEngine::mTimeBase = 1000000;      /*!< time base = 1s (1000000 us) */


