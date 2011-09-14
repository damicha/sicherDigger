/*! ****************************************************************************
 *
 * \file    SDig_TimeEngine.h
 * \brief   Provides common time and trigger functions.
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \details
 *  The time value is stored in micro seconds as a 64 bit unsigned integer value.
 *  The gettimeofday() function is used to get the time from system.
 *
 ******************************************************************************/


#ifndef _SDIG_TIME_ENGINE_H_
#define _SDIG_TIME_ENGINE_H_

#include "SDig_TextEngine.h"

#include <sys/time.h>
#include <stdint.h>

#include <string>

using namespace std;


namespace SDig {

/*!
 * \class   TimeEngine
 */
class TimeEngine
{
/* ======== class attributes ======== */    
public:
    const static uint32_t  mTimeBase;      /*!< time base value in micro seconds */

private:
    uint64_t    mStartTime;         /*!< The first measured time in us */
    uint64_t    mLastTime;          /*!< The last measured time in us */
    uint32_t    mSleepTime;         /*!< Time to sleep until next trigger event will occur */
    uint32_t    mTriggerInterval;   /*!< Determines the trigger points in us */

/* ======== functions ======== */    

public:
    /*!
     * \brief   constructor
     * \param   triggerInterval
     *  Trigger interval in us. Default value is 1000000 (1 second).
     */
    TimeEngine(const uint32_t triggerInterval = 1000000) {
        setStartTime();
        setTriggerInterval(triggerInterval);
    }

    /*!
     * \brief   Set the start time.
     */
    void setStartTime(void) {
        timeval t_val;
        gettimeofday(&t_val, NULL);
        mStartTime = timeval2us(t_val);
    }

    /*!
     * \brief   Set the trigger interval.
     * \param   triggerInterval   
     *  Trigger interval in us.
     */
    void setTriggerInterval(const uint32_t triggerInterval) {
        mTriggerInterval = triggerInterval;
    }

    /*!
     * \brief   Converts the values of a timeval structure into a 64 bit value
     *          of micro seconds
     * \param   t
     *  The timeval structure.
     * \return  64 bit time value in micro seconds. 
     */
    uint64_t timeval2us(const timeval &t) {
        return ((uint64_t)t.tv_sec*1000000 + (uint64_t)t.tv_usec);
    }

    /*!
     * \brief  Waits until the next trigger event occures.
     */
    void wait4Trigger() {
        /* update the last time value */
        timeval t_val;
        gettimeofday(&t_val, NULL);
        mLastTime = timeval2us(t_val);

        /* calculate the waiting time until the next trigger event */
        mSleepTime = mTriggerInterval - (uint32_t)(mLastTime - mStartTime) % mTriggerInterval;

        /* sleep */
        usleep(mSleepTime);
    }

    /*!
     * \brief   Print the values of the class members into a string.
     * \param pLineNum
     *  Number of lines that are used in the string.
     * \return  Created string.
     */
    string getDebugInfo(int *pLineNum = NULL)
    {
        char s[256];

        snprintf(s, 256,
            "mStartTime, mLastTime: %u, %u    \n"
            "consumed time (overall, since last trigger event), left time: %d, %d, %d   \n"
            "next trigger time: %d      \n",
            mStartTime, mLastTime,
            (uint32_t)(mLastTime - mStartTime),
            (uint32_t)(mLastTime - mStartTime) % mTriggerInterval, mSleepTime,
            (uint32_t)((mLastTime - mStartTime) / mTriggerInterval + 1) * mTriggerInterval);

        if (pLineNum != NULL) {
            *pLineNum = 3;
        }

        return string(s);
    }


    /*!
     * \brief   Get the time of the last trigger event.
     * \return  Calculated time.
     */
    uint64_t getTriggerTime() {
        return mLastTime - mStartTime;
    }


};


/* set time base value */
const uint32_t TimeEngine::mTimeBase = 1000000;      /*!< time base = 1s (1000000 us) */


}       // namespace

#endif // _SDIG_TIME_ENGINE_H_
