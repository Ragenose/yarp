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
        unsigned char* buff;
        unsigned char* tempBuff;
        int maxsize;
        int r0,r1,r2,r3,r4,r5,r6,sp,pc;
        int buffSize;

    public:
        yarp(int);
        void read(char* );
        void compile();
        void display();
        void copy(int);
        string checkOperation(unsigned char, int &);
        void checkRegisterChange();
        void checkOperation();
        void showResult();
        void mov_30(); //30
        void sub();
};