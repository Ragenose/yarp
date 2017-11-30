#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cstring>
using namespace std;

int getsize(FILE * file);

class yarp{
    private:
        int length;
        unsigned char* memo;
        unsigned char* buff;
        unsigned char* tempBuff;
        int lineNum;
        int maxsize;
        int memoSize;
        int r0,r1,r2,r3,r4,r5,r6,sp,pc,n,z,c,v;
        int buffSize;
        int status;

        void copy(int); 
        string checkOperation(unsigned char, int &);
        void checkRegisterChange();
        void checkMemoryChange();
        void checkOperation();
        void showResult();
        void halt();
        void call();
        void ret();
        void mov_20();  //mov 20 
        void mov_30();  //mov 30
        void b();
        void sub();
        void add();
        void and_62();
        void eor();
        void ldr_40();
        void str_41();
        void ldr_50();
        void str_51();
        void push(int);
        void pop(int &);
        int findRa();
        int findRb();
        void setRa(int);
        void checkFlag(int,int,int);
        bool checkAddress(int);
        void display(int,int,string);
    public:
        yarp(int);
        void read(char* );
        void run();
        void result();
};