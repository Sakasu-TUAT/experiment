
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int val ;
    char *eargv[argc] ;
    printf("argc : %d\n", argc);
    for(int i=0; i<argc; i++){
        eargv[i] = argv[i+1];
        printf("argv[%d] : %s\n", i, argv[i]);
    }
    eargv[argc-1] = NULL;
    
    switch(fork()) {
        case 0: /* 子プロセス */
            execv(argv[0], eargv) ; /* ファイルの実行 */
            // execvの第一引数はロードしたいファイル名
            perror("can not exec") ;
            exit(0) ;
        case -1:
            perror("child process") ;
            break;
        default:
            /* ここは子プロセスと並行実行される */
            wait(&val) ; /* 親プロセスは終了を待つ */
    }
}