DIR = `basename $(CURDIR)`
COMP = gcc

NAME1 = cw9
THREADS = 3
SECTIONS = 3
LIB1 = threads
EXEC1  = $(NAME1).x
OBJS1  = $(NAME1).o
HEADS1 = $(LIB1).h
LIBS1  = $(LIB1).c

FLAGS = -Wall -std=c99 -pedantic -O
LDLIBS = -lpthread

%.o: %.c
	$(COMP) $(FLAGS) -c $<

.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1) $(LIBS1)
	$(COMP) -o $@ $(FLAGS) $^ $(LDLIBS)

$(OBJS1): $(HEADS1)

.PHONY: Run

Run: $(EXEC1)
	clear
	./$(EXEC1) $(THREADS) $(SECTIONS)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x COMPre COMPre* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )