// Tyler Blaine, Lab 9, CPE2600 111 

// pmod.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // Modify priority by reducing it by 10
    int original_priority = getpriority(PRIO_PROCESS, 0);
    int new_priority = original_priority + 10;  // Moving the priority back by 10

    if (setpriority(PRIO_PROCESS, 0, new_priority) != -1) {
        printf("Priority changed from %d to %d\n", original_priority, getpriority(PRIO_PROCESS, 0));
    }

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec ts;
    ts.tv_sec = 1;             
    ts.tv_nsec = 837272638;       

    if (nanosleep(&ts, NULL) != -1) {
        printf("Goodbye\n");
    }
    return 0;
}
