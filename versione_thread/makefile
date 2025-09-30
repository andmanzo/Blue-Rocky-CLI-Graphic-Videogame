OBJ = main.c partita.c threads.c stampe.c header.h

eseguibile.o: $(OBJ)
	gcc main.c -l ncurses -l pthread -o eseguibile.o
	./eseguibile.o

esegui:
	./eseguibile.o
	
clean:
	rm *.o
	
