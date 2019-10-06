#include "time_schedule.h"
#include <stdio.h>
#include <time.h>

time_t current_time = S_DURATION(23, 58, 0);

CB_FUNC custom_time_callback()
{
    return current_time;
}

void print_time_t( time_t t ) {
    struct tm *t_tm;
    t_tm = gmtime( &t );
    printf("%04d %02d/%02d %02d:%02d:%02d", 
        t_tm->tm_year+1900, 
        t_tm->tm_mon+1,
        t_tm->tm_mday,
        t_tm->tm_hour,
        t_tm->tm_min,
        t_tm->tm_sec
        );
}

CB_FUNC on_start() {
    struct tm *t_tm;
    t_tm = gmtime( &current_time );
    printf("on_start(), time: ");
    print_time_t(current_time);
    printf("\n");
}

CB_FUNC on_end() {
    struct tm *t_tm;
    t_tm = gmtime( &current_time );
    printf("on_end(), time: ");
    print_time_t(current_time);
    printf("\n");
}

int main(int argc, char *argv[])
{
    ScheduledTime s = { 23, 59, 0, S_DURATION(12, 0, 0) };

    TimeSchedule t = TimeSchedule();
    t.SetSchedule(s);
    //t.SetTimeCallback( &custom_time_callback );
    t.SetCallback( CB_GET_TIME, &custom_time_callback );
    t.SetCallback( CB_ON_START, &on_start );
    t.SetCallback( CB_ON_END, &on_end );
    printf("1: %d\n", t.Check());

    bool check;
    for ( int i = 0; i<(60*60*48); i++ )
    {
        current_time += 1;
        check = t.Check();
        if ( check ) {
            //printf("%d: %d\n", current_time, t.Check());
        }
    }
    
    struct tm tm_t = { 25, 15, 03, 17, 9, 119, 0, 0, 0 };
    /*struct tm tm_t;
    tm_t.tm_sec = 25;
    tm_t.tm_min = 15;
    tm_t.tm_hour = 03;
    tm_t.tm_mday = 17;
    tm_t.tm_mon = ;
    tm_t.tm_ = ;
    */
    time_t rawtime = mktime( &tm_t );
    //printf("%d\n", rawtime);
    //print_tm( &tm_t );
    return 0;
}
