#include <iostream> 
#include "User.h"
#include "Loan.h"
#include "Student.h"
#include "Tax.h"
#include "Mortgage.h"
#include "stock.h"
#include <fstream>
#include <sstream>
#include <string>

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
	mortDeduct=0; 
	stuDeduct=0; 
	stockDeduct=0; 

	stockTotal = 0;

	for( int i = 0; i < 60; i++ ){
		total[i] = 0;
	}

        //instantiate
        default_random_engine generator(time(0));
        vector<string> stock_Names;

        string buy_stock;
	string in;

        // read in the stock names
        string stock_names_file = "stock_names.txt";
        ifstream myfile;
        myfile.open(stock_names_file.c_str());
        if (myfile.is_open()){
                while(getline (myfile,in)){
                        stock_Names.push_back(in);
                }
                myfile.close();
        }

        // generates the stocks 
        int change =0;
        for(int j=0;j<60;j++){
                if(change < 20){
                        stock s (7.5,50.0, stock_Names[j],"High Volatility", generator);
                        stocks.push_back(s);
                } else if(change < 40){
                        stock s (5.0,50.0, stock_Names[j], "Medium Volatility", generator);
                        stocks.push_back(s);
                } else if(change < 60){
                        stock s (2.5,50.0, stock_Names[j], "Low Volatility" ,generator);
                        stocks.push_back(s);
                }
                change++;
        }



        //usleep(10000);
        vector<double> temp;

        //graph stuff
        for (int i = 0; i < 60; ++i)
        {
                temp.push_back( 50 );
        }


        graphs.push_back(temp);

        // Make S&P 500
        double SP = makeSP();
	sp.push_back(SP);


        temp.clear();

        for (int i = 0; i < 60; ++i)
        {
                stocks[i].recalc_price();
                temp.push_back( stocks[i].get_price() );
        }

        graphs.push_back(temp);

        // Make S&P 500
        SP = makeSP();
	sp.push_back(SP);
}

void User::runTax(){

	cout<<"USER RUNNING"<<endl;

	string state; 
        cout<<"\nTAX INFORMATION";

	deductions = mortDeduct + stuDeduct + stockDeduct; 
    Tax myTax(deductions);
    myTax.calcItax(income,getState(), getStatus());
    myTax.writeToFile(); 

}

void User::runLoan(){
    
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

void User::recalcIncome(double stockIncome, double stockBought){
    income = income +stockIncome - stockBought; 
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

double User::makeSP(){
        double total = 0;
        for(int i=0;i<60;i++){
                total += stocks[i].get_price();
        }
        return total / 60;
}

void User::stockTransaction(int i, int buy, int sell){

        double stock_buy = buy * stocks[i].get_price();
        double stock_sell = sell * stocks[i].get_price();
	total[i] = total[i] + buy - sell;

	setStockDeduct(total[i]*stocks[i].get_price() ); 
	recalcIncome(stock_sell, stock_buy); 
	
}

string User::getTotalString( int i ){
	stringstream convert;

	convert << total[i];
	return convert.str();
}

double User::calcStockTotal(){

        //stockTotal = stock_buy - stock_sell; //amount of money made in stocks
}

double User::getStockPrice( int i ){
	return stocks[i].get_price();
}

double User::getGraphPrice( int s, int t ){
	return graphs[t][s];
}

double User::getSP( int t ){
	return sp[t];
}	

void User::stockRecalc(int time){

	vector<double> temp;

	for( int i = 0; i < 60; i++ ){
		stocks[i].recalc_price();
                temp.push_back( stocks[i].get_price() );
	}

        graphs.push_back(temp);

        double SP = makeSP();
	sp.push_back(SP);
	
}

double User::getTaxable(){
	return income - deductions;
}
