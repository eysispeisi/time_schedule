/*
    time_schedule.h
    Version: 0.02
*/
//#define __DEBUG__

#ifndef TIME_SCHEDULE_H
#define TIME_SCHEDULE_H

#include <stdint.h>
#include <time.h>

#define TIME_SCHEDULE_VERSION 0.02

#define S_DURATION(h,m,s) (3600*h+60*m+s)

#ifdef __DEBUG__
    void print_tm(struct tm*);
#endif//__DEBUG__

typedef struct ScheduledTime {
    uint8_t hour, min, sec;
    uint32_t duration;
} ScheduledTime;

#define CB_FUNC time_t
typedef CB_FUNC (*f_time_t)();

time_t default_time_callback();

enum CB_TYPES { 
    CB_ON_START = 0x01, 
    CB_ON_END = 0x02, 
    CB_GET_TIME = 0x04
    };

class TimeSchedule {

    public:
        TimeSchedule();
        TimeSchedule( ScheduledTime );

        void SetSchedule( ScheduledTime );
        bool Check(); // return true if schedule criteria is met.
        void SetCallback( int, f_time_t );
        // on_start callback
        // on_end callback
        

    private:
        bool _is_active;
        ScheduledTime _scheduled_time;
        time_t _start_time, _end_time;
        f_time_t _time_callback,
                 _on_start_callback,
                 _on_end_callback;
        void update_times();
        time_t get_time(); // return seconds as in time.h

};

#endif //TIME_SCHEDULE_H