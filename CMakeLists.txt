cmake_minimum_required(VERSION 3.25)
project(shell C)

set(CMAKE_C_STANDARD 17)

add_executable(shell src/main.c src/lib/map.c src/cmd.c src/cmd.h src/cmd/cd.c src/cmd/cd.h src/global.h src/global.c src/lib/str.h src/lib/str.c src/lib/io.c src/lib/path.c src/lib/stack.h src/lib/stack.c src/cmd/pushd.c src/cmd/pushd.h src/cmd/dirs.h src/cmd/dirs.c src/cmd/popd.c src/cmd/history.h src/cmd/history.c src/cmd/ex.h src/cmd/ex.c src/lexer.c src/lexer.h src/parser.c src/parser.h src/ast.h src/token.h src/token.c)
