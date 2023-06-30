#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define ARGVSIZE 100

const char whitespace[] = " \t\r\n\v";
const char reDirect[] = ">";

int parsecmd(char **argv, char *buf, char *ebuf)
{
	char *s;
	int i = 0;

	s = buf;

	while (s < ebuf)
	{
		while (s < ebuf && strchr(whitespace, *s))
			s++;
		if (ebuf <= s)
			return -1;

		argv[i++] = s;
		while (s < ebuf && !strchr(whitespace, *s))
			s++;
		*s = '\0';
		s++;
	}

	return 1;
}

void runcmd(char *buf)
{
	char *argv[ARGVSIZE];

	memset(argv, 0, ARGVSIZE);
	if (parsecmd(argv, buf, &buf[strlen(buf)]) > 0)
		if (execvp(argv[0], argv) < 0)
			perror("execvp");
	exit(-1);
}

int getcmd(char *buf, int len)
{
	printf("> ");
	fflush(stdin);
	memset(buf, 0, len);
	fgets(buf, len, stdin);

	if (buf[0] == 0)
		return -1;
	return 0;
}

int main(int argc, char **argv){
	static char buf[BUFSIZE];

	while (getcmd(buf, BUFSIZE) >= 0) {
		// リダイレクト関連の変数
		char *s = buf;          // 解析対象の文字列の開始位置を指すポインタ
		char *r;                // リダイレクト演算子の位置を探すポインタ
		char *filename = NULL;  // リダイレクト先ファイル名を格納するポインタ
		int fd = 1;             // 標準出力のディスクリプタ
		int f = -1;             // リダイレクト先ファイルのディスクリプタ
		char redirectFlag = 0;  // リダイレクトの発生フラグ

		while ((r = strchr(s, '>'))) {
			*r = '\0'; // > を NULL 文字で上書き

			// > から ファイル名までスペースを飛ばす
			do {
				r++;
			} while (strchr(whitespace, *r));
			
			filename = r;

			// 最後の改行を消すためにファイル名の最後を探す
			do {
				r++;
			} while (!strchr(whitespace, *r));

			*r = '\0'; // 改行を NULL 文字で上書き

			// リダイレクト先ファイルをオープン
			if ((f = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
				perror("open error");
				return -1;
			}
			redirectFlag = 1;
			s = ++r;
		}

		if (fork() == 0) {
			if (redirectFlag){
				// fd 1 をリダイレクト先に書き換える
				close(fd);
				fd = dup(f);
				close(f);
			}
			runcmd(buf);
		}
		wait(NULL);
	}
	exit(0);
}
