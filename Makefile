CC = gcc
FILE = main
LIBS = 
WARNINGS = -Wall -Wextra -Wpedantic -Werror


.PHONY: valgrind cpl Cpl run Run val Val cln Cln


all: Cpl Run Cln

valgrind: Cpl Val Cln


cpl:
	$(CC) -o $(FILE).exe $(FILE).c $(LIBS) $(WARNINGS)
Cpl:
	@$(CC) -o $(FILE).exe $(FILE).c $(LIBS) $(WARNINGS)


run:
	./$(FILE).exe
Run:
	@./$(FILE).exe

val:
	valgrind ./$(FILE).exe
Val:
	@valgrind ./$(FILE).exe

cln:
	rm -f $(FILE).exe
Cln:
	@rm -f $(FILE).exe