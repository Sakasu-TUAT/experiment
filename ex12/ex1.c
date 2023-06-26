#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int val;
    struct timeval start_time, end_time;
    struct timeval child_end_time;
    struct timeval parent_end_time;

    gettimeofday(&start_time,NULL);
    gettimeofday(&end_time,NULL);
    double func_overhead=1e6*(end_time.tv_sec-start_time.tv_sec)+(end_time.tv_usec-start_time.tv_usec);
    printf("function_time:%4f [usec]\n",func_overhead);

    gettimeofday(&start_time, NULL); // 開始時間を取得

    switch (fork()) {
        case 0: // 子プロセス
            // ここに子プロセスの処理
            gettimeofday(&child_end_time,NULL);
            double child_overhead=1000*1000*(child_end_time.tv_sec-start_time.tv_sec)+(child_end_time.tv_usec-start_time.tv_usec)-func_overhead;
            printf("child_time:%4f [usec]\n",child_overhead);
            exit(0); // 単に終了するだけ

        case -1: // fork()のエラー
            perror("child process");
            break;

        default: // 親プロセス
            // ここに親プロセスの処理
            // 子プロセスと並行実行される
            gettimeofday(&parent_end_time, NULL); // 終了時間を取得
            double parent_overhead=1e6*(parent_end_time.tv_sec-start_time.tv_sec)+(parent_end_time.tv_usec-start_time.tv_usec)-func_overhead;
            printf("parent_time:%4f [usec]\n",parent_overhead);
            wait(&val); // 子プロセスの終了を待つ
    }
    printf("val : %d\n", val); 
    gettimeofday(&end_time, NULL); // 終了時間を取得
    double overhead=1e6*(end_time.tv_sec-start_time.tv_sec)+(end_time.tv_usec-start_time.tv_usec)-func_overhead;
    printf("total_time:%4f [usec]\n",overhead);

    return 0;
}
