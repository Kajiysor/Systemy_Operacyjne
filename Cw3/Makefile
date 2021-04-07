COMP = gcc
FLAGS = -pedantic -Wall -std=c99

3_A = 3_a.c
3_B = 3_b.c
3_C = 3_c-1.c
3_C-2 = 3_c-2.c


compileAll: $(3_A) $(3_B) $(3_C) $(3_C-2)
	$(COMP) $(FLAGS) $(3_A) -o 3A
	$(COMP) $(FLAGS) $(3_B) -o 3B
	$(COMP) $(FLAGS) $(3_C) -o 3C
	$(COMP) $(FLAGS) $(3_C-2) -o 3C-2

.PHONY: clean

clean:
	rm -f 3A
	rm -f 3B
	rm -f 3C-1
	rm -f 3C-2
