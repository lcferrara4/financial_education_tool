#include <iostream> 
#include "Loan.h"
#include "Tax.h"

using namespace std; 

Loan::Loan(){

    double rate, princ, months; 
    bool tax; 
    
    cout<<"Enter interest rate: "<<endl; 
    cin>>rate;
    cout<<"Is this lona tax dectible? ( 0 for no 1 for yes)"<<endl; 
    cin>>tax; 
    cout<<"What is the principal?"<<endl; 
    cin>>princ; 
    cout<<"In how many months would you like to be debt free?"<<endl; 
    cin>>months; 

    setRate(rate); 
    setTax(tax); 
    setMonths(months); 
    setPrinc(princ); 

     

}

Loan::Loan(double iRate, bool tax, double p, double t){

    interestRate=iRate; 
    taxDeduct = tax; 
    princ = p; 
    months= t; 
}

Loan::~Loan(){
    setRate(0); 
    setTax(0); 
    setMonths(0); 
    setPrinc(0); 

}
double Loan::getIrate(){
    return interestRate; 
}

bool Loan::getTax(){
    return taxDeduct; 
}

double Loan::getPrinc(){
    return princ; 
}

void Loan::setPrinc(double newP){
    princ=newP; 
}
double Loan::getMonths(){
    return months;
}

void Loan::setRate(double rate){
    interestRate=rate; 
}
void Loan::setMonths(double month){
    months=month; 
}
void Loan::setTax(bool tax){
    taxDeduct=tax; 
}
