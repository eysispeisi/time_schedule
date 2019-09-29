#include "time_schedule.h"
#include <stdio.h>
#include <time.h>

time_t current_time = S_DURATION(23, 58, 0);

time_t custom_time_callback()
{
    return current_time;
}

int main(int argc, char *argv[])
{
    ScheduledTime s = { 23, 59, 0, S_DURATION(0, 2, 0) };

    TimeSchedule t = TimeSchedule();
    t.SetSchedule(s);
    t.SetTimeCallback( &custom_time_callback );
    printf("1: %d\n", t.Check());

    bool check;
    for ( int i = 0; i<(60*60*24); i++ )
    {
        current_time += 60;
        check = t.Check();
        if ( check )
            printf("%d: %d\n", current_time, t.Check());
    }
    
    return 0;
}
