COMP = gcc
FLAGS = -g -pedantic -Wall -O0 -std=c99

CW2 = parent.c
CHILD = child.c


compileAll: $(CW2) $(CHILD)
	$(COMP) $(FLAGS) $(CW2) -o PARENT
	$(COMP) $(FLAGS) $(CHILD) -o CHILD

.PHONY: clean

clean:
	rm -f PARENT
	rm -f CHILD