CC = gcc
CFLAGS = -Wall -Werror -Wextra  -std=c11

SOURCES_BACK = brick_game/tetris/s21*.c
SOURCES_FRONT = gui/cli/s21*.c
MAIN = brick_game/tetris/main_tetris.c
SCORE = brick_game/tetris/score.txt

TEST = my_test/tests_back.c
TEST_BACK = brick_game/tetris/s21_backend.c brick_game/tetris/s21_figures.c

OS = $(shell uname)

ifeq ($(OS),Linux)
    det_OS = -lcheck -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif

all : clean dist gcov_report dvi

install: clean uninstall
	$(CC) $(CFLAGS) $(MAIN) $(SOURCES_BACK) $(SOURCES_FRONT) -o my_tetris -lncurses $(det_OS)
	./my_tetris

uninstall: 
	rm -rf my_tetris

dvi:
	open documentation_tetris.md

dist: clean install
	mkdir dist
	tar -czvf dist/tetris_the_archive.tgz $(SOURCES_BACK) $(SOURCES_FRONT) $(MAIN) $(TEST) $(SCORE) brick_game/tetris/*.h gui/cli/s21*.h documentation_tetris.md Makefile

test: 
	$(CC) $(CFLAGS) --coverage $(TEST_BACK) $(TEST) -lncurses -o test $(det_OS)
	./test

gcov_report: test
	./test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

check:
	cp ../materials/linters/.clang-format ./

	clang-format -style=Google -i brick_game/tetris/*.c
	clang-format -style=Google -i brick_game/tetris/*.h
	clang-format -style=Google -i gui/cli/*.c
	clang-format -style=Google -i my_test/*.c

	clang-format -style=Google -i gui/cli/*.h

	clang-format -style=Google -n brick_game/tetris/*.c
	clang-format -style=Google -n brick_game/tetris/*.h
	clang-format -style=Google -n gui/cli/*.c
	clang-format -style=Google -n gui/cli/*.h

	rm -rf .clang-format

clean: uninstall
	rm -rf gcov_report report *.gc* *.o *.info *.a test.dSYM test dist compose-dev.yaml 


