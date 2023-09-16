#include "DataStructure.h"

//���ֵĶ���
typedef struct letter
{
    //���ֵ����
    int code;
    //���ֵ�ֵ
    int value;
}letter;



//�����б�Ķ���
typedef struct letterListElem {
    //��ǰ�����б�Ԫ������
    letter nowLetter;
    //ָ������ֵĵ�һ�����߽ڵ�
    jumpNode firstJumpNode;
    //������Ŀǰ���Ӿ��к��еĸ���
    int nowNum;
}letterListElem, * letterListNode;




//���߽ڵ�Ķ���
typedef struct jumpElem
{
    //�����߽ڵ��Ӧ�������б�Ԫ
    letterListNode letterListNode;
    //�����߽ڵ��Ӧ���Ӿ䵥Ԫ
    clauseElemNode clauseElemNode;
    //ǰ�����߽ڵ�
    jumpElem* priorJumpNode;
    jumpElem* nextJumpNode;

}jumpElem, * jumpNode;



//�Ӿ䵥Ԫ�Ķ���
typedef struct clauseElem
{
    //��ǰ�Ӿ䵥Ԫ�����ֱ��
    int code;
    //��ǰ�Ӿ䵥Ԫ�����Ӿ�ı��
    int clauseCode;
    //��ǰ�־䵥Ԫǰ��Ľڵ�
    clauseElem* nextElemNode;
    clauseElem* priorElemNode;
    //ָ������ֵ����߽ڵ�
    jumpNode jumpNode;
}clauseElem, * clauseElemNode;



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
    letterListElem letterList[1000];
    clause clauseList[10000];
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

