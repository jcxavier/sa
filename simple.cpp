unsigned int a = 1;

#include "folder/sampleinclude.h"
#include <vector>

using namespace std;

struct abc
{
    int x;
    int y;
};

class Lol
{
    int a;
};

unsigned int loluint = 2;

typedef struct AAADZDSD { double asd; float c; } AAZ;

#define RND_CONSTANT 163

static int XYZ = 12;

double ez = 0.0;

vector<int> asdasdasdasd;

int arrayz[10001];

#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
    int a = 3;
    int b = 2;
    
    signed long ull = -11;
    unsigned int uintlol = 1;
    uintlol = 2;
    
    bool bvar = true;
    char acac = 'a';
    
    string xdstring = "asdasdasdbcdad";
    
    void* rndPtr;
    short shortie = 2;
    
    int assigned = 3;
    int xunsigned = 2;
    
    b += a;
    
    int c = mpy(a, b);
    
    abc st;
    
    struct abcx
    {
        int x;
        int y;
    };

    class Lolx
    {
        int a;
    };
    
    st.x = 2;
    st.y = 3;
    
    AAZ aaz;
    aaz.asd = st.x + 3 - RND_CONSTANT;
    
    cout << "Hello world " << st.x << " i are lol" << endl;
    
    {
        arrayz[30] = 0;
    }
    
    cin >> a >> b;
    
    if (2 != 3 % 2 & 3 && 2 || (3+4) * 2 + 1 ^ ((3 << 2) >> 1) + ++c - 2 - --c + c-- / 1 == 1 | 1 + ~1)
        a = b;
    else if (0)
        b >>= a;
    else
        c ^= (a ? a : b);
        
    
    return 0;
}
