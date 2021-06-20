#include <math.h>

//extern "C"
//{
//#include "helper.h"
//}

#include "playerControl.h"

#ifdef main
#undef main
#endif

int main()
{
	playerControl controler;
	controler.init();
	controler.start();
	controler.stop();
	
	return 0;
}

