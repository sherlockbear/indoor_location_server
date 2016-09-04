/*****************************************************************************************************
 * 文件名：IO.c
 * 功  能：输入输出源文件。
 * 说  明：无。
*****************************************************************************************************/

#include "IO.h"

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
int8_t GetRSSISample(RSSI* baseaddr,uint32_t number,uint8_t dimension,FILE* fp)
{
    uint8_t mac[6];
    uint32_t i,j,k;

    for(i = 0;i < number;i++){
        fscanf(fp,"[%d, %d]\n[",&baseaddr[i].x,&baseaddr[i].y);

        for(j=0;j<dimension;j++){
            fscanf(fp,"'%x:%x:%x:%x:%x:%x', %d, ",&mac[0],&mac[1],&mac[2],&mac[3],&mac[4],&mac[5],&baseaddr[i].dBm[j]);
            baseaddr[i].MAC[j] = mac[0];
            for(k = 1;k < 6;k++){
				baseaddr[i].MAC[j] = baseaddr[i].MAC[j]*256 + mac[k];
			}
        }
        fscanf(fp,"]\n");
        if(feof(fp))
            return -1;
    }
    return 0;
}

/*****************************************************************************************************
 * 函数名：InputMeaWlan
 * 参  数：1.dimension  每个点的RSSI信号个数
           2.fp         文件指针
 * 说  明：无
 * 返回值：待测点的RSSI结构体
*****************************************************************************************************/
RSSI InputMeaWlan(uint8_t dimension,FILE* fp)
{
	RSSI meawlan;
	uint8_t mac[6];
	uint8_t j,k;

	meawlan.x = 0;
	meawlan.y = 0;

	fscanf(fp,"[");
	for(j = 0;j < dimension;j++){
		fscanf(fp,"'%x:%x:%x:%x:%x:%x', %d, ",&mac[0],&mac[1],&mac[2],&mac[3],&mac[4],&mac[5],&meawlan.dBm[j]);
		meawlan.MAC[j] = mac[0];
		for(k = 1;k < 6;k++){
			meawlan.MAC[j] = meawlan.MAC[j]*256 + mac[k];
		}
	}
	fscanf(fp,"]");

	return meawlan;
}
