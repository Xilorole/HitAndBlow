//
// Created by niwan on 10/31/2017.
//

#include <iostream>
#include <random>
#include <cstring>
#include <ctime>

//printfで定義される部分に関しては変数のviewableを切り替えることで描画する・しないを変更できるようにしてあります
//具体的にはクラスQuestionerの内部のメソッドのログがそれに当たります。
#define printf if(viewable)printf

using namespace std;

//今回使用する乱数の生成範囲。桁数。4なら0000から9999まで生成する。
const static int digit = 4;

static bool viewable;
class Questioner;
void sampleAlgorithm2(Questioner q, int *data);
void sampleAlgorithm(Questioner q, int *data);
void myAlgorithm(Questioner q, int *data);
void swap(int d1,int d2,int *ptr);


class Questioner{
    int thinkingNumber[digit]={0};
    mt19937 mt;

public:
    vector<int> vec;
    int cleared;
    int moves;
    bool isCleared;
    void generate();
    void print();
    void result();
    void print(int* data);
    int* check(int checkNum, int *data);
    int* check(int *checkNumDigit, int *data);
    void checkModule(int checkNum,int *checkNumDigit,int *data);
    Questioner();
    //指定の数字同士を交換する
    void convertIntToArray(int number, int *arrayPtr);
};

//コンストラクタ。内部に数を保持する。
Questioner::Questioner() {
    for (int i = 0; i < digit; ++i) {
        vec.push_back(i);
    }
    mt19937 mt(0);
    isCleared=false;
    cleared = 0;
    moves =0;
    int set = mt() % (int) pow(10, digit);
    for (auto& i:vec) {
        thinkingNumber[digit-i-1] = set % 10;
        set /= 10;
    }
    printf("<generated>\n");
}

//Questionerに対して乱数の生成命令を出す。
//クリア状態isClearedが真でない場合に呼ぶとエラーメッセージが出て、新たなものを生成できない。
void Questioner::generate(){
    if(isCleared) {
        int set = mt() % (int) pow(10, digit);
        for (auto e:vec) {
            thinkingNumber[digit-e-1] = set % 10;
            set /= 10;
        }
        printf("#cleared. generation succeeded.\n");
        isCleared = false;
    }else{
        printf("#uncleared. generation failed.\n");
    }
}

//Questionerに対して想定している問題をprintするように命令する。
void Questioner::print() {
    for (auto e:thinkingNumber) {
        printf("%d",e);
    }
    printf("\n");
}

void Questioner::result() {
    cout << "average moves : " << (double)moves/cleared << endl;
}

//checkの返り値として得られるdataを投げるとそれっぽく表示してくれる。
void Questioner::print(int* data){
    printf("%d:%dhit(s) %dblow(s)\n",data[2],data[0],data[1]);
}

//配列形式で与えられたptrのd1番目とd2番目をスワップする。
void swap(int d1,int d2,int *ptr){
    int temp = ptr[d1];
    ptr[d1] = ptr[d2];
    ptr[d2] = temp;
}

//arrayPtrにnumberを配列化したものを投げ込む
void Questioner::convertIntToArray( int number,int *arrayPtr){

    for (auto e:vec) {
        arrayPtr[digit-e-1] = number % 10;
        number /= 10;
    }
}

//配列checkNumDigitをチェックする。checkerに結果を投げ込む。
int *Questioner::check(int *checkNumDigit, int *data) {
    int checkNum = 0;
    for (auto j:vec) {
        checkNum += checkNumDigit[j];
        checkNum *= 10;
    }
    checkNum/=10;
    Questioner::checkModule(checkNum, checkNumDigit, data);
    return data;
}

//調べたい数字checkNumを渡すと結果が帰ってくる。checkerに結果を投げ込む。
int *Questioner::check(int checkNum, int *data) {
    int checkNumDigit[digit];
    Questioner::convertIntToArray(checkNum,checkNumDigit);
    Questioner::checkModule(checkNum, checkNumDigit, data);
    return data;
}

void Questioner::checkModule(int checkNum, int *checkNumDigit, int *data) {
    moves++;
    int digitRecorder[10] = {0};
    data[0]=0;data[1]=0;data[2]=checkNum;
    for (auto i:vec) {
        digitRecorder[thinkingNumber[i]]++;
        if (checkNumDigit[i] == thinkingNumber[i]) {
            data[0]++;
            checkNumDigit[i] = -1;
            digitRecorder[thinkingNumber[i]]--;
        }
    }
    for (auto i:vec) {
        if (checkNumDigit[i] == -1)continue;
        if (digitRecorder[checkNumDigit[i]] > 0) {
            digitRecorder[checkNumDigit[i]]--;
            data[1]++;
        }
    }
    if(data[0]==digit){
        printf("<matched:%d>\n",checkNum);

        isCleared=true;
        cleared++;
    }
}

int main(){
    Questioner q;
    int data[3];
    viewable = true;

    clock_t start = clock();


    //sampleAlgorithm(q,data);
    //sampleAlgorithm2(q, data);

    myAlgorithm(q,data);


    clock_t end = clock();
    std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";

}



//自分のアルゴリズムはここにかこう！
void myAlgorithm(Questioner q,int *data){

    int checkNumDigit[4];
    q.check(1123,data);
    q.print(data);
    q.convertIntToArray(1123,checkNumDigit);

    swap(1,2,checkNumDigit);
    q.check(checkNumDigit,data);
    q.print(data);

    q.result();
}




//3000個に対して網羅的探索をする
void sampleAlgorithm2(Questioner q, int *data){
    for (int j = 0; j < 3000; j++) {
        for (int i = 0; i < pow(10,digit); ++i) {
            q.check(i,data);
            //q.print(data);
            if(data[0]==digit) {
                q.generate();
                break;
            }
        }
    }
}

//記述方法のサンプルなど
void sampleAlgorithm(Questioner q, int *data) {
    //SAMPLE CODE

    int set;


    set =1111;
    q.check(set,data);
    //setを確認する。
    //data[0]がヒットの数、data[1]がブローの数を受け取る。

    q.print(data);

    q.check(set = 1678,data);
    q.print(data);

    //.generate()は新しい数字を考えてもらう。当たった状態でないとうまくいかない。
    q.generate();


    //配列dataを返すのでこのような記述をしてもok
    q.print(q.check(set = 1781,data));


    //当たったのでうまくいく
    q.generate();



    q.check(set=1772,data);
    q.print(data);

    q.check(set = 1555,data);
    q.print(data);

    q.check(1568,data);
    q.print(data);

    q.result();
}