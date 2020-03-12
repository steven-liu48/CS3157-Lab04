mdb-lookup: mdb-lookup.o ../../lab3/solutions/part1
	gcc -o mdb-lookup mdb-lookup.o -L../../lab3/solutions/part1 -lmylist

mdb-lookup.o: mdb-lookup.c ../../lab3/part1/libmylist.a
	gcc -c -g -Wall mdb-lookup.c -I../../lab3/solutions/part1

.PHONY: vtest
vtest: mdb-lookup
	valgrind --leak-check=yes ./mdb-lookup mdb-cs3157

.PHONY: clean
clean:
	rm -f *.o *.a mdb-lookup
