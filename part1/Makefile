mdb-lookup: mdb-lookup.o ../../lab3/part1/libmylist.a
	gcc -o mdb-lookup mdb-lookup.o -L../../lab3/part1 -lmylist

mdb-lookup.o: mdb-lookup.c ../../lab3/part1/libmylist.a
	gcc -c -g -Wall mdb-lookup.c -I../../lab3/part1

.PHONY: vtest
vtest: revecho
	valgrind --leak-check=yes mdb-lookup

.PHONY: clean
clean:
	rm -f *.o *.a a.out
