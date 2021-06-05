DIR = `basename $(CURDIR)`
COMP = gcc
FLAGS = -Wall -std=c99 -pedantic -O
LDLIBS = -lrt

NAME1 = server
NAME2 = client
LIB1 = queue

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

LIBS1  = $(LIB1).c


%.o: %.c
	$(COMP) $(FLAGS) -c $<

.PHONY: compileAll
compileAll: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(COMP) -o $@ $(FLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2) $(LIBS1) 
	$(COMP) -o $@ $(FLAGS) $^ $(LDLIBS)

.PHONY: Run

Run: $(EXEC1) $(EXEC2)
	xterm -hold -title SERVER -bg palevioletred1 -e ./$(EXEC1) &
	xterm -hold -title CLIENT1 -bg DarkSlateGray3 -e ./$(EXEC2) &
	xterm -hold -title CLIENT2 -bg DarkSlateGray3 -e ./$(EXEC2) &
	xterm -hold -title CLIENT3 -bg DarkSlateGray3 -e ./$(EXEC2)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )