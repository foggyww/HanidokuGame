#define _CRT_SECURE_NO_WARNINGS 1
#include "Hanidoku.h"

#define MLENGTH 40*sqrt(3)//六边形的竖直方向的长度
#define INITL 600
#define INITT 50

void printToFile2(int num, FILE* fp) {
	if (num > 0)
		fprintf(fp, "%d ", num - 10 - num / 10 + 1);
	//printf("%d ",num);
	else
		fprintf(fp, "%d ", -(abs(num) - 10 - abs(num) / 10 + 1));
	//printf("%d ",num);
}

void printClauseEnd2(FILE* fp, int* clauseNum) {
	fprintf(fp, "0\n");
	//printf("0\n");
	*clauseNum += 1;
}

void creatCNF(const char* FileName, int ord[100]) {
	int num = 0;
	FILE* fpw = fopen(FileName, "w");
	FILE* fpr = fopen("baseCNF.cnf", "r");
	int clauseNum=0;
	for (int i = 1; i <= 61; i++) {
		if (ord[i] > 0) num++;
	}
	fprintf(fpw, "p cnf %d %d\n", 549, 7468 + num);
	for (int i = 1; i <= 61; i++) {
		if (ord[i] > 0) {
			printToFile2(CODE(i, ord[i]), fpw);
			printClauseEnd2(fpw, &clauseNum);
		}
	}
	char ords[1000];
	for (int i = 1; i <= 7468; i++) {
		fgets(ords, 999, fpr);
		fprintf(fpw, "%s", ords);
	}
	fclose(fpw);
	fclose(fpr);
}

void getAnswer(int answer[100]) {
	int count = 1;
	for (int i = 1; i <= 61; i++) {
		for (int j = 1; j <= 9; j++) {
			if (answerCNF.letterList[count].nowLetter.value == 1) {
				answer[i] = j;
			}
			count++;
		}
	}
}

void drawHexagon(POINT point,int length) {
	POINT pts[6] = { {point.x, point.y - length / 2}, {point.x + length / 4 * sqrt(3), point.y - length / 4}, {point.x + length / 4 * sqrt(3),point.y + length / 4} ,
					{point.x,point.y + length / 2},{point.x - length / 4 * sqrt(3),point.y + length / 4},{point.x - length / 4 * sqrt(3),point.y - length / 4} };
	fillpolygon(pts,6);
}

bool INGRID(int x, int y, RECT r) {
	if (x >= r.left && x <= r.right && y >= r.top && y <= r.bottom) return true;
	return false;
}

RECT r1 = { 50, 50, 150, 100 };
RECT r2 = { 50, 150, 150, 200 };
RECT r3 = { 600, 600, 750, 650 };
RECT r4 = { 800,600,950,650 };
RECT r5 = { 50,250,150,300 };
RECT r6 = { 800,700,950,750 };
RECT r7 = { 600,0,700,50 };

void initGame(int writePrompt) {
	COLORREF mBackgroud = RGB(186, 255, 255);
	COLORREF mFrameColor = RGB(105, 203, 205);
	COLORREF mFillColor = RGB(149, 248, 210);
	setbkcolor(mBackgroud);
	cleardevice();
	setfillcolor(mFillColor);
	setlinecolor(mFrameColor);
	fillrectangle(r1.left, r1.top, r1.right, r1.bottom);
	fillrectangle(r2.left, r2.top, r2.right, r2.bottom);
	fillrectangle(r3.left, r3.top, r3.right, r3.bottom);
	fillrectangle(r4.left, r4.top, r4.right, r4.bottom);
	fillrectangle(r5.left, r5.top, r5.right, r5.bottom);

	settextcolor(BLUE);
	setbkmode(TRANSPARENT);

	drawtext(_T("EASY"), &r1, DT_SINGLELINE|DT_VCENTER| DT_CENTER);
	drawtext(_T("HARD"), &r2, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	drawtext(_T("SHOW ANSWER"), &r3, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	drawtext(_T("JUDGE ANSWER"), &r4, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	drawtext(_T("F5"), &r5, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	if (writePrompt == 1) {
		drawtext(_T("CORRECT！"), &r6, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else if (writePrompt == -1) {
		drawtext(_T("WRONG！"), &r6, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	int line, row;
	ForLine(line) {
		ForRow(line, row) {
			int num = 9 - abs(5 - line);
			drawHexagon({ INITL + row * 60 - abs(num-5)*30,(LONG)(INITT + line * 30 * sqrt(3)) }, MLENGTH);
		}
	}

}

void chooseFile(int level,int ord[100]) {
	FILE* fp = NULL;
	srand((unsigned)time(NULL));
	int num = rand()%1000;
	if (level == EASY) {
		fp = fopen("beehiveExample/easy_hanidoku.txt", "r");
	}
	else if (level == HARD) {
		fp = fopen("beehiveExample/hard_hanidoku.txt", "r");
	}
	char ords[200];
	for (int i = 1; i < num; i++) {
		fgets(ords, 199, fp);
	}
	char temp;
	fscanf(fp, "%c%c%c%c%c", &temp, &temp, &temp, &temp, &temp);
	for (int i = 1; i <= 61; i++) {
		char number;
		fscanf(fp, "%c", &number);
		ord[i] = number - '0';
	}
	fclose(fp);
}

int judgeMsg(int x, int y) {
	if (INGRID(x,y,r1)) {
		return -1;
	}
	else if(INGRID(x,y,r2)) {
		return -2;
	}
	else if (INGRID(x, y, r3)) {
		return -3;
	}
	else if(INGRID(x,y,r4)) {
		return -4;
	}
	else if (INGRID(x, y, r5) ){
		return -5;
	}
	else {
		int line, row,count=1;
		ForLine(line) {
			ForRow(line, row) {
				int num = 9 - abs(5 - line);
				int nowx = INITL + row * 60 - abs(num - 5) * 30;
				int nowy = INITT + line * 30 * sqrt(3);
				RECT r = { nowx - 20, nowy - 20, nowx + 20, nowy + 20 };
				if (INGRID(x, y, r)) return count;
				count++;
			}
		}
	}
	return 0;
}

#define BUFFERSIZE 2

void Transform(char c[BUFFERSIZE], TCHAR  result[BUFFERSIZE]) {
	MultiByteToWideChar(CP_ACP, 0, c, -1, result, BUFFERSIZE);
}

void showNum(int ord[100]) {
	int count = 0;
	int line, row;
	ForLine(line) {
		ForRow(line, row) {
			int num = 9 - abs(5 - line);
			count++;
			if (ord[count] == 0) continue;
			char c[2];
			c[0] = ord[count] + '0';
			c[1] = '\0';
			TCHAR result[BUFFERSIZE];
			Transform(c,result);
			RECT r1 = { INITL + row * 60 - abs(num - 5) * 30-20, (LONG)(INITT + line * 30 * sqrt(3))-20, INITL + row * 60 - abs(num - 5) * 30+20, (LONG)(INITT + line * 30 * sqrt(3)+20) };
			drawtext(result, &r1, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}
	}
}

bool judgeAnswer(int ord[100], int answer[100]) {
	for (int i = 1; i <= 61; i++) {
		if (ord[i] == 0) continue;
		if (ord[i] != answer[i]) return false;
	}
	return true;
}

void Hanidoku(void)
{
	initgraph(1260, 780, 0);
	initGame(0);
	ExMessage msg;
	int hasFill = 0;
	int hasShow = 0;
	int ord[100]={0};
	int answer[100] = { 0 };
	long mClock=0;
	long nowClock = 0;
	while (true) {
		nowClock = clock();
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				int result = judgeMsg(msg.x, msg.y);
				if (result==-1) {
					cleardevice();
					initGame(0);
					chooseFile(EASY, ord);
					creatCNF("hanidoku.cnf", ord);
					CNF * mCNF = loadFile("hanidoku.cnf");
					solver(mCNF);
					getAnswer(answer);
					showNum(ord);
					hasFill = 1;
				}
				else if (result == -2) {
					cleardevice();
					initGame(0);
					chooseFile(HARD, ord);
					creatCNF("hanidoku.cnf", ord);
					CNF* mCNF = loadFile("hanidoku.cnf");
					drawtext(_T("loading..."), &r7, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
					int res=solver(mCNF);
					if (res == 0) {
						cleardevice();
						initGame(0);
						drawtext(_T("load Failed"), &r7, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
						hasFill = 0;
						continue;
					}
					getAnswer(answer);
					cleardevice();
					initGame(0);
					showNum(ord);
					hasFill = 1;
				}
				else if (result == -3) {
					if (hasFill) {
						if (!hasShow) {
							cleardevice();
							initGame(0);
							showNum(answer);
						}
					}
				}
				else if (result == -4) {
					if (hasFill) {
						bool res = judgeAnswer(ord, answer);
						if (res == true) {
							cleardevice();
							initGame(1);
							showNum(ord);
							mClock = clock();
						}
						else {
							cleardevice();
							initGame(-1);
							showNum(ord);
							mClock = clock();
						}
					}
				}
				else if (result == -5) {
					if (hasFill) {
						cleardevice();
						initGame(0);
						showNum(ord);
					}
				}
				else if (result > 0) {
					if (hasFill) {
						ord[result] += 1;
						if (ord[result] > 9) ord[result] = 0;
						cleardevice();
						initGame(0);
						showNum(ord);
					}
				}

			}
		}
		if (mClock != 0) {
			if ((double)(nowClock - mClock) / CLOCKS_PER_SEC >= 5) {
				cleardevice();
				initGame(0);
				showNum(ord);
				mClock = 0;
			}
		}
	}
	int a;
	if (_getch());
}