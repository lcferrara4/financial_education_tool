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

void Tax::calcItax(double income, string UserState){

    state = clean(UserState); 
    cout<<state; 
    //string state = "Arizona";
    string newStr; 
    bool married=0; 
    bool single=1; 
    vector<vector<string> > row;  
    double value, value2,max;  

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
/*
    for(int i=0; i<row.size(); i++){
        for(int j=0; j<row[i].size(); j++){ 
            cout<<row[i][j]<<' '; 
        }
        cout<<' '; 
    }
    */
    
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
/*
    for(int i=0; i<singleFed.size(); i++){
        for(int j=0; j<singleFed[i].size(); j++){
            cout<<singleFed[i][j]<<" "; 
        }
        cout<<endl; 
    }
*/
   if (single){
        for(int i=0; i<singleFed.size()-1; i++){
            //cout<<"inFed"; 
            if (income >=413200){//highest tax bracket
                fedRate = .396; 
                break;
            }
           /* else{
                value = boost::lexical_cast<double>(singleFed[i][1]); 
                value2 = boost::lexical_cast<double>(singleFed[i+1][1]); 
                cout<<value<<" "<<value2<<endl; 
                    if (income >= value && income < value2){
                        cout<<singleFed[i][0]; 
                        fedRate = boost::lexical_cast<double>(singleFed[i][0]); 
                        cout<<"after"; 
                        break; 
                    }
            }
            */
            else if(income >=411500 && income <413200){
                fedRate = .35; 
                break; 
            }
            else if(income <411500 && income >= 189300){
                fedRate = .28;
                break; 
            }
            else if (income<189300 && income >=90750){
                fedRate = .25; 
                break; 
            }
            else if(income < 90750 && income >=37450){
                fedRate = .15; 
                break; 
            }
            else if (income <37450 && income >=9225){
                fedRate = .10; 
                break; 
            }
            else{
                fedRate = .05; 
                break; 
            } 
        }
    }
    else if (married){
        for (int i=0; i<marriedFed.size()-1; i++){
            if (income >=464850){
                fedRate = .396; 
                break; 
            }
             else if(income >=411500 && income <464850){
                fedRate = .35; 
                break; 
            }
            else if(income <411500 && income >= 230450){
                fedRate = .28;
                break; 
            }
            else if (income<230450 && income >=151200){
                fedRate = .25; 
                break; 
            }
            else if(income < 151200 && income >=74900){
                fedRate = .15; 
                break; 
            }
            else if (income <74900 && income >=18450){
                fedRate = .10; 
                break; 
            }
            else{
                fedRate = .05; 
                break; 
            }
            /*else if(income <=464850){
                value=boost::lexical_cast<double>(marriedFed[i][1]); 
                value2=boost::lexical_cast<double>(marriedFed[i+1][1]); 
                if(income >= value && income <value2){
                    fedRate=boost::lexical_cast<double>(marriedFed[i][0]);
                    break; 
                }
            }*/

        }
    }

     if (state == "Colorado" || state == "Illinois" || state == "Michigan" || state == "Indiana"){
        stateRate = boost::lexical_cast<double>(row[0][1]); 
        stateRate = stateRate * fedRate / 100; 
     }
     //if (stateRate < .0000000000001){
     //    stateRate = 0; 
     //}

    //CALCULATE INCOME TAX 
     
    double taxable; 
    taxable = income - deductions;
     
    cout<<endl<<fedRate<<" is fed, state is: "<<stateRate<<endl; 

    netIncome = income -taxable*stateRate - taxable*fedRate; 

    cout<<income<<" is your income"<<endl; 

    
    cout<<"Net income: "<<netIncome<<endl; 
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
    myFile<<"state rate for"<<state<<": "<<stateRate<<endl;
    myFile<<"federal tax rate: "<<fedRate<<endl; 
    myFile <<"netIncome: "<<netIncome<<endl; 
    myFile.close(); 

}
