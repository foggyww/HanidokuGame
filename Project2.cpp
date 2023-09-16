#define _CRT_SECURE_NO_WARNINGS 1
#include "DPLL.h"
#include "solver.h"
#include "Hanidoku.h"

allTop AllTop=NULL;
int count=0;
long startTime=0;
long nowTime = 0;
CNF answerCNF;

int main(){
    int op=1; //命令的数字
    CNF * mCNF=NULL; //当前已创建的CNF文件
    while(op){
        printf("      Please select your action \n");
	    printf("-------------------------------------------------\n");
	    printf("    	  1. CreateCNF\n");
	    printf("    	  2. JudegeSAT\n");
	    printf("    	  3. DPLLSolving\n");
	    printf("    	  4. PlayHanidoku\n");
        scanf("%d",&op);
        int res;
        switch (op)
        {
        case 1:
            if(mCNF!=NULL){
                printf("创建失败,CNF文件已存在\n");
                break;
            }
            char FileName[100];
            printf("请输入你要载入的文件:");
            scanf("%s",FileName);
            mCNF=loadFile(FileName);
            printf("\n创建成功");
            break;
        case 2:
            if(mCNF==NULL){
                printf("未创建CNF文件\n");
                break;
            }
             res = solver(mCNF);
             if (res == 1) printf("\nyes\n用时:%d", nowTime - startTime);
             else if (res == 0) printf("\n超时");
            else printf("\nno");
            break;
        case 3:
            if(mCNF==NULL){
                printf("未创建CNF文件\n");
                break;
            }
            res = solver(mCNF);
            if(res==1){
                FILE* fp = fopen("SAT/out.res", "w");
                fprintf(fp, "s 1\n");
                for(int i=1;i<=mCNF->letterNum;i++){
                    fprintf(fp,"v %d ",answerCNF.letterList[i].nowLetter.code*answerCNF.letterList[i].nowLetter.value);
                    fprintf(fp, "\n");
                }
                fprintf(fp,"t %d", nowTime - startTime);
                fclose(fp);
            }else if(res==0) {
                FILE* fp = fopen("SAT/out.res", "w");
                fprintf(fp, "s -1");
                fclose(fp);
            }
            else {
                FILE* fp = fopen("SAT/out.res", "w");
                fprintf(fp,"s 0");
                fclose(fp);
            }
            break;
        case 4:
            Hanidoku();
            break;
        default:
            break;
        }//end of switch
        getchar();getchar();
    }//end of while

   /* FILE * fp1 = fopen("newCNF.cnf","r");
    FILE * fp2 = fopen("SATExample/test(1).txt","r");
    char ords[1000];
    int num1,num2;
    char ords2[10000][100];
    char ords3[10000][100];
    fscanf(fp1,"%s",ords);
    fscanf(fp1,"%s",ords);
    fscanf(fp1,"%s",ords);
    fscanf(fp1,"%d",&num1);
    for(int i=1;i<=num1;i++){
        fgets(ords2[i],100,fp1);
    }
    fscanf(fp2,"%s",ords);
    fscanf(fp2,"%s",ords);
    fscanf(fp2,"%s",ords);
    fscanf(fp2,"%d",&num2);
    for(int i=1;i<=num2;i++){
        fgets(ords3[i],100,fp2);
    }
    for(int i=1;i<=num1;i++){
        for(int j=1;j<=num2;j++){
            if(strcmp(ords2[i],ords3[j])==0){
                ords2[i][0]='\0';
                ords3[j][0]='\0';
            }
        }
    }
    printf("\n\nme\n\n\n\n");
    for(int i=1;i<=num1;i++){
        printf("%s",ords2[i]);
    }
    printf("\n\nhe\n\n\n\n");
    for(int i=1;i<=num2;i++){
        printf("%s",ords3[i]);
    }
    scanf("%d",&num1);*/
    return 0;
}