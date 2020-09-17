#include<fstream>
#include<cstdlib>
using namespace std;
int main(){
    const int nums = 100000;
    const int del = 50000;
    const int query = 100000;
    ofstream os("num.txt", ios::out);
    srand(time(NULL));
    for (int i = 0; i<nums; ++i){
        os<<0<<' '<<(rand()%(nums))<<'\n';
    }
    for (int i = 0; i<del; ++i){
        os<<1<<' '<<(rand()%(nums))<<'\n';
    }
    for (int i = 0; i<query; ++i){
        os<<2<<' '<<(rand()%(nums))<<'\n';
    }
    return 0;
}
