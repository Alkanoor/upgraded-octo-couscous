USE_BOOST_CUSTOM_WINDOWS = 0
USE_BOOST_LINUX = 0

OBJ_DIR = obj
RELEASE_DIR = bin
OUTPUT_DIR = output

CC = g++
CFLAGS = -Wall -Werror -O1 -std=c++11 -I"C:\Program Files (x86)\CodeBlocks\boost_1_59_0" -g

ifeq ($(strip $(USE_BOOST_LINUX)),1)
LDFLAGS = -std=c++11 -L"C:\Boost\lib" -lboost_regex -g
else
	ifeq ($(strip $(USE_BOOST_CUSTOM_WINDOWS)),1)
	LDFLAGS = -std=c++11 -L"C:\Boost\lib" -lboost_regex-mgw49-mt-1_59
	else
	LDFLAGS = -std=c++11 -L"C:\Boost\lib"
	endif
endif

TEST1 = $(OBJ_DIR)/read_csv.o $(OBJ_DIR)/util.o
TEST2 = $(OBJ_DIR)/replace_test.o $(OBJ_DIR)/util.o
TEST3 = $(OBJ_DIR)/read_csv_with_preprocessing.o $(OBJ_DIR)/util.o $(OBJ_DIR)/preprocessing.o $(OBJ_DIR)/counts.o
TEST4 = $(OBJ_DIR)/test_counts.o $(OBJ_DIR)/counts.o
TEST5 = $(OBJ_DIR)/vectorize_test.o $(OBJ_DIR)/util.o $(OBJ_DIR)/preprocessing.o $(OBJ_DIR)/vectorizer.o
TEST6 = $(OBJ_DIR)/test_tfidf.o $(OBJ_DIR)/util.o $(OBJ_DIR)/preprocessing.o $(OBJ_DIR)/vectorizer.o $(OBJ_DIR)/tfidf.o $(OBJ_DIR)/comparaison_train_test.o
TEST7 = $(OBJ_DIR)/distances_for_lemmatisation_test.o $(OBJ_DIR)/util.o $(OBJ_DIR)/preprocessing.o $(OBJ_DIR)/vectorizer.o $(OBJ_DIR)/comparaison_train_test.o
TEST8 = $(OBJ_DIR)/test_all_cases.o $(OBJ_DIR)/util.o $(OBJ_DIR)/preprocessing.o $(OBJ_DIR)/vectorizer.o $(OBJ_DIR)/comparaison_train_test.o
TEST9 = $(OBJ_DIR)/test_learner.o $(OBJ_DIR)/util.o $(OBJ_DIR)/vectorizer.o $(OBJ_DIR)/learner.o

VPATH = .:../utils


all: test1 test2 test3 test4 test5 test6 test7 test8 test9

test1: createDir read-csv

test2: createDir replace_test

test3: createDir read_csv_with_preprocessing

test4: createDir test_counts

test5: createDir vectorize_test

test6: createDir test_tfidf

test7: createDir distances_for_lemmatisation_test

test8: createDir test_all_cases

test9: createDir test_learner


read-csv: $(TEST1)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

replace_test: $(TEST2)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

read_csv_with_preprocessing: $(TEST3)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

test_counts: $(TEST4)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

vectorize_test: $(TEST5)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

test_tfidf: $(TEST6)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

distances_for_lemmatisation_test: $(TEST7)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

test_all_cases: $(TEST8)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@

test_learner: $(TEST9)
	$(CC) -o $(RELEASE_DIR)/$@ $^ $(LDFLAGS)
	$(RELEASE_DIR)/$@


$(OBJ_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

createDir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(OUTPUT_DIR)

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(RELEASE_DIR)
	@rm -rf $(OUTPUT_DIR)
