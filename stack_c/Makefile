SRC_DIR = src/
LINN_DIR = $(SRC_DIR)linn_lib/
SRC_FILE_NAMES = j_stack.c
SRC_FILES = $(foreach f, $(SRC_FILE_NAMES), $(SRC_DIR)$f)

TEST_DIR = test/
CUNIT_DIR = $(TEST_DIR)cunit/
TEST_FILE_NAMES = CU_main.c stackTest.c j_stackTest.c l_stackTest.c
TEST_FILES = $(foreach f, $(TEST_FILE_NAMES), $(TEST_DIR)$f)

CC = gcc
OBJS  = $(SRC_FILES:.c=.o)
OBJS += $(TEST_FILES:.c=.o)
LIBS  = $(LINN_DIR)libl_stack.a
LIBS += $(CUNIT_DIR)libcunit.a

CFLAGS  = -Wall
CFLAGS += -I$(SRC_DIR)
CFLAGS += -I$(TEST_DIR)
CFLAGS += -I$(CUNIT_DIR)
CFLAGS += -I$(LINN_DIR)

test_runner: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean win-clean
clean:
	$(RM) *.exe $(OBJS) -

win-clean:
	cmd /C del /S *.exe *.o 2>nul