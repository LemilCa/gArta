CC = gcc
EXEC_FILE = gArta.exe
C_FILE = gArta.c
LIBS = 
WARNINGS = -Wall -Wextra -Wpedantic -Werror


.PHONY: valgrind cpl Cpl run Run val Val cln Cln


all: Cpl Run Cln

valgrind: Cpl Val Cln


cpl:
	$(CC) -o $(EXEC_FILE) $(C_FILE) $(LIBS) $(WARNINGS)
Cpl:
	@$(CC) -o $(EXEC_FILE) $(C_FILE) $(LIBS) $(WARNINGS)


run:
	./$(EXEC_FILE)
Run:
	@./$(EXEC_FILE)

val:
	valgrind ./$(EXEC_FILE)
Val:
	@valgrind ./$(EXEC_FILE)

cln:
	rm -f $(EXEC_FILE)
Cln:
	@rm -f $(EXEC_FILE)