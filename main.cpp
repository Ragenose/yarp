#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include "read.h"
using namespace std;
//Zuoxiu Xing
//200362635

int main(int argc, char* argv[]){
	const int maxsize = 1024;
	int size;
	unsigned char * buff = new unsigned char[maxsize];
	int length = 0;
	if(!argv[2]){        //if no input line number, default line number 200
		length = 200;
	}
	else{
		string temp = argv[2];
		length = atoi(temp.c_str());	//get the argument length
	}
	yarp sim(length);
	sim.read(argv[1]); //read file and store it to buffer
	if(sim.getFileRead()){  //if there is a file
		sim.run();	   //run the bytes
		sim.result();     //show result
	}
	else{                 //if cannot read the file
		cout << "Cannot open the file"<<endl;
	}
	return 0;
}