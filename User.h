#include "Tax.h"
using namespace std; 

class Student; 
class Mortgage; 
class Tax; 

class User{

    friend class Tax; 
    public: 
        User(); 
       // ~User();
        Student makeStudent(); 
        Mortgage makeMortgage(); 
        Tax makeTax(double, double); 
        Student getStudent(); 
        Mortgage getMortgage(); 
        Tax getTax();     
    private: 
        //Mortgage myMort;
        //Tax myTax(double, double);
        //Student myStu; 
};
