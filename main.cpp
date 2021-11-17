#include <iostream>
#include <vector>

using namespace std;

int PSL = 9999;
double MF = 0;
int L = 8;
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
    sequence.push_back(-1);
    sequence.push_back(1);
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

void getMF(vector <int> sequence, double ckVsota){
    double L2 = L * L;
    double multi = 2;
    double mf = L2/(multi*ckVsota);
    if (mf > MF){
        MF = mf;
        bestMFSequence = sequence;
    }
    cout << "\n" <<"best MF: " << mf;
}

void Ck(vector <int> sequence){
    vector <int> Cks;
    int ck = 0;
    int ck2 = 0;
    double ckVsota = 0;
    int ckHigh = 0;
    for (int k = 1; k < L - 1; k++){
        for(int i = 0; i < L-k; i++){
            ck += sequence[i] * sequence[i+k];
        }
        cout << ck << "; ";
        if (ck <0){
            ck = -ck;
        }
        if (k > 1){
            if (ck > ckHigh){
                ckHigh = ck;
            }
        }
        ck2 = ck * ck;
        ckVsota += ck2;
        ck = 0;
    }
    if (ckHigh < PSL){
        PSL = ckHigh;
        bestPSLSequence = sequence;
    }
    getMF(sequence, ckVsota);
    cout << "\n" << "best PSL: " << PSL;
}

int main() {
    sequenceFill();
    Ck(sequence);
    //sequenceFill();
    //vector <double> cks;
    //int temp = 0;
    //int temp2 = 0;
    //for (int i = 0; i < L - 1 ; i++){
    //    temp2 = sequence[i] * sequence[i+1];
    //    temp += temp2;
    //    cks.push_back(temp2);
    //}
    //
    //for (int i = 0; i < L - 1; i++){
    //    cout << cks[i] << ";";
    //}
    return 0;
}
