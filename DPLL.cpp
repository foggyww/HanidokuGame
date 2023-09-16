

#define _CRT_SECURE_NO_WARNINGS 1
#include "DPLL.h"
//初始化文字
void initLetter(letter* tarNode, int code) {
    tarNode->code = code;
    tarNode->value = 0;
}
//初始化文字列表
void initLetterListElem(letterListNode tarNode, int code) {
    initLetter(&tarNode->nowLetter, code);
    tarNode->firstJumpNode = NULL;
    tarNode->nowNum = 0;
}
//初始化跳线节点
void initJumpElem(jumpNode tarNode) {
    tarNode->clauseElemNode = NULL;
    tarNode->letterListNode = NULL;
    tarNode->nextJumpNode = NULL;
    tarNode->priorJumpNode = NULL;
}
//初始化子句单元
void initClauseElem(clauseElemNode tarNode, int code, int clauseCode) {
    tarNode->code = code;
    tarNode->clauseCode = clauseCode;
    tarNode->jumpNode = NULL;
    tarNode->nextElemNode = NULL;
    tarNode->priorElemNode = NULL;
}
//初始化子句
void initClause(clauseNode tarNode, int code) {
    tarNode->code = code;
    tarNode->firstElem = NULL;
    tarNode->deleted = 0;
    tarNode->elemNum = 0;
}
//初始化CNF文件
void initCNF(CNF* mCNF, int clauseNum, int letterNum) {
    mCNF->clauseNum = clauseNum;
    mCNF->letterNum = letterNum;
    mCNF->originClauseNum = clauseNum;
}
//初始化指针栈
void initStack(floorStack* tarStack) {
    tarStack->clauseTop = NULL;
    tarStack->elemTop = NULL;
    tarStack->jumpTop = NULL;
    tarStack->numTop = NULL;
    tarStack->valueTop = NULL;
    tarStack->clauseElemNumTop = NULL;
    tarStack->deletedClauseNum = 0;
}
//添加指针栈
void addStack() {
    allTop newTop = (allTop)malloc(sizeof(allStack));
    newTop->mStack = (floorStack*)malloc(sizeof(floorStack));
    initStack(newTop->mStack);
    newTop->next = AllTop;
    AllTop = newTop;
}


//载入文件
CNF * loadFile(const char FileName[100]){
    //scanf("%s",fileName);
    FILE * fp = fopen(FileName,"r");
    CNF * res = createCNF(fp);
    fclose(fp);
    return res;
}

//创建CNF
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

//读取变元
void addListElem(int code,CNF * mCNF){
    //初始化目标节点
    initLetterListElem(&mCNF->letterList[code],code);
}

//将指定的子句单元加到跳线内
void addToJump(clauseElemNode mClauseElemNode,int letterCode,CNF * mCNF){
    //将编号转为原始编号
    letterCode = abs(letterCode);
    //该文字在子句中出现的次数+1
    letterListNode letterElem = &mCNF->letterList[letterCode];
    letterElem->nowNum++;
    //在跳线中加入该子句单元节点
    jumpNode newJumpNode = (jumpNode)malloc(sizeof(jumpElem));
    initJumpElem(newJumpNode);
    //初始化新的跳线节点
    newJumpNode->clauseElemNode=mClauseElemNode;
    mClauseElemNode->jumpNode=newJumpNode;
    newJumpNode->letterListNode=&mCNF->letterList[letterCode];
    //将跳线节点加入跳线
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
    //给子句单元节点加上指向跳线
    mClauseElemNode->jumpNode=newJumpNode;
}

//读取子句
void addClause(int Clausecode,CNF * mCNF,FILE * fp){
    //初始化目标节点
    clauseNode newClause = &mCNF->clauseList[Clausecode];
    initClause(newClause,Clausecode);
    //开始读入子句
    int elemCode;
    //创建好头结点
    fscanf(fp,"%d",&elemCode);
    clauseElemNode newElem = (clauseElemNode)malloc(sizeof(clauseElem));
    newClause->elemNum++;
    initClauseElem(newElem,elemCode,Clausecode);
    newClause->firstElem = newElem;
    addToJump(newElem,elemCode,mCNF);
    //开始创建其他的
    clauseElemNode nowElem = newClause->firstElem;
    fscanf(fp,"%d",&elemCode);
    while(elemCode!=0){
        //初始化新节点
        newElem = (clauseElemNode)malloc(sizeof(clauseElem));
        newClause->elemNum++;
        initClauseElem(newElem,elemCode,Clausecode);
        //将新节点加入子句
        nowElem->nextElemNode=newElem;
        newElem->priorElemNode=nowElem;
        //将新节点加入跳线
        addToJump(newElem,elemCode,mCNF);
        //继续读入
        nowElem = newElem;
        fscanf(fp,"%d",&elemCode);
    }
}

//将指定位置的原子句指针压入栈
void pushClause(floorStack * mStack,int origin,int * location){
    clauseStackTop newTop = (clauseStackTop)malloc(sizeof(clauseStack));
    newTop->location=location;
    newTop->origin=origin;
    newTop->next=mStack->clauseTop;
    mStack->clauseTop=newTop;
    mStack->deletedClauseNum++;
}

//将指定位置的原跳线指针压入栈
void pushJump(floorStack * mStack,jumpNode origin, jumpNode * location){
    jumpStackTop newTop = (jumpStackTop)malloc(sizeof(jumpStack));
    newTop->location=location;
    newTop->origin=origin;
    newTop->next=mStack->jumpTop;
    mStack->jumpTop=newTop;
}

//将指定位置的原子句单元指针压入栈
void pushElem(floorStack * mStack,clauseElemNode origin,clauseElemNode * location){
    ElemStackTop newTop = (ElemStackTop)malloc(sizeof(ElemStack));
    newTop->location=location;
    newTop->origin=origin;
    newTop->next=mStack->elemTop;
    mStack->elemTop=newTop;
}

//将改变了值的文字压入栈
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

//将变元数量的改变压入栈
void pushLetterNum(floorStack * mStack,int * location){
    numStackTop newTop = (numStackTop)malloc(sizeof(numStack));
    newTop->location=location;
    newTop->next=mStack->numTop;
    mStack->numTop=newTop;
}

//将子句数量的改变压入栈
void pushClauseElemNum(floorStack * mStack,int * location){
    clauseElemNumStackTop newTop = (clauseElemNumStackTop)malloc(sizeof(clauseElemNumStack));
    newTop->location=location;
    newTop->next=mStack->clauseElemNumTop;
    mStack->clauseElemNumTop=newTop;
}

//初始删除跳线
void initDeleteJump(jumpNode nowJump){
    //判断跳线单元位置决定删除方式，分别为头部、中部、尾部
    letterListNode nowLetter=nowJump->letterListNode;
    if(nowJump->priorJumpNode==NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        nowLetter->firstJumpNode=nextJump;
        if(nextJump!=NULL) //若为空则为最后一个
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

//删除跳线单元，并将操作压入栈
void deleteJump(floorStack * mStack,jumpNode nowJump){
    //判断跳线单元位置决定删除方式，分别为头部、中部、尾部
    letterListNode nowLetter=nowJump->letterListNode;
    if(nowJump->priorJumpNode==NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        nowLetter->firstJumpNode=nextJump;
        if(nextJump!=NULL) //若为空则为最后一个
        nextJump->priorJumpNode=priorJump;
        //将操作压入栈
        pushJump(mStack,nowJump,&nowLetter->firstJumpNode);
        if(nextJump!=NULL) //若为空则为最后一个
        pushJump(mStack,nowJump,&nextJump->priorJumpNode);
        pushLetterNum(mStack,&nowLetter->nowNum);
    }else if(nowJump->nextJumpNode!=NULL){
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        priorJump->nextJumpNode=nextJump;
        nextJump->priorJumpNode=priorJump;
        //将操作压入栈
        pushJump(mStack,nowJump,&priorJump->nextJumpNode);
        pushJump(mStack,nowJump,&nextJump->priorJumpNode);
        pushLetterNum(mStack,&nowLetter->nowNum);
    }else{
        jumpNode priorJump = nowJump->priorJumpNode;
        jumpNode nextJump = nowJump->nextJumpNode;
        nowJump->letterListNode->nowNum--;
        priorJump->nextJumpNode=nextJump;
        //将操作压入栈
        pushJump(mStack,nowJump,&priorJump->nextJumpNode);
        pushLetterNum(mStack,&nowLetter->nowNum);
    }
}

//初始删除子句
void initDeleteClause(int clauseCode,CNF * mCNF){
    //找到目标子句，将其从链表中删除，并将操作压入栈
    //如果不是删的尾子句
    clauseNode nowClause = &mCNF->clauseList[clauseCode];
    nowClause->deleted=1;
    mCNF->clauseNum--;
    //将子句中每个单元的跳线节点从链表中删除
    clauseElemNode nowElem= nowClause->firstElem;
    while(nowElem!=NULL){
        jumpNode nowJump = nowElem->jumpNode;
        initDeleteJump(nowJump);
        nowElem=nowElem->nextElemNode;
    }
}

//删除子句
void deleteClause(int clauseCode,floorStack * mStack,CNF * mCNF){
    //找到目标子句，将其从链表中删除，并将操作压入栈
    //如果不是删的尾子句
    clauseNode nowClause = &mCNF->clauseList[clauseCode];
    nowClause->deleted=1;
    mCNF->clauseNum--;
    pushClause(mStack,0,&nowClause->deleted);
    //将子句中每个单元的跳线节点从链表中删除
    clauseElemNode nowElem= nowClause->firstElem;
    while(nowElem!=NULL){
        jumpNode nowJump = nowElem->jumpNode;
        deleteJump(mStack,nowJump);
        nowElem=nowElem->nextElemNode;
    }
}

//删除子句的一个单元
int deleteElem(clauseElemNode elemNode,floorStack * mStack,CNF * mCNF){
    //将子句单元从子句中删除，并压入栈
    clauseNode nowClause = &mCNF->clauseList[elemNode->clauseCode];
    nowClause->elemNum--;
    pushClauseElemNum(mStack,&nowClause->elemNum);
    //判断子句单元位置决定删除方式，分别为头部、中部、尾部
    if(elemNode->priorElemNode==NULL){
        clauseElemNode priorElemNode = elemNode->priorElemNode;
        clauseElemNode nextElemNode = elemNode->nextElemNode;
        //找到子句，将子句的第一个单元改为所单元删除的下一个单元
        nowClause->firstElem=nextElemNode;
        pushElem(mStack,elemNode,&nowClause->firstElem);
        if(nextElemNode==NULL){
            //删除了最后一个，出现空子句
            return FALSE;
        }else{
            //不是剩最后一个
            nextElemNode->priorElemNode=priorElemNode;
            pushElem(mStack,elemNode,&nextElemNode->priorElemNode);
        }
    }else if(elemNode->nextElemNode!=NULL){
        clauseElemNode priorElemNode = elemNode->priorElemNode;
        clauseElemNode nextElemNode = elemNode->nextElemNode;
        priorElemNode->nextElemNode=nextElemNode;
        nextElemNode->priorElemNode=priorElemNode;
        //将操作压入栈
        pushElem(mStack,elemNode,&priorElemNode->nextElemNode);
        pushElem(mStack,elemNode,&nextElemNode->priorElemNode);
    }else{
        clauseElemNode priorElemNode = elemNode->priorElemNode;
        clauseElemNode nextElemNode = elemNode->nextElemNode;
        priorElemNode->nextElemNode=nextElemNode;
        //将操作压入栈
        pushElem(mStack,elemNode,&priorElemNode->nextElemNode);
    }
    //将子句单元对应的跳线单元删除
    jumpNode nowJump = elemNode->jumpNode;
    deleteJump(mStack,nowJump);
    return TRUE;
}

//单位子句传播
int UP(int tarCode,int TorF,floorStack * mStack,CNF * mCNF){
    //找到目标文字
    letterListNode nowLetter = &mCNF->letterList[tarCode];
    //开始处理跳线
    jumpNode nowJumpNode = nowLetter->firstJumpNode;
    while(nowJumpNode!=NULL){
        //若该子句单元的值为真，消去这个子句
        if(nowJumpNode->clauseElemNode->code*TorF==tarCode){
            deleteClause(nowJumpNode->clauseElemNode->clauseCode,mStack,mCNF);
        }
        //若该子句单元的值为假，消去这个子句单元
        if(nowJumpNode->clauseElemNode->code*TorF==-tarCode){
            int judegeEmpty = deleteElem(nowJumpNode->clauseElemNode,mStack,mCNF);
            if(judegeEmpty==FALSE) return judegeEmpty;
        }
        //继续取跳线节点
        nowJumpNode = nowLetter->firstJumpNode;
    }
    return TRUE;
}

//初始孤立文字删去
int initPLE(CNF * mCNF){
    int index=1;
    while(index<=mCNF->letterNum){
        //找到只在子句里存在一个的文字，将其所在的子句消去，并对该文字赋值
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

//孤立文字消去
int PLE(floorStack * mStack,CNF * mCNF){
    int index=1;
    while(index<=mCNF->letterNum){
        //找到只在子句里存在一个的文字，将其所在的子句消去，并对该文字赋值
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

//选择下一个赋值的字母
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
        //调试
        //if(nowLetter==NULL) return 0; 
        //调试
        code++;
    }
    return maxCode;*/
}

//恢复子句
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

//恢复跳线单元
void recoverJump(floorStack * mStack){
    jumpStackTop nowTop = mStack->jumpTop;
    while(nowTop!=NULL){
        *nowTop->location=nowTop->origin;
        jumpStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//恢复子句单元
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

//恢复字母赋值
void recoverValue(CNF * mCNF,floorStack * mStack){
    valueStackTop nowTop = mStack->valueTop;
    while(nowTop!=NULL){
        *nowTop->location=UNDEFINE;
        valueStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//恢复字母数量
void recoverLetterNum(floorStack * mStack){
    numStackTop nowTop = mStack->numTop;
    while(nowTop!=NULL){
        *nowTop->location+=1;
        numStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//恢复子句单元数量
void recoverClauseElemNum(floorStack * mStack){
    clauseElemNumStackTop nowTop = mStack->clauseElemNumTop;
    while(nowTop!=NULL){
        *nowTop->location+=1;
        clauseElemNumStackTop freeTop = nowTop;
        nowTop=nowTop->next;
        free(freeTop);
    }
}

//利用指针栈恢复一层的操作
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

//深度优先搜索
int DPLL(floorStack * mStack ,int choosedLetter,int TorF,CNF * mCNF){

    nowTime = clock();
    if (nowTime - startTime >= 20000) return TIMEOUT;

    count++;
    if(count%100000==0) printf("%d\n",count/100000);
    //将被选择的字母的值改为真或假
    letterListNode nowLetter = &mCNF->letterList[choosedLetter];
    nowLetter->nowLetter.value=TorF;
    //将操作入栈
    pushValue(AllTop->mStack,choosedLetter,mCNF);

    //进行单位子句传播和孤立文字消去
    int judgeEmpty;
    //通过删除过程中判空来鉴定是否有空子句
    judgeEmpty = UP(choosedLetter,TorF,mStack,mCNF);
    if(judgeEmpty==FALSE) return FALSE;
    //如果公式空了，则为真
    if(mCNF->clauseNum==0){
        answerCNF=*mCNF;
        nowTime = clock();
        return TRUE;
    }
    //选择下一个字母进行赋值
    int nextChoosed = ChooseVariable(mStack,mCNF);
    //将选择的字母赋值为真，深搜结果
    addStack();
    int res1 = DPLL(AllTop->mStack,nextChoosed,TRUE,mCNF);
    recoverStack(mCNF);
    if(res1==TRUE) return res1;
    if (res1 == TIMEOUT) return res1;
    //选择的字母赋值为假，深搜结果
    addStack();
    int res2 = DPLL(AllTop->mStack,nextChoosed,FALSE,mCNF);
    recoverStack(mCNF);
    if(res2==TRUE) return res2;
    if (res2 == TIMEOUT) return res2;
    //结果均为假
    return FALSE;
}


