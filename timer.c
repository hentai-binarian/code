#include <stdio.h>
#include <time.h>
#include <windows.h>

#define CONFIG_FILE "config.txt"
#define MAX_CMD_LEN 100

char cmd[MAX_CMD_LEN];
void run(void);

// run the command
void run(void){
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    BOOL success = CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if (!success) {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
    } else {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return;
}

int main(void) {
    int hour, min, sec;
    FILE *fp = fopen(CONFIG_FILE, "r");

    // file error check
    if (fp == NULL) {
        fprintf(stderr, "Can't open the config file.\n");
        return 1;
    }
    // read file
    if (fscanf(fp, "%02d:%02d:%02d %99[^\n]", &hour, &min, &sec, cmd) != 4) {
        fprintf(stderr, "Config file format is invalid.\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("Start the command at %02d:%02d:%02d\n", hour, min, sec);

    // time check loop
    while(1) {
        time_t now = time(NULL);
        struct tm tm_now;
        localtime_s(&tm_now, &now);
        printf("Current time: %02d:%02d:%02d\r", tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec);

        if(tm_now.tm_hour == hour && tm_now.tm_min == min && tm_now.tm_sec == sec) {
            printf("Start the command now: %s\n", cmd);
            run();
            break;
        }
        Sleep(500); // sleep for 500 milliseconds
    }
    return 0;
}
