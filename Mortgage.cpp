#include <fstream>
#include "Loan.h"
#include "Mortgage.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
/*
Mortgage::Mortgage(double ir, bool t, double pr, double mont){
    setPrinc(pr); 
    setTax(t); 
    setMonths(mont); 
    setRate(ir); 
} 
*/

Mortgage::Mortgage(){
    
}



void Mortgage::amortize(){
    double principal=getPrinc(); 
    double intRate=getIrate();
    intRate = intRate /100;  
    int currMonth =1; 
    double interest, monthlyPayment, payment; 
    vector<double> temp;
    double months=getMonths(); 

    monthlyPayment=(principal * intRate * pow((1 + intRate),months) / (pow((1 + intRate),months) -1 )); 
    
    do{
        interest=principal*intRate; 
        temp.push_back(currMonth);
        temp.push_back(interest); 
        temp.push_back(principal);
        table.push_back(temp);
        interest = principal*intRate; 
        payment=monthlyPayment - interest; 
        principal = principal - payment; 
        currMonth++;
        temp.clear();
    }while (principal > payment); 
    interest=intRate*(monthlyPayment - principal);  
    principal = 0; 
    temp.push_back(currMonth);
    temp.push_back(interest); 
    temp.push_back(principal); 
    table.push_back(temp); 
    temp.clear(); 
    
    
}

ostream &operator<<(ostream &output, const Mortgage &M){

    output<<"MONTH\tINTEREST BALANCE"<<endl;
    for (int i=0; i<M.table.size(); i++){
        for (int j=0; j<M.table[i].size(); j++){
            output<<M.table[i][j]<<'\t'; 
        }
        output<<endl;
    }

}


void Mortgage::writeToFile(){

        ofstream myFile; 
        myFile.open("loanInfo.txt"); 
        myFile<<"MONTH\tINTEREST BALANCE"<<endl; 
	for(int i=0; i<table.size(); i++){
                for(int j=0; j<table[i].size(); j++){
                        myFile<<table[i][j]<<'\t';
                }
                myFile<<endl; 
        }
}

