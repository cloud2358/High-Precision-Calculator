#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int N;

int main() {
    cout<<"Rec count: ";
    cin>>N;
    double Pi = 0;
    for (int i = 1; i <= N; i++) {
        double t = 2 * i - 1;
        if (i & 1) {
            Pi += 4.0 / i;
        }
        else {
            Pi -= 4.0 / i;
        }
        cout<<"Current Pi: "<<Pi<<"\r"<<flush;
    }
    cout<<endl<<"Final Pi: "<<Pi<<endl;
    return 0;
}