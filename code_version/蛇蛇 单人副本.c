#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define H 35				//�ߴ����	 
#define W 70

//ȫ�ֱ���
int move;					//С���ƶ�  1234�ֱ������������
int food_x,food_y,food2_x,food2_y;			//ʳ��λ��
int boom_x,boom_y;          //ը��λ��
int oldtail_i,oldtail_j,oldhead_i,oldhead_j;
int newhead_i,newhead_j;
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
void StartupSingle() {
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
//����
	canvas[H/2][W/2]=1;
	for(i=1; i<=4; i++) {
		canvas[H/2][W/2-i]=i+1;
	}
//Ĭ�ϳ���������
	move=4;
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


void MovesnakeSingle() {
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
			if(canvas[i][j]>0) {
				if(max<canvas[i][j]) {
					max=canvas[i][j];
					oldtail_i=i;
					oldtail_j=j;
				}
				if(canvas[i][j]==2) {
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

	//�Ե�ʳ���β�Ͳ����㣬δ�Ե���Ѿɵ�β��ĩ�˹���
	//�Ե�����
	if(canvas[newhead_i][newhead_j]==-2) {
		printf("\a");
		score++;
		if(speed>=20) { //�ٶȷֱ���100,90,80,70,60,50,40,30,20,10��
			speed-=10;
		}
		start=clock();
		stop=clock();
		canvas[food_x][food_y]=1;
		food_x=rand()%(H-5)+2;
		food_y=rand()%(W-5)+2;
		canvas[food_x][food_y]=-2;
	} else if(canvas[newhead_i][newhead_j]==-4) {
		printf("\a");
		score++;
		if(speed>=20) {
			speed-=10;
		}
		start=clock();
		stop=clock();
		canvas[food2_x][food2_y]=1;
		food2_x=rand()%(H-5)+2;
		food2_y=rand()%(W-5)+2;
		canvas[food2_x][food2_y]=-4;
	}
	//û�гԵ�
	else {
		canvas[oldtail_i][oldtail_j]=0;
	}

	//��ʱ�۷ֻ���
	{
		if(duration>=30) {
			int max2=0;
			for(i=1; i<H-1; i++) {
				for(j=1; j<W-1; j++) {
					if(canvas[i][j]>0) {
						if(max2<canvas[i][j]) {
							max2=canvas[i][j];
							oldtail_i=i;
							oldtail_j=j;
						}
					}
				}
			}
			canvas[oldtail_i][oldtail_j]=0;
			score--;
		}
	}

	//��Ϸ�����������ײǽ���Լ����Լ���Ե�ը�����������
	if((canvas[newhead_i][newhead_j]>1)||(canvas[newhead_i][newhead_j]==-1)||(canvas[newhead_i][newhead_j]==-3)||score<-10) {
		printf("\n     Game Over!\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	// ��ͨ�ƶ����ǳԵ�ʳ��
	else {
		canvas[newhead_i][newhead_j]=1;
	}
}

void updatawithoutinputSingle() {
	MovesnakeSingle();
}

void updatewithinputSingle() {
	char input;
	if(kbhit()) {
		input=getch();
		if(input=='w') {
			move=1;
			MovesnakeSingle();
		} else if(input=='s') {
			move=2;
			MovesnakeSingle();
		} else if(input=='a') {
			move=3;
			MovesnakeSingle();
		} else if(input=='d') {
			move=4;
			MovesnakeSingle();
		}
	}
}




