#include "MyList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	TList M;
	
	fromFileToList(M);
	findNamesOnCat(M);

	return 0;
}

