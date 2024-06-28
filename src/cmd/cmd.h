typedef struct {
    char *cmd;
    char **argv;
} Command;

typedef int (*c_fun)(char**);

c_fun c_get(char *cmd);

/**
 * 入力からコマンドを解釈し Command 構造体を返す
 * @param line 1行の入力
 * @param argc
 * @return Command
 */
Command c_interprete(char *line, int argc);
