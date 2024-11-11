// Tyler Blaine, Lab 9, CPE2600 111 

// info.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    // Get the current time in nanoseconds
    struct timespec time;
    if (clock_gettime(CLOCK_REALTIME, &time) == 0) {
        printf("Current time in nanoseconds: %ld\n", time.tv_nsec + time.tv_sec * 1000000000);
    }
    
    // Get the system’s network name
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0 && strlen(hostname) > 0) {
        printf("Network name: %s\n", hostname);
    }

    // Get the OS name, release, version, and hardware type
    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        if (strlen(sys_info.sysname) > 0){
            printf("Operating system name: %s\n", sys_info.sysname);
        }
        if (strlen(sys_info.release) > 0){
            printf("Operating system release: %s\n", sys_info.release);
        }
        if (strlen(sys_info.version) > 0){
            printf("Operating system version: %s\n", sys_info.version);
        }
        if (strlen(sys_info.machine) > 0){
            printf("Hardware type: %s\n", sys_info.machine);
        } 
    }

    // Get the number of CPUs on the system
    int num_cpus = get_nprocs();
    if (num_cpus > 0) {
        printf("Number of CPUs: %d\n", num_cpus);
    }

    // Get total and free memory
    struct sysinfo mem_info;
    if (sysinfo(&mem_info) == 0) {
        printf("Total physical memory in bytes: %ld\n", mem_info.totalram * mem_info.mem_unit);
        printf("Total free memory in bytes: %ld\n", mem_info.freeram * mem_info.mem_unit);
    }
    return 0;
}
