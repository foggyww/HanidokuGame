#pragma once

#ifndef Fun_H

#define Fun_H
#include "DataStructure.h"
//��ʼ������
 void initLetter(letter* tarNode, int code);
//��ʼ�������б�
void initLetterListElem(letterListNode tarNode, int code);
//��ʼ�����߽ڵ�
void initJumpElem(jumpNode tarNode);
//��ʼ���Ӿ䵥Ԫ
void initClauseElem(clauseElemNode tarNode, int code, int clauseCode);
//��ʼ���Ӿ�
void initClause(clauseNode tarNode, int code);
//��ʼ��CNF�ļ�
void initCNF(CNF* mCNF, int clauseNum, int letterNum);
//��ʼ��ָ��ջ
void initStack(floorStack* tarStack);
//���ָ��ջ
void addStack();
//�����ļ�
CNF* loadFile(const char FileName[100]);
//����CNF
CNF* createCNF(FILE* fp);
//��ȡ��Ԫ
void addListElem(int code, CNF* mCNF);
//��ָ�����Ӿ䵥Ԫ�ӵ�������
void addToJump(clauseElemNode mClauseElemNode, int letterCode, CNF* mCNF);
//��ȡ�Ӿ�
void addClause(int Clausecode, CNF* mCNF, FILE* fp);
//��ָ��λ�õ�ԭ�Ӿ�ָ��ѹ��ջ
void pushClause(floorStack* mStack, int origin, int* location);
//��ָ��λ�õ�ԭ����ָ��ѹ��ջ
void pushJump(floorStack* mStack, jumpNode origin, jumpNode* location);
//��ָ��λ�õ�ԭ�Ӿ䵥Ԫָ��ѹ��ջ
void pushElem(floorStack* mStack, clauseElemNode origin, clauseElemNode* location);
//���ı���ֵ������ѹ��ջ
void pushValue(floorStack* mStack, int letterCode, CNF* mCNF);
//����Ԫ�����ĸı�ѹ��ջ
void pushLetterNum(floorStack* mStack, int* location);
//���Ӿ������ĸı�ѹ��ջ
void pushClauseElemNum(floorStack* mStack, int* location);
//��ʼɾ������
void initDeleteJump(jumpNode nowJump);
//ɾ�����ߵ�Ԫ����������ѹ��ջ
void deleteJump(floorStack* mStack, jumpNode nowJump);
//��ʼɾ���Ӿ�
void initDeleteClause(int clauseCode, CNF* mCNF);
//ɾ���Ӿ�
void deleteClause(int clauseCode, floorStack* mStack, CNF* mCNF);
//ɾ���Ӿ��һ����Ԫ
int deleteElem(clauseElemNode elemNode, floorStack* mStack, CNF* mCNF);
//��λ�Ӿ䴫��
int UP(int tarCode, int TorF, floorStack* mStack, CNF* mCNF);
//��ʼ��������ɾȥ
int initPLE(CNF* mCNF);
//����������ȥ
int PLE(floorStack* mStack, CNF* mCNF);
//ѡ����һ����ֵ����ĸ
int ChooseVariable(floorStack* mStack, CNF* mCNF);
//�ָ��Ӿ�
void recoverClause(CNF* mCNF, floorStack* mStack);
//�ָ����ߵ�Ԫ
void recoverJump(floorStack* mStack);
//�ָ��Ӿ䵥Ԫ
void recoverElem(floorStack* mStack);
//�ָ���ĸ��ֵ
void recoverValue(CNF* mCNF, floorStack* mStack);
//�ָ���ĸ����
void recoverLetterNum(floorStack* mStack);
//�ָ��Ӿ䵥Ԫ����
void recoverClauseElemNum(floorStack* mStack);
//����ָ��ջ�ָ�һ��Ĳ���
void recoverStack(CNF* mCNF);
//�����������
int DPLL(floorStack* mStack, int choosedLetter, int TorF, CNF* mCNF);

#endif // !Fun_H