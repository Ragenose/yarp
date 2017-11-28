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
	sim.read(argv[1]); //read file and store it to buffer
	sim.compile();	   //run the bytes
	sim.display();     //show result
	return 0;
}