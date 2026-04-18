CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude # -pedantic -std=c11 -D_POSIX_C_SOURCE=200809L
TARGET  = my_shell

PACKAGE = assign2_24711891
VERSION = 1.0
DISTDIR = $(PACKAGE)-$(VERSION)

SRC_DIR = src
INC_DIR = include

SRCS    = $(SRC_DIR)/main.c \
          $(SRC_DIR)/signals.c \
          $(SRC_DIR)/prompt.c \
          $(SRC_DIR)/input.c \
          $(SRC_DIR)/builtins.c \
          $(SRC_DIR)/exec.c

OBJS    = $(SRCS:.c=.o)

.PHONY: all clean dist

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(DISTDIR) $(DISTDIR).tar.gz

# Header dependencies
$(SRC_DIR)/main.o:     $(SRC_DIR)/main.c $(INC_DIR)/signals.h $(INC_DIR)/prompt.h $(INC_DIR)/input.h $(INC_DIR)/builtins.h $(INC_DIR)/exec.h
$(SRC_DIR)/signals.o:  $(SRC_DIR)/signals.c $(INC_DIR)/signals.h
$(SRC_DIR)/prompt.o:   $(SRC_DIR)/prompt.c $(INC_DIR)/prompt.h
$(SRC_DIR)/input.o:    $(SRC_DIR)/input.c $(INC_DIR)/input.h $(INC_DIR)/signals.h
$(SRC_DIR)/builtins.o: $(SRC_DIR)/builtins.c $(INC_DIR)/builtins.h
$(SRC_DIR)/exec.o:     $(SRC_DIR)/exec.c $(INC_DIR)/exec.h

dist:
	rm -rf $(DISTDIR)
	mkdir -p $(DISTDIR)/src $(DISTDIR)/include
	cp $(SRC_DIR)/*.c $(DISTDIR)/src
	cp $(INC_DIR)/*.h $(DISTDIR)/include
	cp Makefile README.md $(DISTDIR) 2>/dev/null || true
	tar -czf $(DISTDIR).tar.gz $(DISTDIR)
	rm -rf $(DISTDIR)