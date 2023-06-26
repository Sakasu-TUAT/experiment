#include <stdio.h>
#include <stdlib.h>
#define COUNT 8

int main(int argc, char *argv[]){
    int val ;
    int pfd[2] ; /* パイプのファイル記述子が格納 */
    pipe(pfd) ; /* パイプのファイル記述子を得る*/
    switch(fork()) {
        case 0:
            /* 親プロセスへデータを書き出す */
            write_data(pfd[1]);

        case -1: /* fork()のエラー */
            perror("child process") ;
            break;
        
        default: /* 親プロセス */
        /* 子プロセスからデータを読み込む */
        read_data(pfd[0]) ;
        wait(&val) ;
    }
}


write_data(int fd) /* fdへ乱数データを書く*/{
    int i, v ;
    for(i = 0 ; i < COUNT; ++i) {
        v = rand(); /* 乱数生成 */
        write(fd, &v, sizeof(v));
    }
}
/* fdからデータを読んで端末へ書く */
read_data(int fd) {
    int i, v ;
    for(i = 0 ; i < COUNT ; ++i) {
        read(fd, &v, sizeof(v));
        printf("read val:%d\n", v);
    }
}