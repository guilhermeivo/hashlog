GIT_VERSION := "$(shell git describe --abbrev=4 --always --tags)"

CC        ?= gcc
CFLAGS    := -Wall -Wextra -O2 -I./include -DVERSION=\"$(GIT_VERSION)\"

LIBS      := -lcrypto -lm -lconfuse
LDFLAGS  += -Wl,-T,commandinfo.ld

BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src

TARGET_NAME ?= hashlog
TARGET := $(BIN_PATH)/$(TARGET_NAME)

PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin
MANDIR := $(PREFIX)/share/man
MANPAGE := $(OBJ_PATH)/$(TARGET_NAME).1

SRC := $(shell find $(SRC_PATH) -name '*.c')
OBJ := $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC))

.PHONY: all clean distclean

all: $(TARGET) $(MANPAGE)

$(TARGET): $(OBJ) | $(BIN_PATH)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH):
	mkdir -p $@

$(MANPAGE):
	help2man ./$(TARGET) -o $(MANPAGE)

install: all
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)

	install -d $(MANDIR)/man1
	gzip -c $(MANPAGE) | install -m 644 /dev/stdin $(MANDIR)/man1/$(TARGET_NAME).1.gz

uninstall:
	rm -f $(BINDIR)/$(TARGET_NAME)
	rm -f $(MANDIR)/man1/$(TARGET_NAME).1.gz

clean:
	rm -f $(OBJ)
	rm -f $(MANPAGE)

distclean: clean
	rm -f $(TARGET)