#ifndef DESIGN_H_INCLUDED
#define DESIGN_H_INCLUDED
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

#include "manual_sdl.h"
#include "digital.h"


void mainpage_loading();

void page(char ch)
{
     quit = false;
     bool flag = false;
     set_clip(0,0,510,160,0,160,0,310);
        load_page_secondpage(ch);
     Buttons b1(618,234,164,72);
    Buttons b2(618,351,164,72);
    Buttons b3(618,475,164,72);

    Mix_PlayMusic( music, -1 );
    display_page_secondpage(b1,b2,b3,ch);
    SDL_Flip(screen);
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) quit = true;
            if (!(b1.get_clicks()||b2.get_clicks()||b3.get_clicks()))
              {
                    b1.click_check();
                    b2.click_check();
                    b3.click_check();
                    flag = true;
              }
        }

        if (!(b1.get_clicks()||b2.get_clicks()||b3.get_clicks())||flag)
         {
            display_page_secondpage(b1,b2,b3,ch);
            SDL_Flip(screen);
            SDL_Delay(200);
            b1.temp = buttonImage1;
            b2.temp = buttonImage1;
            b3.temp = buttonImage1;
            SDL_Flip(screen);
            flag = false;
         }
    }
    if (b1.get_clicks())
    {
        load_digital();

    }
    else if (b2.get_clicks())
    {
        mainpage_loading();

    }
    else if (b3.get_clicks())
    {
        quit = true;
    }
}


void mainpage_loading()
{
     Buttons bu1(516,353,352,109);
Buttons bu2(520,572,352,109);
        main_page(bu1,bu2);
        if (bu1.get_clicks())
        {
           page('a');
        }
        else if (bu2.get_clicks())
        {
            page('d');
        }
}


#endif // DESIGN_H_INCLUDED
