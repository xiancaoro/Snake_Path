#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define H 35				//尺寸界面	 
#define W 70 

//全局变量
int move,move2;					//小蛇移动  1234分别代表上下左右
int food_x,food_y,food2_x,food2_y;			//食物位置
int boom_x,boom_y;          //炸弹位置
int oldtail_i,oldtail_j,oldhead_i,oldhead_j;
int oldtail2_i,oldtail2_j,oldhead2_i,oldhead2_j;
int newhead_i,newhead_j;
int newhead2_i,newhead2_j;
extern int canvas[H][W];		//0为空格，-1为边框，-2,-4为吃的，-3为炸弹，1为蛇头⊙，大于1为身体o
extern int score;                //得分统计 
extern int speed;
extern clock_t start,stop;         //记录前后两次吃到食物的时刻 
extern double duration;            //记录吃到食物的间隔时间 


//移动蛇蛇
//找到数组canvas的数据，蛇头蛇身（正数）+1
//把蛇尾巴（最大元素）变为0
//吃到食物旧则尾巴不归零
//根据输入的上下左右把一个空白点设为1（新头）


//初始化数据
void StartupDouble() {
	int i,j;
//边框
	for(i=0; i<H; i++) {
		canvas[i][0]=-1;
		canvas[i][W-1]=-1;
	}
	for(j=0; j<W; j++) {
		canvas[0][j]=-1;
		canvas[H-1][j]=-1;
	}
//蛇蛇初始化
	canvas[H/2][W/4]=10001;
	for(i=1; i<=4; i++) {
		canvas[H/2+i][W/4]=i+10001;
	}
	canvas[H/2][W*3/4]=20001;
	for(i=1; i<=4; i++) {
		canvas[H/2+i][W*3/4]=i+20001;
	}

//默认初方向向上
	move=1;
	move2=1;
//食物初始化
	{
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
		food2_x=rand()%(H-5)+2;
		food2_y=rand()%(W-5)+2;
		canvas[food2_x][food2_y]=-4;
	}
//炸弹初始化
	{
		boom_x=rand()%(H-5)+2;
		boom_y=rand()%(W-5)+2;
		canvas[boom_x][boom_y]=-3;
	}
}


void MovesnakeDouble() {
	stop=clock();
	int i,j;
	for(i=1; i<H-1; i++) {
		for(j=1; j<W-1; j++) {
			if(canvas[i][j]>0) {
				canvas[i][j]++;
			}
		}
	}

	int max=0;

	for(i=1; i<H-1; i++) {
		for(j=1; j<W-1; j++) {
			if(canvas[i][j]>10000&&canvas[i][j]<20000) {
				if(max<canvas[i][j]) {
					max=canvas[i][j];
					oldtail_i=i;
					oldtail_j=j;
				}
				if(canvas[i][j]%10000==2) {
					oldhead_i=i;
					oldhead_j=j;
				}
			}
		}
	}

	if(move==1) {
		newhead_i=oldhead_i-1;		// 向上
		newhead_j=oldhead_j;
	}
	if(move==2) {
		newhead_i=oldhead_i+1;		//向下
		newhead_j=oldhead_j;
	}
	if(move==3) {
		newhead_i=oldhead_i;		//向左
		newhead_j=oldhead_j-1;
	}
	if(move==4) {
		newhead_i=oldhead_i;		//向右
		newhead_j=oldhead_j+1;
	}

	max=0;

	for(i=1; i<H-1; i++) {
		for(j=1; j<W-1; j++) {
			if(canvas[i][j]>20000) {
				if(max<canvas[i][j]) {
					max=canvas[i][j];
					oldtail2_i=i;
					oldtail2_j=j;
				}
				if(canvas[i][j]%10000==2) {
					oldhead2_i=i;
					oldhead2_j=j;
				}
			}
		}
	}

	if(move2==1) {
		newhead2_i=oldhead2_i-1;		// 向上
		newhead2_j=oldhead2_j;
	}
	if(move2==2) {
		newhead2_i=oldhead2_i+1;		//向下
		newhead2_j=oldhead2_j;
	}
	if(move2==3) {
		newhead2_i=oldhead2_i;		//向左
		newhead2_j=oldhead2_j-1;
	}
	if(move2==4) {
		newhead2_i=oldhead2_i;		//向右
		newhead2_j=oldhead2_j+1;
	}
	
	
	//吃到食物旧尾巴不归零，未吃到则把旧的尾巴末端归零
	//吃到东西
	if(canvas[newhead_i][newhead_j]==-2) { //蛇一吃食物一
		printf("\a");
		score++;
		if(speed>=20) { //速度分别有100,90,80,70,60,50,40,30,20,10档
			speed-=10;
		}
		start=clock();
		stop=clock();
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
	} 
	else if(canvas[newhead_i][newhead_j]==-4) { //蛇一吃食物二
		printf("\a");
		score++;
		if(speed>=20) {
			speed-=10;
		}
		start=clock();
		stop=clock();
		food2_x=rand()%(H-5)+2;
		food2_y=rand()%(W-5)+2;
		canvas[food2_x][food2_y]=-2;
	} 
	else {       //蛇一没吃到
		canvas[oldtail_i][oldtail_j]=0;
	}

	if(canvas[newhead2_i][newhead2_j]==-2) { //蛇二吃食物一
		printf("\a");
		score++;
		if(speed>=20) { //速度分别有100,90,80,70,60,50,40,30,20,10档
			speed-=10;
		}
		start=clock();
		stop=clock();
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
	} 
	else if(canvas[newhead2_i][newhead2_j]==-4) { //蛇二吃食物二
		printf("\a");
		score++;
		if(speed>=20) {
			speed-=10;
		}
		start=clock();
		stop=clock();
		food2_x=rand()%(H-5)+2;
		food2_y=rand()%(W-5)+2;
		canvas[food2_x][food2_y]=-2;
	} 
	else {       //蛇二没吃到
		canvas[oldtail2_i][oldtail2_j]=0;
	}

	//超时扣分机制
//	{
//		if(duration>=30) {
//			int max2=0;
//			for(i=1; i<H-1; i++) {
//				for(j=1; j<W-1; j++) {
//					if(canvas[i][j]>0) {
//						if(max2<canvas[i][j]) {
//							max2=canvas[i][j];
//							oldtail_i=i;
//							oldtail_j=j;
//						}
//					}
//				}
//			}
//			canvas[oldtail_i][oldtail_j]=0;
//			score--;
//		}
//	}

	//游戏死亡的情况：撞墙或自己吃自己或吃到炸弹或分数过低
	if(canvas[newhead_i][newhead_j]>0||canvas[newhead2_i][newhead2_j]>0
	||canvas[newhead_i][newhead_j]==-1||canvas[newhead2_i][newhead2_j]==-1
	||canvas[newhead_i][newhead_j]==-3||canvas[newhead2_i][newhead2_j]==-3
	||score<-10) {
		printf("\n     Game Over!\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	// 普通移动或是吃到食物
	else {
		canvas[newhead_i][newhead_j]=10001;
		canvas[newhead2_i][newhead2_j]=20001;
	}
}

void updatawithoutinputDouble() {
	MovesnakeDouble();
}

void updatewithinputDouble() {
	char input;
	if(kbhit()) {
		input=getch();
		if(input=='w') {
			move=1;
			MovesnakeDouble();
		} 
		else if(input=='s') {
			move=2;
			MovesnakeDouble();
		} 
		else if(input=='a') {
			move=3;
			MovesnakeDouble();
		} 
		else if(input=='d') {
			move=4;
			MovesnakeDouble();
		}
		else if(input=='i') {
			move2=1;
			MovesnakeDouble();
		} 
		else if(input=='k') {
			move2=2;
			MovesnakeDouble();
		} 
		else if(input=='j') {
			move2=3;
			MovesnakeDouble();
		} 
		else if(input=='l') {
			move2=4;
			MovesnakeDouble();
		}
	}
}




