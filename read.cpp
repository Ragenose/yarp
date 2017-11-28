#include "read.h"


int getsize(FILE * file) {
	int size;
	fseek(file, 0, SEEK_END);  //go to the end of file
	size = ftell(file);		   //store the size of the file
	fseek(file, 0, SEEK_SET);  //go back to the beginning of file
	return size;			   //return the size
}

yarp::yarp(int alength){
	r0 = r1 = r2 = r3 = r4 = r5 = r6 = sp = pc =0;
	length = alength;
	maxsize = 1024;
	buff = new unsigned char[maxsize];
	tempBuff = new unsigned char[6];
}

void yarp::read(char* filename){
	FILE * file = fopen(filename, "rb");	//try to open the file

	if (!file) {
		cout << "could not open file" << endl;	//if cannot open the file, print error message
	}
	else {														//if can open the file
		buffSize = getsize(file);								//get the size of the file
		fread(buff, buffSize,1, file);								//read the file and store into the buffer
		fclose(file);													//close file
	}
}


void yarp::display(){
	int counter = 0;
	int line =1;
	int tempSize;
	string opName;
	//traversal every element in the buffer
	while (counter < buffSize && line <= length){
		int lineLength=0;
		cout <<"pc = "<<setw(3)<<setfill('0')<<counter<<": " << "step: " << line;  //print the index
		opName = checkOperation(buff[counter],tempSize);   			//check the operation
		for( int i =0; i<tempSize;i++){
			cout <<" "<< hex << setw(2) << setfill('0') << int(buff[counter]);	//print elements
			counter ++;
			lineLength ++;
		}
		line++;
		cout << setw(20-lineLength+(6-lineLength))<<setfill(' ') << opName << endl;	//print the name
	}

	cout << "Stopped in "<<line<<" steps at PC=0x"<<hex<<setw(3)<<setfill('0')<<pc<<endl;
	cout <<"Changes to registers: "<<endl;
	checkRegisterChange();

}

//check which register is changed from 0 and display the change
void yarp::checkRegisterChange(){
	if(r0 != 0){
		cout << "r0: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r0<<endl;
	}
	if(r1 != 0){
		cout << "r1: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r1<<endl;
	}
	if(r2 != 0){
		cout << "r2: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r2<<endl;
	}
	if(r3 != 0){
		cout << "r3: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r3<<endl;
	}
	if(r4 != 0){
		cout << "r4: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r4<<endl;
	}
	if(r5 != 0){
		cout << "r5: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r5<<endl;
	}
	if(r6 != 0){
		cout << "r6: 00000000 -> "<< hex << setw(8)<<setfill('0')<<r6<<endl;
	}
	if(sp != 0){
		cout << "sp: 00000000 -> "<< hex << setw(8)<<setfill('0')<<sp<<endl;
	}
}
//use switch statement to check the operation name and the length of the operation
string yarp::checkOperation(unsigned char temp , int &size){
	switch(temp){
		case 0x00: {
			size = 1;
			return "HALT";
		}
		case 0x10: {
			size = 1;
			return  "NOP";
		}
		case 0x20: {
			size = 2;
			return "MOV";
		}
		case 0x30: {
			size = 6;
			return "MOV";
		}
		case 0x40: {
			size = 2;
			return "LDR";
		}
		case 0x41: {
			size = 2;
			return "STR";
		}
		case 0x50: {
			size = 6;
			return "LDR";
		}
		case 0x51: {
			size = 6;
			return "STR";
		}
		case 0x60:{
			size = 2;
			return "ADD";
		}
		case 0x61:{
			size = 2;
			return "SUB";
		}
		case 0x62:{
			size = 2;
			return "AND";
		}
		case 0x63:{
			size = 2;
			return "EOR";
		}
		case 0x80: {
			size= 5;
			return "CALL";
		}
		case 0x90: {
			size =1;
			return "RET";
		}
		case 0xa0: {
			size = 2;
			return "PUSH";
		}
		case 0xb0: {
			size = 2;
			return "POP";
		}
		default: {
			temp = temp >> 4;
			if(temp == 0x7){
				size = 5;
				return "B";
			}
			else{
				size = 1;
				return "NOT OPERATION";	//for some weird bytes
			}
		}
	}
}

//check which operation it is and call that function
void yarp::checkOperation(){
	int size= 1;
	unsigned char temp = buff[pc];
	switch(temp){
	case 0x00: {
			break;
		}
		case 0x10: {
			break;
		}
		case 0x20: {
			break;
		}
		case 0x30: {
			size = 6;
			copy(size);
			mov_30();
			break;
		}
		case 0x40: {
			break;
		}
		case 0x41: {
			break;
		}
		case 0x50: {
			break;
		}
		case 0x51: {
			break;
		}
		case 0x60:{
			break;
		}
		case 0x61:{
			size = 2;
			copy(2);
			sub();
			break;
		}
		case 0x62:{
			break;
		}
		case 0x63:{
			break;
		}
		case 0x80: {
			break;
		}
		case 0x90: {
			break;
		}
		case 0xa0: {
			break;
		}
		case 0xb0: {
			break;
		}
		default: {
			temp = temp >> 4;
			if(temp == 0x7){
				size = 5;
			}
			else{
				size = 1;
			}
		}
	}

	
}

//copy current instruction to a temp buffer
void yarp::copy(int size){
	for(int i =0;i<size;i++){
		tempBuff[i] = buff[pc+i];
	}
	pc+=size;
}

//mov 30 function
void yarp::mov_30(){
	int value=0;
	for(int i =0;i<4;i++){		//get the 32 bit value
		value |= (int)(tempBuff[2+i] << (i*8));
	}
	switch(tempBuff[1]>>4){			//check which register will be moved
		case 0x0: {
			r0 = value;				//move the value into the register
			break;
		}
		case 0x1: {
			r1 =value;
			break;
		}
		case 0x2: {
			r2 =value;
			break;
		}
		case 0x3: {
			r3 =value;
			break;
		}
		case 0x4: {
			r4 =value;
			break;
		}
		case 0x5: {
			r5 =value;
			break;
		}
		case 0x6: {
			r6 =value;
			break;
		}
		case 0x7: {
			sp = value;
			break;
		}
	}
}

//sub function
void yarp::sub(){
	int ra,rb = 0;
	switch(tempBuff[1] & 0xf){		//find which register is rb
		case 0x0: {
			rb = r0;
			break;
		}
		case 0x1: {
			rb = r1;
			break;
		}
		case 0x2: {
			rb =r2;
			break;
		}
		case 0x3: {
			rb =r3;
			break;
		}
		case 0x4: {
			rb=r4;
			break;
		}
		case 0x5: {
			rb =r5;
			break;
		}
		case 0x6: {
			rb =r6;
			break;
		}
	}
	switch(tempBuff[1]>>4){			//find which register is ra
		case 0x0: {
			r0 -=rb;				//store ra-rb into the register
			break;
		}
		case 0x1: {
			r1 -=rb;
			break;
		}
		case 0x2: {
			r2 -=rb;
			break;
		}
		case 0x3: {
			r3 -=rb;
			break;
		}
		case 0x4: {
			r4 -=rb;
			break;
		}
		case 0x5: {
			r5 -=rb;
			break;
		}
		case 0x6: {
			r6 -=rb;
			break;
		}
	}
	
}
void yarp::compile(){
	for(int i =0;i<length;i++){
		checkOperation();
	}
}