COMP = gcc
FLAGS = -pedantic -Wall -std=c99

cw5 = cw5.c
manufacturer = manufacturer.c
consumer = consumer.c


compileAll: $(cw5) $(manufacturer) $(consumer)
	$(COMP) $(FLAGS) $(cw5) -o CW5
	$(COMP) $(FLAGS) $(manufacturer) -o MANUFACTURER
	$(COMP) $(FLAGS) $(consumer) -o CONSUMER

.PHONY: clean

clean:
	rm -f CW5
	rm -f MANUFACTURER
	rm -f CONSUMER

Run:
	mkfifo -m 0644 testfifo \
	& xterm -hold -title PRODUCENT -e ./manufacturer input.txt output.txt testfifo \
	& xterm -hold -title KONSUMENT -e ./consumer input.txt output.txt testfifo

