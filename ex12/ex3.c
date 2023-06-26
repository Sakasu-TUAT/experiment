#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int val;
    int shared_number = 0;
    switch (fork()) {
        case 0: // 子プロセス
            // ここに子プロセスの処理
            shared_number++;
            printf("child_number : %d\n", shared_number);
            exit(0); // 単に終了するだけ

        case -1: // fork()のエラー
            perror("child process");
            break;

        default: // 親プロセス
            // ここに親プロセスの処理
            // 子プロセスと並行実行される
            shared_number++;
            printf("parent_number : %d\n", shared_number);
            wait(&val); // 子プロセスの終了を待つ
    }
    

    return 0;
}
