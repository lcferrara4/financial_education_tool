//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Button constants
const int BUTTON_WIDTH = SCREEN_WIDTH / 8;
const int BUTTON_HEIGHT = SCREEN_HEIGHT / 8;
const int TOTAL_BUTTONS = 5;

class LTexture
{
        public:
                //Initializes variables
                LTexture();

                //Deallocates memory
                ~LTexture();

                //Loads image at specified path
                bool loadFromFile( std::string path );

                //Creates image from font string
                bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

                //Deallocates texture
                void free();
                
                //Set color modulation
                void setColor( Uint8 red, Uint8 green, Uint8 blue );
                
                //Set blending
                void setBlendMode( SDL_BlendMode blending );

                //Set alpha modulation
                void setAlpha( Uint8 alpha );
                
                //Renders texture at given point
                void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
                
                //Gets image dimensions
                int getWidth();
                int getHeight();
        
        private:
                //The actual hardware texture
                SDL_Texture* mTexture;

                //Image dimensions
                int mWidth;
                int mHeight;
};

//The mouse button
class LButton
{
        public:
                //Initializes internal variables
                LButton();

                //Sets top left position
                void setPosition( int x, int y );

                //Handles mouse event
                int handleEvent( SDL_Event* e );

                //Shows button sprite
                void render();

        private:
                //Top left position
                SDL_Point mPosition;

                //Currently used global sprite
                //LButtonSprite mCurrentSprite;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
//SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

/*
//Mouse button sprites
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
LTexture gButtonSpriteSheetTexture;
*/

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

//Loan Screen Rendered Textures
LTexture taxScreenTextTexture;
LTexture taxPromptTextTexture;
LTexture taxInputTextTexture;

//Stock Screen Rendered Textures
LTexture stockScreenTextTexture;

//Loan Screen Rendered Textures
LTexture loanScreenTextTexture;
LTexture gPromptTextTexture;
LTexture gInputTextTexture;
LTexture monthPromptTextTexture;
LTexture monthInputTextTexture;

//Planner Screen Rendered Textures
LTexture plannerScreenTextTexture;



LTexture::LTexture()
{
        //Initialize
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
}

LTexture::~LTexture()
{
        //Deallocate
        free();
}

bool LTexture::loadFromFile( std::string path )
{
        //Get rid of preexisting texture
        free();

        //The final texture
        SDL_Texture* newTexture = NULL;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
                printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
                //Color key image
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

                //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
                if( newTexture == NULL )
                {
                        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                }
                else
                {
                        //Get image dimensions
                        mWidth = loadedSurface->w;
                        mHeight = loadedSurface->h;
                }

                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
        }

        //Return success
        mTexture = newTexture;
        return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
        //Get rid of preexisting texture
        free();

        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
        if( textSurface == NULL )
        {
                printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        else
        {
                //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
                if( mTexture == NULL )
                {
                        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                }
                else
                {
                        //Get image dimensions
                        mWidth = textSurface->w;
                        mHeight = textSurface->h;
                }

                //Get rid of old surface
                SDL_FreeSurface( textSurface );
        }

        //Return success
        return mTexture != NULL;
}

void LTexture::free()
{
        //Free texture if it exists
        if( mTexture != NULL )
        {
                SDL_DestroyTexture( mTexture );
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
        }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
        //Modulate texture rgb
        SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
        //Set blending function
        SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
        //Modulate texture alpha
        SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != NULL )
        {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
        return mWidth;
}

int LTexture::getHeight()
{
        return mHeight;
}

LButton::LButton()
{
        mPosition.x = 0;
        mPosition.y = 0;
 
}

void LButton::setPosition( int x, int y )
{
        mPosition.x = x;
        mPosition.y = y;
}

int LButton::handleEvent( SDL_Event* e )
{
        //If mouse event happened
        if( e->type == SDL_MOUSEBUTTONDOWN )
        {
                //Get mouse position
                int x, y;
                SDL_GetMouseState( &x, &y );

                //Check if mouse is in button
                bool inside = true;
	
                //Mouse is left of the button
                if( x < mPosition.x )
                {
                        inside = false;
                }
                //Mouse is right of the button
                else if( x > mPosition.x + BUTTON_WIDTH )
                {
                        inside = false;
                }
                //Mouse above the button
                else if( y < mPosition.y )
                {
                        inside = false;
                }
                //Mouse below the button
                else if( y > mPosition.y + BUTTON_HEIGHT )
                {
                        inside = false;
                }

                //Mouse is inside button
                if( inside )
                {
			return 1;
		}
		return 0;
        }
}


bool init()
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

bool loadMedia()
{
        //Loading success flag
        bool success = true;

        //Open the font
        gFont = TTF_OpenFont( "fonts/cooper_light.ttf", 16 );
        if( gFont == NULL )
        {
                printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
        }
        else
        {
                //Render text
                SDL_Color textColor = { 0, 0, 0 };
                if( !mainTextTexture.loadFromRenderedText( "Home", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
		if( !taxTextTexture.loadFromRenderedText( "Taxes", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !loanTextTexture.loadFromRenderedText( "Loans", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !stockTextTexture.loadFromRenderedText( "Stocks", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !plannerTextTexture.loadFromRenderedText( "Planner", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
 
       }

        //Open font for welcome message
        gFont = TTF_OpenFont( "fonts/sans_serif_nb.ttf", 28 );
        if( gFont == NULL )
        {
                printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
        }
        else
        {
                //Render text
                SDL_Color textColor = { 255, 255, 255 };
                if( !welcomeTextTexture.loadFromRenderedText( "Welcome to your Financial Planner", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !taxScreenTextTexture.loadFromRenderedText( "TAXES", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !loanScreenTextTexture.loadFromRenderedText( "LOANS", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !stockScreenTextTexture.loadFromRenderedText( "STOCKS", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }
                if( !plannerScreenTextTexture.loadFromRenderedText( "YOUR PLAN", textColor ) )
                {
                        printf( "Failed to render text texture!\n" );
                        success = false;
                }

                if( !gPromptTextTexture.loadFromRenderedText( "Enter Text:", textColor ) )
                {
                        printf( "Failed to render prompt text!\n" );
                        success = false;
                }
                if( !monthPromptTextTexture.loadFromRenderedText( "Enter Months:", textColor ) )
                {
                        printf( "Failed to render prompt text!\n" );
                        success = false;
                }
                if( !taxPromptTextTexture.loadFromRenderedText( "Tax Text:", textColor ) )
                {
                        printf( "Failed to render prompt text!\n" );
                        success = false;
                }
        }




        return success;
}

void close()
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

	gPromptTextTexture.free();
	gInputTextTexture.free();

        monthPromptTextTexture.free();
        monthInputTextTexture.free();
	
	taxPromptTextTexture.free();
	taxInputTextTexture.free();

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

int main( int argc, char* args[] )
{
	int currentScreen = 0;

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
                        std::string inputText = "Principal";
                        gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );

                        std::string monthText = "Months";
                        monthInputTextTexture.loadFromRenderedText( monthText.c_str(), textColor );
 		
			std::string taxText = "Income";
			taxInputTextTexture.loadFromRenderedText( taxText.c_str(), textColor );                       

                        //Enable text input
                        SDL_StartTextInput();

                	int x, y;

			//While application is running
			while( !quit )
			{

				bool renderText = false;
				bool renderMonthText = false;
				bool renderTaxText = false;
	
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
							if( taxText.length() > 0 && currentScreen == 1 ){
                                                                taxText = taxText.substr(0, taxText.size() - 1);
                                                                renderTaxText = true;
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
                                                                SDL_SetClipboardText( taxText.c_str() );

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
                                                                taxText = SDL_GetClipboardText();
                                                                renderTaxText = true;
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
                                                                taxText += e.text.text;
                                                                renderTaxText = true;
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
						//Render new text
						gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
					}
					//Text is empty
					else
					{
						//Render space texture
						gInputTextTexture.loadFromRenderedText( " ", textColor );
					}
				}     	

                                //Rerender month text if needed
                                if( renderMonthText )
                                {
                                        //Text is not empty 
                                        if( monthText != "" )
                                        {
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


				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderClear( gRenderer );

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
			
				//Render current frame
				mainTextTexture.render( SCREEN_WIDTH / 10 - mainTextTexture.getWidth() ,  SCREEN_HEIGHT / 8 - mainTextTexture.getHeight() );
                                taxTextTexture.render( SCREEN_WIDTH / 10 - taxTextTexture.getWidth() , 2  * SCREEN_HEIGHT / 8 - taxTextTexture.getHeight() );
                                stockTextTexture.render( SCREEN_WIDTH / 10 - stockTextTexture.getWidth(), 3 * SCREEN_HEIGHT / 8 - stockTextTexture.getHeight() );
				loanTextTexture.render( SCREEN_WIDTH / 10 - loanTextTexture.getWidth(), 4 * SCREEN_HEIGHT / 8 - loanTextTexture.getHeight() );
				plannerTextTexture.render( SCREEN_WIDTH / 10 - plannerTextTexture.getWidth(), 5 * SCREEN_HEIGHT / 8 - plannerTextTexture.getHeight() );
				
				//Display chosen screen
				if( currentScreen == 0 ){
					welcomeTextTexture.render( SCREEN_WIDTH / 2 - welcomeTextTexture.getWidth() / 2 ,  SCREEN_HEIGHT / 2 - welcomeTextTexture.getHeight() / 2 );
					currentScreen = 0;
				}
				else if( currentScreen == 1 )
				{
                                        taxScreenTextTexture.render( SCREEN_WIDTH / 2 - taxScreenTextTexture.getWidth() / 2 ,  0 );
                                        //Render text textures
                                        taxPromptTextTexture.render( ( SCREEN_WIDTH - taxPromptTextTexture.getWidth() ) / 2, 100 );
                                        taxInputTextTexture.render( ( SCREEN_WIDTH - taxInputTextTexture.getWidth() ) / 2, 100 + taxPromptTextTexture.getHeight() );
				}	
				else if( currentScreen == 2 )
				{
                                        stockScreenTextTexture.render( SCREEN_WIDTH / 2 - stockScreenTextTexture.getWidth() / 2 ,  0 );
				}
				else if( currentScreen == 3 )
				{
                                        loanScreenTextTexture.render( SCREEN_WIDTH / 2 - loanScreenTextTexture.getWidth() / 2 , 0 );

					//Render text textures
					gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 100 );
					gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, 100 + gPromptTextTexture.getHeight() );

                                        monthPromptTextTexture.render( ( SCREEN_WIDTH - monthPromptTextTexture.getWidth() ) / 2, 200 );
                                        monthInputTextTexture.render( ( SCREEN_WIDTH - monthInputTextTexture.getWidth() ) / 2, 200 + monthPromptTextTexture.getHeight() );

				}
				else if( currentScreen == 4 )
				{
                                	plannerScreenTextTexture.render( SCREEN_WIDTH / 2 - plannerScreenTextTexture.getWidth() / 2 , 0 );
				}
				
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
