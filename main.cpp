#include <iostream>
#include <vector>

using namespace std;

int PSL = 0;
double MF = 0;
int l = 6;
vector <int> sequence;

void sequenceFill(){
    sequence.push_back(1);
    sequence.push_back(-1);
    sequence.push_back(-1);
    sequence.push_back(-1);
    sequence.push_back(1);
    sequence.push_back(-1);
}

int main() {
    sequenceFill();
    vector <double> cks;
    int temp = 0;
    int temp2 = 0;
    for (int i = 0; i < l - 1 ; i++){
        temp2 = sequence[i] * sequence[i+1];
        temp += temp2;
        cks.push_back(temp2);
    }

    for (int i = 0; i < l - 1; i++){
        cout << cks[i] << ";";
    }
    return 0;
}
