#define _CRT_SECURE_NO_WARNINGS 1
#include "DPLL.h"
#include "solver.h"
int solver(CNF * mCNF){
    initPLE(mCNF);
    addStack();
    startTime = clock();
    int choosedLetter=ChooseVariable(AllTop->mStack,mCNF);
    //先将第一个选择的字母赋值为真，看结果
    int res1=DPLL(AllTop->mStack,choosedLetter,TRUE,mCNF);
    if (res1 == TRUE || res1 == TIMEOUT) {
        return res1;
    }
    recoverStack(mCNF);
    //再将第一个选择的字母赋值为假，看结果
    addStack();
    int res2=DPLL(AllTop->mStack,choosedLetter,FALSE,mCNF);
    if(res2==TRUE||res2==TIMEOUT){
        return res2;
    }
    recoverStack(mCNF);
    //均为假
    return FALSE;
}