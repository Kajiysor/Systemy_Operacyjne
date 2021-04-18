COMP = gcc
FLAGS = -pedantic -Wall -std=c99

cw4 = cw4.c
CW4 = CW4


compileAll: $(cw4) 
	$(COMP) $(FLAGS) $(cw4) -o $(CW4)

.PHONY: clean

clean:  $(CW4)
	rm -f $(CW4)


