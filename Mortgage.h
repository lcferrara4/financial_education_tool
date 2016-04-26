#ifndef MORTGAGE_H
#define MORTGAGE_H

#include <iostream>
#include <vector>


class Tax; 
class Mortgage : public Loan{

    friend ostream &operator<<(ostream&, const Mortgage &M); 

    friend class Tax; 

    public:
        Mortgage();
        Mortgage(double ir, bool t, double princ, double month): Loan(ir,t,princ,month) {
            setRate(ir);
            setTax(t);
            setPrinc(princ); 
            setMonths(month);
        };  
        void amortize(); 
	void writeToFile();     
private:
        vector<vector<double> > table; 
}; 

#endif
