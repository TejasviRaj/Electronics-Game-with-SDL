#ifndef ANALOG_H_INCLUDED
#define ANALOG_H_INCLUDED
#include <SDL/SDL.h>
#include "Design.h"
int level1_analog();

using namespace std;

class circuit
{
    protected:
SDL_Rect box;
    int bit;

public:
circuit(){}
circuit(int a):bit(a){}
circuit( int x, int y)
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
    circuit operator+ (circuit b)
    {
        return circuit(bit&b.bit);
    }

     circuit operator|| (circuit b)
    {
        return circuit(bit|b.bit);
    }


    int get_bit()
    {
        return bit;
    }

    void flipscreen()
    {

    if (bit==1)
               {

                SDL_BlitSurface(setBMP, NULL, screen, &box);
                 SDL_Flip(screen);


               }
               else if (bit==0)
               {
                    SDL_BlitSurface(resetBMP, NULL, screen, &box);

                 SDL_Flip(screen);

               }

             /*  else if (bit==2)
               {
                   SDL_BlitSurface (shortBMP,NULL,screen,&box);

               }*/
    }



    void setposition(int x,int y)
    {
        box.x = x;
    box.y = y;
    }

};




      // output o (200,200);

class npn:public circuit
{
    public:

npn (int a,int b):circuit(a ,b){}

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


class branch:public circuit
{
    public:
        branch(){}
branch(circuit a )
    {
        bit=a.get_bit();
    }
};

branch circuit1,circuit2;

class LED:public circuit
{
public:
    LED(){}
    LED (int a,int b):circuit(a ,b){}

    LED(circuit a )
    {

        bit=a.get_bit();


    }

    check()
    {
        if ((circuit1.get_bit()==0 && circuit2.get_bit()==0) || (circuit1.get_bit()==0 && circuit2.get_bit()==1) )
        {
            bit=0;
        }
        else if (circuit1.get_bit()==1 && circuit2.get_bit()==0 )
        {
            bit=1;
            level_completed();
        }
        else if (circuit1.get_bit()==1 && circuit2.get_bit()==1)
            bit=0;
    }


};

int load_analog()
{
    analog_loadfile();

      return (level1_analog());

}

int level1_analog()
{
    running =true;
        npn a(60,40);
        npn b(100,80);
        npn c(140,120);
        npn d(180,160);
        npn e(220,200);
        npn f(240,240);
        npn g(280,280);

        branch b1,b2;

        LED o(0,0);

                levelno = TTF_RenderText_Solid(font,"Level 1",textcolor);
applySurface(30,0,levelno,screen);

        applySurface(330,150,levelImage,screen);
        applySurface(1040,5,home,screen);
        Buttons bo(1040,5,234,94);
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

       circuit1=(a+b)||(c+d);
       circuit2=e+(f||g);
o.check();
o.flipscreen();
            a.click_check();
            b.click_check();
            c.click_check();
            d.click_check();
                        e.click_check();
            f.click_check();
            g.click_check();
bo.click_check();
            if (bo.get_clicks()) return 2;

        }
    }
}




#endif




