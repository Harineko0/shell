# Programming C Subset Shell
## Available Commands
### 基本
* 外部コマンド: execvp (p.46)
* cd: directory.c (p.44)
  1. 絶対パスなら cwd を置き換え, 相対パスなら cwd と結合, ~ なら HOME と結合, 引数なしなら HOME に設定して終了  
    `path.resolve(char *a, char *b)`: a の末尾に / が無かったら / を付けて b と結合
  2. cwd のパスを正規化 (. や .. を取り除く)
```
. = 削除
.. = 直前のディレクトリを削除
```
```
** := ([a-zA-Z0-9]+)(..)(.)

(nothing) = HOME  
/** = 絶対パス  
./** = 
../** =   
~/**
** = ./** と同じ
```
* dirs  
* pushd   
* popd  
* history
* !!  
  1つ前のコマンドを再度実行
* !string  
  string で始まる最新のコマンドを実行
* ワイルドカード  
  `*` のみ カレントディレクトリにある全てのファイル名
* prompt  
```shell
$ prompt abc
abc prompt
Command: prompt $
$ 
```
* スクリプト  
  シェルの実行ファイルに `script_file` をリダイレクトで入力する
* alias <command1 command2>
* alias
  エイリアス一覧
* unalias command1

### 拡張
* !n  
  ヒストリで n 番目にあるコマンドを実行
* !-n
* ワイルドカード `*strings` `strings*`
* シェルスクリプト

### Extra
* シェルスクリプト
  * `command <args...>`
  * `var="string"`
  * `var=10`
  * `list=(val1 val2 val3)`
  * `$(( 1 + 1 ))`
  * `$var`
  * ~~command \`command <args...>\`~~
  * ```shell
    # [[ $var = chicken ]]
    if expr; then
    
    elif expr; then
    
    else
    
    fi
    ```
  * ```shell
    # 1 2 3 or `seq 1 -l 10`
    for symbol in expr; do
    
    done
    ```
  * ```shell
    function symbol (){
      echo "$1 $2"
    }
    symbol 'arg'
    ```
* 解析
  * トークン
    * LITERAL
    * IF
    * THEN
    * ELIF
    * ELSE
    * FI
    * FOR
    * DO
    * DONE
    * EQUAL =
    * LEFTPARE (
    * RIGHTPARE )
    * LEFTCURLY {
    * RIGHTCURLY }
    * SEMICOLON ;
    * DOLLAR $
  * lexer
    * 
  * AST
    * Expression = command, var=, fn 
    * Statement = if, for, function
    * トップレベルシンボルの優先順位: function > alias > 内部 command > 外部 command
```yaml
Program ::= Statement
Statement ::= Statement Statement | <IfStatement | ForStatement | FunctionStatement | ExpressionStatement> EOL
IfStatement ::= 'if' ExecuteExpression EOL 'then' Statement EOL
  <'elif' Expression EOL 'then' Statement>*
  <'else' Statement>? 'fi'
ForStatement ::= 'for' Literal 'in' LiteralExpression EOL 'do' Statement 'done'
FunctionStatement ::= 'function' Literal '()' '{' Statement '}'
ExpressionStatement ::= ExecuteExpression
#CommandStatement ::= LiteralExpression+ | '[[' LiteralExpression+ ']]'
#VariableStatement ::= Literal '=' LiteralExpression

YieldExpression ::= LiteralExpression | BackQuoteExpression | VariableExpression
LiteralExpression ::= Literal
BackQuoteExpression ::= '`' ExecuteExpression '`'
VariableExpression ::= '$' Literal

ExecuteExpression ::= CommandExpression | AssignExpression
CommandExpression ::= YieldExpression+ | '[[' YieldExpression+ ']]'
AssignExpression ::= Literal '=' YieldExpression

// ↓ for test command
ConditionalExpression ::= '(' ConditionalExpression ')' 
  | ConditionalExpression '&&' ConditionalExpression
  | ConditionalExpression '||' ConditionalExpression
  | '!' ConditionalExpression  // 論理否定
  | VarLiteral <'==' | '!='> VarLiteral
  | Number <'-eq' | '-ne' | '-lt' | '-le' | '-gt' | '-ge'> Number
  | <'-d' | '-e' | '-f' | '-L' | '-r' | '-s' | '-w' | '-x'> Literal

EOL ::= ';' | '\n'
// VarLiteral ::= '$' Literal | Literal
Literal ::= Literal Literal | <'a' | 'b' | ... | 'z' | '_'>

Number ::= ZNumber | NNumber ZNumber+
ZNumber ::= 0 | NNumber
NNumber ::= 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```
* リダイレクト

## 設計
1. 標準入力から入力を受け取る
2. コマンドを cmd + arguments に分ける
3. cmd -> 関数ポインタの HashMap から cmd に対応する関数を取り出し, arguments を引数に入れて実行する
4. コマンド関数は 0 or 1 を返す. 出力は各関数内で行う
5. TODO: 0 or 1 の戻り値はどう扱う?

### 必要な変数
* current working directory
* コマンド履歴: 先頭, 末尾, 検索
  * DoublyLinkedList: まずこれのみで実装する
  * Tri 木: !string string から始まるノードを検索し, その子の中から最も最新のノードを取り出す
* ディレクトリスタック: 一番上に push, pop
* エイリアスの HashMap
* コマンドの HashMap
* prompt

### ソースコード構成
* main.c
* map.c: HashMap
* list.c: DoublyLinkedList