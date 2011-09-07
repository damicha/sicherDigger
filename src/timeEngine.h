/*! ****************************************************************************
 * \file    timeEngine.h
 * \class   timeEngine
 * \brief   Provides common time and trigger functions.
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \details
 * The time value is stored in micro seconds as a 64 bit unsigned integer value.
 * The gettimeofday() function is used to get the time from system.
 *
 ******************************************************************************/


#ifndef _TIME_ENGINE_H_
#define _TIME_ENGINE_H_

#include "textEngine.h"

#include <sys/time.h>
#include <stdint.h>

#include <string>

using namespace std;


/*!
 * \class   timeEngine
 */
class timeEngine
{
/* ======== class attributes ======== */    
public:
    const static uint32_t  time_base;      /*!< time base value in micro seconds */

private:
    uint64_t    start_time;         /*!< The first measured time in us */
    uint64_t    last_time;          /*!< The last measured time in us */
    uint32_t    sleep_time;         /*!< Time to sleep until next trigger event will occur */
    uint32_t    trigger_interval;   /*!< Determines the trigger points in us */

/* ======== functions ======== */    

public:
    /*!
     * \brief   constructor
     * \param   trigger_interval   Trigger interval in us. Default value is
     *                             1000000 (1 second).
     */
    timeEngine(uint32_t trigger_interval = 1000000) {
        setStartTime();
        setTriggerInterval(trigger_interval);
    }

    /*!
     * \brief   Set the start time.
     */
    void setStartTime(void) {
        timeval t_val;
        gettimeofday(&t_val, NULL);
        start_time = timeval2us(t_val);
    }

    /*!
     * \brief   Set the trigger interval.
     * \param   trigger_interval   Trigger interval in us.
     */
    void setTriggerInterval(const uint32_t trigger_interval) {
        this->trigger_interval = trigger_interval;
    }

    /*!
     * \brief   Converts the values of a timeval structure into a 64 bit value
     *          of micro seconds
     * \param   t   The timeval structure.
     * \return      64 bit time value in micro seconds. 
     */
    uint64_t timeval2us(const timeval &t) {
        return ((uint64_t)t.tv_sec*1000000 + (uint64_t)t.tv_usec);
    }

    /*!
     * \ brief  Waits until the next trigger event occures.
     */
    void wait4Trigger() {
        /* update the last time value */
        timeval t_val;
        gettimeofday(&t_val, NULL);
        last_time = timeval2us(t_val);

        /* calculate the waiting time until the next trigger event */
        sleep_time = trigger_interval - (uint32_t)(last_time - start_time) % trigger_interval;

        /* sleep */
        usleep(sleep_time);
    }

    /*!
     * \brief   Print the values of the class members into a string.
     * \param lines
     *  Number of lines that are used in the string.
     * \return  Created string.
     */
    string getDebugInfo(int *lines = NULL)
    {
        char s[256];

        snprintf(s, 256,
            "start_time, last_time: %u, %u\n"
            "consumed time (overall, since last trigger event), left time: %d, %d, %d\n"
            "next trigger time: %d\n",
            start_time, last_time,
            (uint32_t)(last_time - start_time),
            (uint32_t)(last_time - start_time) % trigger_interval, sleep_time,
            (uint32_t)((last_time - start_time) / trigger_interval + 1) * trigger_interval);

        if (lines != NULL) {
            *lines = 3;
        }

        return string(s);
    }


    /*!
     * \brief  Get the time of the last trigger event.
     */
    uint64_t getTriggerTime() {
        return last_time - start_time;
    }


};


/* set time base value */
const uint32_t timeEngine::time_base = 1000000;      /*!< time base = 1s (1000000 us) */

#endif // _TIME_ENGINE_H_
