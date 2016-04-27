#include "Tax.h"
using namespace std; 

class Student; 
class Mortgage; 
class Tax;
class stock;

class User{

//    friend class Tax; 
    public: 
        User(); 
	User(double, string, bool, double, double, int, double, bool);
        void runTax();
	void runLoan();
        void setStockDeduct(double);
        void setIncome(double);
	void setState(string);
	void recalcIncome(double, double); 
	void setStatus(bool); 
        void setInterestRate(double);
	void setPrinciple(double);
	void setMonths(int);
	void setType(bool);
	void setScholarship(double);
	string getState();
	bool getStatus();  

	void stockRecalc(int);
	void stockTransaction(int,int,int);
	void setStockType();
	void setStockName();
	void setStockPrice();
	void setStockTotal();
	double getStockTotal();
	double makeSP();
	double calcStockTotal();
	string getTotalString(int);
	double getStockPrice(int);
	double getGraphPrice(int, int);
	double getSP(int);
	double getTaxable();
    private:
	// tax variables
        bool status; 
	double stockDeduct; 
	double mortDeduct; 
	double stuDeduct; 
        double income; 
        string state; 
	// loan variables
	double interestRate;
	double principle;
	int months;
	bool type;
	double scholarship;
        double deductions;
	// stock variables
	//string stockType;
	//string stockName;
	double stockPrice;
	double stockTotal;
	int total[60];
        vector<stock> stocks;
        vector<vector<double> > graphs;

	vector<double> sp;

	vector<int> stockType;
	vector<int> stockNumber;
	vector<double> stockAmount;

};
