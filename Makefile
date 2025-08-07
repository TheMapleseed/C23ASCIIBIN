# Makefile for ASCIIBIN Project
# Follows clean code principles and modular design

# Compiler and flags
CC = clang
CFLAGS = -std=c23 -Wall -Wextra -pedantic -Werror
DEBUG_CFLAGS = $(CFLAGS) -g -DDEBUG
RELEASE_CFLAGS = $(CFLAGS) -O2 -DNDEBUG

# Directories
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = asciibin.c lookup_table.c main.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Target executable
TARGET = $(BINDIR)/asciibin

# Default target
all: $(TARGET)

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Compile object files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@

# Debug build
debug: CFLAGS = $(DEBUG_CFLAGS)
debug: $(TARGET)

# Release build
release: CFLAGS = $(RELEASE_CFLAGS)
release: $(TARGET)

# Test with address sanitizer
test-asan: CFLAGS += -fsanitize=address
test-asan: $(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install (copy to system path)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/asciibin

# Run the program
run: $(TARGET)
	./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all        - Build the project (default)"
	@echo "  debug      - Build with debug symbols"
	@echo "  release    - Build optimized release version"
	@echo "  test-asan  - Build with address sanitizer"
	@echo "  clean      - Remove build artifacts"
	@echo "  install    - Install to system"
	@echo "  uninstall  - Remove from system"
	@echo "  run        - Build and run the program"
	@echo "  help       - Show this help message"

# Phony targets
.PHONY: all debug release test-asan clean install uninstall run help 