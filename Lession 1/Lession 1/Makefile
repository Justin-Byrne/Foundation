# VARIABLES
## Binary
BIN := dice_game

## Compiler
CXX := gcc

# CONDITIONALS
ifeq ($(OS),Windows_NT)
	CLEAN := del *.o && del $(BIN)
else
	CLEAN := rm -f *.o && rm -f $(BIN)
endif

# COMMANDS
## All
all: $(BIN)

## Binary
$(BIN): main.c
	touch $@
	$(CXX) main.c -o $@

## Clean
clean:
	$(CLEAN)