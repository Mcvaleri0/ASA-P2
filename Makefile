
proj: proj.o
	gcc -g -Wall -pedantic -o proj proj.o

proj.o: proj.c
	gcc -g -Wall -pedantic -c proj.c

run:
	mkdir Testes/Meus-Outputs;
	sh testes.txt

diff:
	sh diff.txt

clean:
	rm -f *.o proj
	rm -r Testes/Meus-Outputs
