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

double ez = 0000.0 + 1.10 + 1.0 +
 0.00 -
  0.00 
  + 
  0.00 *
  .12;

vector<int> asdasdasdasd;

int arrayz[10001];

#include <iostream>
#include <string>

// this is my main and short void signed unsigned here are reserved words
int main(int argc, char* argv[]) // this is main commenting
{
    int a = 3;
    int b = 2;
// lol    
    signed long ull = -11;
    unsigned /* cant touch this */ int uintlol = 1;
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
    
   
   switch (c)
   {
       case 1:
       a = a; break;
       case 2:
       a = b; break;
       case 3:
       b = a; break;
       default:
       b = b;
   }
   
   while (shortie--)
   {
       for (int i = 0; i < b || i > a; i++)
           c += i;
   }
   
   do {
       c += mpy(a,b);
   } while(shortie--);
   
    
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
