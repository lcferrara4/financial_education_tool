#include "Tax.h"
using namespace std; 

class Student; 
class Mortgage; 
class Tax; 

class User{
    public: 
        User(); 
        ~User(); 
        Student *getStudent(); 
        Mortgage *getMortgage(); 
        Tax *getTax();     
    private: 
        Mortgage *myMort;
        Tax *myTax;
        Student *myStu; 
};
