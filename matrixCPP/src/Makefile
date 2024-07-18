CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -g
OS = $(shell uname)
TEST = -lgtest -coverage
SRC = *.cpp

ifeq ($(OS),Linux)
    det_OS = -lrt -lpthread -lm
	for_lcov = 
else
    det_OS = -lpthread
	for_lcov = --ignore-errors inconsistent
endif

all: clean s21_matrix_oop.a gcov_report

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.cpp *.h
	clang-format -style=Google -i *.cpp *.h
	rm .clang-format
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ --check-config *.cpp *.h

test: clean
	$(CC) $(CFLAGS) $(SRC) -o test $(TEST) $(det_OS)

gcov_report: test
	./test
	lcov -t "result" -o res.info --no-external $(for_lcov) -c -d . 
	genhtml -o report res.info 
	open report/index.html

valgrind: clean test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clean:
	rm -rf report *.gc* *.o *.info *.a *.dSYM test s a.out

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a

s21_matrix_oop.o:
	$(CC) $(CFLAGS) $(SRC) -c

comp:
	$(CC) $(CFLAGS) s21_matrix_oop.cpp $(det_OS)
	./a.out