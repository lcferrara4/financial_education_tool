#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <fstream>

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;

//Button constants
const int BUTTON_WIDTH = SCREEN_WIDTH / 8;
const int BUTTON_HEIGHT = SCREEN_HEIGHT / 8;
const int TOTAL_BUTTONS = 5;

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


