# Programming C Subset Shell
## Available Commands
### 基本
* cd  
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

### Extra
* test コマンド? シェルスクリプト?
* シェル変数
* mkdir
* cat

## 設計
### 必要な変数
* コマンド履歴: 先頭, 末尾, 検索
  * LinkedList: まずこっちで実装する?
  * Tri 木: !string string から始まるノードを検索し, その子の中から最も最新のノードを取り出す
* ディレクトリスタック: 一番上に push, pop
* エイリアスの HashMap
* prompt

### ソースコード構成