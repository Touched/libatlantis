#include "../atlantis/atlantis.h"
#include "System.h"
#include <cstring>

int main(int argc, char **argv) {

	test::System sys;

	init((atlantis::Emulator*) &sys);

	char image[50];
	strcpy(image, "./test.gba");
	char *args[2] =  {argv[0], image};

	load(2,args);


	return 0;
}



