#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "data-types.h"
#include "destination.h"
#include "user-input.h"


int main() {

	//stvaranje datoteke
	char dest_file[] = "destinations.bin";

	int condition = 1;
	while (condition) {
		condition = main_menu(dest_file);
	}

	return 0;
}