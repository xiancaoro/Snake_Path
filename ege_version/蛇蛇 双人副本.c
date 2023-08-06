#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define H 35				//�ߴ����	 
#define W 70 

//ȫ�ֱ���
int move,move2;					//С���ƶ�  1234�ֱ������������
int food_x,food_y,food2_x,food2_y;			//ʳ��λ��
int boom_x,boom_y;          //ը��λ��
int oldtail_i,oldtail_j,oldhead_i,oldhead_j;
int oldtail2_i,oldtail2_j,oldhead2_i,oldhead2_j;
int newhead_i,newhead_j;
int newhead2_i,newhead2_j;
extern int canvas[H][W];		//0Ϊ�ո�-1Ϊ�߿�-2,-4Ϊ�Եģ�-3Ϊը����1Ϊ��ͷ�ѣ�����1Ϊ����o
extern int score;                //�÷�ͳ�� 
extern int speed;
extern clock_t start,stop;         //��¼ǰ�����γԵ�ʳ���ʱ�� 
extern double duration;            //��¼�Ե�ʳ��ļ��ʱ�� 


//�ƶ�����
//�ҵ�����canvas�����ݣ���ͷ����������+1
//����β�ͣ����Ԫ�أ���Ϊ0
//�Ե�ʳ�����β�Ͳ�����
//����������������Ұ�һ���հ׵���Ϊ1����ͷ��


//��ʼ������
void StartupDouble() {
	int i,j;
//�߿�
	for(i=0; i<H; i++) {
		canvas[i][0]=-1;
		canvas[i][W-1]=-1;
	}
	for(j=0; j<W; j++) {
		canvas[0][j]=-1;
		canvas[H-1][j]=-1;
	}
//���߳�ʼ��
	canvas[H/2][W/4]=10001;
	for(i=1; i<=4; i++) {
		canvas[H/2+i][W/4]=i+10001;
	}
	canvas[H/2][W*3/4]=20001;
	for(i=1; i<=4; i++) {
		canvas[H/2+i][W*3/4]=i+20001;
	}

//Ĭ�ϳ���������
	move=1;
	move2=1;
//ʳ���ʼ��
	{
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
		food2_x=rand()%(H-5)+2;
		food2_y=rand()%(W-5)+2;
		canvas[food2_x][food2_y]=-4;
	}
//ը����ʼ��
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
		newhead_i=oldhead_i-1;		// ����
		newhead_j=oldhead_j;
	}
	if(move==2) {
		newhead_i=oldhead_i+1;		//����
		newhead_j=oldhead_j;
	}
	if(move==3) {
		newhead_i=oldhead_i;		//����
		newhead_j=oldhead_j-1;
	}
	if(move==4) {
		newhead_i=oldhead_i;		//����
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
		newhead2_i=oldhead2_i-1;		// ����
		newhead2_j=oldhead2_j;
	}
	if(move2==2) {
		newhead2_i=oldhead2_i+1;		//����
		newhead2_j=oldhead2_j;
	}
	if(move2==3) {
		newhead2_i=oldhead2_i;		//����
		newhead2_j=oldhead2_j-1;
	}
	if(move2==4) {
		newhead2_i=oldhead2_i;		//����
		newhead2_j=oldhead2_j+1;
	}
	
	
	//�Ե�ʳ���β�Ͳ����㣬δ�Ե���Ѿɵ�β��ĩ�˹���
	//�Ե�����
	if(canvas[newhead_i][newhead_j]==-2) { //��һ��ʳ��һ
		printf("\a");
		score++;
		if(speed>=20) { //�ٶȷֱ���100,90,80,70,60,50,40,30,20,10��
			speed-=10;
		}
		start=clock();
		stop=clock();
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
	} 
	else if(canvas[newhead_i][newhead_j]==-4) { //��һ��ʳ���
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
	else {       //��һû�Ե�
		canvas[oldtail_i][oldtail_j]=0;
	}

	if(canvas[newhead2_i][newhead2_j]==-2) { //�߶���ʳ��һ
		printf("\a");
		score++;
		if(speed>=20) { //�ٶȷֱ���100,90,80,70,60,50,40,30,20,10��
			speed-=10;
		}
		start=clock();
		stop=clock();
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
	} 
	else if(canvas[newhead2_i][newhead2_j]==-4) { //�߶���ʳ���
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
	else {       //�߶�û�Ե�
		canvas[oldtail2_i][oldtail2_j]=0;
	}

	//��ʱ�۷ֻ���
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

	//��Ϸ�����������ײǽ���Լ����Լ���Ե�ը�����������
	if(canvas[newhead_i][newhead_j]>0||canvas[newhead2_i][newhead2_j]>0
	||canvas[newhead_i][newhead_j]==-1||canvas[newhead2_i][newhead2_j]==-1
	||canvas[newhead_i][newhead_j]==-3||canvas[newhead2_i][newhead2_j]==-3
	||score<-10) {
		printf("\n     Game Over!\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	// ��ͨ�ƶ����ǳԵ�ʳ��
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




