#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono;

int PSL = 9999;
double MF = 0;
int L = 2501;
int nfesLmt = 1000000;
int nfes = 0;
int seed = 0;
int threads = 0;
vector <int> sequence;
vector <vector<int>> sosedi;
vector <vector<int>> kandidati;
vector <int> bestPSLSequence;
vector <int> bestMFSequence;
mutex myMutex;

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
    kandidati.push_back(sosedi[0]);
    for(int i = 1; i <= L; i++){
        if (sequence[i-1] == -1){
            sosedi[i][i-1] = 1;
        }
        else{
            sosedi[i][i-1] = -1;
        }
        //try {
        //    kandidati.push_back(sosedi[i]);
        //}catch (bad_alloc){
        //    cout << "Ran out of memory!" << nfes << endl;
        //}
    }
    //sosedi.clear();
}

void randomize(){
    random_device rd;
    mt19937 mt(seed+nfes);
    uniform_int_distribution<int> dist(0,1);
    for ( int i = 0; i < L; i++){
        sequence.push_back(dist(mt));
    }
    for ( int i = 0; i < L; i++){
        if(sequence[i] == 0){
            sequence[i] = -1;
        }
    }
    //for (auto it = sequence.begin(); it != sequence.end(); ++it)
    //    cout << ' ' << *it;
    //cout << endl;
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
        myMutex.lock();
        PSL = ckHigh;
        bestPSLSequence = sequence;
        myMutex.unlock();
    }
    //getMF(sequence, ckVsota);
}

void threadRun(int from, int to){
    while (from < to){
        Ck(sosedi[from]);
        from++;
    }
}

void exeThreads(int threads){
    vector<thread>guide;
    int from = 0;
    int to = L/threads-1;
    int multi = L/threads;
    for (int i = 0; i < threads; i++){
        guide.push_back(thread (threadRun, from, to));
        from = to+1;
        to += multi;
    }
    for (int i = 0; i < threads; i++){
        guide[i].join();
    }
    for (int i = 0; i < threads; i++){
        guide.pop_back();
    }
}

void getRandomSequence(int L){
    while (nfes < nfesLmt){
        randomize();
        for ( int i = 0; i <= L; i++){
            if(nfes < nfesLmt){
                sosedi.push_back(sequence);
                nfes++;
            }
        }
        getSosede();
        exeThreads(threads);
        cout <<endl<< "nfes: "<<nfes<< endl;
        cout << "\n" << "best PSL: " << PSL;
        sequence.clear();
        sosedi.clear();
    }
    //for (int i = 0; i < 22; i++){
    //    for (int j = 0; j < L; j++){
    //        cout << kandidati[i][j] <<", ";
    //    }
    //    cout << endl;
    //}
}

int main() {
    cout << "enter seed: " << endl;
    cin >> seed;
    cout << "enter threads: " << endl;
    cin >> threads;
    //sequenceFill();
    auto start = high_resolution_clock::now();
    getRandomSequence(L);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Duration in seconds:" << duration.count() << endl;
    //Ck(sequence);
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
    cout << "\n" << "best PSL: " << PSL;
    cout << "dela";
    return 0;
}
