/*
    time_schedule.cpp
    Version: 0.02
*/

#include "time_schedule.h"

time_t default_time_callback()
{ 
    return time(NULL); 
}

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


void TimeSchedule::SetCallback( CB_TYPES cb_type, f_time_t callback )
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
    time_t now = this->get_time();

    struct tm *tm_start_time = gmtime(&now);
    tm_start_time->tm_hour = this->_scheduled_time.hour;
    tm_start_time->tm_min = this->_scheduled_time.min;
    tm_start_time->tm_sec = this->_scheduled_time.sec;

    this->_start_time = mktime( tm_start_time );
    this->_end_time = this->_start_time + this->_scheduled_time.duration;
}


bool isValid_time(ScheduledTime t) {
  return  ( 0 <= t.hour && t.hour <= 23 &&
            0 <= t.min && t.min <= 59 &&
            0 <= t.sec && t.sec <= 59 &&
            t.duration > 0 );
}