#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#define MAX_LEN 256
#define MAX_ARG 10

typedef struct {
    char *cmd;
    char **argv;
} Command;

int cmd(char *cmd, char *argv, ...);
Command gen_command(char *input);
void error(char *format, ...);

int main() {
    char buff[MAX_LEN];

    while (fgets(buff, MAX_LEN, stdin) != NULL) {
        if (buff[strlen(buff) - 1] != '\n') {
            error("Too long statement (max: %d)", MAX_LEN);
        }

        Command cmd = gen_command(buff);
        puts(cmd.cmd);

        int i = 0;
        while (cmd.argv[i] != NULL) {
            puts(cmd.argv[i++]);
        }
        break;
    }

    return 0;
}

/**
 * 入力からコマンドを解釈し Command 構造体を返す
 * @param input 1行の入力
 * @return Command
 */
Command gen_command(char *input) {
    Command cmd;
    cmd.cmd = strtok(input, " ");

    cmd.argv = malloc((sizeof (void*)) * MAX_ARG);
    int i = 0;
    while ((cmd.argv[i++] = strtok(NULL, " ")) != NULL){
        if (i >= MAX_ARG) {
            error("Too many arguments.");
            break;
        }
    }
    return cmd;
}

int cmd(char *cmd, char *argv, ...) {
    puts(cmd);
    return 0;
}

/**
 * エラー出力する
 * @param format フォーマット文字列
 * @param ... フォーマットに入るパラメタ
 */
void error(char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
