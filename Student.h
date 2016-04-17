#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include "Loan.h" 
#include <iostream>

class Tax; 

class Student : public Loan{

    friend ostream &operator<<(ostream&, const Student &S); 
    friend class Tax; 

    public:
        Student(); 
        Student(double, double); 
        void createPlan();
        void setScholar(double); 
    private:
        double scholarship; 
        vector<vector<double> > table; 
}; 

#endif
