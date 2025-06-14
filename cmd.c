#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#include <locale.h>

#define CONFIG_FILE "config.txt"
#define MAX_CMD_LEN 256

void trim_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int main() {
    char command[MAX_CMD_LEN];
    int target_hour, target_minute;

    FILE *fp = fopen(CONFIG_FILE, "r");
    if (fp == NULL) {
        // 設定ファイルがないとき
        printf("not config file\n");
        printf("plese input time(HH MM): ");
        scanf("%d %d", &target_hour, &target_minute);
        getchar(); // 改行除去

        printf("plese input command: ");
        fgets(command, MAX_CMD_LEN, stdin);
        trim_newline(command);

        // 保存
        fp = fopen(CONFIG_FILE, "w");
        if (fp) {
            fprintf(fp, "%02d:%02d %s\n", target_hour, target_minute, command);
            fclose(fp);
        } else {
            perror("failed file save");
            return 1;
        }
    } else {
        // 読み込み
        if (fscanf(fp, "%d:%d %[^\n]", &target_hour, &target_minute, command) != 3) {
            fprintf(stderr, "config file format is incorrect\n");
            fclose(fp);
            return 1;
        }
        fclose(fp);
    }

    printf("start monitoring：%02d:%02d command run...\n", target_hour, target_minute);

    while (1) {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);

        if (tm_now->tm_hour == target_hour && tm_now->tm_min == target_minute){
            printf("start command : %s\n", command);

            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;
            CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
            break;
        }
        Sleep(1000); 
    }

    return 0;
}

