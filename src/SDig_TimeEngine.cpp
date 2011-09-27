/*! ****************************************************************************
 *
 * \file    SDig_TimeEngine.cpp
 * \brief   Implementation of the TimeEngine class
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/


#include "SDig_TimeEngine.h"

#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

#include <string>

using namespace std;


/*!
 * \brief  Waits until the next trigger event occures.
 */
void SDig::TimeEngine::wait4TriggerEvent()
{
    /* get current time */
    uint64_t    currentTime = getTime();

    /* calculate the time of the next expected trigger event */
    uint64_t    nextTriggerTime = currentTime + mTriggerInterval - currentTime % mTriggerInterval;
    //uint64_t    nextTriggerTime = (currentTime/mTriggerInterval + 1) * mTriggerInterval;

    /* calculate the time to sleep */
    uint64_t    sleepTime = nextTriggerTime - currentTime;

    /* sleep */
    usleep(sleepTime);


#if 0
    /* update the last time value */
    mLastTime = getTime();

    /* calculate the waiting time until the next trigger event */
    mSleepTime = mTriggerInterval - (uint32_t)(mLastTime - mStartTime) % mTriggerInterval;

    /* sleep */
    usleep(mSleepTime);
#endif
}


/*!
 * \brief   Print the values of the class members into a string.
 * \param pLineNum
 *  Number of lines that are used in the string.
 * \return  Created string.
 */
string SDig::TimeEngine::getDebugInfo(int *pLineNum)
{
    char s[256] = "";
#if 0
    snprintf(s, 256,
        "mStartTime, mLastTime: %ld, %ld    \n"
        "consumed time (overall, since last trigger event), left time: %d, %d, %d   \n"
        "next trigger time: %d      \n",
        mStartTime, mLastTime,
        (uint32_t)(mLastTime - mStartTime),
        (uint32_t)(mLastTime - mStartTime) % mTriggerInterval, mSleepTime,
        (uint32_t)((mLastTime - mStartTime) / mTriggerInterval + 1) * mTriggerInterval
    );
#endif
    if (pLineNum != NULL) {
        *pLineNum = 3;
    }

    return string(s);
}

/* set time base value */
const uint64_t SDig::TimeEngine::mTimeBase = 1000000;      /*!< time base = 1s (1000000 us) */
