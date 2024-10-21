CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
OS = $(shell uname)
tests = -lgtest -coverage
MATRIX_SRC = $(wildcard ./back/matrix/*cpp)
MATRIX_HDR = $(wildcard ./back/matrix/*h)
SRC = $(wildcard ./back/*.cpp)
HDR = $(wildcard ./back/*.h)
GUICPP = $(wildcard ./gui/*.cpp)
GUIH = $(wildcard ./gui/*.h)
BUILD_GUI_DIR = BUILD_GUI_DIR
BUILD_TEST_DIR = BUILD_TEST_DIR
BUILD = build
PRO_FILE = 3DViewer.pro
CPPCHECK_FLAGS = --enable=all --language=c++ --suppress=unusedFunction --suppress=missingInclude

ifeq ($(OS),Linux)
  det_OS = -lrt -lpthread -lm
	for_lcov = 
	project = 3DViewer
else
  det_OS = -lpthread
	for_lcov = --ignore-errors inconsistent
	project = 3DViewer.app
endif

all: gcov_report dist

install:
	@mkdir -p $(BUILD_GUI_DIR)
	@mkdir -p $(BUILD)
	@cd $(BUILD_GUI_DIR) && qmake ../gui/$(PRO_FILE) && make && make clean && rm Makefile
	@mv $(BUILD_GUI_DIR)/$(project) $(BUILD)
	@rm -rf ./$(BUILD_GUI_DIR)

launch:
	@chmod 0700 /run/user/1000/
	@sudo build/3DViewer

uninstall:
	@rm -rf ./$(BUILD) ./$(BUILD_GUI_DIR)

tests: clean
	@$(CC) $(CFLAGS) $(SRC) $(MATRIX_SRC) ./tests/*.cpp -o testsObj $(tests) $(det_OS)
	@./testsObj

gcov_report: tests
	@lcov -t "result" -o res.info -c -d .
	@lcov --extract res.info "*/parser.cpp" "*/affinTrans.cpp" "*/otherTrans.cpp" -o res.info
	@genhtml -o report res.info
	@google-chrome report/index.html
	@rm -rf *.gc* *.o *.info *.a *.dSYM a.out testsObj

check: cpp_check valgrind
	@cp ../materials/linters/.clang-format ./
	@find . -name "*.cpp" -o -name "*.h" | xargs clang-format -style=Google -n
	@find . -name "*.cpp" -o -name "*.h" | xargs clang-format -style=Google -i
	@rm .clang-format
	@make clean

cpp_check:
	@cppcheck $(SRC) $(HDR) $(GUICPP) $(GUIH) $(CPPCHECK_FLAGS)

valgrind: tests
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./testsObj

clean: uninstall
	@rm -rf report *.gc* *.o *.info *.a *.dSYM a.out testsObj documentation dist

dvi:
	@doxygen
	@google-chrome documentation/html/index.html
	
dist: dvi install
	@mkdir -p dist
	@cp -R ./$(BUILD) ./dist/
	@cp -R ./documentation ./dist/documentation
	@cd ./dist && tar cvzf 3DViewerVmake2.0.tgz *
	@cd ./dist && rm -rf $(BUILD) documentation 

install_doxygen:
	@sudo apt-get update
	@sudo apt-get install graphviz
	@sudo apt-get install doxygen
