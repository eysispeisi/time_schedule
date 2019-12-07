#include "time_schedule.h"
#include <stdio.h>
#include <time.h>

time_t current_time = S_DURATION(23, 58, 0);

CB_FUNC custom_time_callback()
{
    return current_time;
}

CB_FUNC on_start() {
    struct tm *t_tm;
    t_tm = gmtime( &current_time );
}

CB_FUNC on_end() {
    struct tm *t_tm;
    t_tm = gmtime( &current_time );
}


bool Test_Callback() {
    current_time = S_DURATION(23, 59, 58);
    ScheduledTime s = { 23, 59, 59, S_DURATION(0, 0, 2) };
    TimeSchedule t = TimeSchedule();
    t.SetSchedule(s);
    t.SetCallback( CB_GET_TIME, &custom_time_callback );
    t.SetCallback( CB_ON_START, &on_start );
    t.SetCallback( CB_ON_END, &on_end );
    
    if (t.Check() != false) {
        printf("Test_Callback failed: active before trigger");
        return 1;
    }

    current_time += 1;
    if (t.Check() != true) {
        printf("Test_Callback failed: not activated on time.");
        return 1;
    }

    current_time += 1;
    if (t.Check() != true) {
        printf("Test_Callback failed: did not remain active passed midnight.");
        return 1;
    }
    
    current_time += 1;
    if (t.Check() != false) {
        printf("Test_Callback failed: did not deactivate on time.");
        return 1;
    }
}

int main(int argc, char *argv[])
{
    
    printf("Test_Callback: %s\n", Test_Callback() ? "fail" : "success" ); 
    return 0;
}
