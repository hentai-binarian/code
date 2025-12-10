#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#include <locale.h>

#define CONFIG_FILE "config.txt"
#define MAX_CMD_LEN 256

int main() {
    char cmd[MAX_CMD_LEN];
    int target_hour, target_minute;

    FILE *fp = fopen(CONFIG_FILE, "r");
    if (fscanf(fp, "%02d:%02d %[^\n]", &target_hour, &target_minute, cmd) != 3) {
        fprintf(stderr, "config file format is incorrect\n");
        fclose(fp);
        return 1;
    }

    printf("start at %02d:%02d command run...\n", target_hour, target_minute);

    while (1) {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);

        if(tm_now->tm_hour == target_hour && tm_now->tm_min == target_minute){
            printf("start command: %s\n", cmd);

            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;
            CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
            break;
        }
        Sleep(1000); 
    }

    return 0;
}

