#pragma once

#ifndef Fun_H

#define Fun_H
#include "DataStructure.h"
//初始化文字
 void initLetter(letter* tarNode, int code);
//初始化文字列表
void initLetterListElem(letterListNode tarNode, int code);
//初始化跳线节点
void initJumpElem(jumpNode tarNode);
//初始化子句单元
void initClauseElem(clauseElemNode tarNode, int code, int clauseCode);
//初始化子句
void initClause(clauseNode tarNode, int code);
//初始化CNF文件
void initCNF(CNF* mCNF, int clauseNum, int letterNum);
//初始化指针栈
void initStack(floorStack* tarStack);
//添加指针栈
void addStack();
//载入文件
CNF* loadFile(const char FileName[100]);
//创建CNF
CNF* createCNF(FILE* fp);
//读取变元
void addListElem(int code, CNF* mCNF);
//将指定的子句单元加到跳线内
void addToJump(clauseElemNode mClauseElemNode, int letterCode, CNF* mCNF);
//读取子句
void addClause(int Clausecode, CNF* mCNF, FILE* fp);
//将指定位置的原子句指针压入栈
void pushClause(floorStack* mStack, int origin, int* location);
//将指定位置的原跳线指针压入栈
void pushJump(floorStack* mStack, jumpNode origin, jumpNode* location);
//将指定位置的原子句单元指针压入栈
void pushElem(floorStack* mStack, clauseElemNode origin, clauseElemNode* location);
//将改变了值的文字压入栈
void pushValue(floorStack* mStack, int letterCode, CNF* mCNF);
//将变元数量的改变压入栈
void pushLetterNum(floorStack* mStack, int* location);
//将子句数量的改变压入栈
void pushClauseElemNum(floorStack* mStack, int* location);
//初始删除跳线
void initDeleteJump(jumpNode nowJump);
//删除跳线单元，并将操作压入栈
void deleteJump(floorStack* mStack, jumpNode nowJump);
//初始删除子句
void initDeleteClause(int clauseCode, CNF* mCNF);
//删除子句
void deleteClause(int clauseCode, floorStack* mStack, CNF* mCNF);
//删除子句的一个单元
int deleteElem(clauseElemNode elemNode, floorStack* mStack, CNF* mCNF);
//单位子句传播
int UP(int tarCode, int TorF, floorStack* mStack, CNF* mCNF);
//初始孤立文字删去
int initPLE(CNF* mCNF);
//孤立文字消去
int PLE(floorStack* mStack, CNF* mCNF);
//选择下一个赋值的字母
int ChooseVariable(floorStack* mStack, CNF* mCNF);
//恢复子句
void recoverClause(CNF* mCNF, floorStack* mStack);
//恢复跳线单元
void recoverJump(floorStack* mStack);
//恢复子句单元
void recoverElem(floorStack* mStack);
//恢复字母赋值
void recoverValue(CNF* mCNF, floorStack* mStack);
//恢复字母数量
void recoverLetterNum(floorStack* mStack);
//恢复子句单元数量
void recoverClauseElemNum(floorStack* mStack);
//利用指针栈恢复一层的操作
void recoverStack(CNF* mCNF);
//深度优先搜索
int DPLL(floorStack* mStack, int choosedLetter, int TorF, CNF* mCNF);

#endif // !Fun_H