/*
    time_schedule.h
    Version: 0.02
*/

#ifndef TIME_SCHEDULE_H
#define TIME_SCHEDULE_H

#include <stdint.h>
#include <time.h>

#define TIME_SCHEDULE_VERSION 0.02

#define S_DURATION(h,m,s) ( (uint32_t)( 3600*(uint32_t)h + 60*(uint16_t)m + s ) )

typedef struct time_duration {
    uint8_t hour, min, sec;
    uint32_t duration;
} time_duration;

#define CB_FUNC time_t
typedef CB_FUNC (*f_time_t)();

time_t default_time_callback();

enum CB_TYPES { 
    CB_ON_START = 0x01, 
    CB_ON_END = 0x02, 
    CB_GET_TIME = 0x04
    };

bool isValid_time(time_duration);

class TimeSchedule {

    public:
        TimeSchedule();
        TimeSchedule( time_duration );

        void SetSchedule( time_duration );
        bool Check(); // return true if schedule criteria is met.
        void SetCallback( CB_TYPES, f_time_t );

    private:
        bool _is_active;
        time_duration _scheduled_time;
        time_t _start_time, _end_time;
        f_time_t _time_callback,
                 _on_start_callback,
                 _on_end_callback;
        void update_times();
        time_t get_time(); // return seconds as in time.h

};

#endif //TIME_SCHEDULE_H