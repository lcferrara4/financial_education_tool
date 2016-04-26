#ifndef TAX_H
#define TAX_H

#include <iostream>
#include <string>
#include "Loan.h"
#include "Mortgage.h"
#include "Student.h"
#include <vector>

class Mortgage; 
class Student; 

using namespace std; 
class Tax{

    friend class Mortgage; 
    friend class Student;  
    friend class User; 

    public: 
        Tax(double);  
        void calcItax(double, string, bool); 
        void writeToFile(); 
    private:
        //double income; 
        string state; 
        double stateRate; 
        double fedRate; 
        double netIncome;
        double deductions;
        double taxAmount; 
	    Mortgage *myMort; 
        Student *myStu; 
        vector<vector<string> > singleState; 
        vector<vector<string> > marriedState; 
        vector<vector<string> > singleFed; 
        vector<vector<string> > marriedFed; 
        string clean(string); 

};

#endif
