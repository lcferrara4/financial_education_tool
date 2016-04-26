//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <fstream>
#include <boost/lexical_cast.hpp>

//#include "User.h"
#include "LTexture.h"
#include "LButton.h"

using namespace std;
 

class SDL
{
	public:
		SDL();
			
		//Starts up SDL and creates window
		bool init();

		//Loads media
		bool loadMedia();

		//Frees media and shuts down SDL
		void close();

		int handleEvents();

		void displayMenu();
		int displayScreen( int, int, int );

		void printTable( int );		

		// get functions
		double getIncome();
		string getState();
		bool getStatus();
		bool getTaxOutput();

		string getType();
		double getPrinciple();
		int getMonths();
		double getScholarship();
		
		void setTaxOutput();
	private:
		//Buttons objects
		LButton gButtons[ TOTAL_BUTTONS ];

		//Menu Rendered textures
		LTexture mainTextTexture;
		LTexture taxTextTexture;
		LTexture loanTextTexture;
		LTexture stockTextTexture;
		LTexture plannerTextTexture;

		//Home Screen Rendered Textures
		LTexture welcomeTextTexture;

		//Tax Screen Rendered Textures
		LTexture taxScreenTextTexture;
		LTexture taxPromptTextTexture;
		LTexture taxInputTextTexture;
		LTexture statePromptTextTexture;
		LTexture stateInputTextTexture;
		LTexture statusPromptTextTexture;
		LTexture marriedInputTextTexture;
		LTexture singleInputTextTexture;

		LTexture stateRateTextTexture;
		LTexture fedRateTextTexture;
		LTexture netIncomeTextTexture;

		//Stock Screen Rendered Textures
		LTexture stockScreenTextTexture;
		LTexture spTextTexture;
		LTexture stocksTextTexture[60];

		//Loan Screen Rendered Textures
		LTexture loanScreenTextTexture;
		LTexture princPromptTextTexture;
		LTexture princInputTextTexture;
		LTexture monthPromptTextTexture;
		LTexture monthInputTextTexture;
                LTexture newPromptTextTexture;
                LTexture mortInputTextTexture;
                LTexture studInputTextTexture;
		LTexture scholPromptTextTexture;
		LTexture scholInputTextTexture;

		//Planner Screen Rendered Textures
		LTexture plannerScreenTextTexture;

		string state;
		int income;
		int type;
		bool status;
		User myUser;
		bool output;
		double interestRate;
		double principle;
		int months;
		double scholarship;
		bool loanType;
};

SDL::SDL(){
	User myUser();
}

bool SDL::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
                        //Create vsynced renderer for window
                        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
                        if( gRenderer == NULL )
                        {
                                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                                success = false;
                        }
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

		                //Initialize SDL_ttf
                                if( TTF_Init() == -1 )
                                {
                                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                                        success = false;
                                }

			}
		}
	}

        //Set buttons in corners
        gButtons[ 0 ].setPosition( 0, 0 );
        gButtons[ 1 ].setPosition( 0, BUTTON_HEIGHT );
        gButtons[ 2 ].setPosition( 0, 2 * BUTTON_HEIGHT );
        gButtons[ 3 ].setPosition( 0, 3 * BUTTON_HEIGHT );
	gButtons[ 4 ].setPosition( 0, 4 * BUTTON_HEIGHT );

	return success;
}

bool SDL::loadMedia()
{
        //Loading success flag
        bool success = true;

        //Open the font
        gFont = TTF_OpenFont( "fonts/cooper_light.ttf", 32 );
        if( gFont == NULL )
        {
                printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
        }
        else
        {
                //Render text
                SDL_Color textColor = { 0, 0, 0 };
                mainTextTexture.loadFromRenderedText( "Home", textColor );
		taxTextTexture.loadFromRenderedText( "Taxes", textColor );
                loanTextTexture.loadFromRenderedText( "Loans", textColor );
                stockTextTexture.loadFromRenderedText( "Stocks", textColor );
                plannerTextTexture.loadFromRenderedText( "Planner", textColor );
       }

        gFont = TTF_OpenFont( "fonts/cooper_light.ttf", 12 );
        if( gFont == NULL )
        {
                printf( "Failed to load cooper light font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
        }
        else
        {
	        SDL_Color textColor = { 255, 255, 255 };

		ifstream inFile;
        	inFile.open ("stock_names.txt");

        	string word;
		for( int i = 0; i < 60; i++ ){
			std::getline(inFile, word);
			stocksTextTexture[i].loadFromRenderedText( word, textColor);
		}
        }


        //Open font for welcome message
        gFont = TTF_OpenFont( "fonts/sans_serif_nb.ttf", 28 );
        if( gFont == NULL )
        {
                printf( "Failed to load Sans Serif font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
        }
        else
        {

                //Render text
                SDL_Color textColor = { 255, 255, 255 };
                welcomeTextTexture.loadFromRenderedText( "Welcome to your Financial Planner", textColor );
                taxScreenTextTexture.loadFromRenderedText( "TAXES", textColor );
                loanScreenTextTexture.loadFromRenderedText( "LOANS", textColor );
                stockScreenTextTexture.loadFromRenderedText( "STOCKS", textColor );
                plannerScreenTextTexture.loadFromRenderedText( "YOUR PLAN", textColor );
                spTextTexture.loadFromRenderedText( "ND 60", textColor );

		princPromptTextTexture.loadFromRenderedText( "Principle:", textColor );
                monthPromptTextTexture.loadFromRenderedText( "Months:", textColor );
                newPromptTextTexture.loadFromRenderedText( "New Loan:", textColor );
                mortInputTextTexture.loadFromRenderedText( "Mortgage", textColor );
                studInputTextTexture.loadFromRenderedText( "Student", textColor );
                scholPromptTextTexture.loadFromRenderedText( "Scholarship:", textColor );

                taxPromptTextTexture.loadFromRenderedText( "Income:", textColor );
                statePromptTextTexture.loadFromRenderedText( "State:", textColor );
                statusPromptTextTexture.loadFromRenderedText( "Status:", textColor );
                marriedInputTextTexture.loadFromRenderedText( "Married", textColor );
                singleInputTextTexture.loadFromRenderedText( "Single", textColor );
	}



        return success;
}

void SDL::close()
{
        //Free loaded images
 	mainTextTexture.free();
       	taxTextTexture.free();
        loanTextTexture.free();
        stockTextTexture.free();
        plannerTextTexture.free();
	welcomeTextTexture.free();
       	taxScreenTextTexture.free();
        loanScreenTextTexture.free();
        stockScreenTextTexture.free();
        plannerScreenTextTexture.free();

	princPromptTextTexture.free();
	princInputTextTexture.free();
        monthPromptTextTexture.free();
        monthInputTextTexture.free();
        newPromptTextTexture.free();
        mortInputTextTexture.free();
        studInputTextTexture.free();
        scholPromptTextTexture.free();
        scholInputTextTexture.free();
	
	taxPromptTextTexture.free();
	taxInputTextTexture.free();
	statePromptTextTexture.free();
	stateInputTextTexture.free();
	statusPromptTextTexture.free();
        marriedInputTextTexture.free();
        singleInputTextTexture.free();

	for( int i = 0; i < 50; i++ ){
		stocksTextTexture[i].free();
	}
	spTextTexture.free();

        //Free global font
        TTF_CloseFont( gFont );
        gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
        TTF_Quit();	
	IMG_Quit();
	SDL_Quit();
}

int SDL::handleEvents()
{
	income = 50000;
	state = "Indiana";
	status = 0;
	int currentScreen = 0;
	output = 0;

	interestRate = 2;
	principle = 1000;
	months = 1;
	scholarship = 0;
	loanType = 1;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	

                        //Main loop flag
                        bool quit = false;

                        //Event handler
                        SDL_Event e;

                        //Set text color as black
                        SDL_Color textColor = { 0, 250, 250, 0xFF };

                        //The current input text.
                        std::string inputText = "20000";
                        princInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

                        std::string monthText = "1";
                        monthInputTextTexture.loadFromRenderedText( monthText.c_str(), textColor );

                        std::string scholText = "0";
                        scholInputTextTexture.loadFromRenderedText( scholText.c_str(), textColor );
 		
			std::string taxText = "50000";
			taxInputTextTexture.loadFromRenderedText( taxText.c_str(), textColor );                       

                        std::string stateText = "Indiana";
                        stateInputTextTexture.loadFromRenderedText( stateText.c_str(), textColor );


                        //Enable text input
                        SDL_StartTextInput();

                	int x, y;

			//While application is running
			while( !quit )
			{

				bool renderText = false;
				bool renderMonthText = false;
				bool renderTaxText = false;
				bool renderStateText = false;	

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

        				//If mouse event happened
        				else if( e.type == SDL_MOUSEBUTTONDOWN )
        				{
                				//Get mouse position
                				SDL_GetMouseState( &x, &y );
					}

                                       	//Special key input
                                        else if( e.type == SDL_KEYDOWN )
                                        {
                                                //Handle backspace
                                                if( e.key.keysym.sym == SDLK_BACKSPACE )
                                                {
							if( currentScreen == 1 ){
                                                                if( y > SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() && y < SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() + 35 ){
                                                                        if( taxText.length() > 0 && x > SCREEN_WIDTH / 4 - 5 && x < SCREEN_WIDTH / 4 + 120 ){
                                                                		taxText = taxText.substr(0, taxText.size() - 1);
                                                                                renderTaxText = true;
                                                                        }
                                                                        else if( stateText.length() > 0 && x > SCREEN_WIDTH / 2 - 5 && x < SCREEN_WIDTH / 2 + 220 ){
                                                                		stateText = stateText.substr(0, stateText.size() - 1);
                                                                                renderStateText = true;
                                                                        }
                                                                }

							}
                                                        //lop off character - loan screen
                                                        else if( currentScreen == 3 ){
								if( inputText.length() > 0 && y < 150 ){
                                                        		inputText = inputText.substr(0, inputText.size() - 1);
                                                        		renderText = true;
								}
								if( monthText.length() > 0 && y >= 150 ){
                                                                        monthText = monthText.substr(0, monthText.size() - 1);
                                                                        renderMonthText = true;
								}
							}
                                                }
                                                //Handle copy
                                                else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                                                {
							if( currentScreen == 1 ){
                                                                if( y > SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() && y < SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() + 35 ){
                                                                        if( x > SCREEN_WIDTH / 4 - 5 && x < SCREEN_WIDTH / 4 + 120 ){
                                                                		SDL_SetClipboardText( taxText.c_str() );
                                                                        }
                                                                        else if( x > SCREEN_WIDTH / 2 - 5 && x < SCREEN_WIDTH / 2 + 220 ){
                                                                		SDL_SetClipboardText( stateText.c_str() );
                                                                        }
                                                                }


							}
							else if( currentScreen == 3 ){
								if( y < 150 )
                                                        		SDL_SetClipboardText( inputText.c_str() );
                                                		else
									SDL_SetClipboardText( monthText.c_str() );
							}
						}
                                                //Handle paste
                                                else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                                                {
							if( currentScreen == 1 ){
								if( y > SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() && y < SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() + 35 ){
									if( x > SCREEN_WIDTH / 4 - 5 && x < SCREEN_WIDTH / 4 + 120 ){
										taxText = SDL_GetClipboardText();
                                                                		renderTaxText = true;
									}
									else if( x > SCREEN_WIDTH / 2 - 5 && x < SCREEN_WIDTH / 2 + 220 ){
										stateText = SDL_GetClipboardText();
                                                                                renderStateText = true; 
                                                                        }
								}
							}
							else if( currentScreen == 3 ){
								if( y < 150 ){
                                                        		inputText = SDL_GetClipboardText();
                                                        		renderText = true;
								}
								else{
                                                                        monthText = SDL_GetClipboardText();
                                                                        renderMonthText = true;
								}
							}
                                                }
                                        }
                                        //Special text input event
                                        else if( e.type == SDL_TEXTINPUT )
                                        {
                                                //Not copy or pasting
                                                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                                                {
							if( currentScreen == 1 ){
                                                                if( y > SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() && y < SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() + 35 ){
                                                                        if( x > SCREEN_WIDTH / 4 - 5 && x < SCREEN_WIDTH / 4 + 120 ){
                       								taxText += e.text.text;
                                                                                renderTaxText = true;
                                                                        }
                                                                        else if( x > SCREEN_WIDTH / 2 - 5 && x < SCREEN_WIDTH / 2 + 220 ){
                       								stateText += e.text.text;
                                                                                renderStateText = true;
                                                                        }
                                                                }
							}
							else if( currentScreen == 3 ){
                                                        	//Append character
								if( y < 150 ){
                                                        		inputText += e.text.text;
                                                        		renderText = true;
								}
								else{
                                                                        monthText += e.text.text;
                                                                        renderMonthText = true;
								}
							}
                                                }
                                        }
				
					//Handle button events
                                        for( int i = 0; i < TOTAL_BUTTONS; ++i )
                                        {
                                        	int check = gButtons[ i ].handleEvent( &e );
				      		if( check == 1 )
							currentScreen = i;
					}
				}	

			      	//Rerender text if needed
			      	if( renderText )
			      	{
					//Text is not empty 
					if( inputText != "" )
					{
						principle = boost::lexical_cast<double>(inputText);
						//Render new text
						princInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
					}
					//Text is empty
					else
					{
						//Render space texture
						princInputTextTexture.loadFromRenderedText( " ", textColor );
					}
				}     	

                                //Rerender month text if needed
                                if( renderMonthText )
                                {
                                        //Text is not empty 
                                        if( monthText != "" )
                                        {
						months = boost::lexical_cast<int>(monthText);
                                                //Render new text
                                                monthInputTextTexture.loadFromRenderedText( monthText.c_str(), textColor );
                                        }
                                        //Text is empty
                                        else
                                        {
                                                //Render space texture
                                                monthInputTextTexture.loadFromRenderedText( " ", textColor );
                                        }
                                }

                                //Rerender tax text if needed
                                if( renderTaxText )
                                {
                                        //Text is not empty 
                                        if( taxText != "" )
                                        {
						income = boost::lexical_cast<double>(taxText);
                                               //Render new text
                                                taxInputTextTexture.loadFromRenderedText( taxText.c_str(), textColor );
                                        }
                                        //Text is empty
                                        else
                                        {
                                                //Render space texture
                                                taxInputTextTexture.loadFromRenderedText( " ", textColor );
                                        }
                                } 
                                if( renderStateText )
                                {
                                        //Text is not empty 
                                        if( stateText != "" )
                                        {
						state = stateText;
                                                //Render new text
                                                stateInputTextTexture.loadFromRenderedText( stateText.c_str(), textColor );
                                        }
                                        //Text is empty
                                        else
                                        {
                                                //Render space texture
                                                stateInputTextTexture.loadFromRenderedText( " ", textColor );
                                        }
                                }


				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderClear( gRenderer );

				//Display menu
				displayMenu();
			
				//Display chosen screen
				currentScreen = displayScreen(currentScreen, x, y);
				
				//Update screen
				SDL_RenderPresent( gRenderer );
                        
			}
                        
			//Disable text input
                        SDL_StopTextInput();

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

void SDL::displayMenu(){
	
	//Render white filled rect
	SDL_Rect mainRect = { 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( gRenderer, &mainRect );

	//Render green filled rect
	SDL_Rect taxRect = { 0, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( gRenderer, &taxRect );

	//Render blue filled quad
	SDL_Rect stockRect = { 0, BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect( gRenderer, &stockRect );

	//Render yellow filled quad
	SDL_Rect loanRect = { 0, BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( gRenderer, &loanRect );

	//Render light blue filled quad
	SDL_Rect planRect = { 0, BUTTON_HEIGHT * 4, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( gRenderer, &planRect );

	//Menu options
	mainTextTexture.render( SCREEN_WIDTH / 10 - mainTextTexture.getWidth() ,  SCREEN_HEIGHT / 8 - mainTextTexture.getHeight() );
	taxTextTexture.render( SCREEN_WIDTH / 10 - taxTextTexture.getWidth() , 2  * SCREEN_HEIGHT / 8 - taxTextTexture.getHeight() );
	stockTextTexture.render( SCREEN_WIDTH / 10 - stockTextTexture.getWidth(), 3 * SCREEN_HEIGHT / 8 - stockTextTexture.getHeight() );
	loanTextTexture.render( SCREEN_WIDTH / 10 - loanTextTexture.getWidth(), 4 * SCREEN_HEIGHT / 8 - loanTextTexture.getHeight() );
	plannerTextTexture.render( SCREEN_WIDTH / 10 - plannerTextTexture.getWidth(), 5 * SCREEN_HEIGHT / 8 - plannerTextTexture.getHeight() );
}

int SDL::displayScreen( int currentScreen, int x, int y ){

	if( currentScreen == 0 ){
		welcomeTextTexture.render( SCREEN_WIDTH / 2 - welcomeTextTexture.getWidth() / 2 ,  SCREEN_HEIGHT / 2 - welcomeTextTexture.getHeight() / 2 );
		currentScreen = 0;
	}
	else if( currentScreen == 1 ){
		output = 0;
		myUser.setIncome(income);
		myUser.setState(state);
		myUser.setStatus(status);

		taxScreenTextTexture.render( SCREEN_WIDTH / 2 - taxScreenTextTexture.getWidth() / 2 ,  0 );
		
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                SDL_Rect calcRect = { SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 8, 125, 70 };
                SDL_RenderFillRect( gRenderer, &calcRect );

		// Input Rect
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );

		SDL_Rect incomeRect = { SCREEN_WIDTH / 4 - 5, SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight(), 125, 35 };
		SDL_RenderDrawRect( gRenderer, &incomeRect );

		SDL_Rect stateRect = { SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 8 + statePromptTextTexture.getHeight(), 225, 35 };
		SDL_RenderDrawRect( gRenderer, &stateRect );

		SDL_Rect marriedRect = { 3 * SCREEN_WIDTH / 4 - 5, SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight(), 125, 35 };

		SDL_Rect singleRect = { 3 * SCREEN_WIDTH / 4 - 5, SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight() + 35, 125, 35 };

		if(status == 0){
			SDL_RenderFillRect( gRenderer, &marriedRect );
			SDL_RenderDrawRect( gRenderer, &singleRect );
		}
		else{
                	SDL_RenderFillRect( gRenderer, &singleRect );
			SDL_RenderDrawRect( gRenderer, &marriedRect );
		}

		if( x > (3 * SCREEN_WIDTH / 4 - 5) && x < (3 * SCREEN_WIDTH / 4 + 120) ){
			if( y > (SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight()) && y < (SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight() + 35) ){
				status = 0;
			}
			else if( y > (SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight() + 35) && y < (SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight() + 70) ){
				status = 1;
			}
		}

		if( x > (SCREEN_WIDTH / 4) && x < SCREEN_WIDTH / 4 + 125 && y > 3 * SCREEN_HEIGHT / 8 && y < 3 * SCREEN_HEIGHT / 8 + 70){
			setTaxOutput();
		}

		if( output == 1 ){
			ifstream inFile;
			inFile.open ("taxInfo.txt");

			SDL_Color textColor = { 255, 255, 255 };

			string word;
			std::getline(inFile, word);
			stateRateTextTexture.loadFromRenderedText( word, textColor );
			std::getline(inFile, word);
			fedRateTextTexture.loadFromRenderedText( word,textColor );
			std::getline(inFile, word);
			netIncomeTextTexture.loadFromRenderedText( word, textColor );
			

			stateRateTextTexture.render( 3 * SCREEN_WIDTH / 4, 3*SCREEN_HEIGHT / 8 );
			fedRateTextTexture.render( 3 * SCREEN_WIDTH / 4,  5 *SCREEN_HEIGHT / 8 );
			netIncomeTextTexture.render( 3 * SCREEN_WIDTH / 4,  7 * SCREEN_HEIGHT / 8 );
		}

		//Render text textures
		taxPromptTextTexture.render( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8 );
		taxInputTextTexture.render( SCREEN_WIDTH / 4,  SCREEN_HEIGHT / 8 + taxPromptTextTexture.getHeight() + 5 );
		statePromptTextTexture.render( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 );
		stateInputTextTexture.render( SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 8 + statePromptTextTexture.getHeight() + 5 );
		statusPromptTextTexture.render( 3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8 );
		marriedInputTextTexture.render( 3 * SCREEN_WIDTH / 4,  SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight() + 5 );
		singleInputTextTexture.render( 3 * SCREEN_WIDTH / 4,  SCREEN_HEIGHT / 8 + statusPromptTextTexture.getHeight() + 45 );
	}
	else if( currentScreen == 2 )
	{
		stockScreenTextTexture.render( SCREEN_WIDTH / 2 - stockScreenTextTexture.getWidth() / 2 ,  0 );

		SDL_Rect spRect = { SCREEN_WIDTH / 2 - 100, 530, 200, 50 };
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( gRenderer, &spRect );

		spTextTexture.render( SCREEN_WIDTH / 2 - stockScreenTextTexture.getWidth() / 2, 535);

		for( int i = 0; i < 12; i++ ){
			for( int j = 0; j < 5; j++ ){
				SDL_Rect stockRect = { 165 + (180 * j), 35 + (40 * i), 180, 40 };
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
				SDL_RenderDrawRect( gRenderer, &stockRect );
			}
		}
		int count = 0;
		for( int i = 0; i < 12; i++ ){
			for( int j = 0; j < 5; j++ ){
				stocksTextTexture[count ].render( 170 + (180 * j), 40 + (40 * i));
				count++;
			}
		}
		if( y > 35 && y < 75 ){
			if( x > 165 && x < 345 )
				currentScreen = 50;
			else if( x > 345 && x < 525 )
				currentScreen = 51;
			else if( x > 525 && x < 705 )
				currentScreen = 52;
			else if( x > 705 && x < 885 )
				currentScreen = 53;
			else if( x > 885 && x < 1065 )
				currentScreen = 54;
		}
		else if( y > 75 && y < 115 ){
			if( x > 165 && x < 345 )
				currentScreen = 55;
			else if( x > 345 && x < 525 )
				currentScreen = 56;
			else if( x > 525 && x < 705 )
				currentScreen = 57;
			else if( x > 705 && x < 885 )
				currentScreen = 58;
			else if( x > 885 && x < 1065 )
				currentScreen = 59;
		}
		else if( y > 115 && y < 155 ){
			if( x > 165 && x < 345 )
				currentScreen = 60;
			else if( x > 345 && x < 525 )
				currentScreen = 61;
			else if( x > 525 && x < 705 )
				currentScreen = 62;
			else if( x > 705 && x < 885 )
				currentScreen = 63;
			else if( x > 885 && x < 1065 )
				currentScreen = 64;
		}
		else if( y > 155 && y < 195 ){
			if( x > 165 && x < 345 )
				currentScreen = 65;
			else if( x > 345 && x < 525 )
				currentScreen = 66;
			else if( x > 525 && x < 705 )
				currentScreen = 67;
			else if( x > 705 && x < 885 )
				currentScreen = 68;
			else if( x > 885 && x < 1065 )
				currentScreen = 69;
		}
		else if( y > 195 && y < 235 ){
			if( x > 165 && x < 345 )
				currentScreen = 70;
			else if( x > 345 && x < 525 )
				currentScreen = 71;
			else if( x > 525 && x < 705 )
				currentScreen = 72;
			else if( x > 705 && x < 885 )
				currentScreen = 73;
			else if( x > 885 && x < 1065 )
				currentScreen = 74;
		}
		else if( y > 235 && y < 275 ){
			if( x > 165 && x < 345 )
				currentScreen = 75;
			else if( x > 345 && x < 525 )
				currentScreen = 76;
			else if( x > 525 && x < 705 )
				currentScreen = 77;
			else if( x > 705 && x < 885 )
				currentScreen = 78;
			else if( x > 885 && x < 1065 )
				currentScreen = 79;
		}
		else if( y > 275 && y < 315 ){
			if( x > 165 && x < 345 )
				currentScreen = 80;
			else if( x > 345 && x < 525 )
				currentScreen = 81;
			else if( x > 525 && x < 705 )
				currentScreen = 82;
			else if( x > 705 && x < 885 )
				currentScreen = 83;
			else if( x > 885 && x < 1065 )
				currentScreen = 84;
		}
		else if( y > 315 && y < 355 ){
			if( x > 165 && x < 345 )
				currentScreen = 85;
			else if( x > 345 && x < 525 )
				currentScreen = 86;
			else if( x > 525 && x < 705 )
				currentScreen = 87;
			else if( x > 705 && x < 885 )
				currentScreen = 88;
			else if( x > 885 && x < 1065 )
				currentScreen = 89;
		}
		else if( y > 355 && y < 395 ){
			if( x > 165 && x < 345 )
				currentScreen = 90;
			else if( x > 345 && x < 525 )
				currentScreen = 91;
			else if( x > 525 && x < 705 )
				currentScreen = 92;
			else if( x > 705 && x < 885 )
				currentScreen = 93;
			else if( x > 885 && x < 1065 )
				currentScreen = 94;
		}
		else if( y > 395 && y < 435 ){
			if( x > 165 && x < 345 )
				currentScreen = 95;
			else if( x > 345 && x < 525 )
				currentScreen = 96;
			else if( x > 525 && x < 705 )
				currentScreen = 97;
			else if( x > 705 && x < 885 )
				currentScreen = 98;
			else if( x > 885 && x < 1065 )
				currentScreen = 99;
		}
		else if( y > 435 && y < 475 ){
			if( x > 165 && x < 345 )
				currentScreen = 100;
			else if( x > 345 && x < 525 )
				currentScreen = 101;
			else if( x > 525 && x < 705 )
				currentScreen = 102;
			else if( x > 705 && x < 885 )
				currentScreen = 103;
			else if( x > 885 && x < 1065 )
				currentScreen = 104;
		}
		else if( y > 475 && y < 515 ){
			if( x > 165 && x < 345 )
				currentScreen = 105;
			else if( x > 345 && x < 525 )
				currentScreen = 106;
			else if( x > 525 && x < 705 )
				currentScreen = 107;
			else if( x > 705 && x < 885 )
				currentScreen = 108;
			else if( x > 885 && x < 1065 )
				currentScreen = 109;
		}

		else if( y > 530 && y < 580 ){
			if( x > SCREEN_WIDTH / 2 - 100 && x < SCREEN_WIDTH / 2 + 100 )
				currentScreen = 110;
		}

	}
	else if( currentScreen == 3 )
	{
//		output = 0;
		//myUser.setInterestRate(interestRate);
		myUser.setPrinciple(principle);
		myUser.setMonths(months);
		myUser.setType(loanType);
	
		if( loanType == 0 ){
			myUser.setScholarship(scholarship);
		}

		loanScreenTextTexture.render( SCREEN_WIDTH / 2 - loanScreenTextTexture.getWidth() / 2 , 0 );

		//calculate button
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                SDL_Rect calcRect = { SCREEN_WIDTH / 4, 500, 125, 70 };
                SDL_RenderFillRect( gRenderer, &calcRect );

                SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                SDL_Rect studRect = { ( SCREEN_WIDTH - mortInputTextTexture.getWidth() ) / 4 - 5, SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight(), 125, 35 };
                SDL_RenderDrawRect( gRenderer, &studRect );

                SDL_Rect mortRect = { ( SCREEN_WIDTH - mortInputTextTexture.getWidth() ) / 4 - 5, SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight() + 35, 125, 35 };
                SDL_RenderDrawRect( gRenderer, &mortRect );

                SDL_Rect princRect = { ( SCREEN_WIDTH - princPromptTextTexture.getWidth() ) / 4 - 5, 200 + princPromptTextTexture.getHeight(), 125, 35 };
                SDL_RenderDrawRect( gRenderer, &princRect );

                SDL_Rect monthRect = { ( SCREEN_WIDTH - monthPromptTextTexture.getWidth() ) / 4 - 5, 300 + monthPromptTextTexture.getHeight(), 125, 35 };
                SDL_RenderDrawRect( gRenderer, &monthRect );

		SDL_Rect scholRect = { ( SCREEN_WIDTH - scholInputTextTexture.getWidth() ) / 4 - 5, 400 + scholPromptTextTexture.getHeight(), 125, 35 };

		if( loanType == 0 ){
			SDL_RenderFillRect( gRenderer, &studRect );
			SDL_RenderDrawRect( gRenderer, &scholRect );
			scholPromptTextTexture.render( ( SCREEN_WIDTH - scholPromptTextTexture.getWidth() ) / 4, 400 );
			scholInputTextTexture.render( ( SCREEN_WIDTH - scholInputTextTexture.getWidth() ) / 4, 400 + scholPromptTextTexture.getHeight() );
		}
		else{
                	SDL_RenderFillRect( gRenderer, &mortRect );
		}

                if( x > (( SCREEN_WIDTH - mortInputTextTexture.getWidth() ) / 4 - 5) && x < (( SCREEN_WIDTH - mortInputTextTexture.getWidth() ) / 4 + 120) ){
                        if( y > (SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight()) && y < (SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight() + 35) ){
				loanType = 0;
			}
                        else if( y > (SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight() + 35) && y < (SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight() + 70) ){
                		loanType = 1;
			}
		}

		if( x > (SCREEN_WIDTH / 4) && x < SCREEN_WIDTH / 4 + 125 && y > 500 && y < 570){
                        setTaxOutput();
                }


                if( output == 1 ){
                        LTexture loanTableTextTexture[months+1];

		        ifstream inFile;
                        inFile.open ("loanInfo.txt");

                        SDL_Color textColor = { 255, 255, 255 };

                        string word;
			for( int i = 0; i < months + 1; i++ ){
                        	std::getline(inFile, word);
                        	loanTableTextTexture[i].loadFromRenderedText( word, textColor );
			}

			for( int i = 0; i < months + 1; i++ ){

                        	loanTableTextTexture[i].render( 3 * SCREEN_WIDTH / 4, 20 + ( SCREEN_HEIGHT - 50 ) / i );

			}
                }


		//Render text textures
		princPromptTextTexture.render( ( SCREEN_WIDTH - princPromptTextTexture.getWidth() ) / 4, 200 );
		princInputTextTexture.render( ( SCREEN_WIDTH - princInputTextTexture.getWidth() ) / 4, 200 + princPromptTextTexture.getHeight() );

		monthPromptTextTexture.render( ( SCREEN_WIDTH - monthPromptTextTexture.getWidth() ) / 4, 300 );
		monthInputTextTexture.render( ( SCREEN_WIDTH - monthInputTextTexture.getWidth() ) / 4, 300 + monthPromptTextTexture.getHeight() );

		newPromptTextTexture.render( ( SCREEN_WIDTH - newPromptTextTexture.getWidth() ) / 4, SCREEN_HEIGHT / 8 );
		studInputTextTexture.render( ( SCREEN_WIDTH - studInputTextTexture.getWidth() ) / 4, SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight() + 5 );
                mortInputTextTexture.render( ( SCREEN_WIDTH - mortInputTextTexture.getWidth() ) / 4, SCREEN_HEIGHT / 8 + newPromptTextTexture.getHeight() + 40 );
	}
	else if( currentScreen == 4 )
	{
		plannerScreenTextTexture.render( SCREEN_WIDTH / 2 - plannerScreenTextTexture.getWidth() / 2 , 0 );
	}



	return currentScreen;

}

double SDL::getIncome(){
	return income;
}

string SDL::getState(){
	return state;
}

bool SDL::getStatus(){
	return status;
}

void SDL::setTaxOutput(){

	myUser.run();
	output = 1;
}
