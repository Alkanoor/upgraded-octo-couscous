OBJ_DIR = obj
SRC_DIR1 = .
SRC_DIR2 = utils
SRC = $(wildcard $(SRC_DIR2)/*.cpp) $(wildcard $(SRC_DIR1)/*.cpp)
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
VPATH=.:utils


RELEASE_DIR = bin
RELEASE_DEBUG_DIR = binDebug
EXEC = $(RELEASE_DIR)/final_prog
EXEC_DEBUG = $(RELEASE_DEBUG_DIR)/final_prog
TESTS = tests
OUTPUT = output


CC = g++
CFLAGS = -Wall -Werror -O1 -std=c++11 -I"C:\Program Files (x86)\CodeBlocks\boost_1_59_0"
LDFLAGS = -lboost_system -lboost_regex
LDFLAGS_DEBUG = -g


all: createDir $(EXEC)

makeDebug: createDir $(EXEC_DEBUG)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC_DEBUG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDFLAGS_DEBUG)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

test-read-csv:
	make -C $(TESTS) test1

test-replace:
	make -C $(TESTS) test2

test-read-csv-with-preprocessing:
	make -C $(TESTS) test3

test-counts:
	make -C $(TESTS) test4

test_tfidf:
	make -C $(TESTS) test6

test_crossval:
	make -C $(TESTS) test7

test_grid:
	make -C $(TESTS) test11

test_perceptron:
	make -C $(TESTS) test12


exec-and-redirect:
	$(EXEC) > $(OUTPUT)/current_out.txt

createDir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(RELEASE_DEBUG_DIR)
	@mkdir -p $(OUTPUT)

clean :
	make -C $(TESTS) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(RELEASE_DEBUG_DIR)
	@rm -rf $(OUTPUT)
