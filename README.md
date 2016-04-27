Teddy Brombach
Lauren Ferrara
Emily Obaditch 

Fundamentals of Computing II Final Project
Financial Education Tool: User-Guide

    The goal of this project is to create a simplified financial education tool which teaches users how taxes, loans, and stocks effect their finances and how these different attributes relate to each other.  When run the user enters the welcome window and can choose from /5/ different screens to enter into.  These are Home (the welcome screen),Loans, Stocks, Taxes, or overview.  
    Tax Screen:
        Enter information used in calculating taxes: Annual income, state, and filing status
        Click calculate button
        Federal Tax Rate, State Tax Rate, Taxable Income,and Net Income will be displayed
        Net Income: total amount of money user makes in a year including taxes
        Taxable Income:  Since loans and stocks are tax deductible the program will factor these out of the income when calculating tax.  Taxable income displays the amount that is being taxed by the state and government tax rates.  

    Loan Screen: 
        Enter information used in creating a plan to pay off a loan: 
            Type of loan (Student or Mortgage)
            Interest Rate (student loans have no interest rate)
            Loan Principle
            Months to pay off Loan
        Click Calculate Button
        An amortization table will be displayed if the loan is of type Mortgage, while a simple plan will be displayed is the loan is of type student.  
        The principle of the loan will be factored into calculating the taxable income in the tax screen as loans are considered tax deductions.  

    Stock Screen: 
        Stocks are of three types to ensure accurate and realistic marekt activity, stocks are either of high volatility, medium volatitliy, low volatility.  
        Each stock name is listed in the table shown as well as the current price of the stock.  Press the space bar to update time and see how each stock changes.  
        To buy or sell a stock, or view the graph of the stocks trends throughout time click on the name of the stock you would like to view more about.  
        When in the specificed stock screen enter the amout of that stock you would like to buy and the amount of that stock you would like to sell, then press enter for a transaction.  
        To update the graph and increment the stock market press space.  
        To exit and return to the main stock screen press the 'Stocks' button on the sidebar.  
        The amount of money in the stock market is tax deductible and will be factored into the taxable income in the tax screen. 
        ND60 Value: Takes all stocks and averages them for an overall evaluation of the markets performance.  

    Compiling Instructions:
        A Makefile is provided so simply type "make" in the command line. 
        Note: MUST be run on a machine with SDL/SDL_2

    Known Bugs: 
        When entering numerical values only digits 0-9 can be used (no letters).  This is because SDL takes in the input as a string and the program converts it to a double to to calculations on.  The program will not be able to convert a non 0-9 character into a double.  
        The user must enter the exact name of the state (capitalized and no spaces) when entering tax information.  
        Our loan plans assume a loan time of around 2-3 years (24 - 36 months).  Any longer will be calculated correctly, the table will just be somewhat hard to read as it needs to be resized to fit the window.  

     
