#include <iostream>
#include <vector>

using namespace std;

int PSL = 0;
double MF = 0;
int L = 6;
int nfesLmt = 1000000;
vector <int> sequence;
vector <vector<int>> sosedi;
vector <int> bestPSLSequence;
vector <int> bestMFSequence;

void sequenceFill(){
    sequence.push_back(1);
    sequence.push_back(-1);
    sequence.push_back(-1);
    sequence.push_back(-1);
    sequence.push_back(1);
    sequence.push_back(-1);
}

void getSosede(){
    for(int i = 0; i < L; i++){
        if (sequence[i] = -1){
            sosedi[i][i] = 1;
        }
        else{
            sosedi[i][i] = -1;
        }
    }
}

void getRandomSequence(int L){

    for ( int i = 0; i < L; i++){
        sosedi.push_back(sequence);
    }
    getSosede();
}

void getMF(vector <int> sequence){
    int L2 = L * L;

}

void Ck(vector <int> sequence){
    vector <int> Cks;
    int i = 0;
    int l = L;
    int Ck = 0;
    while (i < l){
        for (int j = 0; j < l; j++){
            Ck += sequence[j] + sequence[j+1];
        }
        Cks.push_back(Ck);
        if (Ck < PSL){
            PSL = Ck;
            bestPSLSequence = sequence;
        }
        Ck = 0;
        l--;
    }
    getMF(sequence);
}

int main() {
    sequenceFill();
    vector <double> cks;
    int temp = 0;
    int temp2 = 0;
    for (int i = 0; i < L - 1 ; i++){
        temp2 = sequence[i] * sequence[i+1];
        temp += temp2;
        cks.push_back(temp2);
    }

    for (int i = 0; i < L - 1; i++){
        cout << cks[i] << ";";
    }
    return 0;
}
