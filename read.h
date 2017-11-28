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
        int maxsize;
        int memoSize;
        int r0,r1,r2,r3,r4,r5,r6,sp,pc,n,z,c,v;
        int buffSize;

        void copy(int);
        string checkOperation(unsigned char, int &);
        void checkRegisterChange();
        void checkMemoryChange();
        void checkOperation();
        void showResult();
        void mov_30(); //30
        void sub();
        void add();
        void and_62();
        void str_41();
        void str_51();
        int findRa();
        int findRb();

    public:
        yarp(int);
        void read(char* );
        void compile();
        void display();
        
};