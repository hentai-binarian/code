#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    double sped, time, dist;
    int numb;
    while(1){
        puts("番号を選択してください。\n"
             "1:距離を求める。\n"
             "2:速度を求める。\n"
             "3:時間を求める。");
        scanf("%d", &numb);
        if(numb == 1){
            puts("距離を求めます。\n"
                 "時速km/hを入力してください。");
            scanf("%lf", &sped);
            puts("かかった時間を分単位で入力してください。");
            scanf("%lf", &time);
            printf("距離=%.2lfkm(%.lfm)\n\n", sped*(time/60), 1000*(sped*(time/60)));
            continue;
        }
        if(numb == 2){
            puts("速度を求めます。\n"
                 "距離kmを入力してください。");
            scanf("%lf", &dist);
            puts("かかった時間を分単位で入力してください。");
            scanf("%lf", &time);
            printf("速度=%.2lfkm/h(%.2lfm/s)\n\n", 60*(dist/time), (60*(dist/time)/3.6));
            continue;
        }
        if(numb == 3){
            puts("時間を求めます。\n"
                 "距離kmを入力してください。");
            scanf("%lf", &dist);
            puts("時速km/hを入力してください。");
            scanf("%lf", &sped);
            printf("時間=%.2lf分(%.2lf時間)\n\n", 60*(dist/sped), (dist/sped));
            continue;
        }
    }
}
