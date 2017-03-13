#ifndef ANALOG_H_INCLUDED
#define ANALOG_H_INCLUDED


#include <iostream>
#include <SDL/SDL.h>
SDL_Event event;
SDL_Surface *screen;
SDL_Surface *resetBMP;
SDL_Surface *setBMP;
Uint32 screenColor;
bool running = true;
using namespace std;

class variable
{
    protected:
SDL_Rect box;
    bool bit;

public:
variable(){}
variable(int a):bit(a){}
variable( int x, int y)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = 65;
    box.h = 65;
bit=0;
    //SDL_BlitSurface(resetBMP, NULL, screen, &box);
    flipscreen();
 //       SDL_Flip(screen);
}
    variable operator& (variable b)
    {
        return variable(bit&b.bit);
    }

     variable operator| (variable b)
    {
        return variable(bit|b.bit);
    }

    variable operator~ ()
    {
        return variable(!bit);
    }

   variable operator^ (variable b)
    {
        return variable(bit^b.bit);
    }

    int get_bit()
    {
        return bit;
    }

    void flipscreen()
    {

    if (bit)
               {

                SDL_BlitSurface(setBMP, NULL, screen, &box);
                 SDL_Flip(screen);
               }
               else
               {
                    SDL_BlitSurface(resetBMP, NULL, screen, &box);

                 SDL_Flip(screen);
               }
    }



    void setposition(int x,int y)
    {
        box.x = x;
    box.y = y;
    }

};


class output:public variable
{
public:
    output(){}
    output (int a,int b):variable(a ,b){}

    output(variable a )
    {

        bit=a.get_bit();
    }


};

      // output o (200,200);

class input:public variable
{
    public:

input (int a,int b):variable(a ,b){}

void click_check()
{
    int x=0,y=0;
     //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
      if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                bit=!bit;
                               // SDL_BlitSurface(setBMP, NULL, screen, &box);

              flipscreen();
          //     o-> flipscreen();
            }
        }
    }
}


};

class wire:public variable
{
    public:
        wire(){}
wire(variable a )
    {
        bit=a.get_bit();
    }
};





void sdl_init();
void sdl_quit();



int main(int argc, char* argv[])
{

    sdl_init();
        input a(60,40);
        input b(100,150);
        input c(200,200);
        input d(300,300);
        wire w1,w2;

        output o(0,0);
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
            w1=a&b;
        w2=c|d;
o=w1&w2;
//o.zero();
o.setposition(0,0);
o.flipscreen();
            a.click_check();
            b.click_check();
            c.click_check();
            d.click_check();
        }
    }
  sdl_quit();
}
void sdl_init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    setBMP = SDL_LoadBMP("set.bmp");

    resetBMP=SDL_LoadBMP("Reset.bmp");

    screenColor = SDL_MapRGB(screen->format, 25, 23, 90);
     SDL_FillRect(screen, NULL, screenColor);


}

void sdl_quit()
{
      SDL_FreeSurface(screen);
    SDL_FreeSurface(setBMP);
    SDL_FreeSurface(resetBMP);

    SDL_Quit();
}

void level1()
{

}




#endif // ANALOG_H_INCLUDED
