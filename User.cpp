#include <iostream> 
#include "User.h"
#include "Loan.h"
#include "Student.h"
#include "Tax.h"
#include "Mortgage.h"


User::User(){

	income = 50000;
	state = "Indiana";
	status = 0;

	interestRate = 0; 
	principle = 1000;
	months = 1;
	scholarship = 0;
	type = 0;
	deductions = 0;

/*
    cout<<"Enter Income: "; 
    cin>>income; 
    cout<<"Enter State: "; 
    cin>>state; 
*/
}

User::User(double i, string s, bool stat, double in, double p, int m, double schol, bool t){
	income = i;
	state = s;
	status = stat; 
	
	interestRate = in;
	principle = p;
	months = m;
	scholarship = schol;
	type = t;
}

void User::runTax(){

	cout<<"USER RUNNING"<<endl;

	string state; 
        cout<<"\nTAX INFORMATION";

    Tax myTax(deductions);
    myTax.calcItax(income,getState(), getStatus());
    myTax.writeToFile(); 

}

void User::runLoan(){
    double mortDeduct, stuDeduct;
    double userIncome, deductions;

	if( type ){
    		Mortgage myMort(interestRate, 1, principle, months); 
	    	mortDeduct = myMort.getPrinc();   
		stuDeduct = 0;
	    	myMort.amortize();
		myMort.writeToFile();  
	    	cout<<myMort; 
	}
	else{  
    		Student myStu(interestRate, 1, principle, months, scholarship);
		stuDeduct = myStu.getPrinc();
		mortDeduct = 0;
    		cout<<"\nSTUDENT LOAN PLAN"<<endl; 
    		myStu.createPlan(); 
    		myStu.writeToFile(); 
		cout<<myStu; 
	}

    deductions = mortDeduct+stuDeduct+stockDeduct; 

}

bool User::getStatus(){
	return status; 
}

void User::setStockDeduct(double value){
    stockDeduct = value; 
}

void User::addIncome(double stockIncome){
    income = income +stockIncome; 
}

void User::setIncome(double i){
	income = i; 
}
void User::setState(string s){
	state = s;
}

void User::setStatus( bool s ){
	status = s;
}

void User::setInterestRate(double i){
        interestRate = i;
}

void User::setPrinciple(double p){
        principle = p;
}

void User::setMonths( int m ){
        months = m;
}

void User::setScholarship( double s ){
	scholarship = s;
}

void User::setType( bool t ){
        type = t;
}

string User::getState(){
    return state; 
}
