/*****************************************************************************************************
 * 文件名：IO.h
 * 功  能：输入输出头文件。
 * 说  明：无。
*****************************************************************************************************/

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdint.h>
#include "common.h"

/*****************************************************************************************************
 * 函数名：GetRSSISample
 * 参  数：1.baseaddr   保存RSSI数据的基地址
           2.number     要读取的点数
		   3.dimension  每个点的RSSI信号个数
		   4.fp         文件指针
 * 说  明：无
 * 返回值：-1 读取点的个数小于参数number的值
            1 读取成功
*****************************************************************************************************/
int8_t GetRSSISample(RSSI* baseaddr,uint32_t number,uint8_t dimension,FILE* fp);

/*****************************************************************************************************
 * 函数名：InputMeaWlan
 * 参  数：1.dimension  每个点的RSSI信号个数
           2.fp         文件指针
 * 说  明：无
 * 返回值：待测点的RSSI结构体
*****************************************************************************************************/
RSSI InputMeaWlan(uint8_t dimension,FILE* fp)

#endif
