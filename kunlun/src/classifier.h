/*****************************************************************************************************
 * 文件名：classifier.h
 * 功  能：分类器头文件。
 * 说  明：无。
*****************************************************************************************************/



#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <stdint.h>
#include "common.h"

/*****************************************************************************************************
 * 函数名：GetMinDistance
 * 参  数：1.prewlan     当前的向量基地址
           2.nextwlan    下一个向量基地址
		   3.meawlan     待测向量的基地址
		   4.dimension   向量的维数
 * 说  明：无。
 * 返回值：和待测点最近的向量
*****************************************************************************************************/
RSSI GetMinDistance(RSSI prewlan,RSSI nextwlan,RSSI meawlan,uint8_t dimension);

#endif