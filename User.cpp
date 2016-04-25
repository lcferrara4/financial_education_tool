#include <iostream> 
#include "User.h"
#include "Loan.h"
#include "Student.h"
#include "Tax.h"
#include "Mortgage.h"


User::User(){

    cout<<"Enter Income: "; 
    cin>>income; 
    cout<<"Enter State: "; 
    cin>>state; 

}

void User::run(){
    Mortgage myMort(.5, 1, 1000, 6);  
    Student myStu(0, 1, 500, 3, 0);

    double mortDeduct, stuDeduct;
    double userIncome, deductions;
    string state; 
     
    mortDeduct = myMort.getPrinc();   
    myMort.amortize(); 
    cout<<myMort; 

    stuDeduct = myStu.getPrinc();
    cout<<"\nSTUDENT LOAN PLAN"<<endl; 
    myStu.createPlan(); 
    cout<<myStu; 

    cout<<"\nTAX INFORMATION";
    deductions = mortDeduct+stuDeduct+stockDeduct; 

    Tax myTax(deductions);
    myTax.calcItax(income,getState());
    myTax.writeToFile(); 

}

void User::setStockDeduct(double value){
    stockDeduct = value; 
}

void User::setIncome(double stockIncome){
    income = income +stockIncome; 
}

string User::getState(){
    return state; 
}
