#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define H 35				//�ߴ����	 
#define W 70 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int canvas[H][W]={0};		//0Ϊ�ո�-1Ϊ�߿�-2,-4Ϊ�Եģ�-3Ϊը����1Ϊ��ͷ�ѣ�����1Ϊ����o
int score=0;                //�÷�ͳ�� 
int speed=100;
clock_t start,stop;         //��¼ǰ�����γԵ�ʳ���ʱ�� 
double duration=0.0;            //��¼�Ե�ʳ��ļ��ʱ�� 

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
	printf("		   ̰���ߴ���ս\n");
	printf("��Ϸ����*��ʾ��Ϸ�ı߽磬+�����ߵ�ʳ�x�����߳��˻�����ը��Ŷ��\n"); 
	printf("�Ե�ը����ײ���߽����ײ���ߵ����壬����Ϸ������\n");
	printf("����ģʽ���ֱ���w��a��s��d���������ߵ��˶���\n");
	printf("˫��ģʽ����һ��w��a��s��d�����ƣ��߶���i��j��k��l�����ơ�\n");
	printf("��������԰�1ѡ����ģʽ����2ѡ��˫��ģʽ\n");
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
			printf("��������1��2������ַ���������\a\n");
		}
	}
}

void scoreshow() {
	if(score<10) {
		printf("����Ŭ����");
	} else if(score==10) {
		printf("�õ�10���ˣ���̫���ˣ�");
	} else if(score<20) {
		printf("���ͣ���20�ֻ���һ��㣡");
	} else {
		printf("Wonderful!");
	}
}

//�趨��ʾ����
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
	printf("��ǰ���ϴγԵ�ʳ�����õ�ʱ�䣺%.1lf s  ",duration);
	printf("\nĿǰ�÷֣� %d\n",score);
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
