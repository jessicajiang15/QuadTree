#include <iostream>
//main.
#include <fstream>
#include "Forest.h"

int main() {
    ofstream file;
    file.open("example.txt");
    int *p;
    p=(int*)malloc(sizeof(int)*10);
    for(int i=0;i<10;i++)
    {
        p[i]=i;
    }
    file<<"{";
    for(int i=0;i<10;i++)
    {
        if(i==9)
        {
            file<<to_string(p[i]);
            break;
        }
        file<<to_string(p[i])+", ";
    }
    file<<"}";
    std::cout << "Quad Tree!\n"<<std::endl;
    file.close();
    return 0;
}

