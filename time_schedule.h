/*
    time_schedule.h
    Version: 0.01
*/

#ifndef TIME_SCHEDULE_H
#define TIME_SCHEDULE_H

#include <stdint.h>
#include <time.h>

#define TIME_SCHEDULE_VERSION 0.01

#define S_DURATION(h,m,s) (3600*h+60*m+s)


typedef struct ScheduledTime {
    uint8_t hour, min, sec;
    uint32_t duration;
} ScheduledTime;

typedef time_t (*f_time_t)();

time_t default_time_callback();

class TimeSchedule {

    public:
        TimeSchedule();
        TimeSchedule( ScheduledTime );
        void SetSchedule( ScheduledTime );
        bool Check(); // return true if schedule criteria is met.
        void SetTimeCallback( f_time_t );

    private:
        ScheduledTime _scheduled_time;
        time_t _start_time, _end_time;
        f_time_t _time_callback;
        void update_times();
        time_t get_time(); // return seconds as in time.h

};

#endif //TIME_SCHEDULE_H