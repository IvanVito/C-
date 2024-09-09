CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17

TESTS_FLAG = -lgtest -coverage -lgtest_main

# Исходники и заголовки
GUI_SRC = $(wildcard gui/cli/*.c)
DESKTOP_SRC =$(wildcard gui/desktop/*.cpp)
SNAKE_SRC = $(wildcard brick_game/snake/*.cpp)
TETRIS_SRC = $(wildcard brick_game/brick_game/*.c)
MENU_SRC = $(wildcard brick_game/menu/*.cpp)
TESTS_SRC = $(wildcard brick_game/tests/*.cpp)

GUI_HDR = $(wildcard gui/cli/*.h)
DESKTOP_HDR = $(wildcard gui/desktop/*.h)
SNAKE_HDR = $(wildcard brick_game/snake/*.h)
TETRIS_HDR = $(wildcard brick_game/brick_game/*.h)
TESTS_HDR = $(wildcard brick_game/tests/*.h)
MENU_H = $(wildcard brick_game/menu/*.h)

# Объектные файлы для snake, tetris, menu, tests
GUI_OBJ_SNAKE = $(patsubst gui/cli/%.c, obj/snake/%.o, $(GUI_SRC))
SNAKE_OBJ = $(patsubst brick_game/snake/%.cpp, obj/snake/%.o, $(SNAKE_SRC))

GUI_OBJ_TETRIS = $(patsubst gui/cli/%.c, obj/tetris/%.o, $(GUI_SRC))
TETRIS_OBJ = $(patsubst brick_game/brick_game/%.c, obj/tetris/%.o, $(TETRIS_SRC))

MENU_OBJ_CLI = obj/menu/menu.o obj/snake/gui.o obj/snake/snake.o
TESTS_OBJ = $(patsubst brick_game/tests/%.cpp, obj/tests/%.o, $(TESTS_SRC))
TESTS_ADD = brick_game/snake/fsm.cpp brick_game/snake/snake.cpp brick_game/tests/tests.cpp 

PROJECT_SNAKE = snake
BUILD_DIR_SNAKE = build/cli

PROJECT_TETRIS = tetris
BUILD_DIR_TETRIS= build/cli

BUILD_DIR_CLI= build/cli
BUILD_DIR_DESKTOP= build/desktop

TESTS = tests
BUILD_DIR_TEST = build/tests

OS = $(shell uname)

ifeq ($(OS),Linux)
	det_OS = -lm -lrt -lpthread -lncurses
	for_lcov =
	DESKTOP = desktop
	CLI = cli
else
	det_OS = -lpthread 
	for_lcov = --ignore-errors inconsistent
	DESKTOP = desktop.app
	CLI = cli.app
endif

# Правила по умолчанию
all: check dist tests gcov_report clean

check:
	cp ../materials/linters/.clang-format ./gui/cli/
	cp ../materials/linters/.clang-format ./gui/desktop/
	cp ../materials/linters/.clang-format ./brick_game/snake
	cp ../materials/linters/.clang-format ./brick_game/brick_game
	cp ../materials/linters/.clang-format ./brick_game/menu
	cp ../materials/linters/.clang-format ./brick_game/tests

	clang-format -style=Google -n $(GUI_SRC) $(GUI_HDR)
	clang-format -style=Google -i $(GUI_SRC) $(GUI_HDR)

	clang-format -style=Google -n $(DESKTOP_SRC) $(DESKTOP_HDR)
	clang-format -style=Google -i $(DESKTOP_SRC) $(DESKTOP_HDR)

	clang-format -style=Google -n $(SNAKE_SRC) $(SNAKE_HDR)
	clang-format -style=Google -i $(SNAKE_SRC) $(SNAKE_HDR)

	clang-format -style=Google -n $(TETRIS_SRC) $(TETRIS_HDR)
	clang-format -style=Google -i $(TETRIS_SRC) $(TETRIS_HDR)

	clang-format -style=Google -n $(TESTS_SRC) $(TESTS_HDR)
	clang-format -style=Google -i $(TESTS_SRC) $(TESTS_HDR)

	clang-format -style=Google -n $(MENU_SRC) $(MENU_HDR)
	clang-format -style=Google -i $(MENU_SRC) $(MENU_HDR)

	rm ./gui/cli/.clang-format
	rm ./gui/desktop/.clang-format
	rm ./brick_game/snake/.clang-format
	rm ./brick_game/brick_game/.clang-format
	rm ./brick_game/menu/.clang-format
	rm ./brick_game/tests/.clang-format

	cppcheck --enable=all --language=c++ --suppress=unusedFunction --suppress=missingIncludeSystem $(GUI_SRC) $(GUI_HDR) $(SNAKE_SRC) $(SNAKE_HDR) $(MENU_SRC) $(MENU_HDR) $(TESTS_SRC) $(TESTS_HDR) $(TETRIS_SRC) $(TETRIS_HDR) $(DESKTOP_SRC) $(DESKTOP_HDR)

# Компиляция проекта snake
$(PROJECT_SNAKE): snake.a $(GUI_OBJ_SNAKE) $(SNAKE_OBJ)
	$(CC) $(CFLAGS) -D SNAKE  $(GUI_OBJ_SNAKE) $(SNAKE_OBJ) -o $@ $(det_OS)

snake.a: $(filter-out obj/snake/main.o obj/snake/controller.o, $(SNAKE_OBJ))
	ar rcs $@ $^
	ranlib $@

# Компиляция проекта tetris
$(PROJECT_TETRIS): tetris.a $(GUI_OBJ_TETRIS) $(TETRIS_OBJ)
	$(CC) $(CFLAGS) $(GUI_OBJ_TETRIS) $(TETRIS_OBJ) -o $@ $(det_OS)
	
tetris.a: $(TETRIS_OBJ)
	ar rcs $@ $(TETRIS_OBJ)
	ranlib $@

$(CLI): obj/menu/menu.o
	$(CC) $(CFLAGS) -D SNAKE $(MENU_OBJ_CLI) -o cliMenu $(det_OS)

$(TESTS):
	@mkdir -p $(BUILD_DIR_TEST)
	$(CC) $(CFLAGS) $(TESTS_ADD) -o $(BUILD_DIR_TEST)/$@ $(TESTS_FLAG) $(det_OS)
	./$(BUILD_DIR_TEST)/$(TESTS)

# Правила для создания объектных файлов для snake
obj/snake/%.o: gui/cli/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -D SNAKE -c $< -o $@

obj/snake/%.o: brick_game/snake/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -D SNAKE  -c $< -o $@

# Правила для создания объектных файлов для tetris
obj/tetris/%.o: gui/cli/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

obj/tetris/%.o: brick_game/brick_game/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

obj/menu/%.o: brick_game/menu/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -D SNAKE  -c $< -o $@

clean:
	rm -rf  obj **/*.gc* **/**/*.o **/*.o *.info *.a test.dSYM snake.dSYM tetris.dSYM a.out *.txt

origin: clean
	make uninstall
	rm -rf documentation dist report

gcov_report: tests
	lcov -t "result" -o res.info -c -d .
	lcov --remove res.info '/usr/*' '*/tests/*' -o res.info
	genhtml -o report res.info
	google-chrome report/index.html

install_doxygen:
	sudo apt-get update
	sudo apt-get install graphviz
	sudo apt-get install doxygen

valgrind: tests
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./build/tests/tests

dvi:
	doxygen
	google-chrome documentation/html/index.html
	
dist: install dvi
	mkdir -p dist
	cp -R ./$(BUILD_DIR_CLI) ./dist/
	cp -R ./$(BUILD_DIR_DESKTOP) ./dist/
	cp -R ./documentation ./dist/documentation
	cd ./dist && tar cvzf snakeAndTetris.tgz *
	cd ./dist && rm -rf $(CLI) $(DESKTOP) documentation 

install_cli:
	make $(PROJECT_SNAKE) && mkdir -p $(BUILD_DIR_SNAKE) && mv ./$(PROJECT_SNAKE) ./$(BUILD_DIR_SNAKE)
	make $(PROJECT_TETRIS) && mkdir -p $(BUILD_DIR_TETRIS) && mv ./$(PROJECT_TETRIS) ./$(BUILD_DIR_TETRIS)
	make $(CLI) && mkdir -p $(BUILD_DIR_CLI) && mv ./cliMenu ./$(BUILD_DIR_CLI)
	make clean

play_cli:
	chmod 700 /run/user/1000/
	./$(BUILD_DIR_CLI)/cliMenu

install_snake:
	cd ./gui/desktop && qmake CONFIG+=snake && make && make clean && rm Makefile

install_menu:
	cd ./gui/desktop && qmake CONFIG+=menu && make && make clean && rm Makefile

install_tetris:
	cd ./gui/desktop && qmake CONFIG+=tetris && make && make clean && rm Makefile

install_qt: install_snake install_tetris install_menu 

play_qt:
	chmod 700 /run/user/1000/
	export QT_QPA_PLATFORM=wayland && ./build/desktop/desktopMenu

install: install_qt install_cli

uninstall:
	rm -rf build

	

