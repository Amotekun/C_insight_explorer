file_explorer: main.c src/*.c
	gcc main.c src/*.c -Iinclude -o file_explorer -L/opt/homebrew/lib -lcurl