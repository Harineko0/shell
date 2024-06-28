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
* test コマンド? シェルスクリプト?
* シェル変数
* mkdir
* cat
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