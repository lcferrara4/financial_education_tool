main: main.o stock.o
	g++ main.o stock.o -o main

main.o: main.cpp
	g++ -c main.cpp

stock.o: stock.cpp
	g++ -c stock.cpp

clean:
	rm -f *.o main
