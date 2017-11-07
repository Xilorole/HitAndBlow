//
// Created by niwan on 10/31/2017.
//

#include <iostream>
#include <random>
#include <cstring>
#include <ctime>

//printf�Œ�`����镔���Ɋւ��Ă͕ϐ���viewable��؂�ւ��邱�Ƃŕ`�悷��E���Ȃ���ύX�ł���悤�ɂ��Ă���܂�
//��̓I�ɂ̓N���XQuestioner�̓����̃��\�b�h�̃��O������ɓ�����܂��B
#define printf if(viewable)printf

using namespace std;

//����g�p���闐���̐����͈́B�����B4�Ȃ�0000����9999�܂Ő�������B
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
    //�w��̐������m����������
    void convertIntToArray(int number, int *arrayPtr);
};

//�R���X�g���N�^�B�����ɐ���ێ�����B
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

//Questioner�ɑ΂��ė����̐������߂��o���B
//�N���A���isCleared���^�łȂ��ꍇ�ɌĂԂƃG���[���b�Z�[�W���o�āA�V���Ȃ��̂𐶐��ł��Ȃ��B
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

//Questioner�ɑ΂��đz�肵�Ă������print����悤�ɖ��߂���B
void Questioner::print() {
    for (auto e:thinkingNumber) {
        printf("%d",e);
    }
    printf("\n");
}

void Questioner::result() {
    cout << "average moves : " << (double)moves/cleared << endl;
}

//check�̕Ԃ�l�Ƃ��ē�����data�𓊂���Ƃ�����ۂ��\�����Ă����B
void Questioner::print(int* data){
    printf("%d:%dhit(s) %dblow(s)\n",data[2],data[0],data[1]);
}

//�z��`���ŗ^����ꂽptr��d1�Ԗڂ�d2�Ԗڂ��X���b�v����B
void swap(int d1,int d2,int *ptr){
    int temp = ptr[d1];
    ptr[d1] = ptr[d2];
    ptr[d2] = temp;
}

//arrayPtr��number��z�񉻂������̂𓊂�����
void Questioner::convertIntToArray( int number,int *arrayPtr){

    for (auto e:vec) {
        arrayPtr[digit-e-1] = number % 10;
        number /= 10;
    }
}

//�z��checkNumDigit���`�F�b�N����Bchecker�Ɍ��ʂ𓊂����ށB
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

//���ׂ�������checkNum��n���ƌ��ʂ��A���Ă���Bchecker�Ɍ��ʂ𓊂����ށB
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



//�����̃A���S���Y���͂����ɂ������I
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




//3000�ɑ΂��Ėԗ��I�T��������
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

//�L�q���@�̃T���v���Ȃ�
void sampleAlgorithm(Questioner q, int *data) {
    //SAMPLE CODE

    int set;


    set =1111;
    q.check(set,data);
    //set���m�F����B
    //data[0]���q�b�g�̐��Adata[1]���u���[�̐����󂯎��B

    q.print(data);

    q.check(set = 1678,data);
    q.print(data);

    //.generate()�͐V�����������l���Ă��炤�B����������ԂłȂ��Ƃ��܂������Ȃ��B
    q.generate();


    //�z��data��Ԃ��̂ł��̂悤�ȋL�q�����Ă�ok
    q.print(q.check(set = 1781,data));


    //���������̂ł��܂�����
    q.generate();



    q.check(set=1772,data);
    q.print(data);

    q.check(set = 1555,data);
    q.print(data);

    q.check(1568,data);
    q.print(data);

    q.result();
}