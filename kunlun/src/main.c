/*****************************************************************************************************
 * 文件名：main.c
 * 功  能：主程序。
 * 说  明：无。
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
		printf("读取文件read.dat失败\n");
	}
	if( (fpinput = fopen("input.dat","r+")) == NULL ){
		printf("读取文件read.dat失败\n");
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
		printf("请将输入数据存放在input.dat中，按下Enter键:");
		getchar();

		meawlan = GetMinPoint(baseaddr,3,meawlan,5);
		printf("最近的坐标为：%d %d\n\n",meawlan.x,meawlan.y);
	}
}
