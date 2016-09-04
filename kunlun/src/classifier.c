/*****************************************************************************************************
 * 文件名：classifier.c
 * 功  能：分类器源文件。
 * 说  明：无。
*****************************************************************************************************/

#include "classifier.h"

/*****************************************************************************************************
 * 函数名：GetMinDistance
 * 参  数：1.prewlan     当前RSSI结构体
           2.nextwlan    下一个RSSI结构体
		   3.meawlan     待测RSSI结构体
		   4.dimension   向量的维数
 * 说  明：无。
 * 返回值：和待测点最近的向量
*****************************************************************************************************/
RSSI GetMinDistance(RSSI prewlan,RSSI nextwlan,RSSI meawlan,uint8_t dimension)
{
	uint32_t  predistance = 0;
	uint32_t nextdistance = 0;
	uint8_t i,j,temp;
	
	for(i = 0;i < dimension;i++){
		temp = 0;
		
		/*判断是否有相同MAC地址的信号并计算向量距离*/
		for(j = 0;j < dimension;j++){
			if( meawlan.MAC[i] == prewlan.MAC[j] ){
				predistance += (meawlan.dBm[i] - prewlan.dBm[j]) * (meawlan.dBm[i] - prewlan.dBm[j]);
				temp++;
				break;
			}
		}
		for(j = 0;j < dimension;j++){
			if( meawlan.MAC[i] == nextwlan.MAC[j] ){
				nextdistance += (meawlan.dBm[i] - nextwlan.dBm[j]) * (meawlan.dBm[i] - nextwlan.dBm[j]);
				temp += 2;
				break;
			}
		}
		if(temp == 1){
			nextdistance += (meawlan.dBm[i] + 255) * (meawlan.dBm[i] + 255);
		}
		else if(temp == 2){
			predistance += (meawlan.dBm[i] + 255) * (meawlan.dBm[i] + 255);
		}
	}
	
	if( nextdistance < predistance )
		return nextwlan;
	else
		return prewlan;
}

/*****************************************************************************************************
 * 函数名：GetMinPoint
 * 参  数：1.baseaddr    保存RSSI样点的基地址
           2.number      样点的个数
		   3.meawlan     待测RSSI信号
		   4.dimension   向量的维数
 * 说  明：无。
 * 返回值：含有坐标的待测RSSI结构体
*****************************************************************************************************/
RSSI GetMinPoint(RSSI* baseaddr,uint32_t number,RSSI meawlan,uint8_t dimension)
{
	uint32_t i;
	RSSI prewlan;
	
	prewlan = baseaddr[0];
	
	for(i = 1;i < number;i++){
		prewlan = GetMinDistance(prewlan,baseaddr[i],meawlan,dimension);
	}
	
	meawlan.x = prewlan.x;
	meawlan.y = prewlan.y;
	
	return meawlan;
}