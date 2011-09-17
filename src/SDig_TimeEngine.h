/*! ****************************************************************************
 *
 * \file    SDig_TimeEngine.h
 * \brief   Declarations of TimeEngine class
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/


#ifndef _SDIG_TIME_ENGINE_H_
#define _SDIG_TIME_ENGINE_H_

#include <sys/time.h>
#include <stdint.h>

#include <string>

using namespace std;


namespace SDig {

/*!
 * \class   TimeEngine
 * \brief
 *  Provides common time and trigger functions.
 * \details
 *  The time value is stored in micro seconds as a 64 bit unsigned integer value.
 *  The gettimeofday() function is used to get the time from system.
 */
class TimeEngine
{
/* ======== class attributes ======== */    

private:
    uint64_t    mStartTime;         /*!< The first measured time in us */
    uint64_t    mLastTime;          /*!< The last measured time in us */
    uint32_t    mSleepTime;         /*!< Time to sleep until next trigger event will occur */
    uint32_t    mTriggerInterval;   /*!< Determines the trigger points in us */
    const static uint32_t  mTimeBase;      /*!< time base value in micro seconds */

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

    /* Waits until the next trigger event occures. */
    void wait4Trigger();
    
    /* Prints the values of the class members into a string. */
    string getDebugInfo(int *pLineNum = NULL);


    /*!
     * \brief   Get the time of the last trigger event.
     * \return  Calculated time.
     */
    uint64_t getTriggerTime() {
        return mLastTime - mStartTime;
    }


    /*!
     * \brief   Get the time base;
     * \return  time base value in micro seconds.
     */
    uint64_t getTimeBase() {
        return mTimeBase;
    }


};


}       // namespace

#endif // _SDIG_TIME_ENGINE_H_
