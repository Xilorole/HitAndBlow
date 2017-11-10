//
// Created by niwan on 2017/11/10.
//

#include <iostream>
#include <random>
#include <ctime>
using namespace std;


class Questioner{
    int digit=0;
    int thinkingNumber = 0;
public:
    vector<int> vec;
    int* check(int checkNum, int *data);
    void checkModule(int checkNum,int *checkNumDigit,int *data);
    void set(int number);
    Questioner(int _digit);
    //指定の数字同士を交換する
    void convertIntToArray(int number, int *arrayPtr);
};

//コンストラクタ。内部に数を保持する。
Questioner::Questioner(int _digit) {
    digit = _digit;
    for (int i = 0; i < digit; ++i) {
        vec.push_back(i);
    }
}

//arrayPtrにnumberを配列化したものを投げ込む
void Questioner::convertIntToArray( int number,int *arrayPtr){
    for (auto e:vec) {
        arrayPtr[digit-e-1] = number % 10;
        number /= 10;
    }
}

//調べたい数字checkNumを渡すと結果が帰ってくる。checkerに結果を投げ込む。
int *Questioner::check(int checkNum, int *data) {
    int checkNumDigit[digit];
    Questioner::convertIntToArray(checkNum,checkNumDigit);
    Questioner::checkModule(checkNum, checkNumDigit, data);
    return data;
}

void Questioner::checkModule(int checkNum, int *checkNumDigit, int *data) {
    int digitRecorder[10] = {0};
    data[0]=0;data[1]=0;data[2]=checkNum;

    int thinkingNumDigit[digit];
    Questioner::convertIntToArray(thinkingNumber,thinkingNumDigit);

    for (auto i:vec) {
        digitRecorder[thinkingNumDigit[i]]++;
        if (checkNumDigit[i] == thinkingNumDigit[i]) {
            data[0]++;
            checkNumDigit[i] = -1;
            digitRecorder[thinkingNumDigit[i]]--;
        }
    }
    for (auto i:vec) {
        if (checkNumDigit[i] == -1)continue;
        if (digitRecorder[checkNumDigit[i]] > 0) {
            digitRecorder[checkNumDigit[i]]--;
            data[1]++;
        }
    }
}

void Questioner::set(int number) {
    thinkingNumber = number;
}

int main() {
    int count=0;
    int digits=4;
    mt19937 mt(static_cast<unsigned int>(time(nullptr)));
    int first = mt() % (int)pow(10,digits);
    int hits,blows;
    Questioner q(digits);
    vector<int> vec;
    int data[3] ={0};

    cout << "#Hit and Blow Game\n"
            "/Think about 4 digit Number.\n"
            "/This machine would ask a number which it estimates what you are thinking of.\n"
            "/Please reply how many hits and blows there are in following format.\n"
            "/format:[hits](space)[blows]\n"
            "/e.g.) '2 0'\n" << endl;

    cout << "How is "  << first << " : ";
    cin >> hits >> blows ;
    count++;


    q.set(first);


    for(int i=0;i<pow(10,digits);i++) {
        q.check(i, data);
        if (data[0] == hits && data[1] == blows && i != first){
            vec.push_back(i);
        }
    }

    while (true) {
        vector<int> _vec = vec;
        vec.clear();

        first = _vec[(int) (mt()%_vec.size())];
        q.set(first);

        cout << "How is " << first << " : ";
        cin >> hits >> blows;
        count++;

        if (hits == digits) {
            cout << "yay! My score was "<< count <<" times!" << endl;
            break;
        } else {
            for (auto v:_vec) {
                q.check(v, data);
                if (data[0] == hits && data[1] == blows && v != first) {
                    vec.push_back(v);
                }
            }
            cout << "Candidate #: "<<vec.size() <<endl;
        }
    }
    system ("pause");
}