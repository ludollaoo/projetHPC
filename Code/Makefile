CC=gcc
CCFLAGS= -Wall -g
LIBFLAGS= 
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
TST= $(wildcard unitTest/*.c)
OBJ_TEST = $(filter-out main.o, $(OBJ)) $(TST:.c=.o)
EXEC= mouvement


all: $(EXEC)

testcase : $(OBJ_TEST) 
	gcc -Wall  -o $@ $^

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@ -lm

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

