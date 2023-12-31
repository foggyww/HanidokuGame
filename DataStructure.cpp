#include "DataStructure.h"

//文字的定义
typedef struct letter
{
    //文字的序号
    int code;
    //文字的值
    int value;
}letter;



//文字列表的定义
typedef struct letterListElem {
    //当前文字列表单元的文字
    letter nowLetter;
    //指向该文字的第一个跳线节点
    jumpNode firstJumpNode;
    //该文字目前在子句中含有的个数
    int nowNum;
}letterListElem, * letterListNode;




//跳线节点的定义
typedef struct jumpElem
{
    //该跳线节点对应的文字列表单元
    letterListNode letterListNode;
    //该跳线节点对应的子句单元
    clauseElemNode clauseElemNode;
    //前后跳线节点
    jumpElem* priorJumpNode;
    jumpElem* nextJumpNode;

}jumpElem, * jumpNode;



//子句单元的定义
typedef struct clauseElem
{
    //当前子句单元的文字编号
    int code;
    //当前子句单元所在子句的编号
    int clauseCode;
    //当前字句单元前后的节点
    clauseElem* nextElemNode;
    clauseElem* priorElemNode;
    //指向该文字的跳线节点
    jumpNode jumpNode;
}clauseElem, * clauseElemNode;



//子句的定义
typedef struct clause
{
    //子句编号
    int code;
    //子句的第一个文字
    clauseElemNode firstElem;
    //子句的文字数
    int elemNum;
    //是否被删除
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
    //原先该位置指针的值
    int origin;
    //指针所在位置
    int* location;
    //栈的下一个元素
    clauseStack* next;
}clauseStack, * clauseStackTop;

typedef struct jumpStack {
    //原先该位置指针的值
    jumpNode origin;
    //指针所在位置
    jumpNode* location;
    //栈的下一个元素
    jumpStack* next;
}jumpStack, * jumpStackTop;

typedef struct numStack {
    //数字所在位置
    int* location;
    //栈的下一个元素
    numStack* next;
}numStack, * numStackTop;

typedef struct ElemStack {
    //原先该位置指针的值
    clauseElemNode origin;
    //指针所在位置
    clauseElemNode* location;
    //栈的下一个元素
    ElemStack* next;
}ElemStack, * ElemStackTop;

typedef struct valueStack {
    //指针所在位置
    int* location;
    //栈的下一个元素
    valueStack* next;
}valueStack, * valueStackTop;

typedef struct clauseElemNumStack {
    //数字所在位置
    int* location;
    //栈的下一个元素
    clauseElemNumStack* next;
}clauseElemNumStack, * clauseElemNumStackTop;

//每一层的指针栈
typedef struct floorStack
{
    //所删除子句的指针记录栈
    //栈顶
    clauseStackTop clauseTop;
    //删除子句的数量
    int deletedClauseNum;
    //所删除跳线节点的指针记录栈
    //栈顶
    jumpStackTop jumpTop;
    //所删除数字的指针记录栈
    //栈顶
    numStackTop numTop;
    //所删除子句节点的指针记录栈
    //栈顶
    ElemStackTop elemTop;
    //文字值栈
    valueStackTop valueTop;
    //句子长度栈
    clauseElemNumStackTop clauseElemNumTop;
}floorStack;



typedef struct allStack {
    floorStack* mStack;
    allStack* next;
}allStack, * allTop;

