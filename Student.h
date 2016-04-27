#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include "Loan.h" 
#include <iostream>

class Student : public Loan{

    friend ostream &operator<<(ostream&, const Student &S); 

    public:
        Student(); 
        Student(double ir, bool t, double princ, double month , double scholar) : Loan(ir, t, princ, month) {
        setPrinc(princ);
        setRate(ir);
        setMonths(month);
        setTax(t);
        setScholar(scholar); 
        }
        void createPlan();
        void setScholar(double); 
	void writeToFile(); 
    private:
        double scholarship; 
        vector<vector<double> > table; 
}; 

#endif
