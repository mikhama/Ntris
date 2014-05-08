Ntris: 		main.o ntris.o ui.o
			gcc -o Ntris main.o ntris.o ui.o -lncurses
main.o:		main.c
			gcc -c main.c
ntris.o: 	ntris.c
			gcc -c ntris.c
ui.o:		ui.c
			gcc -c ui.c
clean:
			rm -f *.o Ntris save
