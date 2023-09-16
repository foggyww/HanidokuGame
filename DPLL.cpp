

#define _CRT_SECURE_NO_WARNINGS 1
#include "DPLL.h"
//��ʼ������
void initLetter(letter* tarNode, int code) {
    tarNode->code = code;
    tarNode->value = 0;
}
//��ʼ�������б�
void initLetterListElem(letterListNode tarNode, int code) {
    initLetter(&tarNode->nowLetter, code);
    tarNode->firstJumpNode = NULL;
    tarNode->nowNum = 0;
}
//��ʼ�����߽ڵ�
void initJumpElem(jumpNode tarNode) {
    tarNode->clauseElemNode = NULL;
    tarNode->letterListNode = NULL;
    tarNode->nextJumpNode = NULL;
    tarNode->priorJumpNode = NULL;
}
//��ʼ���Ӿ䵥Ԫ
void initClauseElem(clauseElemNode tarNode, int code, int clauseCode) {
    tarNode->code = code;
    tarNode->clauseCode = clauseCode;
    tarNode->jumpNode = NULL;
    tarNode->nextElemNode = NULL;
    tarNode->priorElemNode = NULL;
}
//��ʼ���Ӿ�
void initClause(clauseNode tarNode, int code) {
    tarNode->code = code;
    tarNode->firstElem = NULL;
    tarNode->deleted = 0;
    tarNode->elemNum = 0;
}
//��ʼ��CNF�ļ�
void initCNF(CNF* mCNF, int clauseNum, int letterNum) {
    mCNF->clauseNum = clauseNum;
    mCNF->letterNum = letterNum;
    mCNF->originClauseNum = clauseNum;
}
//��ʼ��ָ��ջ
void initStack(floorStack* tarStack) {
    tarStack->clauseTop = NULL;
    tarStack->elemTop = NULL;
    tarStack->jumpTop = NULL;
    tarStack->numTop = NULL;
    tarStack->valueTop = NULL;
    tarStack->clauseElemNumTop = NULL;
    tarStack->deletedClauseNum = 0;
}
//���ָ��ջ
void addStack() {
    allTop newTop = (allTop)malloc(sizeof(allStack));
    newTop->mStack = (floorStack*)malloc(sizeof(floorStack));
    initStack(newTop->mStack);
    newTop->next = AllTop;
    AllTop = newTop;
}


//�����ļ�
CNF * loadFile(const char FileName[100]){
    //scanf("%s",fileName);
    FILE * fp = fopen(FileName,"r");
    CNF * res = createCNF(fp);
    fclose(fp);
    return res;
}

//����CNF
CNF * createCNF(FILE * fp){
    CNF * mCNF = (CNF*)malloc(sizeof(CNF));
    char ord='\0';
    fscanf(fp,"%c",&ord);
    char ords[100];
    while(ord=='c'){
        fgets(ords,99,fp);
        fscanf(fp,"%c",&ord);
    }
    fscanf(fp,"%s",ords);
    int letterNum,clauseNum;
    fscanf(fp,"%d %d",&letterNum,&clauseNum);
    initCNF(mCNF,clauseNum,letterNum);
    for(int i=1;i<=letterNum;i++){
        addListElem(i,mCNF);
    }
    for(int i=1;i<=clauseNum;i++){
        addClause(i,mCNF,fp);
    }
    return mCNF;
}

//��ȡ��Ԫ
void addListElem(int code,CNF * mCNF){
    //��ʼ��Ŀ��ڵ�
    initLetterListElem(&mCNF->letterList[code],code);
}

//��ָ�����Ӿ䵥Ԫ�ӵ�������
void addToJump(clauseElemNode mClauseElemNode,int letterCode,CNF * mCNF){
    //�����תΪԭʼ���
    letterCode = abs(letterCode);
    //���������Ӿ��г��ֵĴ���+1
    letterListNode letterElem = &mCNF->letterList[letterCode];
    letterElem->nowNum++;
    //�������м�����Ӿ䵥Ԫ�ڵ�
    jumpNode newJumpNode = (jumpNode)malloc(sizeof(jumpElem));
    initJumpElem(newJumpNode);
    //��ʼ���µ����߽ڵ�
    newJumpNode->clauseElemNode=mClauseElemNode;
    mClauseElemNode->jumpNode=newJumpNode;
    newJumpNode->letterListNode=&mCNF->letterList[letterCode];
    //�����߽ڵ��������
    if(letterElem->firstJumpNode==NULL){
        letterElem->firstJumpNode=newJumpNode;
    }else{
        jumpNode nowJumpNode = letterElem->firstJumpNode;
        while(nowJumpNode->nextJumpNode!=NULL){
            nowJumpNode=nowJumpNode->nextJumpNode;
        }
        newJumpNode->priorJumpNode=nowJumpNode;
        nowJumpNode->nextJumpNode=newJumpNode;
    }
    //���Ӿ䵥Ԫ�ڵ����ָ������
    mClauseElemNode->jumpNode=newJumpNode;
}

//��ȡ�Ӿ�
void addClause(int Clausecode,CNF * mCNF,FILE * fp){
    //��ʼ��Ŀ��ڵ�
    clauseNode newClause = &mCNF->clauseList[Clausecode];
    initClause(newClause,Clausecode);
    //��ʼ�����Ӿ�
    int elemCode;
    //������ͷ���
    fscanf(fp,"%d",&elemCode);
    clauseElemNode newElem = (clauseElemNode)malloc(sizeof(clauseElem));
    newClause->elemNum++;
    initClauseElem(newElem,elemCode,Clausecode);
    newClause->firstElem = newElem;
    addToJump(newElem,elemCode,mCNF);
    //��ʼ����������
    clauseElemNode nowElem = newClause->firstElem;
    fscanf(fp,"%d",&elemCode);
    while(elemCode!=0){
        //��ʼ���½ڵ�
        newElem = (clauseElemNode)malloc(sizeof(clauseElem));
        newClause->elemNum++;
        initClauseElem(newElem,elemCode,Clausecode);
        //���½ڵ�����Ӿ�
        nowElem->nextElemNode=newElem;
        newElem->priorElemNode=nowElem;
        //���½ڵ��������
        addToJump(newElem,elemCode,mCNF);
        //��������
        nowElem = newElem;
        fscanf(fp,"%d",&elemCode);
    }
}

//��ָ��λ�õ�ԭ�Ӿ�ָ��ѹ��ջ
void pushClause(floorStack * mStack,int origin,int * location){
    clauseStackTop newTop = (clauseStackTop)malloc(sizeof(clauseStack));
    newTop->location=location;
    newTop->origin=origin;
    newTop->next=mStack->clauseTop;
    mStack->clauseTop=newTop;
    mStack->deletedClauseNum++;
}

//��ָ��λ�õ�ԭ����ָ��ѹ��ջ
void pushJump(floorStack * mStack,jumpNode origin, jumpNode * location){
    jumpStackTop newTop = (jumpStackTop)malloc(sizeof(jumpStack));
    newTop->location=location;
    newTop->origin=origin;
    newTop->next=mStack->jumpTop;
    mStack->jumpTop=newTop;
}

//��ָ��λ�õ�ԭ�Ӿ䵥Ԫָ��ѹ��ջ
void pushElem(floorStack * mStack,clauseElemNode origin,clauseElemNode * location){
    ElemStackTop newTop = (ElemStackTop)malloc(sizeof(ElemStack));
    newTop->location=location;
    newTop->origin=origin;
    newTop->next=mStack->elemTop;
    mStack->elemTop=newTop;
}

//���ı���ֵ������ѹ��ջ
void pushValue(floorStack * mStack,int letterCode,CNF * mCNF){
    if(letterCode==24){
        int test=24;
    }
    if(count>99500&&letterCode==24){
        int test=1;
    }
    valueStackTop newTop = (valueStackTop)malloc(sizeof(valueStack));
    newTop->location=&mCNF->letterList[letterCode].nowLetter.value;
    newTop->next=mStack->valueTop;
    mStack->valueTop=newTop;
}

//����Ԫ�����ĸı�ѹ��ջ
void pushLetterNum(floorStack * mStack,int * location){
    numStackTop newTop = (numStackTop)malloc(sizeof(numStack));
    newTop->location=location;
    newTop->next=mStack->numTop;
    mStack->numTop=newTop;
}

//���Ӿ������ĸı�ѹ��ջ
void pushClauseElemNum(floorStack * mStack,int * location){
    clauseElemNumStackTop newTop = (clauseElemNumStackTop)malloc(sizeof(clauseElemNumStack));
    newTop->location=location;
    newTop->next=mStack->clauseElemNumTop;
    mStack->clauseElemNumTop=newTop;
}

//��ʼɾ������
void initDeleteJump(jumpNode nowJump){
    //�ж����ߵ�Ԫλ�þ���ɾ����ʽ���ֱ�Ϊͷ�����в���β��
    letterListNode nowLetter=nowJump->letterListNode;
    if(nowJump->priorJumpNode==NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        nowLetter->firstJumpNode=nextJump;
        if(nextJump!=NULL) //��Ϊ����Ϊ���һ��
        nextJump->priorJumpNode=priorJump;
    }else if(nowJump->nextJumpNode!=NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        priorJump->nextJumpNode=nextJump;
        nextJump->priorJumpNode=priorJump;
    }else{
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        priorJump->nextJumpNode=nextJump;
    }
}

//ɾ�����ߵ�Ԫ����������ѹ��ջ
void deleteJump(floorStack * mStack,jumpNode nowJump){
    //�ж����ߵ�Ԫλ�þ���ɾ����ʽ���ֱ�Ϊͷ�����в���β��
    letterListNode nowLetter=nowJump->letterListNode;
    if(nowJump->priorJumpNode==NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        nowLetter->firstJumpNode=nextJump;
        if(nextJump!=NULL) //��Ϊ����Ϊ���һ��
        nextJump->priorJumpNode=priorJump;
        //������ѹ��ջ
        pushJump(mStack,nowJump,&nowLetter->firstJumpNode);
        if(nextJump!=NULL) //��Ϊ����Ϊ���һ��
        pushJump(mStack,nowJump,&nextJump->priorJumpNode);
        pushLetterNum(mStack,&nowLetter->nowNum);
    }else if(nowJump->nextJumpNode!=NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        priorJump->nextJumpNode=nextJump;
        nextJump->priorJumpNode=priorJump;
        //������ѹ��ջ
        pushJump(mStack,nowJump,&priorJump->nextJumpNode);
        pushJump(mStack,nowJump,&nextJump->priorJumpNode);
        pushLetterNum(mStack,&nowLetter->nowNum);
    }else{
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        priorJump->nextJumpNode=nextJump;
        //������ѹ��ջ
        pushJump(mStack,nowJump,&priorJump->nextJumpNode);
        pushLetterNum(mStack,&nowLetter->nowNum);
    }
}

//��ʼɾ���Ӿ�
void initDeleteClause(int clauseCode,CNF * mCNF){
    //�ҵ�Ŀ���Ӿ䣬�����������ɾ������������ѹ��ջ
    //�������ɾ��β�Ӿ�
    clauseNode nowClause = &mCNF->clauseList[clauseCode];
    nowClause->deleted=1;
    mCNF->clauseNum--;
    //���Ӿ���ÿ����Ԫ�����߽ڵ��������ɾ��
    clauseElemNode nowElem= nowClause->firstElem;
    while(nowElem!=NULL){
        jumpNode nowJump = nowElem->jumpNode;
        initDeleteJump(nowJump);
        nowElem=nowElem->nextElemNode;
    }
}

//ɾ���Ӿ�
void deleteClause(int clauseCode,floorStack * mStack,CNF * mCNF){
    //�ҵ�Ŀ���Ӿ䣬�����������ɾ������������ѹ��ջ
    //�������ɾ��β�Ӿ�
    clauseNode nowClause = &mCNF->clauseList[clauseCode];
    nowClause->deleted=1;
    mCNF->clauseNum--;
    pushClause(mStack,0,&nowClause->deleted);
    //���Ӿ���ÿ����Ԫ�����߽ڵ��������ɾ��
    clauseElemNode nowElem= nowClause->firstElem;
    while(nowElem!=NULL){
        jumpNode nowJump = nowElem->jumpNode;
        deleteJump(mStack,nowJump);
        nowElem=nowElem->nextElemNode;
    }
}

//ɾ���Ӿ��һ����Ԫ
int deleteElem(clauseElemNode elemNode,floorStack * mStack,CNF * mCNF){
    //���Ӿ䵥Ԫ���Ӿ���ɾ������ѹ��ջ
    clauseNode nowClause = &mCNF->clauseList[elemNode->clauseCode];
    nowClause->elemNum--;
    pushClauseElemNum(mStack,&nowClause->elemNum);
    //�ж��Ӿ䵥Ԫλ�þ���ɾ����ʽ���ֱ�Ϊͷ�����в���β��
    if(elemNode->priorElemNode==NULL){
        clauseElemNode priorElemNode = elemNode->priorElemNode;
        clauseElemNode nextElemNode = elemNode->nextElemNode;
        //�ҵ��Ӿ䣬���Ӿ�ĵ�һ����Ԫ��Ϊ����Ԫɾ������һ����Ԫ
        nowClause->firstElem=nextElemNode;
        pushElem(mStack,elemNode,&nowClause->firstElem);
        if(nextElemNode==NULL){
            //ɾ�������һ�������ֿ��Ӿ�
            return FALSE;
        }else{
            //����ʣ���һ��
            nextElemNode->priorElemNode=priorElemNode;
            pushElem(mStack,elemNode,&nextElemNode->priorElemNode);
        }
    }else if(elemNode->nextElemNode!=NULL){
        clauseElemNode priorElemNode = elemNode->priorElemNode;
        clauseElemNode nextElemNode = elemNode->nextElemNode;
        priorElemNode->nextElemNode=nextElemNode;
        nextElemNode->priorElemNode=priorElemNode;
        //������ѹ��ջ
        pushElem(mStack,elemNode,&priorElemNode->nextElemNode);
        pushElem(mStack,elemNode,&nextElemNode->priorElemNode);
    }else{
        clauseElemNode priorElemNode = elemNode->priorElemNode;
        clauseElemNode nextElemNode = elemNode->nextElemNode;
        priorElemNode->nextElemNode=nextElemNode;
        //������ѹ��ջ
        pushElem(mStack,elemNode,&priorElemNode->nextElemNode);
    }
    //���Ӿ䵥Ԫ��Ӧ�����ߵ�Ԫɾ��
    jumpNode nowJump = elemNode->jumpNode;
    deleteJump(mStack,nowJump);
    return TRUE;
}

//��λ�Ӿ䴫��
int UP(int tarCode,int TorF,floorStack * mStack,CNF * mCNF){
    //�ҵ�Ŀ������
    letterListNode nowLetter = &mCNF->letterList[tarCode];
    //��ʼ��������
    jumpNode nowJumpNode = nowLetter->firstJumpNode;
    while(nowJumpNode!=NULL){
        //�����Ӿ䵥Ԫ��ֵΪ�棬��ȥ����Ӿ�
        if(nowJumpNode->clauseElemNode->code*TorF==tarCode){
            deleteClause(nowJumpNode->clauseElemNode->clauseCode,mStack,mCNF);
        }
        //�����Ӿ䵥Ԫ��ֵΪ�٣���ȥ����Ӿ䵥Ԫ
        if(nowJumpNode->clauseElemNode->code*TorF==-tarCode){
            int judegeEmpty = deleteElem(nowJumpNode->clauseElemNode,mStack,mCNF);
            if(judegeEmpty==FALSE) return judegeEmpty;
        }
        //����ȡ���߽ڵ�
        nowJumpNode = nowLetter->firstJumpNode;
    }
    return TRUE;
}

//��ʼ��������ɾȥ
int initPLE(CNF * mCNF){
    int index=1;
    while(index<=mCNF->letterNum){
        //�ҵ�ֻ���Ӿ������һ�������֣��������ڵ��Ӿ���ȥ�����Ը����ָ�ֵ
        letterListNode nowLetter = &mCNF->letterList[index];
        if(nowLetter->nowNum==1){
            jumpNode nowJump = nowLetter->firstJumpNode;
            clauseElemNode nowElem = nowJump->clauseElemNode;
            int clauseCode = nowElem->clauseCode;
            nowLetter->nowLetter.value=nowLetter->nowLetter.code/nowElem->code;
            initDeleteClause(clauseCode,mCNF);
        }
        index++;
    }
    return TRUE;
}

//����������ȥ
int PLE(floorStack * mStack,CNF * mCNF){
    int index=1;
    while(index<=mCNF->letterNum){
        //�ҵ�ֻ���Ӿ������һ�������֣��������ڵ��Ӿ���ȥ�����Ը����ָ�ֵ
        letterListNode nowLetter = &mCNF->letterList[index];
        if(nowLetter->nowNum==1){
            jumpNode nowJump = nowLetter->firstJumpNode;
            clauseElemNode nowElem = nowJump->clauseElemNode;
            int clauseCode = nowElem->clauseCode;
            nowLetter->nowLetter.value=nowLetter->nowLetter.code/nowElem->code;
            pushValue(mStack,nowLetter->nowLetter.code,mCNF);
            deleteClause(clauseCode,mStack,mCNF);
        }
        index++;
    }
    return TRUE;
}

//ѡ����һ����ֵ����ĸ
int ChooseVariable(floorStack * mStack, CNF * mCNF){
    int code=1;
    int maxNum=0;
    int maxCode=0;
    for(code=1;code<=mCNF->originClauseNum;code++){
        if(mCNF->clauseList[code].deleted==0&&mCNF->clauseList[code].elemNum==1){
            int letterCode = abs(mCNF->clauseList[code].firstElem->code);
            return letterCode;
        }
    }
    PLE(mStack,mCNF);
    for (code = 1; code <= mCNF->letterNum; code++) {
        if(mCNF->letterList[code].nowLetter.value==UNDEFINE)
        return code;
    }
    return code;
    /*code = 1;
    while(code<=mCNF->letterNum){
        letterListNode nowLetter = &mCNF->letterList[code];
        if(nowLetter->nowLetter.value==UNDEFINE&&nowLetter->nowNum>maxNum){
            maxCode=code;
            maxNum=nowLetter->nowNum;
        }
        //����
        //if(nowLetter==NULL) return 0; 
        //����
        code++;
    }
    return maxCode;*/
}

//�ָ��Ӿ�
void recoverClause(CNF * mCNF,floorStack * mStack){
    clauseStackTop nowTop = mStack->clauseTop;
    while(nowTop!=NULL){
        *nowTop->location=nowTop->origin;
        clauseStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
    mCNF->clauseNum+=mStack->deletedClauseNum;
}

//�ָ����ߵ�Ԫ
void recoverJump(floorStack * mStack){
    jumpStackTop nowTop = mStack->jumpTop;
    while(nowTop!=NULL){
        *nowTop->location=nowTop->origin;
        jumpStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//�ָ��Ӿ䵥Ԫ
void recoverElem(floorStack * mStack){
    ElemStackTop nowTop = mStack->elemTop;
    while(nowTop!=NULL){
        if(count>99500&&nowTop->origin->code==24){
            int test=1;
        }
        *nowTop->location=nowTop->origin;
        ElemStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//�ָ���ĸ��ֵ
void recoverValue(CNF * mCNF,floorStack * mStack){
    valueStackTop nowTop = mStack->valueTop;
    while(nowTop!=NULL){
        *nowTop->location=UNDEFINE;
        valueStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//�ָ���ĸ����
void recoverLetterNum(floorStack * mStack){
    numStackTop nowTop = mStack->numTop;
    while(nowTop!=NULL){
        *nowTop->location+=1;
        numStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//�ָ��Ӿ䵥Ԫ����
void recoverClauseElemNum(floorStack * mStack){
    clauseElemNumStackTop nowTop = mStack->clauseElemNumTop;
    while(nowTop!=NULL){
        *nowTop->location+=1;
        clauseElemNumStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//����ָ��ջ�ָ�һ��Ĳ���
void recoverStack(CNF * mCNF){
    floorStack * mStack = AllTop->mStack;
    recoverClause(mCNF,mStack);
    recoverElem(mStack);
    recoverJump(mStack);
    recoverValue(mCNF,mStack);
    recoverLetterNum(mStack);
    recoverClauseElemNum(mStack);
    allTop freeTop = AllTop;
    AllTop=AllTop->next;
    free(freeTop);
}

//�����������
int DPLL(floorStack * mStack ,int choosedLetter,int TorF,CNF * mCNF){

    nowTime = clock();
    if (nowTime - startTime >= 20000) return TIMEOUT;

    count++;
    if(count%100000==0) printf("%d\n",count/100000);
    //����ѡ�����ĸ��ֵ��Ϊ����
    letterListNode nowLetter = &mCNF->letterList[choosedLetter];
    nowLetter->nowLetter.value=TorF;
    //��������ջ
    pushValue(AllTop->mStack,choosedLetter,mCNF);

    //���е�λ�Ӿ䴫���͹���������ȥ
    int judgeEmpty;
    //ͨ��ɾ���������п��������Ƿ��п��Ӿ�
    judgeEmpty = UP(choosedLetter,TorF,mStack,mCNF);
    if(judgeEmpty==FALSE) return FALSE;
    //�����ʽ���ˣ���Ϊ��
    if(mCNF->clauseNum==0){
        answerCNF=*mCNF;
        nowTime = clock();
        return TRUE;
    }
    //ѡ����һ����ĸ���и�ֵ
    int nextChoosed = ChooseVariable(mStack,mCNF);
    //��ѡ�����ĸ��ֵΪ�棬���ѽ��
    addStack();
    int res1 = DPLL(AllTop->mStack,nextChoosed,TRUE,mCNF);
    recoverStack(mCNF);
    if(res1==TRUE) return res1;
    if (res1 == TIMEOUT) return res1;
    //ѡ�����ĸ��ֵΪ�٣����ѽ��
    addStack();
    int res2 = DPLL(AllTop->mStack,nextChoosed,FALSE,mCNF);
    recoverStack(mCNF);
    if(res2==TRUE) return res2;
    if (res2 == TIMEOUT) return res2;
    //�����Ϊ��
    return FALSE;
}


