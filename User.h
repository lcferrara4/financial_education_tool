#include "Tax.h"
using namespace std; 

class Student; 
class Mortgage; 
class Tax; 

class User{

    friend class Tax; 
    public: 
        User(); 
	User(double, string, bool, double, double, int, double, bool);
        void run(); 
        void setStockDeduct(double);
        void setIncome(double);
	void setState(string);
	void addIncome(double); 
	void setStatus(bool); 
        void setInterestRate(double);
	void setPrinciple(double);
	void setMonths(int);
	void setType(bool);
	void setScholarship(double);
	string getState();
	bool getStatus();  
    private:
        bool status; 
	double stockDeduct; 
        double income; 
        string state; 
	double interestRate;
	double principle;
	int months;
	bool type;
	double scholarship;
        //Mortgage myMort;
        //Tax myTax(double, double);
        //Student myStu; 
};
