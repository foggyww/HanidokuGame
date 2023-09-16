#ifndef DataS_H

#define DataS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <graphics.h>
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_SIZE 2000
#define TRUE 1
#define FALSE -1
#define UNDEFINE 0
#define TIMEOUT 0
#define EASY 1
#define HARD 2

#define ForLine(line) for(line=1;line<=9;line++)
#define ForRow(line,row) for(row=1;row<=9-abs(5-line);row++)
#define CODE(code,num) ((code*10)+num)
//�����ṹ��
typedef struct letter letter;
typedef struct letterListElem letterListElem,* letterListNode;
typedef struct jumpElem jumpElem,*jumpNode;
typedef struct clause clause,*clauseNode;
typedef struct clauseElem clauseElem,*clauseElemNode;
typedef struct CNF CNF;
typedef struct clauseStack clauseStack,*clauseStackTop;
typedef struct jumpStack jumpStack, *jumpStackTop;
typedef struct numStack numStack, *numStackTop;
typedef struct ElemStack ElemStack, * ElemStackTop;
typedef struct valueStack valueStack, *valueStackTop;
typedef struct clauseElemNumStack clauseElemNumStack, * clauseElemNumStackTop;
typedef struct floorStack floorStack;
typedef struct allStack allStack, * allTop;
//���ֵĶ���
typedef struct letter 
{
    //���ֵ����
    int code;  
    //���ֵ�ֵ
    int value;
}letter;



//�����б�Ķ���
typedef struct letterListElem{ 
    //��ǰ�����б�Ԫ������
    letter nowLetter; 
    //ָ������ֵĵ�һ�����߽ڵ�
    jumpNode firstJumpNode;
    //������Ŀǰ���Ӿ��к��еĸ���
    int nowNum;
}letterListElem,*letterListNode;




//���߽ڵ�Ķ���
typedef struct jumpElem
{
    //�����߽ڵ��Ӧ�������б�Ԫ
    letterListNode letterListNode;
    //�����߽ڵ��Ӧ���Ӿ䵥Ԫ
    clauseElemNode clauseElemNode;
    //ǰ�����߽ڵ�
    jumpElem * priorJumpNode;
    jumpElem * nextJumpNode;

}jumpElem,*jumpNode;



//�Ӿ䵥Ԫ�Ķ���
typedef struct clauseElem
{
    //��ǰ�Ӿ䵥Ԫ�����ֱ��
    int code;
    //��ǰ�Ӿ䵥Ԫ�����Ӿ�ı��
    int clauseCode;
    //��ǰ�־䵥Ԫǰ��Ľڵ�
    clauseElem * nextElemNode;
    clauseElem * priorElemNode;
    //ָ������ֵ����߽ڵ�
    jumpNode jumpNode;
}clauseElem,*clauseElemNode;



//�Ӿ�Ķ���
typedef struct clause
{
    //�Ӿ���
    int code;
    //�Ӿ�ĵ�һ������
    clauseElemNode firstElem;
    //�Ӿ��������
    int elemNum;
    //�Ƿ�ɾ��
    int deleted;
}clause;





typedef struct CNF
{
    letterListElem letterList[2000];
    clause clauseList[20000];
    int letterNum;
    int clauseNum;
    int originClauseNum;
}CNF;



typedef struct clauseStack {
    //ԭ�ȸ�λ��ָ���ֵ
    int origin;
    //ָ������λ��
    int* location;
    //ջ����һ��Ԫ��
    clauseStack* next;
}clauseStack, * clauseStackTop;

typedef struct jumpStack {
    //ԭ�ȸ�λ��ָ���ֵ
    jumpNode origin;
    //ָ������λ��
    jumpNode* location;
    //ջ����һ��Ԫ��
    jumpStack* next;
}jumpStack, * jumpStackTop;

typedef struct numStack {
    //��������λ��
    int* location;
    //ջ����һ��Ԫ��
    numStack* next;
}numStack, * numStackTop;

typedef struct ElemStack {
    //ԭ�ȸ�λ��ָ���ֵ
    clauseElemNode origin;
    //ָ������λ��
    clauseElemNode* location;
    //ջ����һ��Ԫ��
    ElemStack* next;
}ElemStack, * ElemStackTop;

typedef struct valueStack {
    //ָ������λ��
    int* location;
    //ջ����һ��Ԫ��
    valueStack* next;
}valueStack, * valueStackTop;

typedef struct clauseElemNumStack {
    //��������λ��
    int* location;
    //ջ����һ��Ԫ��
    clauseElemNumStack* next;
}clauseElemNumStack, * clauseElemNumStackTop;

//ÿһ���ָ��ջ
typedef struct floorStack
{
    //��ɾ���Ӿ��ָ���¼ջ
    //ջ��
    clauseStackTop clauseTop;
    //ɾ���Ӿ������
    int deletedClauseNum;
    //��ɾ�����߽ڵ��ָ���¼ջ
    //ջ��
    jumpStackTop jumpTop;
    //��ɾ�����ֵ�ָ���¼ջ
    //ջ��
    numStackTop numTop;
    //��ɾ���Ӿ�ڵ��ָ���¼ջ
    //ջ��
    ElemStackTop elemTop;
    //����ֵջ
    valueStackTop valueTop;
    //���ӳ���ջ
    clauseElemNumStackTop clauseElemNumTop;
}floorStack;



typedef struct allStack {
    floorStack* mStack;
    allStack* next;
}allStack, * allTop;

extern allTop AllTop ;
extern int count;
extern int mTime;
extern CNF answerCNF;
extern long nowTime;
extern long startTime;

#endif // !DataS_H