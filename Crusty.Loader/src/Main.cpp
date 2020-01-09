#include <Crusty.h>
#include "Game.h"


int main()
{
	auto retval = 1;
	auto testapp = std::make_shared<Game>();
	if (!testapp->Bootstrap())
		return retval;

	retval = testapp->Run();

	return retval;
}

