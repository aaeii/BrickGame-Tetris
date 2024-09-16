CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SRC = ./brick_game/tetris/tetris.c ./gui/cli/interface.c
TEST = ./test/test.c
GCOV_FLAGS = -fprofile-arcs -ftest-coverage  --coverage
OS = $(shell uname)

ifeq ($(OS),Linux)
    LIBSFLAGS = -lcheck -lsubunit -lrt -lpthread -lm -lgcov -lncurses 
else
    LIBSFLAGS = -lcheck -lpthread -lm -lgcov -lncurses 
endif

all: clean install

tetris.a:
	$(CC) -c $(SRC)
	ar rc tetris.a *.o
	ranlib tetris.a 
	rm -rf *.o

install: tetris.a
	$(CC) $(CFLAGS) ./brick_game/tetris/main.c $(SRC) -o tetris $(LIBSFLAGS) tetris.a
	./tetris

test: clean tetris.a 
	$(CC) $(CFLAGS) tetris.a $(GCOV_FLAGS) $(SRC) $(TEST) -o test_result $(LIBSFLAGS) -g 
	./test_result

gcov_report: test
	lcov -t "tetris" -o tetris.info -c -d . -q  
	genhtml -o gcov_report/html tetris.info -q
	open gcov_report/html/index.html
	rm -rf tetris.info

uninstall:
	rm -rf tetris

dvi:
	doxygen
	open doxygen/html/index.html

dist: clean 
	mkdir tetris-1.0
	cp -r ./Makefile ./test ./gui ./brick_game ./Doxyfile tetris-1.0
	tar -czf tetris-1.0.tar.gz tetris-1.0
	rm -rf tetris-1.0

clean: uninstall
	rm -rf *.gz *.txt brick_game/tetris/tetris.h.gch *.o *.a *.gcda *.gcno report test_result gcov_report/ rm -rf ./doxygen

clang:
	clang-format -style=Google -n ./brick_game/tetris/*.c ./brick_game/tetris/*.h  ./test/*.c ./gui/cli/*.c ./gui/cli/*.h

clang_fix:
	clang-format -style=Google -i ./brick_game/tetris/*.c ./brick_game/tetris/*.h  ./test/*.c ./gui/cli/*.c ./gui/cli/*.h

log_test:
	valgrind --tool=memcheck --leak-check=yes --log-file=log_test.txt ./test_result