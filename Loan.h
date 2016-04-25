#ifndef LOAN_H
#define LOAN_H
#include <vector>

using namespace std; 



class Loan{

    public:
        Loan(); 
        Loan(double, bool, double, double); 
        ~Loan(); 
        double getIrate(void); 
        double getPrinc(void);
        void setPrinc(double);
        void setTax(bool); 
        void setRate(double); 
        void setMonths(double); 
        bool getTax(void); 
        double getMonths(void); 
    private:
        double interestRate;
        bool taxDeduct; 
        double princ;  
        double months; 

}; 

#endif
