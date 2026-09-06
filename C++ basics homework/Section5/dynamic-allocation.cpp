#include <iostream>
using namespace std;


int main(){
    int *nptr;
     
    nptr = new int[5];

    for(int i = 0; i < 5; i++){
        nptr[i] = i;
    }

    for(int j = 0; j < 5; j++){
        cout << nptr[j] << '\n';
    }

    delete[] nptr;

    

}