#include <iostream>
#include "Ratio.h"

int main()
{
	Ratio ratio;
	ratio.count = 0;
	ratio.count++;
	ratio.pixel_value = 0;
	//delete ratio;
	std::cout<< "hello world " << ratio.count << std::endl;
	return 0;
}//end of main
