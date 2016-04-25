main: main.o Loan.o Mortgage.o Student.o Tax.o User.o stock.o
	g++ -std=c++11 main.o Loan.o Mortgage.o Student.o Tax.o User.o stock.o

main.o: main.cpp
	g++ -c main.cpp

User.o: User.cpp
	g++ -c User.cpp

Loan.o: Loan.cpp
	g++ -c Loan.cpp

Mortgage.o: Mortgage.cpp Loan.o
	g++ -c Mortgage.cpp

Student.o: Student.cpp Loan.o
	g++ -c Student.cpp

Tax.o: Tax.cpp
	g++ -c Tax.cpp

stock.o: stock.cpp
	g++ -std=c++11 -c stock.cpp

clean:
	rm -f *.o main
