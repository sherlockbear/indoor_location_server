/*****************************************************************************************************
 * �ļ�����classifier.c
 * ��  �ܣ�������Դ�ļ���
 * ˵  �����ޡ�
*****************************************************************************************************/

#include "classifier.h"

/*****************************************************************************************************
 * ��������GetMinDistance
 * ��  ����1.prewlan     ��ǰRSSI�ṹ��
           2.nextwlan    ��һ��RSSI�ṹ��
		   3.meawlan     ����RSSI�ṹ��
		   4.dimension   ������ά��
 * ˵  �����ޡ�
 * ����ֵ���ʹ�������������
*****************************************************************************************************/
RSSI GetMinDistance(RSSI prewlan,RSSI nextwlan,RSSI meawlan,uint8_t dimension)
{
	uint32_t  predistance = 0;
	uint32_t nextdistance = 0;
	uint8_t i,j,temp;
	
	for(i = 0;i < dimension;i++){
		temp = 0;
		
		/*�ж��Ƿ�����ͬMAC��ַ���źŲ�������������*/
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
 * ��������GetMinPoint
 * ��  ����1.baseaddr    ����RSSI����Ļ���ַ
           2.number      ����ĸ���
		   3.meawlan     ����RSSI�ź�
		   4.dimension   ������ά��
 * ˵  �����ޡ�
 * ����ֵ����������Ĵ���RSSI�ṹ��
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