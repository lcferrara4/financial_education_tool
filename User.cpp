#include <iostream> 
#include "User.h"
#include "Loan.h"
#include "Student.h"
#include "Tax.h"
#include "Mortgage.h"


User::User(){

    myMort = getMortgage(); 
    myStu = getStudent(); 
    myTax = getTax(); 

}

User::~User(){
    delete *myTax; 
    delete *myMort; 
    delete *myStu; 

Tax* User::getTax(){

    return new Tax; 
}

Mortgage* User::getMortgage(){

    return new Mortgage; 
}

Student* User::getStudent(){

    return new Student; 

}
