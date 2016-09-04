/*****************************************************************************************************
 * �ļ�����IO.c
 * ��  �ܣ��������Դ�ļ���
 * ˵  �����ޡ�
*****************************************************************************************************/

#include "IO.h"

/*****************************************************************************************************
 * ��������GetRSSISample
 * ��  ����1.baseaddr   ����RSSI���ݵĻ���ַ
           2.number     Ҫ��ȡ�ĵ���
		   3.dimension  ÿ�����RSSI�źŸ���
		   4.fp         �ļ�ָ��
 * ˵  ������
 * ����ֵ��-1 ��ȡ��ĸ���С�ڲ���number��ֵ
            1 ��ȡ�ɹ�
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
 * ��������InputMeaWlan
 * ��  ����1.dimension  ÿ�����RSSI�źŸ���
           2.fp         �ļ�ָ��
 * ˵  ������
 * ����ֵ��������RSSI�ṹ��
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
