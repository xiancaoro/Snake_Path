#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define H 35				//尺寸界面	 
#define W 70 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int canvas[H][W]={0};		//0为空格，-1为边框，-2,-4为吃的，-3为炸弹，1为蛇头⊙，大于1为身体o
int score=0;                //得分统计 
int speed=100;
clock_t start,stop;         //记录前后两次吃到食物的时刻 
double duration=0.0;            //记录吃到食物的间隔时间 

void gotoxy(int x,int y); 
void rule(); 
void scoreshow();
void show();
void mode();
void mainSingle();
void mainDouble();

int main() {
	rule();
	mode();
	return 0;
}
void gotoxy(int x,int y) {
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void rule() {
	printf("		   贪吃蛇大作战\n");
	printf("游戏规则：*表示游戏的边界，+是蛇蛇的食物，x是蛇蛇吃了会死的炸弹哦。\n"); 
	printf("吃到炸弹、撞到边界或是撞到蛇的身体，即游戏结束。\n");
	printf("单人模式：分别用w，a，s，d键控制蛇蛇的运动。\n");
	printf("双人模式：蛇一用w，a，s，d键控制，蛇二用i，j，k，l键控制。\n");
	printf("现在你可以按1选择单人模式，按2选择双人模式\n");
	while(1)
	{
		if(kbhit())
		{
			break;
		}
	}
} 

void mode(){
	char word;
	while(1) {
		word=getch();
		if(word=='1') {
			start=clock();
			mainSingle();
			break;
		}
		else if(word=='2') {
			start=clock();
			mainDouble();
			break;
		}
		else {
			printf("您输入了1和2以外的字符，请重试\a\n");
		}
	}
}

void scoreshow() {
	if(score<10) {
		printf("继续努力！");
	} else if(score==10) {
		printf("拿到10分了，你太棒了！");
	} else if(score<20) {
		printf("加油，离20分还差一点点！");
	} else {
		printf("Wonderful!");
	}
}

//设定显示界面
void show() {
	stop=clock();
	gotoxy(0,0);
	int i,j;
	for(i=0; i<H; i++) {
		for(j=0; j<W; j++) {
			if(canvas[i][j]==-1) {
				printf("*");
			} else if(canvas[i][j]==0) {
				printf(" ");
			} else if(canvas[i][j]%10000==1) {
				printf("@");
			} else if(canvas[i][j]%10000>1) {
				printf("o");
			} else if(canvas[i][j]==-2||canvas[i][j]==-4) {
				printf("+");
			} else if(canvas[i][j]==-3) {
				printf("x");
			}
		}
		printf("\n");
	}
	duration=((double)(stop-start))/CLK_TCK;
	printf("当前距上次吃到食物所用的时间：%.1lf s  ",duration);
	printf("\n目前得分： %d\n",score);
	scoreshow();
	Sleep(speed);
}

void mainSingle() {
	StartupSingle();
	while(1) {
		show();
		updatawithoutinputSingle();
		updatewithinputSingle();
	}
}

void mainDouble() {
	StartupDouble();
	while(1) {
		show();
		updatawithoutinputDouble();
		updatewithinputDouble();
	}
}
