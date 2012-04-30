/*! ****************************************************************************
 *
 * \file    TimeEngine.h
 * \brief   Declarations of TimeEngine class
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory. 
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
 *  The class has its own local time that is calculated by substracting the
 *  fixed system start time and the current system time.
 */
// FIXME: add trigger events for :
// gfxEngine, phyEngine
//  - start/stop, set/get

class TimeEngine
{
/* ======== class attributes ======== */    
private:
    uint64_t    mSystemStartTime;   /*!< Global point in time that is
                                         the trigger's start time */
    uint64_t    mTriggerInterval;   /*!< Determines the time between two 
                                         trigger points in us */
    const static uint64_t  mTimeBase;      /*!< time base value in micro seconds */

/* ======== functions ======== */    
public:
    /*!
     * \brief   constructor
     * \param   pTriggerInterval
     *  Trigger interval in us. Default value is 1000000 (1 second).
     */
    TimeEngine(const uint64_t pTriggerInterval = 1000000)
    {
        resetTime();
        setTriggerInterval(pTriggerInterval);
    }

    /*!
     * \brief   Reset the start time.
     */
    void resetTime(void) {
        mSystemStartTime = getSystemTime();
    }


    /*!
     * \brief   Set the trigger interval.
     * \param   pTriggerInterval   
     *  Trigger interval in us.
     */
    void setTriggerInterval(const uint64_t pTriggerInterval) {
        mTriggerInterval = pTriggerInterval;
    }

    /*!
     * \brief   Get the trigger interval.
     * \return  Return with the trigger interval in us.
     */
    uint64_t getTriggerInterval(void) const {
        return mTriggerInterval;
    }

    /*!
     * \brief   Get the local time.
     * \return  Return with a class internal representation.
     */
    uint64_t getTime(void) const {
        return getSystemTime() - mSystemStartTime;
    }
    
private:
    /* Get time from system. */
    uint64_t getSystemTime(void) const;

    /* Converts the values of a timeval structure into a 64 bit value in micro seconds */
    uint64_t timeval2us(const timeval *pTimeVale) const;

public:
    /* Waits until the next trigger event occures. */
    void wait4TriggerEvent() const;
    
    /* Prints the values of the class members into a string. */
    string getDebugInfo(int *pLineNum = NULL) const;


    /*!
     * \brief   Get the time base;
     * \return  time base value in micro seconds.
     */
    uint64_t getTimeBase() const {
        return mTimeBase;
    }


};


}       // namespace

#endif // _SDIG_TIME_ENGINE_H_
