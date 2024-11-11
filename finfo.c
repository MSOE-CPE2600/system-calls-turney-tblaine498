// Tyler Blaine, Lab 9, CPE2600 111 

// finfo.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    struct stat file_stat;
    if (stat(argv[1], &file_stat) != -1) {

        // Print file type
        switch (file_stat.st_mode & S_IFMT) { // Zeroes out all bits except those that represent the file type
            case S_IFDIR:  
            printf("File Type: Directory\n"); 
            break;

            case S_IFREG:
            printf("File Type: Regular file\n");
            break;

            case S_IFCHR:
            printf("File Type: Character device\n"); 
            break;

            case S_IFBLK:
            printf("File Type: Block device\n");
            break;

            case S_IFIFO:
            printf("File Type: FIFO/pipe\n");
            break;

            case S_IFLNK:
            printf("File Type: Symbolic link\n");
            break;

            case S_IFSOCK:
            printf("File Type: Socket\n");
            break;

            default:
            printf("Unknown file type\n"); 
            break;
        }

        // Print permissions
        char output[10] = "---------";
        int permissions[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP,
                                 S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
        
        for (int i = 0; i < 9; i++) {
            if (file_stat.st_mode & permissions[i]) {
                if (i % 3 == 0){
                    output[i] = 'r';
                } else if (i % 3 == 1){
                    output[i] = 'w';
                }
                else{
                    output[i] = 'x';
                }
            }
        }
        printf("Permissions: %s\n", output);

        // Print owner
        printf("Owner: %d\n", file_stat.st_uid);

        // Print file size
        printf("Size in bytes: %ld\n", (long)file_stat.st_size);

        // Print modification time
        char time_str[20];
        struct tm *timeinfo = localtime(&file_stat.st_mtime);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("Last modified: %s\n", time_str);
        
    } else{
        printf("An error has occured\n");
        return -1;
    }

    return 0;
}