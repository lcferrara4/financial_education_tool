main: main.o Loan.o Mortgage.o Student.o Tax.o User.o stock.o
	g++ -std=c++11 main.o Loan.o Mortgage.o Student.o Tax.o User.o stock.o -o main

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

User.o: User.cpp
	g++ -std=c++11 -c User.cpp

Loan.o: Loan.cpp
	g++ -std=c++11 -c Loan.cpp

Mortgage.o: Mortgage.cpp Loan.o
	g++ -std=c++11 -c Mortgage.cpp

Student.o: Student.cpp Loan.o
	g++ -std=c++11 -c Student.cpp

Tax.o: Tax.cpp
	g++ -std=c++11 -c Tax.cpp

stock.o: stock.cpp
	g++ -std=c++11 -c stock.cpp

clean:
	rm -f *.o main
