// Tyler Blaine, Lab 9, CPE2600 111 

// pinfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/syscall.h>

int main(int argc, char* argv[])
{
    // Determine the PID
    pid_t pid;
    if (argc > 1) {
        pid = atoi(argv[1]);  
    } else {
        pid = getpid();
    }

    // Get the process priority
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1) {
        printf("Failed to get process priority\n");
        exit(1);
    }
    printf("Process priority: %d\n", priority);

    // Get the scheduling method
    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        printf("Failed to get scheduling method\n");
        exit(1);
    }
    switch (policy) {
        case SCHED_OTHER:
            printf("Scheduling method: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling method: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling method: SCHED_RR\n");
            break;
        case SCHED_BATCH:
            printf("Scheduling method: SCHED_BATCH\n");
            break;
        case SCHED_IDLE:
            printf("Scheduling method: SCHED_IDLE\n");
            break;
        default:
            printf("Unknown scheduling method\n");
            break;
    }

    // Get CPU information
    unsigned cpu;
    syscall(SYS_getcpu, &cpu, NULL, NULL);
    printf("Current CPU: %u\n", cpu);

    // Get resource usage
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) != -1) {
        printf("User time: %ld.%06ld seconds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("System time: %ld.%06ld seconds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    }

    // Get CPU time limit
    struct rlimit limit;
    if (getrlimit(RLIMIT_CPU, &limit) != -1) {
        printf("CPU time limit: Soft=%ld, Hard=%ld\n", limit.rlim_cur, limit.rlim_max);
    }
    return 0;
}
