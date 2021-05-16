DIR = `basename $(CURDIR)`
AR = ar
ARFLAGS = rsv
COMP = gcc
FLAGS = -Wall -std=gnu99 -pedantic -O -pthread
LDLIBS = -lrt

NAME1 = cw7
NAME2 = producer
NAME3 = consumer
NAME4 = semaphores_lib
NAME5 = shared_memory
LIB1 = semaphores_lib
LIB2 = shared_memory
INPUT = input
OUTPUT = output

LIBS1  = $(LIB1).c
LIBS2  = $(LIB2).c

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

LIB_NAME = My_Functions
LIB_DIR = ./lib
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so
LIB_OBJS = $(OBJS4) $(OBJS5)
HEADS4 = $(NAME4).h
HEADS5 = $(NAME5).h

EXEC1  = $(NAME1).x
EXEC2  = $(NAME2).x
EXEC3  = $(NAME3).x
EXEC1static = $(NAME1)s.x
EXEC2static = $(NAME2)s.x
EXEC3static = $(NAME3)s.x
EXEC1dynamic1 = $(NAME1)d1.x
EXEC2dynamic1 = $(NAME2)d1.x
EXEC3dynamic1 = $(NAME3)d1.x
EXEC1dynamic2 = $(NAME1)d2.x
EXEC2dynamic2 = $(NAME2)d2.x
EXEC3dynamic2 = $(NAME3)d2.x

%.o: %.c %.h
	$(COMP) $(FLAGS) -c $<
%.o: %.c
	$(COMP) $(FLAGS) -c $<

$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(LIB_SHAR): $(LIB_OBJS) 
	$(COMP) -shared -o $@ $(FLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

.PHONY: compileAll
compileAll: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC1static) $(EXEC2static) $(EXEC3static) $(EXEC1d) $(EXEC2d) $(EXEC3d)

$(EXEC1): $(OBJS1) $(LIBS1) $(LIBS2)
	$(COMP) -o $@ $(FLAGS) $^ $(LDLIBS)

$(EXEC2): $(OBJS2) $(LIBS1) $(LIBS2)
	$(COMP) -o $@ $(FLAGS) $^ $(LDLIBS)

$(EXEC3): $(OBJS3) $(LIBS1) $(LIBS2)
	$(COMP) -o $@ $(FLAGS) $^ $(LDLIBS)

$(EXEC1static): $(OBJS1) $(LIB_STAT) 
	$(COMP) -o $@ $(FLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2static): $(OBJS2) $(LIB_STAT) 
	$(COMP) -o $@ $(FLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3static): $(OBJS3) $(LIB_STAT) 
	$(COMP) -o $@ $(FLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC1dynamic1): $(OBJS1) $(LIB_SHAR)
	$(COMP) -o $@ $(FLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC2dynamic1): $(OBJS2) $(LIB_SHAR)
	$(COMP) -o $@ $(FLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC3dynamic1): $(OBJS3) $(LIB_SHAR)
	$(COMP) -o $@ $(FLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC1dynamic2): $(OBJS1) $(LIB_SHAR)
	$(COMP) -o $@ $(FLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2dynamic2): $(OBJS2) $(LIB_SHAR)
	$(COMP) -o $@ $(FLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3dynamic2): $(OBJS3) $(LIB_SHAR)
	$(COMP) -o $@ $(FLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(OBJS4): $(HEADS4)
$(OBJS5): $(HEADS5)

.PHONY: run runStatic runDynamic1 runDynamic2

run: $(EXEC1) $(EXEC2) $(EXEC3)
	clear
	./$(EXEC1) $(EXEC2) $(EXEC3)
	@echo "\n=================================================\n"
	@diff -s $(INPUT) $(OUTPUT)

runStatic: $(EXEC1static) $(EXEC2static) $(EXEC3static)
	clear
	./$(EXEC1static) $(EXEC2static) $(EXEC3static)
	@echo "\n=================================================\n"
	@diff -s $(INPUT) $(OUTPUT)

runDynamic1: $(EXEC1dynamic1) $(EXEC2dynamic1) $(EXEC3dynamic1)
	clear
	./$(EXEC1dynamic1) $(EXEC2dynamic1) $(EXEC3dynamic1)
	@echo "\n=================================================\n"
	@diff -s $(INPUT) $(OUTPUT)

runDynamic2: $(EXEC1dynamic2) $(EXEC2dynamic2) $(EXEC3dynamic2)
	clear
	( export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1dynamic2) $(EXEC2dynamic2) $(EXEC3dynamic2) )
	@echo "\n=================================================\n"
	@diff -s $(INPUT) $(OUTPUT)

.PHONY: clean tar

clean:
	rm -f *.o  *~ *.a *.so *.x COMPre COMPre* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )