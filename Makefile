# Compiler
CC = gcc

# Source files
SRC = main.c event_manager.c module.c event_trigger.c

# Output executable
TARGET = event_manager

# Build the program
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET)

# Clean up
clean:
	rm -f $(TARGET)

