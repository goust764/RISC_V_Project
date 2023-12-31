@echo off
setlocal enabledelayedexpansion

set gcc_args=-Wall -Wextra -g -Wsign-compare
@REM set gcc_args=-Wall -Wextra -O3

set prog[0].nam=rv32icomp
set prog[0].dep=src/string.c src/list.c src/char_group.c src/regexp.c src/unitest.c src/lexem.c src/parser.c src/asm_line.c
set prog[0].dir=prog/
REM set prog[0].arg=../prog/asm_bench_global.asm database.txt ../prog/asm_bench_global.bin -v
@REM set prog[0].arg=../prog/asm_bench_global.asm database.txt test2.bin -v
@REM set prog[0].arg=test.asm database.txt test2.bin -v
set prog[0].arg=../prog/asm_mult.asm database.txt prog/asm_mult.bin -v -c -s 1024

:start
cls
for /l %%i in (0,1,0) do call :display "!prog[%%i].nam!" "!prog[%%i].dep!" "!prog[%%i].dir!" "!prog[%%i].arg!"
pause
goto start

:display [nam] [dep] [dir] [arg]
	echo [94m========== Compilation de %~1.exe ==========[0m
	wsl gcc %gcc_args% %~2 %~3%~1.c -o ./bin/linux_%~1.exe
	if NOT ERRORLEVEL 1 (
		echo.
		echo [94m---------- Execution de %~1.exe ----------[0m
		wsl valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/linux_%~1.exe %~4
		call :print_errlevel "%errorlevel%"
		echo.
	) else (
		echo.
		echo [41mErreur de compilation, veuillez voir le message GCC plus haut[0m
	)
	echo.
	goto :eof

:print_errlevel [errlevel]
	echo.
	echo [96mValeur de retour [97m%~1[0m
	goto :eof