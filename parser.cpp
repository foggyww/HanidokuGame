#define _CRT_SECURE_NO_WARNINGS 1
#include "DPLL.h"
typedef struct plaid{
    int line;
    int order;
    int code;
}plaid;



void printToFile(int num,FILE * fp){
    if(num>0)
    fprintf(fp,"%d ",num-10-num/10+1);
    //printf("%d ",num);
    else
    fprintf(fp,"%d ",-(abs(num)-10-abs(num)/10+1));
    //printf("%d ",num);
}

void printClauseEnd(FILE * fp,int * clauseNum){
    fprintf(fp,"0\n");
    //printf("0\n");
    *clauseNum+=1;
}

void limitPlaid(plaid beehive[10][10],int ord[100],FILE * fp,int * clauseNum){
    int num = 1;
    int line, row;
    ForLine(line) {
        ForRow(line, row) {
            plaid nowPlaid = beehive[line][row];
            if (ord[num] != 0) {
                printToFile(CODE(nowPlaid.code, ord[num]), fp);
                printClauseEnd(fp, clauseNum);
            }
            num++;
        }
    }
    ForLine(line)
        ForRow(line, row) {
        plaid nowPlaid = beehive[line][row];
        //此位置会填1-9
        for (int i = 1; i <= 9; i++) {
            printToFile(CODE(nowPlaid.code, i), fp);
        }
        printClauseEnd(fp, clauseNum);
        //此位置不能同时填两个数
        for (int i = 1; i <= 9; i++) {
            for (int j = i + 1; j <= 9; j++) {
                printToFile(-CODE(nowPlaid.code, i), fp);
                printToFile(-CODE(nowPlaid.code, j), fp);
                printClauseEnd(fp, clauseNum);
            }
        }
    }
}

void limitLine5(plaid beehive[10],FILE * fp,int * clauseNum){
    //必定会存在5
    for(int i=5;i<=5;i++){
        for(int j=1;j<=5;j++){
            printToFile(CODE(beehive[j].code,i),fp);
        }
        printClauseEnd(fp,clauseNum);
    }
    //选填情况
    for(int i=1;i<=4;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=5;k++){
                printToFile(CODE(beehive[k].code,i),fp);
                printToFile(CODE(beehive[k].code,j+5),fp);
            }
            printClauseEnd(fp,clauseNum);
        }
    }
    //每两格不同时填一个数
    for(int i=1;i<=9;i++){
        for(int j=1;j<5;j++){
            for(int k=j+1;k<=5;k++){
                printToFile(-CODE(beehive[j].code,i),fp);
                printToFile(-CODE(beehive[k].code,i),fp);
                printClauseEnd(fp,clauseNum);
            }
        }
    }
}

void limitLine6(plaid beehive[10],FILE * fp,int * clauseNum){
    //必定会存在4,5,6
    for(int i=4;i<=6;i++){
        for(int j=1;j<=6;j++){
            printToFile(CODE(beehive[j].code,i),fp);
        }
        printClauseEnd(fp,clauseNum);
    }
    //选填情况
    for(int i=1;i<=3;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=6;k++){
                printToFile(CODE(beehive[k].code,i),fp);
                printToFile(CODE(beehive[k].code,j+6),fp);
            }
            printClauseEnd(fp,clauseNum);
        }
    }
    //每两格填不同的数
    for(int i=1;i<=9;i++){
        for(int j=1;j<6;j++){
            for(int k=j+1;k<=6;k++){
                printToFile(-CODE(beehive[j].code,i),fp);
                printToFile(-CODE(beehive[k].code,i),fp);
                printClauseEnd(fp,clauseNum);
            }
        }
    }
}

void draw(plaid beehive[10][10]){
    int line,row;
    
    ForLine(line){
        int num = 9 - abs(5-line);
        for(int i=1;i<=9-num;i++){
            printf(" ");
        }
        ForRow(line,row){
            printf("%2d ",beehive[line][row].code);
        }
        printf("\n");
    }
}

void limitLine7(plaid beehive[10],FILE * fp,int * clauseNum){
    //必定会有3,4,5,6,7
    for(int i=3;i<=7;i++){
        for(int j=1;j<=7;j++){
            printToFile(CODE(beehive[j].code,i),fp);
        }
        printClauseEnd(fp,clauseNum);
    }
    //选填情况
    for(int i=1;i<=7;i++){
        printToFile(CODE(beehive[i].code,1),fp);
        printToFile(CODE(beehive[i].code,8),fp);
    }
    printClauseEnd(fp,clauseNum);
    for(int i=1;i<=7;i++){
        printToFile(CODE(beehive[i].code,2),fp);
        printToFile(CODE(beehive[i].code,8),fp);
    }
    printClauseEnd(fp,clauseNum);
    for(int i=1;i<=7;i++){
        printToFile(CODE(beehive[i].code,2),fp);
        printToFile(CODE(beehive[i].code,9),fp);
    }
    printClauseEnd(fp,clauseNum);
    //每两格填不同的数
    for(int i=1;i<=9;i++){
        for(int j=1;j<7;j++){
            for(int k=j+1;k<=7;k++){
                printToFile(-CODE(beehive[j].code,i),fp);
                printToFile(-CODE(beehive[k].code,i),fp);
                printClauseEnd(fp,clauseNum);
            }
        }
    }
}

void limitLine8(plaid beehive[10],FILE * fp,int * clauseNum){
    //2-8是必存在的
    for(int i=2;i<=8;i++){
        for(int j=1;j<=8;j++){
            printToFile(CODE(beehive[j].code,i),fp);
        }
        printClauseEnd(fp,clauseNum);
    }
    //选填情况
    for(int i=1;i<=8;i++){
        printToFile(CODE(beehive[i].code,1),fp);
        printToFile(CODE(beehive[i].code,9),fp);
    }
    printClauseEnd(fp,clauseNum);
    //每两格不同时为一个数
    for(int i=1;i<=9;i++){
        for(int j=1;j<8;j++){
            for(int k=j+1;k<=8;k++){
                printToFile(-CODE(beehive[j].code,i),fp);
                printToFile(-CODE(beehive[k].code,i),fp);
                printClauseEnd(fp,clauseNum);
            }
        }
    }
}

void limitLine9(plaid beehive[10],FILE * fp,int * clauseNum){
    //所有数都必存在
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            printToFile(CODE(beehive[j].code,i),fp);
        }
        printClauseEnd(fp,clauseNum);
    }
    //每两格不同时为一个数
    for(int i=1;i<=9;i++){
        for(int j=1;j<9;j++){
            for(int k=j+1;k<=9;k++){
                printToFile(-CODE(beehive[j].code,i),fp);
                printToFile(-CODE(beehive[k].code,i),fp);
                printClauseEnd(fp,clauseNum);
            }
        }
    }
}

//将蜂窝顺时针转60度
void convertBeehive(plaid beehive[10][10]){
    plaid newBeehive[10][10];
    for(int i=1,j=5;i<=5;i++,j--){
        newBeehive[1][i]=beehive[j][1];
    }
    newBeehive[2][1]=beehive[6][1];
    for(int i=2,j=5;i<=6;i++,j--){
        newBeehive[2][i]=beehive[j][2];
    }
    newBeehive[3][1]=beehive[7][1];
    newBeehive[3][2]=beehive[6][2];
    for(int i=3,j=5;i<=7;i++,j--){
        newBeehive[3][i]=beehive[j][3];
    }
    newBeehive[4][1]=beehive[8][1];
    newBeehive[4][2]=beehive[7][2];
    newBeehive[4][3]=beehive[6][3];
    for(int i=4,j=5;i<=8;i++,j--){
        newBeehive[4][i]=beehive[j][4];
    }
    newBeehive[5][1]=beehive[9][1];
    newBeehive[5][2]=beehive[8][2];
    newBeehive[5][3]=beehive[7][3];
    newBeehive[5][4]=beehive[6][4];
    for(int i=5,j=5;i<=9;i++,j--){
        newBeehive[5][i]=beehive[j][5];
    }
    for(int i=1,j=9;i<=5;i++,j--){
        newBeehive[6][i]=beehive[j][i+1];
    }
    newBeehive[6][6]=beehive[4][6];
    newBeehive[6][7]=beehive[3][6];
    newBeehive[6][8]=beehive[2][6];
    for(int i=1,j=9;i<=5;i++,j--){
        newBeehive[7][i]=beehive[j][i+2];
    }
    newBeehive[7][6]=beehive[4][7];
    newBeehive[7][7]=beehive[3][7];
    for(int i=1,j=9;i<=5;i++,j--){
        newBeehive[8][i]=beehive[j][i+3];
    }
    newBeehive[8][6]=beehive[4][8];
    for(int i=1,j=9;i<=5;i++,j--){
        newBeehive[9][i]=beehive[j][i+4];
    }
    int line,row;
    ForLine(line){
        ForRow(line,row){
            beehive[line][row]=newBeehive[line][row];
        }
    }
}

void limitLine(plaid beehive[10][10],FILE * fp,int * clauseNum){
    int line;
    ForLine(line){
        int num=9-abs(5-line);
        switch (num)
        {
        case 5:
            limitLine5(beehive[line],fp,clauseNum);
            break;
        case 6:
            limitLine6(beehive[line],fp,clauseNum);
            break;
        case 7:
            limitLine7(beehive[line],fp,clauseNum);
            break;
        case 8:
            limitLine8(beehive[line],fp,clauseNum);
            break;
        case 9:
            limitLine9(beehive[line],fp,clauseNum);
            break;
        default:
            break;
        }
    }
}

void creatBeehive(plaid beehive[10][10]){
    int code=1,line,row;
    ForLine(line){
        ForRow(line,row){
            beehive[line][row].code=code;
            code++;
        }
    }
}


void cnfParser(int level,char FileName[100],int ord[100]) {
    FILE * tempFP = fopen("temp.cnf","w");
    
    plaid beehive[10][10];
    creatBeehive(beehive);
    int clauseNum = 0;
    limitPlaid(beehive,ord,tempFP,&clauseNum);
    for(int i=1;i<=3;i++){
        draw(beehive);
        limitLine(beehive,tempFP,&clauseNum);
        convertBeehive(beehive);
    }
    fclose(tempFP);
    tempFP = fopen("temp.cnf","r");
    FILE * cnfFP = fopen(FileName,"w");
    fprintf(cnfFP,"p cnf %d %d\n",549,clauseNum);
    char ords[500];
    while(fgets(ords,499,tempFP)!=NULL){
        fprintf(cnfFP,"%s",ords);
    }
    fclose(tempFP);
    fclose(cnfFP);
}

