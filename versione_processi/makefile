OBJ = main.c partita.c processi.c stampe.c header.h

eseguibile.o: $(OBJ)
	gcc main.c -l ncurses -o eseguibile.o
	./eseguibile.o

esegui:
	./eseguibile.o
	
clean:
	rm *.o
	
