/*
    time_schedule.cpp
    Version: 0.02
*/

#include "time_schedule.h"

#ifdef __DEBUG__
    #include <stdio.h>
#endif//__DEBUG__

time_t default_time_callback()
{ 
    return time(NULL); 
}

#ifdef __DEBUG__
void print_tm(struct tm * tmptr )
{
    printf("%04d %02d/%02d %02d:%02d:%02d\n", 
        tmptr->tm_year+1900, 
        tmptr->tm_mon,
        tmptr->tm_mday,
        tmptr->tm_hour,
        tmptr->tm_min,
        tmptr->tm_sec
        );
}
#endif//__DEBUG__

TimeSchedule::TimeSchedule( ScheduledTime st )
{
    this->_scheduled_time = st;
    this->_time_callback = &default_time_callback;
    this->_on_start_callback = &default_time_callback;
    this->_on_end_callback = &default_time_callback;
    this->_is_active = false;

    this->update_times();
}

TimeSchedule::TimeSchedule()
{
    this->_time_callback = &default_time_callback;
}

void TimeSchedule::SetSchedule( ScheduledTime st )
{
    this->_scheduled_time = st;
    this->update_times();
}

bool TimeSchedule::Check()
{
    time_t now = this->get_time();

    if ( this->_end_time <= now ) 
    {
        this->update_times();
    }
    
    if ( this->_start_time <= now && now < this->_end_time ) {
        if ( !this->_is_active ) {
            this->_is_active = true;
            this->_on_start_callback();
        }
        return true;
    } else {
        if ( this->_is_active ) {
            this->_is_active = false;
            this->_on_end_callback();
        }
    return false;
    }
}

time_t TimeSchedule::get_time()
{
    return (*this->_time_callback)();
}


void TimeSchedule::SetCallback( int cb_type, f_time_t callback )
{
    switch ( cb_type ) {
        
        case ( CB_GET_TIME ) :
            this->_time_callback = callback;
            this->update_times();
        break;
        
        case ( CB_ON_START ) :
            this->_on_start_callback = callback;
        break;
            
        case ( CB_ON_END ) :
            this->_on_end_callback = callback;
        break;

    }
}


void TimeSchedule::update_times()
{
    #ifdef __DEBUG__
        printf("update_times()\n");
    #endif//__DEBUG__

    time_t now = this->get_time();

    #ifdef __DEBUG__
        struct tm * tm_now = gmtime(&now);
        printf("current time: ");
        print_tm(tm_now);
    #endif//__DEBUG__

    struct tm *tm_start_time = gmtime(&now);
    tm_start_time->tm_hour = this->_scheduled_time.hour;
    tm_start_time->tm_min = this->_scheduled_time.min;
    tm_start_time->tm_sec = this->_scheduled_time.sec;

    #ifdef __DEBUG__
        printf("start time: ");
        print_tm(tm_start_time);
    #endif//__DEBUG__

    this->_start_time = mktime( tm_start_time );
    this->_end_time = this->_start_time + this->_scheduled_time.duration;

    #ifdef __DEBUG__
        struct tm *tm_end_time = gmtime( &this->_end_time );
        printf("end time: ");
        print_tm(tm_end_time);
    #endif//__DEBUG__

}

