#include "key.h"
#include "delay.h"

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //�����ɿ���־
    if(mode==1)
			key_up=1;    //֧������
    if(key_up&&(KEY1==1||KEY2==1))
    {
        delay_ms(20);
        key_up=0;
        if(KEY1==1)  
					return KEY1_PRES;
        else if(KEY2==1)  
					return KEY2_PRES;
    }
		else if(KEY1==0&&KEY2==0)
			key_up=1;
    return 0;   //�ް�������
}
