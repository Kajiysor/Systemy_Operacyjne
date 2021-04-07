COMP = gcc
FLAGS = -g -Wall -O0 -std=c11

1_A = 1a.c
1_B = 1b.c
1_C = 1c.c
1_D = 1d.c
1_E = 1e.c


compileAll: $(1_A) $(1_B) $(1_C) $(1_D) $(1_E)
	$(COMP) $(FLAGS) $(1_A) -o 1A
	$(COMP) $(FLAGS) $(1_B) -o 1B
	$(COMP) $(FLAGS) $(1_C) -o 1C
	$(COMP) $(FLAGS) $(1_D) -o 1D
	$(COMP) $(FLAGS) $(1_E) -o 1E

.PHONY: clean

clean:
	rm -f 1A
	rm -f 1B
	rm -f 1C
	rm -f 1D
	rm -f 1E
