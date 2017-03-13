#include <string>

#include "manual_sdl.h"
//#include "digital.h"

#include "Design.h"


int main(int argc, char* argv[])
{

	   if (sdl_init()==false) return 1;
        mainpage_loading();
        clean_up();

    return 0;
}





