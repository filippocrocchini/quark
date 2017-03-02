BIN_DIR = ./bin
OBJ_DIR = ./obj
SRC_DIR = ./src
INC_DIR = ./include

CC = g++
CFLAGS = -Wall -g

INCLUDES = -I$(INC_DIR)
LIBS = -lm
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

PURPLE = '\033[1;35m'
YELLOW = '\033[1;33m'
BLUE = '\033[1;34m'
NC = '\033[0m'

BOLD = '\033[1m'
# Output name
PROGRAM = smart

.PHONY: run setup clear

all: setup compile run

setup:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(INC_DIR)

clear:
	@rm -r $(OBJ_DIR)

run: setup
	@clear
	@echo -e $(BOLD)$(PURPLE)Running \"$(PROGRAM)\".$(NC)
	@echo
	@$(BIN_DIR)/$(PROGRAM)

compile: setup $(PROGRAM)
	@echo -e $(BOLD)$(YELLOW)The program \"$(PROGRAM)\" has been linked!$(NC)
	@echo

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
	@echo -e $(BOLD)$(BLUE)Compiled $< to $@.$(NC)
	@echo

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(PROGRAM) $(OBJS) $(LIBS)
