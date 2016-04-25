#include "Tax.h"
using namespace std; 

class Student; 
class Mortgage; 
class Tax; 

class User{

    friend class Tax; 
    public: 
        User(); 
        void run(); 
        void setStockDeduct(double);
        void setIncome(double); 
    private:
        double stockDeduct; 
        double income; 
        string state; 
        //Mortgage myMort;
        //Tax myTax(double, double);
        //Student myStu; 
};
