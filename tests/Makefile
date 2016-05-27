OBJ_DIR = obj
RELEASE_DIR = bin

CC = g++
CFLAGS = -Wall -Werror -O1 -std=c++11
LDFLAGS =

TEST1 = read_csv.o


all: test1 test2

test1: createDir read-csv

test2:
	echo "TEST2"


read-csv: $(TEST1)
	$(CC) -o $(RELEASE_DIR)/$@ $(OBJ_DIR)/$^ ../utils/util.cpp $(LDFLAGS)
	$(RELEASE_DIR)/$@


%.o: %.cpp
	$(CC) -o $(OBJ_DIR)/$@ -c $< $(CFLAGS)

createDir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RELEASE_DIR)

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RELEASE_DIR)
