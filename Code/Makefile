CC=gcc
CCFLAGS= -Wall -O3 -pg 
LIBFLAGS= -mssse3 -msse4 -fopenmp
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
TST= $(wildcard Test/OK/*.c)
OBJ_TEST = $(filter-out main.o, $(OBJ)) $(TST:.c=.o)
EXEC= mouvement


all: $(EXEC)

testcase : $(OBJ_TEST) 
	gcc -Wall  -o $@ $^

$(EXEC): $(OBJ)
	$(CC) -pg $(LIBFLAGS) $^ -o $@  

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depend:
	gcc -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC)
cleantest:
	rm -f $(OBJ_TEST) testcase
distclean : clean cleantest

