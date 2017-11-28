#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "read.h"
using namespace std;
//Zuoxiu Xing
//200362635

int main(int argc, char* argv[]){
	const int maxsize = 1024;
	int size;
	unsigned char * buff = new unsigned char[maxsize];
	int length = argv[2][0] - '0';	//get the argument length
	yarp sim(length);
	sim.read(argv[1]);
	sim.compile();
	sim.display();
	return 0;
}