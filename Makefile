main: main.o Loan.o Mortgage.o Student.o Tax.o User.o
	g++ main.o Loan.o Mortgage.o Student.o Tax.o User.o -o main

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

clean:
	rm -f *.o main
