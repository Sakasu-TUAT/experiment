#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
//静的領域：グローバル変数
int static_data_1=0;
int static_data_2=0;
int main(int argc, char *argv[]){
    //スタック領域に配置
    int stack1 = 0;
    int stack2 = 0;
    printf("main:%p\n",main);
    printf("static_data_1:%p\n",&static_data_1);
    printf("static_data_2:%p\n",&static_data_2);
    printf("stack1:%p\n",&stack1);
    printf("stack2:%p\n",&stack2);
    //関数の先頭を指すポインタを作成してそこにデータを代入してみる
    // int *code = &main;
    // *code = 0x00;
}