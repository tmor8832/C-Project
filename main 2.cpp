#include <iostream>
#include <math.h>
using namespace std;
float tirnoSolver(float x);
float tirnoSolver(float x){
    float k, Pi;
    Pi = 3.14159265358;
    float y;
    y = tan(x);
    return y;
}

int main(){
    int screen[80][32];
    int j;
    float k, Pi;
    Pi = 3.14159265358;
    
    for (int a = 0; a <= 32; a++)
    {
        for (int b = 0; b <= 80; b++)
        {
            screen[b][a] = 0;
        }
    }
    for (float i = -640; i<640; i++)
    {
        int z = int((i + 640) / 16);
        
        k = 16 + 4 * -tirnoSolver((i * Pi) / 180);
        j = int(k);
        
        if (j <= 32 & j >0)
            screen[z][j] = 1;
    }
    for (int y = 1; y <= 32; y++)
    {
        if (y == 16)
            for (int d = 0; d <= 79; d++)
                if (screen[d][16] == 0)
                    if (d == 39)
                        cout << char(197);
                    else
                        cout << char(196);
                    else
                        cout << char(1);
                    else
                    {
                        for (int x = 0; x <= 79; x++)
                        {
                            if (screen[x][y] == 0)
                                if (x == 39)
                                    cout << "-";//  char(179);
                                else
                                    cout << " ";
                                else
                                    cout << char(1);
                        }
                    }
    }
    printf("Hit any key to continue> ");
    getchar();
    return 0;
}
