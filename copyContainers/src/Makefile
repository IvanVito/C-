CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TEST_DIR = tests
TEST = $(TEST_DIR)/*.cpp
REP = report
VA = vector_array
LSQ = list_stack_queue
MSM = map_set_multiset
SG = -style=Google
CLANG = clang-format

TFLAG = -lgtest -coverage
OS = $(shell uname)

ifeq ($(OS),Linux)
	det_OS = -lm -lrt -lpthread -lgtest_main
	for_lcov =
else
	det_OS = -lpthread -lgtest_main
	for_lcov = --ignore-errors inconsistent
endif

all: check cppcheck start_test

test: clean
	@$(CC) $(CFLAGS) $(TEST) -o ./$(TEST_DIR)/$@ $(TFLAG) $(det_OS)

start_test: test
	@./$(TEST_DIR)/test
	@make clean

gcov_report: clean test
	@./$(TEST_DIR)/test
	@lcov --no-external -o ./$(TEST_DIR)/res.info $(for_lcov) -c -d .
	@genhtml -o ./$(TEST_DIR)/$(REP) ./$(TEST_DIR)/res.info
	@open ./$(TEST_DIR)/$(REP)/index.html

check:
	@cp ../materials/linters/.$(CLANG) ./
	@$(CLANG) $(SG) -n *.h
	@$(CLANG) $(SG) -i *.h
	@mv .$(CLANG) $(VA)/
	@$(CLANG) $(SG) -n $(VA)/*.h
	@$(CLANG) $(SG) -i $(VA)/*.h
	@mv $(VA)/.$(CLANG) $(LSQ)/
	@$(CLANG) $(SG) -n $(LSQ)/*.h
	@$(CLANG) $(SG) -i $(LSQ)/*.h
	@mv $(LSQ)/.$(CLANG) $(MSM)/
	@$(CLANG) $(SG) -n $(MSM)/*.h
	@$(CLANG) $(SG) -i $(MSM)/*.h
	@mv $(MSM)/.$(CLANG) $(TEST_DIR)/
	@$(CLANG) $(SG) -n $(TEST_DIR)/*.h $(TEST)
	@$(CLANG) $(SG) -i $(TEST_DIR)/*.h $(TEST)
	@rm ./$(TEST_DIR)/.$(CLANG)

valgrind: clean test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s ./$(TEST_DIR)/test
	@make clean

cppcheck:
	@$@ --suppress=noExplicitConstructor --enable=all --suppress=missingInclude --language=c++ $(TEST_DIR)/ $(VA)/*.h $(MSM)/*.h $(LSQ)/*.h

clean:
	@rm -rf *.gc* ./$(TEST_DIR)/$(REP) ./$(TEST_DIR)/*.gc* ./$(TEST_DIR)/test ./$(TEST_DIR)/*.info 
