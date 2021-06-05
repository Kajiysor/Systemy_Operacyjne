DIR = `basename $(CURDIR)`
COMP = gcc
FLAGS = -pthread -Wall -std=c99 -pedantic -O

NAME1 = multiplier.c
NAME2 = increment.c
LIB = semaphores_lib.c
PROCESS_AMOUNT = 2
SECTION_AMOUNT = 2
USING_CRITICAL_SECTION = 1

EXEC1  = MULTIPLIER
EXEC2  = INCREMENT


.PHONY: all
all: $(NAME1) $(NAME2) $(LIB)
	$(COMP) -o $(EXEC1) $(FLAGS) $(NAME1) $(LIB)
	$(COMP) -o $(EXEC2) $(FLAGS) $(NAME2) $(LIB)

.PHONY: Run

Run: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2) $(PROCESS_AMOUNT) $(SECTION_AMOUNT) $(USING_CRITICAL_SECTION)

.PHONY: CompileAndRun
CompileAndRun: $(NAME1) $(NAME2) $(LIB)
	$(COMP) -o $(EXEC1) $(FLAGS) $(NAME1) $(LIB)
	$(COMP) -o $(EXEC2) $(FLAGS) $(NAME2) $(LIB)
	clear
	./$(EXEC1) $(EXEC2) $(PROCESS_AMOUNT) $(SECTION_AMOUNT) $(USING_CRITICAL_SECTION)

.PHONY: clean

clean: $(EXEC1) $(EXEC2)
	rm -f $(EXEC1)
	rm -f $(EXEC2)

tar:
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )