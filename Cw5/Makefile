COMP = gcc
FLAGS = -pedantic -Wall -std=c99

cw5 = cw5.c
manufacturer = manufacturer.c
consumer = consumer.c

CW5 = CW5
MANUFACTURER = MANUFACTURER
CONSUMER = CONSUMER
FIFO = cw5b_fifo
INPUT = input.txt
OUTPUT = output.txt


compileAll: $(cw5) $(manufacturer) $(consumer)
	$(COMP) $(FLAGS) $(cw5) -o CW5
	$(COMP) $(FLAGS) $(manufacturer) -o MANUFACTURER
	$(COMP) $(FLAGS) $(consumer) -o CONSUMER

.PHONY: clean, Run, removeFIFO, removeOutput

clean:  $(CW5) $(MANUFACTURER) $(CONSUMER)
	rm -f $(CW5)
	rm -f $(MANUFACTURER)
	rm -f $(CONSUMER)

Run: $(CW5) $(MANUFACTURER) $(CONSUMER) $(INPUT) $(OUTPUT)
	mkfifo -m 0644 $(FIFO) \
	& xterm -hold -title PRODUCENT -e ./MANUFACTURER $(INPUT) $(OUTPUT) $(FIFO) \
	& xterm -hold -title KONSUMENT -e ./CONSUMER $(INPUT) $(OUTPUT) $(FIFO)

removeFIFO: $(FIFO)
	rm -r $(FIFO)

removeOutput: $(OUTPUT)
	rm -f $(OUTPUT)

