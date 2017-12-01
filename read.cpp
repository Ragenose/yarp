#include "read.h"

int getsize(FILE * file) {
	int size;
	fseek(file, 0, SEEK_END);  //go to the end of file
	size = ftell(file);		   //store the size of the file
	fseek(file, 0, SEEK_SET);  //go back to the beginning of file
	return size;			   //return the size
}

yarp::yarp(int alength){
	r0 = r1 = r2 = r3 = r4 = r5 = r6 = sp = pc = n = z = c = v=0;
	status = 1;
	length = alength;
	maxsize = 1024;
	memoSize = 4096;
	lineNum = 1;
	buff = new unsigned char[maxsize];
	memo = new unsigned char[memoSize];
	memset(memo, 0, 4096);
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

//display change in registers, memory, status, flags
void yarp::result(){
	string stat;
	switch(status){
		case 1: stat = "AOK";break;
		case 2: stat = "HLT";break;
		case 3: stat = "ADR";break;
		case 4: stat = "INS";break;
		default: stat = "Unknown status";
	}
	cout << "Stopped in "<<dec<<lineNum-1<<" steps at PC=0x"<<hex<<setw(3)<<setfill('0')<<pc<<
	" Status "<<"'"<<stat<<"'"<<" CC: "<<" N = "<<n<<" Z = " << z <<" C = "<<c<<" V = "<<v<<endl;
	cout <<"Changes to registers: "<<endl;
	checkRegisterChange();
	cout << endl;
	checkMemoryChange();
	cout << endl;
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

//check memeory change
void yarp::checkMemoryChange(){
	cout << "Change in memory: "<<endl;
	int counter = 0;
	while(counter < memoSize){
		if(int(memo[counter]) != 0){		//find any non-zero value in memory and print 8 bytes from that address
			cout << "0x"<< hex<<setw(3)<<setfill('0')<<counter<<": 0x00000000 -> 0x";
			for(int i =3;i>= 0;i--){
				cout <<hex << setw(2)<<setfill('0') << int(memo[counter + i]);
			}
			counter+=4;
			cout << endl;
		}
		counter++;
	}
}

//use switch statement to check the operation name and the length of the operation
//for displaying purpose
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
		case 0x70: {
			size = 5;
			return "BEQ";
		}
		case 0x71: {
			size = 5;
			return "BNE";
		}
		case 0x72: {
			size = 5;
			return "BCS";
		}
		case 0x73: {
			size = 5;
			return "BCC";
		}
		case 0x74: {
			size = 5;
			return "BMI";
		}
		case 0x75: {
			size = 5;
			return "BPL";
		}
		case 0x76: {
			size = 5;
			return "BVS";
		}
		case 0x77: {
			size = 5;
			return "BVC";
		}
		case 0x78: {
			size = 5;
			return "BHI";
		}
		case 0x79: {
			size = 5;
			return "BLS";
		}
		case 0x7a: {
			size = 5;
			return "BGE";
		}
		case 0x7b: {
			size = 5;
			return "BLT";
		}
		case 0x7c: {
			size = 5;
			return "BGT";
		}
		case 0x7d: {
			size = 5;
			return "BLE";
		}
		case 0x7e: {
			size = 5;
			return "BAL";
		}
		default: {
				size = 1;
				return "Illegal instruction";	//for some weird bytes
		}
	}
}

//check which operation it is and call that function
//for running simulator
void yarp::checkOperation(){
	unsigned char temp = buff[pc];
	switch(temp){
	case 0x00: {
			copy(1);
			halt();
			break;
		}
		case 0x10: {
			copy(1);
			break;
		}
		case 0x20: {
			copy(2);
			mov_20();
			break;
		}
		case 0x30: {
			copy(6);
			mov_30();
			break;
		}
		case 0x40: {
			copy(2);
			ldr_40();
			break;
		}
		case 0x41: {
			copy(2);
			str_41();
			break;
		}
		case 0x50: {
			copy(6);
			ldr_50();
			break;
		}
		case 0x51: {
			copy(6);
			str_51();
			break;
		}
		case 0x60:{
			copy(2);
			add();
			break;
		}
		case 0x61:{
			copy(2);
			sub();
			break;
		}
		case 0x62:{
			copy(2);
			and_62();
			break;
		}
		case 0x63:{
			break;
		}
		case 0x80: {
			copy(5);
			call();
			break;
		}
		case 0x90: {
			copy(1);
			ret();
			break;
		}
		case 0xa0: {
			copy(2);
			int value = findRa();
			push(value);
			break;
		}
		case 0xb0: {
			copy(2);
			int value = findRa();
			pop(value);
			setRa(value);
			break;
		}
		//illegal instruction
		default: {
			if(temp >> 4 == 0x7){
				copy(5);
				switch((temp & 0xf)){
					case 0x0: {
						if(z == 1){
							b();
						}
						break;
					}
					case 0x1: {
						if(z == 0){
							b();
						}
						break;
					}
					case 0x2: {
						if(c == 1){
							b();
						}
						break;
					}
					case 0x3: {
						if(c == 0){
							b();
						}
						break;
					}
					case 0x4: {
						if(n == 1){
							b();
						}
						break;
					}
					case 0x5: {
						if(n == 0){
							b();
						}
						break;
					}
					case 0x6: {
						if(v == 1){
							b();
						}
						break;
					}
					case 0x7: {
						if(v == 0){
							b();
						}
						break;
					}
					case 0x8: {
						if(c == 1 && z == 0){
							b();
						}
						break;
					}
					case 0x9: {
						if(c == 0 || z == 1){
							b();
						}
						break;
					}
					case 0xa: {
						if(n == v){
							b();
						}
						break;
					}
					case 0xb: {
						if(n != v){
							b();
						}
						break;
					}
					case 0xc: {
						if(z == 0 && n == v){
							b();
						}
						break;
					}
					case 0xd: {
						if(z == 0 && n != v){
							b();
						}
						break;
					}
					case 0xe: {
						b();
						break;
					}
					default:{
						status = 4;
						copy(1);
					}
				}
			}
			else{
				status = 4;
				copy(1);
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

//halt function
void yarp::halt(){
	status = 2; //set status to HLT
}

//mov 20 function
void yarp::mov_20(){
	int value = findRb();
	setRa(value);
}

//mov 30 function
void yarp::mov_30(){
	int value=0;
	for(int i =0;i<4;i++){		//get the 32 bit value
		value |= (int)(tempBuff[2+i] << (i*8));
	}
	setRa(value);
}

//add function
void yarp::add(){
	int ra,rb,result = 0;
	ra = findRa();
	rb = findRb();
	result = ra + rb;
	setRa(result);
	checkFlag(ra,rb,result);
	//when ra is negative and result is postive, set c = 1, otherwise 0
	if((ra >> 31 == 0xffffffff)  &&(ra >> 31) != (result >> 31)){
		c = 1;
	}
	else{
		c = 0;
	}
}

//sub function
void yarp::sub(){
	int ra,rb,result = 0;
	ra = findRa();
	rb = findRb();
	result = ra - rb;
	setRa(result);
	checkFlag(ra,rb,result);
	//when ra is bigger than rb, there is no borrow, set c = 1, otherwise 0
	if(ra >= rb){
		c = 1;
	}
	else{
		c = 0;
	}
	//if sign of ra and rb are different, if sign of result is not the same as ra
	//overflow occurs and no borrow
	if(ra >> 31 != rb >> 31){
		if(ra >> 31 != result >> 31){
			v = c = 1;
		}
		else{
			v = c = 0;
		}
	}
}

//and function
void yarp::and_62(){
	int ra,rb,result = 0;
	ra = findRa();
	rb = findRb();
	result = ra & rb;
	setRa(result);
	checkFlag(ra,rb,result);	
}

//eor function
void yarp::eor(){
	int ra,rb,result = 0;
	ra = findRa();
	rb = findRb();
	result = ra ^ rb;
	setRa(result);
	checkFlag(ra,rb,result);
}

//ldr_40 function
void yarp::ldr_40(){
	int address = findRb();
	int value = 0;
	if(checkAddress(address)){
		for(int i =0; i<4;i++){
			value |= (memo[address + i]) << i*8;
		}
		setRa(value);
	}
}

//str_41 function
void yarp::str_41(){
	int value = findRa();
	int address = findRb();
	if(checkAddress(address)){
		for(int i =0;i<4;i++){
			memo[address + i] = (value >> (8*i))& 0xff;
		}
	}
}

//ldr_50 function
void yarp::ldr_50(){
	int value = findRa();			//get value that needs to be stored
	int address = findRb();			//get address to store the value
	int temp = 0;
	for(int i =0;i<4;i++){		//get the 32 bit value
		temp |= (int)(tempBuff[2+i] << (i*8));
	}
	address+=temp;					//add the address with 32 bit value
	if(checkAddress(address)){
		for(int i =0; i<4;i++){
			value |= (memo[address + i]) << i*8;
		}
		setRa(value);
	}
}

//str_51 function
void yarp::str_51(){
	int value = findRa();			//get value that needs to be stored
	int address = findRb();			//get address to store the value
	int temp = 0;
	for(int i =0;i<4;i++){		//get the 32 bit value
		temp |= (int)(tempBuff[2+i] << (i*8));
	}
	address+=temp;					//add the address with 32 bit value
	if(checkAddress(address)){
		for(int i =0;i<4;i++){
			memo[address + i] = (value >> (8*i))& 0xff;
		}
	}
}

//push function
void yarp::push(int value){
	for(int i = 3 ; i>=0 ;i--){
		if(checkAddress(sp)){
			sp--;
			memo[sp] = (value >> 8*i) & 0xff;  //store each byte into memory
		}
	}
}

//pop function
void yarp::pop(int & value){
	int tempValue = value;
	value = 0;
	if(checkAddress(sp)){				//if the address is invalid, the register will not change
		for(int i =0;i<4;i++){
			value |= (memo[sp + i]) << i*8;		//load from the address
		}
		sp+=4;
	}
	else{
		value = tempValue;
	}
}

//b function
void yarp::b(){
	int value = 0;
	for(int i =0;i< 4;i++){
		value |= tempBuff[1+i]<< i*8;
	}
	if(value < 0 || value >maxsize){	//check if the value is larger than the maxsize of instrucitons
		status = 3;
	}
	else{
		pc = value;						//set pc equals to the value
	}
}

//call function
void yarp::call(){
	int value = 0;
	for(int i =0;i< 4;i++){
		value |= tempBuff[1+i]<< i*8;
	}
	push(pc);
	pc = value;
}

void yarp::ret(){
	pop(pc);
}
//return value of ra
int yarp::findRa(){
	int ra = 0;
	switch(tempBuff[1]>>4){			//find which register is ra
		case 0x0: {
			ra = r0;				//store ra-rb into the register
			break;
		}
		case 0x1: {
			ra = r1;
			break;
		}
		case 0x2: {
			ra = r2;
			break;
		}
		case 0x3: {
			ra = r3;
			break;
		}
		case 0x4: {
			ra = r4;
			break;
		}
		case 0x5: {
			ra = r5;
			break;
		}
		case 0x6: {
			ra = r6;
			break;
		}
		case 0x7: {
			ra = sp;
			break;
		}
	}
	return ra;
}

//return value of rb
int yarp::findRb(){
	int rb = 0;
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
		case 0x7: {
			rb = sp;
			break;
		}
	}
	return rb;
}

//set ra to result
void yarp::setRa(int result){
	switch(tempBuff[1]>>4){			//find which register is ra
		case 0x0: {
			r0 = result;				//store ra-rb into the register
			break;
		}
		case 0x1: {
			r1= result;
			break;
		}
		case 0x2: {
			r2 = result;
			break;
		}
		case 0x3: {
			r3 = result;
			break;
		}
		case 0x4: {
			r4 = result;
			break;
		}
		case 0x5: {
			r5 = result;
			break;
		}
		case 0x6: {
			r6 = result;
			break;
		}
		case 0x7: {
			sp = result;
			break;
		}
	}
}

//check flag n z v
void yarp::checkFlag(int ra,int rb, int result){
	//check zero
	//if result is zero
	if(result == 0){			
		z = 1;
	}
	else{
		z = 0;
	}
	//check negative
	//if result >> 31 = 0xffffffff, then result is negative
	if((result >> 31) == -1){	
		n =1;					
	}
	else{
		n = 0;
	}
	//check overflow
	//if signs of ra and rb are the same and sign of result is different
	//then there are overflow and carry
	if((ra >>31 == rb >> 31) && (ra>>31 != result >>31)){
		v = c = 1;
	}
	else{
		v = c = 0;
	}
}

//check if address is bigger than the maxsize or smaller than 0
bool yarp::checkAddress(int address){
	if(address <0 || address >memoSize){
		status = 3;
		return false;  //if address is not valid return false
	}
	return true;
}

//try to display any instuction is ran during the procss
void yarp::display(int tempPC, int size, string name){
	int counter = 0;
	cout << "Line: "<<setw(2)<<setfill('0')<<dec<<lineNum<<" ";
	cout << "PC: "<<setw(3)<<setfill('0')<<hex << tempPC << "  ";
	for(int i =0;i<size;i++){
		cout << setw(2)<<setfill('0')<<hex<<int(tempBuff[i])<<' ';    //display current instruction in temp buffer
		counter ++;
	}
	cout << setw(30 - counter*3)<<setfill(' ')<<"| "<< name;
	cout << endl;
	lineNum ++ ;
}

//try to run each step
void yarp::run(){
	int size;    //size of each line of the instruction
	int tempPC;
	string name; //name of the instruction
	for(int i =0;i<length;i++){
		name = checkOperation(buff[pc],size);
		tempPC = pc;
		checkOperation();
		display(tempPC,size,name);
		if(status != 1){  //if any changed status, stop simulating
			i = length;
		}
	}
}