# Project subdirectories
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin

# Compiler rules
CC=gcc
CFLAGS=-I$(INCDIR) -lm -Wall -O3

# Linker flags and libs
LDFLAGS=-lm
LDLIBS=

# Name of final executable
TARGET=run_md

# Expanding these variables immediately with := operator
SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Notes: $@ refers to the file name of the target of the rule
#        $< refers to the name of the first prerequisite
$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $@

# This is a poor way to do this, actually, because an object
# file depends on all header files. I suppose we don't expect
# the headers to change very often. It would be cleaner to build
# a list of header files that each source file depends on, especially
# since this will be a relatively small project.
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean clean_all

clean:
	rm $(BINDIR)/$(TARGET) 

cleanall:
	rm $(BINDIR)/$(TARGET) 
	rm $(OBJECTS)