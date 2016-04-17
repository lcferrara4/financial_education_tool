#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include "Loan.h"
#include "Mortgage.h"
#include "Tax.h"

using namespace std; 
Tax::Tax(double mortDeductions, double studentDeductions){

	  deductions = mortDeductions + studentDeductions; 

    int count=0; 
    string word, line; 
    vector<string> temp; 

    ifstream inFile; 
    inFile.open("singleTaxes.data"); 

   while(! inFile.eof()){
        getline(inFile, line, ',');
        temp.push_back(line); 
        count ++; 
        if (count ==6){
            singleState.push_back(temp); 
            temp.clear(); 
            count =0; 
        }
    }
    for(int i=0; i<singleState.size(); i++){
        for (int j=0; j<singleState[i].size(); j++){
            //cout<<singleState[i][j];  
        }
    }
    inFile.close(); 
    ifstream inFile2; 
    inFile2.open("marriedTaxes.data"); 
    temp.clear();  
    while( !inFile2.eof()){
        getline(inFile2, line, ',');
        temp.push_back(line); 
        count ++; 
        if (count ==6){
            marriedState.push_back(temp); 
            temp.clear(); 
            count =0; 
        }
    }
    for(int i=0; i<marriedState.size(); i++){
        for (int j=0; j<marriedState[i].size(); j++){
            //cout<<marriedState[i][j]<<' '; 
        }
    }
    inFile2.close(); 

    //initialize Federal Vectors
    
    ifstream inFile3; 
    inFile3.open("singleFed.data"); 
    temp.clear(); 
    count=0; 
    while (!inFile3.eof()){
        getline(inFile3, line, ','); 
        temp.push_back(line); 
        count++; 
        if (count == 2){
            singleFed.push_back(temp); 
            temp.clear(); 
            count=0; 
        }
    }
    count=0; 
    inFile3.close();
    
    ifstream inFile4; 
    inFile4.open("marriedFed.data"); 
    temp.clear(); 
    while (!inFile4.eof()){
        getline(inFile4, line, ','); 
        temp.push_back(line); 
        count++; 
        if (count==2){
            marriedFed.push_back(temp); 
            temp.clear(); 
            count=0; 
        }
    }
    inFile4.close(); 
    
}

void Tax::calcItax(){

    string state = "NewJersey";
    string newStr; 
    bool married=0; 
    bool single=1; 
    vector<vector<string> > row; 
    income=25000;
    double value, value2; 

    //find state

    if (single){
        for(int i=0; i<singleState.size(); i++){
            if ((clean(singleState[i][0])) == state){
                 row.push_back(singleState[i]); 
            }
        }
        
    }
    else if (married){
        for (int i=0; i<marriedState.size(); i++){
            if (clean(marriedState[i][0]) == state){
                row.push_back(marriedState[i]); 
            }
        }
    }

       //get state tax rate based on income 
    for(int i=0; i<(row.size()-1); i++){
        value = boost::lexical_cast<double>(row[i][2]); //boost typecasts string to double
        value2=boost::lexical_cast<double>(row[i+1][2]); //boost typecasts string to double 
            
        if (income >= value && income <value2){
               stateRate=boost::lexical_cast<double>(row[i][1]); 
               cout<<stateRate; 
               break; 
        }
    }
    //get federal state rate based on income 
    if (single){
        for(int i=0; i<singleFed.size()-1; i++){
            value=boost::lexical_cast<double>(singleFed[i][1]); 
            value2=boost::lexical_cast<double>(singleFed[i+1][1]); 

            if (income >= value && income <value2){
                fedRate=boost::lexical_cast<double>(singleFed[i][0]); 
                break; 
            }
        }
    }
    else if (married){
        for (int i=0; i<marriedFed.size()-1; i++){
            value=boost::lexical_cast<double>(marriedFed[i][1]); 
            value2=boost::lexical_cast<double>(marriedFed[i+1][1]); 

            if(income >= value && income <value2){
                fedRate=boost::lexical_cast<double>(marriedFed[i][0]);
                break; 
            }
        }
    }

     if (state == "Colorado" || state == "Illinois" || state == "Michigan" || state == "Indiana"){
        stateRate = boost::lexical_cast<double>(row[0][1]); 
        stateRate = stateRate * fedRate / 100; 
     }




    //CALCULATE INCOME TAX 
    
    double taxable = income - deductions; 

    taxAmount = taxable -taxable*stateRate - taxable*fedRate; 

    cout<<income<<" is your income, your tax rate is: "<<endl; 

}

string Tax::clean(string state){
    for(int i=0; i<state.size(); i++){
        if (!isalpha(state[i])){
            state.erase(i,1); 
            i--; 
        }
    }
    return state; 
}

/*
void Tax::getDeductions(){

    
    if (myMort.getTax()){ //bool returns whether or not loan is tax deductible 
        deductions+=myMort.getPrinc(); 
    }

}
*/
