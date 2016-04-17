#include <iostream> 
#include "User.h"
#include "Loan.h"
#include "Student.h"
#include "Tax.h"
#include "Mortgage.h"


User::User(){

    Mortgage myMort; 
    Student myStu;

    double mortDeduct, stuDeduct; 
    
     
    mortDeduct = myMort.getPrinc();   
    myMort.amortize(); 
    cout<<myMort; 

    stuDeduct = myStu.getPrinc(); 
   
    Tax myTax(mortDeduct, stuDeduct);
    myTax.calcItax(); 

}
/*
User::~User(){
    delete myTax; 
    delete myMort; 
    delete myStu; 
}



Tax User::makeTax(double m, double s){
    return new Tax(m,s);  
}

Mortgage User::makeMortgage(){
    return new Mortgage; 
}

Student User::makeStudent(){
    return new Student; 
}


Tax User::getTax(){

    return myTax; 
}

Mortgage User::getMortgage(){

    return myMort; 
}

Student User::getStudent(){

    return myStu; 

}

*/
