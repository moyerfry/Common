CC=g++
AR=ar
AR_OPTS=rvs
CFLAGS=-O2 -std=c++14
BUILD_DIR=./build
INC_DIR=./include
SRC_DIR=./src
MK_DIR_CALL=mkdir
RM_CALL=rm
RM_RECURSIVE_FLAG=-R
OUTPUT_NAME=Common
OUTPUT_LIB_NAME=Lib$(OUTPUT_NAME)
PROGRAM_NAME=$(OUTPUT_NAME)Tests
MAIN_FILE=test.cpp
FILES_IN_SRC = ConfigParser

all: $(BUILD_DIR) $(FILES_IN_SRC)
	make tester
	make lib

tester: $(BUILD_DIR) $(FILES_IN_SRC)
	$(CC) -o $(PROGRAM_NAME) $(MAIN_FILE) $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(FILES_IN_SRC))) $(CFLAGS) -I$(INC_DIR)

lib: $(BUILD_DIR) $(FILES_IN_SRC)
	$(AR) $(AR_OPTS) $(OUTPUT_LIB_NAME).a $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(FILES_IN_SRC)))

$(FILES_IN_SRC):
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_DIR)/$@.o -I$(INC_DIR) -c $(SRC_DIR)/$@.cpp

$(BUILD_DIR):
	$(MK_DIR_CALL) $(BUILD_DIR)

clean:
	$(RM_CALL) $(RM_RECURSIVE_FLAG) $(BUILD_DIR)
	$(RM_CALL) $(PROGRAM_NAME)
	$(RM_CALL) $(OUTPUT_LIB_NAME).a
