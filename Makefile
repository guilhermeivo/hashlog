CC        ?= gcc
CFLAGS    := -Wall -Wextra -O2 -I./include
LIBS      := -lcrypto -lm -lconfuse
LDFLAGS  += -Wl,-T,commandinfo.ld

BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src

TARGET_NAME ?= main
TARGET := $(BIN_PATH)/$(TARGET_NAME)

SRC := $(shell find $(SRC_PATH) -name '*.c')
OBJ := $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC))

.PHONY: all clean distclean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_PATH)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH):
	mkdir -p $@

clean:
	rm -f $(OBJ)

distclean: clean
	rm -f $(TARGET)