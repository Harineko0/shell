cmake_minimum_required(VERSION 3.25)
project(shell C)

set(CMAKE_C_STANDARD 17)

add_executable(shell src/main.c src/lib/map.c src/cmd/cd.c src/global.h src/global.c src/lib/str.h src/lib/str.c src/lib/io.c src/lib/path.c src/lib/stack.h src/lib/stack.c src/cmd/pushd.c src/cmd/dirs.c src/cmd/popd.c src/cmd/history.c src/cmd/ex.c src/lexer.c src/lexer.h src/parser.c src/parser.h src/ast.h src/token.h src/token.c src/ast/yield_expr.c src/ast/execute_expr.c src/ast/statement.c src/ast/program.c src/commands.h src/command.c)
