#ifndef MORTGAGE_H
#define MORTGAGE_H

#include <iostream>
#include <vector>



class Mortgage : public Loan{

    friend ostream &operator<<(ostream&, const Mortgage &M); 

    friend class Tax; 

    public:
        Mortgage();
        Mortgage(double, bool, double, double); 
        void credit(double); 
        void amortize(); 
    private:
        vector<vector<double> > table; 
}; 

#endif
