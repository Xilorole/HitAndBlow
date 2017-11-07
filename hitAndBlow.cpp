//
// Created by niwan on 10/31/2017.
//

#include <iostream>
#include <random>
#include <cstring>
#include <time.h>

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


class Questioner{
    int thinkingNumber[digit];
    mt19937 mt;
public:
    int cleared;
    bool isCleared;
    void generate();
    void print();
    void print(int* data);
    int* check(int checkNum, int *data);
    int* check(int *checkNumDigit, int *data);

    Questioner();
    //�w��̐������m����������
    void swap(int d1,int d2,int *ptr);
    void convertIntToArray(int number, int *arrayPtr);
};

//�R���X�g���N�^�B�����ɐ���ێ�����B
Questioner::Questioner() {
    mt19937 mt(0);
    isCleared=false;
    cleared = 0;
    int set = mt() % (int) pow(10, digit);
    for (int i = 0; i < digit; i++) {
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
        for (int i = 0; i < digit; i++) {
            thinkingNumber[digit-i-1] = set % 10;
            set /= 10;
        }
        printf("#cleared. generation succeeded.\n");
        isCleared = false;
        cleared++;
    }else{
        printf("#uncleared. generation failed.\n");
    }
}

//Questioner�ɑ΂��đz�肵�Ă������print����悤�ɖ��߂���B
void Questioner::print() {
    for (int i = 0; i < digit; i++) {
        printf("%d",thinkingNumber[i]);
    }
    printf("\n");
}

//check�̕Ԃ�l�Ƃ��ē�����data�𓊂���Ƃ�����ۂ��\�����Ă����B
void Questioner::print(int* data){
    printf("%d:%dhit(s) %dblow(s)\n",data[2],data[0],data[1]);
}

//�z��`���ŗ^����ꂽptr��d1�Ԗڂ�d2�Ԗڂ��X���b�v����B
void Questioner::swap(int d1,int d2,int *ptr){
    int temp = ptr[d1];
    ptr[d1] = ptr[d2];
    ptr[d2] = temp;
}

//arrayPtr��number��z�񉻂������̂𓊂�����
void Questioner::convertIntToArray( int number,int *arrayPtr){
    for (int i = 0; i < digit; i++) {
        arrayPtr[digit-i-1] = number % 10;
        number /= 10;
    }
}

//�z��checkNumDigit���`�F�b�N����Bchecker�Ɍ��ʂ𓊂����ށB
int *Questioner::check(int *checkNumDigit, int *data) {
    //data[0]:hit(s) data[1]:blow(s)

    int checkNum = checkNumDigit[0];
    for (int j = 1; j < digit; j++) {
        checkNum *= 10;
        checkNum += checkNumDigit[j];
    }
    cout << checkNum << endl;
    int cp = checkNum;

    data[0]=0;data[1]=0;data[2]=checkNum;
    int digitRecorder[10] = {0};
    for (int i = 0; i < digit; i++) {
        digitRecorder[thinkingNumber[i]]++;
        if (checkNumDigit[i] == thinkingNumber[i]) {
            data[0]++;
            checkNumDigit[i] = -1;
            digitRecorder[thinkingNumber[i]]--;
        }
    }
    for (int i = 0; i < digit; i++) {
        if (checkNumDigit[i] == -1)continue;
        if (digitRecorder[checkNumDigit[i]] > 0) {
            digitRecorder[checkNumDigit[i]]--;
            data[1]++;
        }
    }
    if(data[0]==digit){
        printf("<matched:%d>\n",cp);
        isCleared=true;
    }
    return data;
}

//���ׂ�������checkNum��n���ƌ��ʂ��A���Ă���Bchecker�Ɍ��ʂ𓊂����ށB
int *Questioner::check(int checkNum, int *data) {
    //data[0]:hit(s) data[1]:blow(s)
    int cp = checkNum;

    data[0]=0;data[1]=0;data[2]=checkNum;
    int digitRecorder[10] = {0};

    int checkNumDigit[digit];
    Questioner::convertIntToArray(checkNum,checkNumDigit);

    for (int i = 0; i < digit; i++) {
        digitRecorder[thinkingNumber[i]]++;
        if (checkNumDigit[i] == thinkingNumber[i]) {
            data[0]++;
            checkNumDigit[i] = -1;
            digitRecorder[thinkingNumber[i]]--;
        }
    }
    for (int i = 0; i < digit; i++) {
        if (checkNumDigit[i] == -1)continue;
        if (digitRecorder[checkNumDigit[i]] > 0) {
            digitRecorder[checkNumDigit[i]]--;
            data[1]++;
        }
    }
    if(data[0]==digit){
        printf("<matched:%d>\n",cp);
        isCleared=true;
    }
    return data;
}

int main(){
    Questioner q;
    int data[3];
    viewable = true;

    clock_t start = clock();


    sampleAlgorithm(q,data);
    //sampleAlgorithm2(q, data);

    //myAlgorithm(q,data);


    clock_t end = clock();
    std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";

}



//�����̃A���S���Y���͂����ɂ������I
void myAlgorithm(Questioner q,int *data){

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

}