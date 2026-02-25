EXE=translate
SRC=translate.c task1.c task2.c task3.c task4.c queue.c tlb.c
OBJ=$(SRC:.c=.o)

$(EXE): $(SRC)
	cc -O3 -Wall -o $(EXE) $(SRC)

format:
	clang-format -style=file -i *.c *.h

clean:
	rm -f $(EXE) *.o