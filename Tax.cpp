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
Tax::Tax(double deduct){

    //income = 2500; 
	deductions = deduct;  
      
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

    inFile.close(); 
    ifstream inFile2; 
    inFile2.open("marriedTaxes.data"); 
    temp.clear();  
    count =0; 
    while( ! inFile2.eof()){
        getline(inFile2, line, ',');
        temp.push_back(line);
        count ++; 
        if (count ==6){
            marriedState.push_back(temp); 
            temp.clear(); 
            count =0; 
        }
    }
    inFile2.close(); 

   
}

void Tax::calcItax(double income, string UserState, bool filingStatus){


    state = clean(UserState); 
    bool married, single; 
	
    //set filing status
    if (filingStatus){
		married = 0; 
		single = 1; 
	}
	else if(!filingStatus){
		married =1; 
		single = 0; 
	}
    vector<vector<string> > row;  
    double value, value2,max;  

    //find state information for all incomes 
    if (single){
        for(int i=0; i<singleState.size(); i++){
            if ((clean(singleState[i][0])) == state){
		        row.push_back(singleState[i]); 
            }
        }
        
    }
    if (married){
        for (int k=0; k<marriedState.size(); k++){
            if ((clean(marriedState[k][0])) == state){
                row.push_back(marriedState[k]); 
            }
        }
    }


    
    //get state tax rate based on income
    int size = row.size();
    if (size == 1){
        stateRate = boost::lexical_cast<double>(row[0][1]); 
    }
    else{
    for(int i=0; i<size-1; i++){
        max = boost::lexical_cast<double>(row[size-1][2]);
        if (income >= max){
            stateRate=boost::lexical_cast<double>(row[size-1][1]); 
            break; 
        }
        else{
            value = boost::lexical_cast<double>(row[i][2]); //boost typecasts string to double
            value2 = boost::lexical_cast<double>(row[i+1][2]); //boost typecasts string to double
                if (income >= value && income < value2){
                    stateRate = boost::lexical_cast<double>(row[i][1]);  
                    break; 
                }
        }
    }
    }
    //get federal state rate based on income  
   if (single){
            if (income >=413200){//highest tax bracket
                fedRate = .396; 
            }
            else if(income >=411500 && income <413200){
                fedRate = .35; 
            }
            else if(income <411500 && income >= 189300){
                fedRate = .28;
            }
            else if (income<189300 && income >=90750){
                fedRate = .25; 
            }
            else if(income < 90750 && income >=37450){
                fedRate = .15; 
            }
            else if (income <37450 && income >=9225){
                fedRate = .10; 
            }
            else{
                fedRate = .05; 
        }
    }
    else if (married){
            if (income >=464850){
                fedRate = .396; 
            }
             else if(income >=411500 && income <464850){
                fedRate = .35; 
            }
            else if(income <411500 && income >= 230450){
                fedRate = .28;
            }
            else if (income<230450 && income >=151200){
                fedRate = .25; 
            }
            else if(income < 151200 && income >=74900){
                fedRate = .15; 
            }
            else if (income <74900 && income >=18450){
                fedRate = .10; 
            }
            else{
                fedRate = .05; 
            }
    }


    //states that have rates based on federal rate
     if (state == "Colorado" || state == "Illinois" || state == "Michigan" || state == "Indiana"){
        stateRate = boost::lexical_cast<double>(row[0][1]); 
        stateRate = stateRate * fedRate / 10; 
     }
      
    double taxable; 
    
    taxable = income - deductions;
    netIncome = income -taxable*stateRate - taxable*fedRate; 

   
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

void Tax::writeToFile(){

    ofstream myFile; 

    myFile.open("taxInfo.txt"); 
    myFile<<stateRate*100<<"%"<<endl;
    myFile<<fedRate*100<<"%"<<endl; 
    myFile<<netIncome<<endl; 
    myFile.close(); 

}


