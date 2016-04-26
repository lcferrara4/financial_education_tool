#include <fstream>
#include "Loan.h"
#include "Student.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

Student::Student(){
    double tuit, scholar; 
    cout<<"Do you have any scholarships?  How much?"; 
    cin>>scholar; 
    setScholar(scholar); 
}

/*Student::Student(double iRate, bool t, double pr, double mont, double schol){
    setPrinc(pr); 
    setTax(t); 
    setMonths(mont); 
    setRate(iRate); 
    setScholar(schol);
}
*/

void Student::setScholar(double s){
    scholarship=s; 
}


void Student::createPlan(){
    double total; 
    total = getPrinc() - scholarship; 

    double currMonth = 1; 
    double months = getMonths(); 
    double monthlyPayment = total / months; // ASSUMES NO INTEREST RATE

    vector<double> temp; 

    do{
        temp.push_back(currMonth); 
        temp.push_back(total); 
        table.push_back(temp); 
        total -=monthlyPayment;
        currMonth++; 
        temp.clear(); 
    }while(total>0); 


}

ostream &operator<<(ostream &output, const Student &S){

    output<<"MONTH\tAMOUNT"<<endl; 
    for (int i=0; i<S.table.size(); i++){
        for (int j=0; j<S.table[i].size(); j++){
            output<<S.table[i][j]<<'\t'; 
        }
        output<<endl;
    }

}

void Student::writeToFile(){

	ofstream myFile; 
	myFile.open("loanInfo.txt"); 
	myFile<<"MONTH\tAMOUNT"<<endl; 
	for(int i=0; i<table.size(); i++){
		for(int j=0; j<table[i].size(); j++){
			myFile<<table[i][j]<<'\t';
		}
		myFile<<endl; 
	}
}
