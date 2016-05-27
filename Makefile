OBJ_DIR = obj
SRC_DIR1 = .
SRC_DIR2 = utils
SRC = $(wildcard $(SRC_DIR2)/*.cpp) $(wildcard $(SRC_DIR1)/*.cpp)
OBJ := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
VPATH=.:src


RELEASE_DIR = bin
RELEASE_DEBUG_DIR = binDebug
EXEC = $(RELEASE_DIR)/final_prog
EXEC_DEBUG = $(RELEASE_DEBUG_DIR)/final_prog
TESTS = tests
OUTPUT = output


CC = g++
CFLAGS = -Wall -Werror -O1 -std=c++11
LDFLAGS =
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
	make -C $(TESTS) read-csv

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
