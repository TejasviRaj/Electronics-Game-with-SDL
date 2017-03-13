#ifndef DIGITAL_H_INCLUDED
#define DIGITAL_H_INCLUDED

#include <SDL/SDL.h>
#include "manual_sdl.h"
void digital_sdl_init();

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
        if(bit)
            {
               level_completed();
            }
    }


};

      // output o (200,200);

class input:public variable
{
    public:

input (int a,int b):variable (a,b){}

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





void sdl_quit();
void level1();


void load_digital()
{
    digital_loadfile();

       level1();

}

void level1()
{
        input a(310,210);
        input b(310,270);
        input c(310,540);
        input d(310,480);
        wire w1,w2;
        levelno = TTF_RenderText_Solid(font,"Level 1",textcolor);
     applySurface(30,0,levelno,screen);

        applySurface(330,150,levelImage,screen);
        output o(1015,375);
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
            o.setposition(1015,375);
            o.flipscreen();
            a.click_check();
            b.click_check();
            c.click_check();
            d.click_check();
        }
    }
}




#endif // DIGITAL_H_INCLUDED
