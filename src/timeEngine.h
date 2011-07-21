/***************************************************************************//**
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


#ifndef _TIMEENGINE_H_
#define _TIMEENGINE_H_

#include "txtEngine.h"

#include <sys/time.h>
#include <stdint.h>
using namespace std;


/*!
 * \class   timeEngine
 */
class timeEngine
{
/* ======== class attributes ======== */    
private:
    uint64_t    start_time;         /*!< The first measured time in us */
    uint64_t    last_time;          /*!< The last measured time in us */
    uint32_t    trigger_interval;   /*!< Determines the trigger points in us */

/* ======== functions ======== */    

public:
    /*!
     * \brief   constructor
     * \param   trigger_interval   Trigger interval in us.
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
        uint32_t sleep_time = trigger_interval - (uint32_t)(last_time - start_time) % trigger_interval; 

#if 1
        printf("start_time, last_time: %u, %u\n"
               "consumed time (overall, since last trigger event), left time: %d, %d, %d\n"
               "next trigger time: %d\n",
               start_time, last_time,
               (uint32_t)(last_time - start_time),
               (uint32_t)(last_time - start_time) % trigger_interval, sleep_time,
               (uint32_t)((last_time - start_time) / trigger_interval + 1) * trigger_interval);

        txtEngine::moveCursorLinesUp(3);

#endif
        /* sleep */
        usleep(sleep_time);
    }

    /*!
     * \brief  Get the time of the last trigger event.
     */
    uint64_t getTriggerTime() {
        return last_time - start_time;
    }


};

#endif // _TIMEENGINE_H_
