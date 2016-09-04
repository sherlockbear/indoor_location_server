/*****************************************************************************************************
 * �ļ�����main.c
 * ��  �ܣ�������
 * ˵  �����ޡ�
*****************************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include "common.h"
#include "classifier.h"
#include "IO.h"

void MainLoop(RSSI* baseaddr,RSSI meawlan);

int main()
{
	FILE *fpread,*fpinput;
	if( (fpread = fopen("read.dat","r+")) == NULL ){
		printf("��ȡ�ļ�read.datʧ��\n");
	}
	if( (fpinput = fopen("input.dat","r+")) == NULL ){
		printf("��ȡ�ļ�read.datʧ��\n");
	}

	RSSI wlan[3];
	RSSI meawlan;
	GetRSSISample(wlan,3,5,fpread);
    meawlan = InputMeaWlan(5,fpinput);

	MainLoop(wlan,meawlan);
	return 0;
}

void MainLoop(RSSI *baseaddr,RSSI meawlan)
{
	while(1){
		printf("�뽫�������ݴ����input.dat�У�����Enter��:");
		getchar();

		meawlan = GetMinPoint(baseaddr,3,meawlan,5);
		printf("���������Ϊ��%d %d\n\n",meawlan.x,meawlan.y);
	}
}
