#include "task.h"
#include "car.h"
#include "c.h"


Point ppc[6];//pipeline processing coordinates��ˮ���������

u8 runFinishedTime=0;
u8 taskIndex=0;
u8 flagOrderPPC=0;
u8 flagOrderPPCProToFhd=0;
u8 orderPPC=0;


#define SCAN_TIME 5



void PutMeterial(void);
void X_N_FixAngle(void);
void Y_N_FixAngle(void);

void X_N_FixAngle(void)
{

				//������Ҫ��ʱ������
		if(TSC1 || TSD4)
		{
			CarTurnCounterClockwise();
			CarRunCounterClockwise(400);
			delay_ms(100);
			CarStop();
		}
		else if(TSC4 || TSD1)
		{
			//˳ʱ������
			CarTurnClockwise();
			CarRunClockwise(400);
			delay_ms(100);
			CarStop();
		}
		else if(TSC2 || TSD3)
		{
			CarTurnCounterClockwise();
			CarRunCounterClockwise(400);
			delay_ms(40);
			CarStop();
		}
		else if(TSC3 || TSD2)
		{
			//˳ʱ������
			CarTurnClockwise();
			CarRunClockwise(400);
			delay_ms(40);
			CarStop();
		}
}


void Y_N_FixAngle(void)
{
	if(TSB1||TSB2||TSA2||TSA1){
				//˳ʱ������
			CarTurnCounterClockwise();
			CarRunCounterClockwise(400);
			delay_ms(100);
			CarStop();
	}
	else if(TSB7||TSB8||TSA7||TSA8){
				//˳ʱ������
			CarTurnClockwise();
			CarRunClockwise(400);
			delay_ms(100);
			CarStop();
	}

}


bool equal(Point A,Point B)
{
	if(A.x==B.x && A.y ==B.y)
		return true;
	else 
		return false;

}

void PutMeterial(void)
{
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
}

void CarFineTuningPro(void)
{
		CarTurnLeft();
		while(1)
		{
			CarRunLeft(350);
			if(TSA1)
			{
				CarStop();
				CarLeftBrake_WithRight();
				break;
			}
			delay_ms(2);
		}
}




void CarFineTuningRaw_X_N(void)
{
		CarTurnForward();
		car.speedBase=350;
		while(1)
		{
			CarForwardPID();
			if((TSB8&&TSB7)||(TSB1&&TSB2))
			{
				CarStop();
				CarForwardBrake_WithBackward();
				break;
			}
			delay_ms(2);
		}
}


void CarFineTuningRaw_X_P(void)
{
		CarTurnBackward();
		car.speedBase=400;
		while(1)
		{
			CarBackwardPID();
			if(TSC2||TSC3)
			{
				CarStop();
				CarBackwardBrake_WithForward();
				break;
			}
			delay_ms(2);
		}
}





void CarFineTuningRaw_Y_N(void)
{
		CarTurnRight();
		car.speedBase=400;
		while(1)
		{
			//CarRunLeft(350);
			CarRightPID();
			delay_ms(2);
			if(TSA1||TSB8)
			{
				CarRightBrake_WithLeft();
				break;
			}
		}
				
		//������б
		if(!TSB8&&TSA1)
		{
			//��Ҫ˳ʱ������,LF RF��ͣ LR RR�ӳ�һ���ټ�ͣ
			CarTurnClockwise();
			CarRunClockwise(300);
			delay_ms(100);
			CarStop();
		}
		else if(TSB8&&!TSA1)
		{
			//��ʱ������
			CarTurnCounterClockwise();
			CarRunCounterClockwise(300);
			delay_ms(100);
			CarStop();
		}

		u8 i=GetTSE_Number();
		if(i<4)
		{
			CarTurnBackward();
			CarRunBackward(400);
			delay_ms((4-i)*100);
			CarStop();
		}
		else if(i>5)
		{
			CarTurnForward();
			CarRunForward(400);
			delay_ms((i-5)*100);
			CarStop();
		}
			
	
}


void CarFineTuningRaw_Y_P(void)
{
		CarTurnLeft();
		car.speedBase=400;
		while(1)
		{
			//CarRunRight(350);
			CarLeftPID();
			if(TSB5 || TSA4)
			{
				CarStop();
				//CarRightBrake_WithLeft();
				break;
			}
			delay_ms(2);
		}
}







void CarFineTuningPro_Y_P(void)
{
		CarTurnLeft();
		car.speedBase=400;
		while(1)
		{
			//CarRunLeft(350);
			CarLeftPID();
			delay_ms(2);
			if(TSA8||TSB1)
			{
				CarLeftBrake_WithRight();
				break;
			}
		}
				
		//������б
		if(!TSA8&&TSB1)
		{
			//��Ҫ˳ʱ������,LF RF��ͣ LR RR�ӳ�һ���ټ�ͣ
			CarTurnClockwise();
			CarRunClockwise(300);
			delay_ms(100);
			CarStop();
		}
		else if(TSA8&&!TSB1)
		{
			//��ʱ������
			CarTurnCounterClockwise();
			CarRunCounterClockwise(300);
			delay_ms(100);
			CarStop();
		}

		u8 i=GetTSE_Number();
		if(i<4)
		{
			CarTurnBackward();
			CarRunBackward(400);
			delay_ms((4-i)*100);
			CarStop();
		}
		else if(i>5)
		{
			
			CarTurnForward();
			CarRunForward(400);
			delay_ms((i-5)*100);
			CarStop();
		}
			
	
}


void CarFineTuningPro_Y_N(void)
{
		CarTurnRight();
		car.speedBase=400;
		while(1)
		{
			//CarRunRight(350);
			CarRightPID();
			if(TSB4 || TSA5)
			{
				CarStop();
				//CarRightBrake_WithLeft();
				break;
			}
			delay_ms(2);
		}
}




void CarFineTuningFhd_X_N(void)
{
		CarTurnForward();
		car.speedBase=400;
		while(1)
		{
			CarForwardPID();
			if((TSA8&&TSA7)||(TSA1&&TSA2))
			{
				CarStop();
				CarForwardBrake_WithBackward();
				break;
			}
			delay_ms(2);
		}
		



		
}


void CarFineTuningFhd_X_P(void)
{
		CarTurnBackward();
		car.speedBase=400;
		while(1)
		{
			//CarRunBackward(350);
			CarBackwardPID();
			if(TSC2||TSC3)
			{
				CarStop();
				CarBackwardBrake_WithForward();
				break;
			}
			delay_ms(2);
		}
}




void CarFineTuningProBack(void)
{
		CarTurnRight();
		while(1)
		{
			CarRunRight(350);
			if(TSA5)
			{
				CarStop();
				CarRightBrake_WithLeft();
				break;
			}		
		}
		delay_ms(2);
}


void SendAndWaitMV(u8 order)
{ 
	car.order=ORDER_RESET;
	SendChar_MV(order);
	while(car.order==ORDER_RESET)
		delay_us(100);
}


void CarSetProcessPoint(void)
{
	switch(car.order)
	{
		//���������������ǵ�һ��
		case ORDER_RGB:
			Point_ProcessingAeraRed.x=3;
			Point_ProcessingAeraBlue.x=5;
			break;
		case ORDER_RBG:
			Point_ProcessingAeraRed.x=3;
			Point_ProcessingAeraGreen.x=5;
			break;
		case ORDER_GRB:
			Point_ProcessingAeraGreen.x=3;
			Point_ProcessingAeraBlue.x=5;
			break;
		case ORDER_GBR:
			Point_ProcessingAeraGreen.x=3;
			Point_ProcessingAeraRed.x=5;
			break;
		case ORDER_BRG:
			Point_ProcessingAeraBlue.x=3;
			Point_ProcessingAeraGreen.x=5;
			break;
		case ORDER_BGR:
			Point_ProcessingAeraBlue.x=3;
			Point_ProcessingAeraRed.x=5;
			break;
	}
}






void CarSetFinishedPoint(void)
{
	switch(car.order)
	{
		//���������������ǵ�һ��
		case ORDER_RGB:
			Point_FinishedAeraRed.y=3;
			Point_FinishedAeraBlue.y=5;
			break;
		case ORDER_RBG:
			Point_FinishedAeraRed.y=3;
			Point_FinishedAeraGreen.y=5;
			break;
		case ORDER_GRB:
			Point_FinishedAeraGreen.y=3;
			Point_FinishedAeraBlue.y=5;
			break;
		case ORDER_GBR:
			Point_FinishedAeraGreen.y=3;
			Point_FinishedAeraRed.y=5;
			break;
		case ORDER_BRG:
			Point_FinishedAeraBlue.y=3;
			Point_FinishedAeraGreen.y=5;
			break;
		case ORDER_BGR:
			Point_FinishedAeraBlue.y=3;
			Point_FinishedAeraRed.y=5;
			break;
	}
}









void CarSetProcessPointRFP(void)
{
	switch(car.order)
	{
		case ORDER_RGB:
			Point_ProcessingAeraRed.y-=1;
			Point_ProcessingAeraBlue.y+=1;
			break;
		case ORDER_RBG:
			Point_ProcessingAeraRed.y-=1;
			Point_ProcessingAeraGreen.y+=1;
			break;
		case ORDER_GRB:
			Point_ProcessingAeraGreen.y-=1;
			Point_ProcessingAeraBlue.y+=1;
			break;
		case ORDER_GBR:
			Point_ProcessingAeraGreen.y-=1;
			Point_ProcessingAeraRed.y+=1;
			break;
		case ORDER_BRG:
			Point_ProcessingAeraBlue.y-=1;
			Point_ProcessingAeraGreen.y+=1;
			break;
		case ORDER_BGR:
			Point_ProcessingAeraBlue.y-=1;
			Point_ProcessingAeraRed.y+=1;
			break;
	}
}






void CarSetFinishedPointRFP(void)
{
	//��XN��XPɨ��
	switch(car.order)
	{
		case ORDER_RGB:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
	}
}












void CarSetProcessPointFPR(void)
{
	//��XN��XP
	switch(car.order)
	{
		case ORDER_RGB:
			Point_ProcessingAeraRed.x-=1;
			Point_ProcessingAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_ProcessingAeraRed.x-=1;
			Point_ProcessingAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_ProcessingAeraGreen.x-=1;
			Point_ProcessingAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_ProcessingAeraGreen.x-=1;
			Point_ProcessingAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_ProcessingAeraBlue.x-=1;
			Point_ProcessingAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_ProcessingAeraBlue.x-=1;
			Point_ProcessingAeraRed.x+=1;
			break;
	}
}






void CarSetFinishedPointFPR(void)
{
	switch(car.order)
	{
		case ORDER_RGB:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
	}
}








void CarSetProcessPointPFR(void)
{
	//��XN��XP
	switch(car.order)
	{
		case ORDER_RGB:
			Point_ProcessingAeraRed.x-=1;
			Point_ProcessingAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_ProcessingAeraRed.x-=1;
			Point_ProcessingAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_ProcessingAeraGreen.x-=1;
			Point_ProcessingAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_ProcessingAeraGreen.x-=1;
			Point_ProcessingAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_ProcessingAeraBlue.x-=1;
			Point_ProcessingAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_ProcessingAeraBlue.x-=1;
			Point_ProcessingAeraRed.x+=1;
			break;
	}
}






void CarSetFinishedPointPFR(void)
{
	switch(car.order)
	{
		case ORDER_RGB:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
	}
}






void CarSetProcessPointPRF(void)
{
	//��XN��XP
	switch(car.order)
	{
		case ORDER_RGB:
			Point_ProcessingAeraRed.x-=1;
			Point_ProcessingAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_ProcessingAeraRed.x-=1;
			Point_ProcessingAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_ProcessingAeraGreen.x-=1;
			Point_ProcessingAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_ProcessingAeraGreen.x-=1;
			Point_ProcessingAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_ProcessingAeraBlue.x-=1;
			Point_ProcessingAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_ProcessingAeraBlue.x-=1;
			Point_ProcessingAeraRed.x+=1;
			break;
	}
}






void CarSetFinishedPointPRF(void)
{
	switch(car.order)
	{
		case ORDER_RGB:
			Point_FinishedAeraRed.y-=1;
			Point_FinishedAeraBlue.y+=1;
			break;
		case ORDER_RBG:
			Point_FinishedAeraRed.y-=1;
			Point_FinishedAeraGreen.y+=1;
			break;
		case ORDER_GRB:
			Point_FinishedAeraGreen.y-=1;
			Point_FinishedAeraBlue.y+=1;
			break;
		case ORDER_GBR:
			Point_FinishedAeraGreen.y-=1;
			Point_FinishedAeraRed.y+=1;
			break;
		case ORDER_BRG:
			Point_FinishedAeraBlue.y-=1;
			Point_FinishedAeraGreen.y+=1;
			break;
		case ORDER_BGR:
			Point_FinishedAeraBlue.y-=1;
			Point_FinishedAeraRed.y+=1;
			break;
	}
}




void CarSetProcessPointFRP(void)
{
	//��YP��YN
	switch(car.order)
	{
		case ORDER_RGB:
			Point_ProcessingAeraRed.y+=1;
			Point_ProcessingAeraBlue.y-=1;
			break;
		case ORDER_RBG:
			Point_ProcessingAeraRed.y+=1;
			Point_ProcessingAeraGreen.y-=1;
			break;
		case ORDER_GRB:
			Point_ProcessingAeraGreen.y+=1;
			Point_ProcessingAeraBlue.y-=1;
			break;
		case ORDER_GBR:
			Point_ProcessingAeraGreen.y+=1;
			Point_ProcessingAeraRed.y-=1;
			break;
		case ORDER_BRG:
			Point_ProcessingAeraBlue.y+=1;
			Point_ProcessingAeraGreen.y-=1;
			break;
		case ORDER_BGR:
			Point_ProcessingAeraBlue.y+=1;
			Point_ProcessingAeraRed.y-=1;
			break;
	}
}






void CarSetFinishedPointFRP(void)
{
	//��XN��XPɨ��
	switch(car.order)
	{
		case ORDER_RGB:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_RBG:
			Point_FinishedAeraRed.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_GRB:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraBlue.x+=1;
			break;
		case ORDER_GBR:
			Point_FinishedAeraGreen.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
		case ORDER_BRG:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraGreen.x+=1;
			break;
		case ORDER_BGR:
			Point_FinishedAeraBlue.x-=1;
			Point_FinishedAeraRed.x+=1;
			break;
	}
}












void CarSetPipelinePoint_A(void)
{
	switch(flagOrderPPC)
	{
		case ORDER_RGB:
			ppc[0]=Point_ProcessingAeraRed;
			ppc[1]=Point_ProcessingAeraGreen;
			ppc[2]=Point_ProcessingAeraBlue;
			break;
		case ORDER_RBG:
			ppc[0]=Point_ProcessingAeraRed;
			ppc[1]=Point_ProcessingAeraBlue;
			ppc[2]=Point_ProcessingAeraGreen;
			break;
		case ORDER_GRB:
			ppc[0]=Point_ProcessingAeraGreen;
			ppc[1]=Point_ProcessingAeraRed;
			ppc[2]=Point_ProcessingAeraBlue;
			break;
		case ORDER_GBR:
			ppc[0]=Point_ProcessingAeraGreen;
			ppc[1]=Point_ProcessingAeraBlue;
			ppc[2]=Point_ProcessingAeraRed;
			break;
		case ORDER_BRG:
			ppc[0]=Point_ProcessingAeraBlue;
			ppc[1]=Point_ProcessingAeraRed;
			ppc[2]=Point_ProcessingAeraGreen;
			break;
		case ORDER_BGR:
			ppc[0]=Point_ProcessingAeraBlue;
			ppc[1]=Point_ProcessingAeraGreen;
			ppc[2]=Point_ProcessingAeraRed;
			break;
	}
}






void CarSetPipelinePoint_B(void)
{
	switch(flagOrderPPCProToFhd)
	{
		case ORDER_RGB:
			ppc[0]=Point_ProcessingAeraRed;
			ppc[2]=Point_ProcessingAeraGreen;
			ppc[4]=Point_ProcessingAeraBlue;
			ppc[1]=Point_FinishedAeraRed;
			ppc[3]=Point_FinishedAeraGreen;
			ppc[5]=Point_FinishedAeraBlue;
			break;
		case ORDER_RBG:
			ppc[0]=Point_ProcessingAeraRed;
			ppc[2]=Point_ProcessingAeraBlue;
			ppc[4]=Point_ProcessingAeraGreen;
			ppc[1]=Point_FinishedAeraRed;
			ppc[3]=Point_FinishedAeraBlue;
			ppc[5]=Point_FinishedAeraGreen;
			break;
		case ORDER_GRB:
			ppc[0]=Point_ProcessingAeraGreen;
			ppc[2]=Point_ProcessingAeraRed;
			ppc[4]=Point_ProcessingAeraBlue;
			ppc[1]=Point_FinishedAeraGreen;
			ppc[3]=Point_FinishedAeraRed;
			ppc[5]=Point_FinishedAeraBlue;
			break;
		case ORDER_GBR:
			ppc[0]=Point_ProcessingAeraGreen;
			ppc[2]=Point_ProcessingAeraBlue;
			ppc[4]=Point_ProcessingAeraRed;
			ppc[1]=Point_FinishedAeraGreen;
			ppc[3]=Point_FinishedAeraBlue;
			ppc[5]=Point_FinishedAeraRed;
			break;
		case ORDER_BRG:
			ppc[0]=Point_ProcessingAeraBlue;
			ppc[2]=Point_ProcessingAeraRed;
			ppc[4]=Point_ProcessingAeraGreen;
			ppc[1]=Point_FinishedAeraBlue;
			ppc[3]=Point_FinishedAeraRed;
			ppc[5]=Point_FinishedAeraGreen;
			break;
		case ORDER_BGR:
			ppc[0]=Point_ProcessingAeraBlue;
			ppc[2]=Point_ProcessingAeraGreen;
			ppc[4]=Point_ProcessingAeraRed;
			ppc[1]=Point_FinishedAeraBlue;
			ppc[3]=Point_FinishedAeraGreen;
			ppc[5]=Point_FinishedAeraRed;
			break;
	}
}



void TernimalHandleNoRotation(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		SendAndWaitMV(ORDER_QRCODE);		
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialArea;
	}
//	else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==2)
	{
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=Point_ProcessingAeraC;
	}
	//else if(equal(car.currentPoint,Point_ProcessingAeraA))//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		SendAndWaitMV(ORDER_SCANCOLOR);
		MoveOne_Forward_X_N();		
		SendAndWaitMV(ORDER_SCANCOLOR);
		MoveOne_Forward_X_N();
		SendAndWaitMV(ORDER_SCANCOLOR);
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPoint();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Backward_X_P();
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPoint();//���üӹ���λ����Ϣ
			else
			{
				MoveOne_Backward_X_P();
				MoveOne_Backward_X_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Forward_X_N();		
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Forward_X_N();
				SendAndWaitMV(ORDER_SCANCOLOR);			
				
				CarSetProcessPoint();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=ppc[0].x-car.currentPoint.x;
		
		if(t==1)
		{
			MoveOne_Backward_X_P();
		}
		else if(t==2)
		{
			MoveOne_Backward_X_P();
			MoveOne_Backward_X_P();
		}
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		
		if(equal(ppc[1],Point_ProcessingAeraRed))
			car.terminalPoint=Point_RawMaterialAreaStartMV;
		else		
			car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();			
		
		if(equal(ppc[2],Point_ProcessingAeraRed))
			car.terminalPoint=Point_RawMaterialAreaStartMV;
		else		
			car.terminalPoint=Point_RawMaterialArea;	
	}
//	else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==6)
	{
		SendAndWaitMV(ORDER_CARRYUP);		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		SendAndWaitMV(ORDER_SCANCOLOR);
		MoveOne_Left_Y_P();
		SendAndWaitMV(ORDER_SCANCOLOR);
		MoveOne_Left_Y_P();
		SendAndWaitMV(ORDER_SCANCOLOR);
		
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPoint();//���������
		else{	
			MoveOne_Right_Y_N();
			MoveOne_Right_Y_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPoint();//���������
			else
			{
				MoveOne_Right_Y_N();
				MoveOne_Right_Y_N();
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);			
				
				CarSetFinishedPoint();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}

}















void TernimalHandleNoRotationRPF(void)
{
	///�������մ�
	if(car.pos==1)
	{	
		SendAndWaitMV(ORDER_SCANOBJECT);
		
		MoveOne_Forward_X_N();
		MoveOne_Forward_X_N();
		
		
		MoveOne_Right_Y_N();
		
		u8 t=GetTSC_Number();
		if(t<4)
		{
			CarTurnBackward();
			CarRunBackward(500);
			delay_ms((4-t)*60);
			CarStop();
			SendAndWaitMV(ORDER_QRCODE);
			CarTurnForward();
			CarRunForward(500);
			delay_ms((4-t)*60);
			CarStop();
			
		}
		else
		{
			//�����ź�
		SendAndWaitMV(ORDER_QRCODE);
		
		}
		
		
		
		
				
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;	
	}
	
	else if(car.pos==2)
	{
		u8 i=0;
		while(i<SCAN_TIME)
		{
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetProcessPoint();//���üӹ���λ����Ϣ
				break;
			}
			if(i==SCAN_TIME){
				car.order=ORDER_RGB;
				CarSetProcessPoint();		
			}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
			i++;
		}
				
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		car.terminalPoint=Point_RawMaterialArea;
	}
	
	
	
	else if(car.pos==3)
	{
		Y_N_FixAngle();
		//���������		
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[0];
	}
	//��һ�ε��ӹ���
	else if(car.pos==4)
	{
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==5)
	{
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[1];
	}
	//�ڶ��ε��ӹ���
	else if(car.pos==6)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();			

		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==7)
	{
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//������ȥ�ӹ���
	else if(car.pos==8)
	{
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_QRCodeAera;
	}
	//�ڶ���ɨ��ά��
	else if(car.pos==9)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
	else if(car.pos==10)//ȥɨ�������
	{
		u8 i=0;
		while(i<SCAN_TIME)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetFinishedPoint();//���������
				break;
			}
			MoveOne_Right_Y_N();
			MoveOne_Right_Y_N();
		}		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//���ӹ����ö���1
	else if(car.pos==11)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[1];
	}
	//��������Ŷ���1
	else if(car.pos==12)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[2];
	}
	//���ӹ����ö���2
	else if(car.pos==13)
	{		
		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[3];
	}
	//��������Ŷ���2
	else if(car.pos==14)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[4];
	}
	//���ӹ����ö���3
	else if(car.pos==15)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[5];
	}
	//��������Ŷ���3
	else if(car.pos==16)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//�س�
	else if(car.pos==17)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}

}





void TernimalHandleNoRotationRFP(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		SendAndWaitMV(ORDER_SCANOBJECT);
		
		MoveOne_Forward_X_N();
		MoveOne_Forward_X_N();
		MoveOne_Right_Y_N();
		
		u8 t=GetTSC_Number();
		if(t<4)
		{
			CarTurnBackward();
			CarRunBackward(500);
			delay_ms((4-t)*60);
			CarStop();
			SendAndWaitMV(ORDER_QRCODE);
			CarTurnForward();
			CarRunForward(500);
			delay_ms((4-t)*60);
			CarStop();
			
		}
		else
		{
			//�����ź�
		SendAndWaitMV(ORDER_QRCODE);
		
		}
		
		
		//�����ź�	
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;
	}
	else if(car.pos==2)
	{
			//ȥ�ӹ���ɨ��ɫ
			u8 i=0;
			while(i<8)
			{
				i++;
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();		
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
					CarSetProcessPointRFP();//���üӹ���λ����Ϣ
					break;
				}
				MoveOne_Right_Y_N();
				MoveOne_Right_Y_N();
			}
					
			//����֮ǰɨ���Ķ�ά����������λ������
			CarSetPipelinePoint_A();//���ð��˵�˳��
			car.terminalPoint=Point_RawMaterialArea;
	}
	else if(car.pos==3)
	{
		//�����ź�
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);
		if(car.order==ORDER_FALSE)
		{
			Y_N_FixAngle();
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[0];
	}
	//��һ�ε��ӹ���
	else if(car.pos==4)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		

		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==5)
	{
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==6)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==7)
	{
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);		
		if(car.order==ORDER_FALSE)
		{
			Y_N_FixAngle();
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==8)
	{
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==9)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==10)
	{
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetProcessPointRFP();//���üӹ���λ����Ϣ
				break;
			}
			MoveOne_Backward_X_P();
			MoveOne_Backward_X_P();
		}

		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==12)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==14)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==16)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==17)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}

}



void TernimalHandleNoRotationRFP_t(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		SendAndWaitMV(ORDER_SCANOBJECT);
		
		MoveOne_Forward_X_N();
		MoveOne_Forward_X_N();
		MoveOne_Right_Y_N();
		
		u8 t=GetTSC_Number();
		if(t<4)
		{
			CarTurnBackward();
			CarRunBackward(500);
			delay_ms((4-t)*60);
			CarStop();
			SendAndWaitMV(ORDER_QRCODE);
			CarTurnForward();
			CarRunForward(500);
			delay_ms((4-t)*60);
			CarStop();
			
		}
		else
		{
			//�����ź�
		SendAndWaitMV(ORDER_QRCODE);
		
		}
		
		
		//�����ź�	
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;
	}
	else if(car.pos==2)
	{
			//ȥ�ӹ���ɨ��ɫ
			u8 i=0;
			while(i<8)
			{
				i++;
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();		
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
					CarSetProcessPointRFP();//���üӹ���λ����Ϣ
					break;
				}
				MoveOne_Right_Y_N();
				MoveOne_Right_Y_N();
			}
					
			//����֮ǰɨ���Ķ�ά����������λ������
			CarSetPipelinePoint_A();//���ð��˵�˳��
			car.terminalPoint=Point_RawMaterialArea;
	}
	else if(car.pos==3)
	{
		//�����ź�
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);
		if(car.order==ORDER_FALSE)
		{
			Y_N_FixAngle();
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[0];
	}
	//��һ�ε��ӹ���
	else if(car.pos==4)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		

		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==5)
	{
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==6)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==7)
	{
		Y_N_FixAngle();
		SendAndWaitMV(ORDER_CARRYUP);		
		if(car.order==ORDER_FALSE)
		{
			Y_N_FixAngle();
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==8)
	{
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==9)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==10)
	{
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetProcessPointRFP();//���üӹ���λ����Ϣ
				break;
			}
			MoveOne_Backward_X_P();
			MoveOne_Backward_X_P();
		}

		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==12)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==14)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==16)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==17)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}

}





void TernimalHandleNoRotationRFP_Test(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		delay_ms(500);	
		car.order=ORDER_BGR;  
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialArea;
	}
	else if(car.pos==2)
	{
		//�����ź�
		delay_ms(500);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=Point_ProcessingAeraC;
	}
	//else if(equal(car.currentPoint,Point_ProcessingAeraA))//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		delay_ms(500);
		MoveOne_Left_Y_P();		
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointRFP();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Right_Y_N();
			MoveOne_Right_Y_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointRFP();//���üӹ���λ����Ϣ
			else
			{
					MoveOne_Right_Y_N();
					MoveOne_Right_Y_N();
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Left_Y_P();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Left_Y_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
					CarSetProcessPointRFP();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=ppc[0].y-car.currentPoint.y;
		
		if(t==1)
		{
			MoveOne_Left_Y_P();
		}
		else if(t==2)
		{
			MoveOne_Left_Y_P();
			MoveOne_Left_Y_P();
		}
		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		delay_ms(500);

		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==6)
	{
		delay_ms(500);	
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		delay_ms(500);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointRFP();//���������
		else
		{
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointRFP();//���������
			else
			{
					MoveOne_Forward_X_N();		
					MoveOne_Forward_X_N();

					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
				CarSetFinishedPointRFP();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}

}





void TernimalHandleNoRotationPRF(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;
	}
	else if(car.pos==2)
	{
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetProcessPointPRF();//���üӹ���λ����Ϣ
				break;
			}
			if(i==SCAN_TIME){
				car.order=ORDER_RGB;
				CarSetProcessPointPRF();		
			}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}
		
		CarSetPipelinePoint_A();//���ð��˵�˳��
		car.terminalPoint=Point_RawMaterialAreaFar;
	}
	else if(car.pos==3)//����ԭ����
	{		
		SendAndWaitMV(ORDER_SCANOBJECT);
		MoveOne_Left_Y_P();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[0];
	}
	//��һ�ε��ӹ���
	else if(car.pos==4)
	{				
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==4)
	{
		SendAndWaitMV(ORDER_CARRYUP);
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[1];
	}
	//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==6)
	{
		SendAndWaitMV(ORDER_CARRYUP);
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		car.order=ORDER_RGB;
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
	//ȥɨ�������ɫ
	else if(car.pos==9)
	{
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetFinishedPointPRF();//���������
				break;
			}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[1];
	}
	
	//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(300);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(150);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}
}
	
	

void TernimalHandleNoRotationPFR(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;
	}
	else if(car.pos==2)
	{
				u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetProcessPointPFR();//���üӹ���λ����Ϣ
				break;
			}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}
		
		CarSetPipelinePoint_A();//���ð��˵�˳��
		car.terminalPoint=Point_RawMaterialAreaFar;
	}
	else if(car.pos==3)//����ԭ����
	{
		SendAndWaitMV(ORDER_SCANOBJECT);
		MoveOne_Forward_X_N();
		CarFineTuningRaw_X_N();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		CarFineTuningRaw_X_P();
		car.terminalPoint=ppc[0];
	}
	//��һ�ε��ӹ���
	else if(car.pos==4)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	else if(car.pos==5)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		CarFineTuningRaw_X_P();
		
		car.terminalPoint=ppc[1];
	}
	//�ڶ��ε��ӹ���
	else if(car.pos==6)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==7)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		CarFineTuningRaw_X_P();
		car.terminalPoint=ppc[2];
	}
	//�����ε��ӹ���
	else if(car.pos==8)
	{
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==9)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
	else if(car.pos==10)//�����Ʒ��ʶ��
	{
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetFinishedPointPFR();//���üӹ���λ����Ϣ
				break;
			}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}

		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];

	}
	//���ӹ����ö���1
	else if(car.pos==11)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[1];
	}
	
	//��������Ŷ���1
	else if(car.pos==12)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();

		car.terminalPoint=ppc[2];
	}
	//���ӹ����ö���2
	else if(car.pos==13)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[3];
	}
	//��������Ŷ���2
	else if(car.pos==14)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[4];
	}
	//���ӹ����ö���3
	else if(car.pos==15)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[5];
	}
	//��������Ŷ���3
	else if(car.pos==16)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//�س�
	else if(car.pos==17)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(300);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(200);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}	
}


void TernimalHandleNoRotationFPR(void)
{
		//����ɨ�봦
	if(car.pos==1)
	{
		//�����ź�
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;
	}
	//ɨ�ӹ�����ɫ
	else if(car.pos==2)
	{
		u8 i=0;
		while(i<8){
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Backward_X_P();		
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Backward_X_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
					CarSetProcessPointFPR();//���üӹ���λ����Ϣ
					break;
				}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
			
		}
				//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		car.terminalPoint=Point_RawMaterialArea;
	}	
	else if(car.pos==3)
	{
		SendAndWaitMV(ORDER_SCANOBJECT);
		MoveOne_Forward_X_N();
		CarFineTuningRaw_X_N();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		CarFineTuningRaw_X_P();
		car.terminalPoint=ppc[0];
	}
	else if(car.pos==4)
	{
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==5)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		CarFineTuningRaw_X_P();
		
		car.terminalPoint=ppc[1];
	}
	//�ڶ��ε��ӹ���
	else if(car.pos==6)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==7)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		CarFineTuningRaw_X_P();
		car.terminalPoint=ppc[2];
	}
	//�����ε��ӹ���
	else if(car.pos==8)
	{
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==9)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
	else if(car.pos==10)
	{
		u8 i=0;
		while(i<8){
		SendAndWaitMV(ORDER_SCANCOLOR);
		MoveOne_Backward_X_P();		
		SendAndWaitMV(ORDER_SCANCOLOR);
		MoveOne_Backward_X_P();
		SendAndWaitMV(ORDER_SCANCOLOR);
				if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
					CarSetProcessPointFPR();//���üӹ���λ����Ϣ
					break;
				}
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
			
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[1];
	}
	
	//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		
		car.terminalPoint=ppc[2];
	}
	//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[3];
	}
	//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[4];
	}
	//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningPro_Y_P();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[5];
	}
	//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(300);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(150);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}

}


void TernimalHandleNoRotationFRP(void)
{
		//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		SendAndWaitMV(ORDER_QRCODE);	
		flagOrderPPC=car.order;
		car.terminalPoint=Point_ProcessingAeraA;
	}
	else if(car.pos==2)
	{	
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetProcessPointFRP();//���üӹ���λ����Ϣ
				break;
			}
			MoveOne_Right_Y_N();
			MoveOne_Right_Y_N();
		}
		
		CarSetPipelinePoint_A();//���ð��˵�˳��
		car.terminalPoint=Point_RawMaterialAreaFar;
	}
	else if(car.pos==3)//����ԭ����
	{
		SendAndWaitMV(ORDER_SCANOBJECT);
		MoveOne_Left_Y_P();
		//�����ź�
		SendAndWaitMV(ORDER_CARRYUP);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[0];
	}
	//��һ�ε��ӹ���
	else if(car.pos==4)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	
	else if(car.pos==5)
	{
		SendAndWaitMV(ORDER_CARRYUP);
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[1];
	}
	//�ڶ��ε��ӹ���
	else if(car.pos==6)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==7)
	{
		SendAndWaitMV(ORDER_CARRYUP);
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//�����ε��ӹ���
	else if(car.pos==8)
	{
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==9)
	{		
		SendAndWaitMV(ORDER_QRCODE);
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//��һ�ε������
	else if(car.pos==10)
	{
		u8 i=0;
		while(i<8)
		{
			i++;
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR){
				CarSetFinishedPointFRP();//���üӹ���λ����Ϣ
				break;
			}
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//���ӹ����ö���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[1];
	}
	
	//��������Ŷ���1
	else if(car.pos==12)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();

		car.terminalPoint=ppc[2];
	}
	//���ӹ����ö���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[3];
	}
	//��������Ŷ���2
	else if(car.pos==14)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[4];
	}
	//���ӹ����ö���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		SendAndWaitMV(ORDER_CARRYUP_LOW);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[5];
	}
	//��������Ŷ���3
	else if(car.pos==16)
	{		
		CarFineTuningRaw_Y_N();
		SendAndWaitMV(ORDER_PUTDOWN);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//�س�
	else if(car.pos==17)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(200);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(150);
		
		CarBackwardBrake_WithForward();
		
		while(1)
		delay_ms(3000);
		
		InitCar();
	}

}

void TernimalHandleNoRotationRPF_Test(void)
{
}



void TernimalHandleNoRotationPRF_Test(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		delay_ms(500);	
		car.order=ORDER_BGR;  
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialAreaStartMV;
	}
	else if(car.pos==2)//����ԭ����
	{
		//ɨ��ɫ��
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		MoveOne_Forward_X_N();
		delay_ms(500);
		
		//�����ź�
		delay_ms(500);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=Point_ProcessingAeraA;
	}
	//else if(equal(car.currentPoint,Point_ProcessingAeraA))//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointPRF();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointPRF();//���üӹ���λ����Ϣ
			else
			{
					MoveOne_Forward_X_N();
					MoveOne_Forward_X_N();
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
					CarSetProcessPointPRF();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=car.currentPoint.x-ppc[0].x;
		
		if(t==1)
		{
			MoveOne_Forward_X_N();
		}
		else if(t==2)
		{
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}
		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		delay_ms(500);
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==6)
	{
		delay_ms(500);	
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		delay_ms(500);
		car.order=ORDER_RGB;
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		delay_ms(500);
		MoveOne_Left_Y_P();		
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointPRF();//���������
		else
		{
			MoveOne_Right_Y_N();		
			MoveOne_Right_Y_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointPRF();//���������
			else
			{
				MoveOne_Right_Y_N();		
				MoveOne_Right_Y_N();

				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();		
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				
				CarSetFinishedPointPRF();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}
}
void TernimalHandleNoRotationPFR_Test(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		delay_ms(500);
		car.order=ORDER_BGR;  
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialAreaStartMV;
	}
	else if(car.pos==2)//����ԭ����
	{
		//ɨ��ɫ��
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		MoveOne_Right_Y_N();
		
		CarFineTuningRaw_X_N();
		//�����ź�
		delay_ms(500);
		CarFineTuningRaw_X_P();
		
		car.terminalPoint=Point_ProcessingAeraA;
	}
	//else if(equal(car.currentPoint,Point_ProcessingAeraA))//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointPFR();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointPFR();//���üӹ���λ����Ϣ
			else
			{
					MoveOne_Forward_X_N();
					MoveOne_Forward_X_N();
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
					CarSetProcessPointPFR();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=car.currentPoint.x-ppc[0].x;
		
		if(t==1)
		{
			MoveOne_Forward_X_N();
		}
		else if(t==2)
		{
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}
		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		delay_ms(500);
		CarFineTuningRaw_X_P();
		
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==6)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		delay_ms(500);
		CarFineTuningRaw_X_P();
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		delay_ms(500);
		car.order=ORDER_RGB;
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointPFR();//���������
		else
		{
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointPFR();//���������
			else
			{
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
				
				CarSetFinishedPointPFR();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(300);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(200);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}


}
void TernimalHandleNoRotationFPR_Test(void)
{
		//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		delay_ms(500);
		car.order=ORDER_BGR;  
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialAreaStartMV;
	}
	else if(car.pos==2)//����ԭ����
	{
		//ɨ��ɫ��
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		MoveOne_Right_Y_N();
		
		CarFineTuningRaw_X_N();
		//�����ź�
		delay_ms(500);
		CarFineTuningRaw_X_P();
		
		car.terminalPoint=Point_ProcessingAeraA;
	}
	//else if(equal(car.currentPoint,Point_ProcessingAeraA))//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointFPR();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointFPR();//���üӹ���λ����Ϣ
			else
			{
					MoveOne_Forward_X_N();
					MoveOne_Forward_X_N();
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
					CarSetProcessPointFPR();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=car.currentPoint.x-ppc[0].x;
		
		if(t==1)
		{
			MoveOne_Forward_X_N();
		}
		else if(t==2)
		{
			MoveOne_Forward_X_N();
			MoveOne_Forward_X_N();
		}
		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		delay_ms(500);
		CarFineTuningRaw_X_P();
		
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==6)
	{
		CarFineTuningRaw_X_N();
		//�����ź�
		delay_ms(500);
		CarFineTuningRaw_X_P();
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		delay_ms(500);
		car.order=ORDER_RGB;
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointPFR();//���������
		else
		{
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointPFR();//���������
			else
			{
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
				
				CarSetFinishedPointPFR();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(300);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(150);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}


}




void TernimalHandleNoRotationFRP_Test(void)
{
	//����ɨ�봦
	if(car.pos==1)
	{	
		//�����ź�
		delay_ms(500);	
		car.order=ORDER_BGR;  
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialAreaStartMV;
	}
	else if(car.pos==2)//����ԭ����
	{
		//ɨ��ɫ��
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		MoveOne_Forward_X_N();
		delay_ms(500);
		
		//�����ź�
		delay_ms(500);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=Point_ProcessingAeraC;
	}
	//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		delay_ms(500);
		MoveOne_Right_Y_N();		
		delay_ms(500);
		MoveOne_Right_Y_N();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointFRP();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Left_Y_P();
			MoveOne_Left_Y_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Right_Y_N();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Right_Y_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPointFRP();//���üӹ���λ����Ϣ
			else
			{
					MoveOne_Left_Y_P();
					MoveOne_Left_Y_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Right_Y_N();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Right_Y_N();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
					CarSetProcessPointFRP();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=ppc[0].y-car.currentPoint.y;
		
		if(t==1)
		{
			MoveOne_Left_Y_P();
		}
		else if(t==2)
		{
			MoveOne_Left_Y_P();
			MoveOne_Left_Y_P();
		}
		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		
		car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		delay_ms(500);
		car.terminalPoint=ppc[1];
	}
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_RawMaterialArea;	
	}
	else if(car.pos==6)
	{
		delay_ms(500);	
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_QRCodeAera;
	}
	
	//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		delay_ms(500);
		car.order=ORDER_RGB;
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraA;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		delay_ms(500);
		MoveOne_Backward_X_P();		
		delay_ms(500);
		MoveOne_Backward_X_P();
		delay_ms(500);
		
		car.order=ORDER_RGB;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointFRP();//���������
		else
		{
			MoveOne_Forward_X_N();		
			MoveOne_Forward_X_N();

			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPointRFP();//���������
			else
			{
					MoveOne_Forward_X_N();		
					MoveOne_Forward_X_N();

					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();		
					SendAndWaitMV(ORDER_SCANCOLOR);
					MoveOne_Backward_X_P();
					SendAndWaitMV(ORDER_SCANCOLOR);
				
				CarSetFinishedPointFRP();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
	//else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();

		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=ppc[4];
	}
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	else if(car.pos==14)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningRaw_Y_N();
		delay_ms(500);
		CarFineTuningRaw_Y_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
	//else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{		
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(300);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}

}








void TernimalHandleNoRotationTest(void)
{
	//����ɨ�봦
//	if(equal(car.currentPoint,Point_QRCodeAera))
	if(car.pos==1)
	{	
		//�����ź�
		delay_ms(3000);		
		car.order=ORDER_BGR;
		flagOrderPPC=car.order;
		car.terminalPoint=Point_RawMaterialArea;
	}
//	else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==2)
	{
		delay_ms(500);
		
		if(car.order==ORDER_FALSE)
		{
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_CARRYUP);
		}
		car.terminalPoint=Point_ProcessingAeraA;
	}
	//else if(equal(car.currentPoint,Point_ProcessingAeraA))//��һ�ε��ӹ���
	else if(car.pos==3)
	{		
		delay_ms(500);
		MoveOne_Forward_X_N();		
		delay_ms(500);
		MoveOne_Forward_X_N();
		delay_ms(500);
		
		car.order=ORDER_BGR;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPoint();//���üӹ���λ����Ϣ
		else{	
			MoveOne_Backward_X_P();
			MoveOne_Backward_X_P();
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();		
			SendAndWaitMV(ORDER_SCANCOLOR);
			MoveOne_Forward_X_N();
			SendAndWaitMV(ORDER_SCANCOLOR);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetProcessPoint();//���üӹ���λ����Ϣ
			else
			{
				MoveOne_Backward_X_P();
				MoveOne_Backward_X_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Forward_X_N();		
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Forward_X_N();
				SendAndWaitMV(ORDER_SCANCOLOR);			
				
				CarSetProcessPoint();//���üӹ���λ����Ϣ
			}
		}
		
		//����֮ǰɨ���Ķ�ά����������λ������
		CarSetPipelinePoint_A();//���ð��˵�˳��
		
		int t=ppc[0].x-car.currentPoint.x;
		
		if(t==1)
		{
			MoveOne_Backward_X_P();
		}
		else if(t==2)
		{
			MoveOne_Backward_X_P();
			MoveOne_Backward_X_P();
		}
		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		
		if(equal(ppc[1],Point_ProcessingAeraRed))
			car.terminalPoint=Point_RawMaterialAreaStartMV;
		else		
			car.terminalPoint=Point_RawMaterialArea;	
	}
	
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==4)
	{
		delay_ms(500);			
		car.terminalPoint=ppc[1];
	}
	
	//else if(equal(car.currentPoint,ppc[1]))//�ڶ��ε��ӹ���
	else if(car.pos==5)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();			
		
		if(equal(ppc[2],Point_ProcessingAeraRed))
			car.terminalPoint=Point_RawMaterialAreaStartMV;
		else		
			car.terminalPoint=Point_RawMaterialArea;	
	}
	//else if(equal(car.currentPoint,Point_RawMaterialArea))
	else if(car.pos==6)
	{
		delay_ms(500);		
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//�����ε��ӹ���
	else if(car.pos==7)
	{
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=Point_QRCodeAera;
	}
//else if(equal(car.currentPoint,Point_QRCodeAera))//�ڶ���ɨ��/ɨ��ά��
	else if(car.pos==8)
	{		
		delay_ms(500);
		car.order=ORDER_RGB;
		flagOrderPPCProToFhd=car.order;
		car.terminalPoint=Point_FinishedAeraC;
	}
//	else if(equal(car.currentPoint,Point_FinishedAeraC))
	else if(car.pos==9)
	{
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		MoveOne_Left_Y_P();
		delay_ms(500);
		
		car.order=ORDER_GBR;
		
		if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPoint();//���������
		else{  	
			MoveOne_Right_Y_N();
			MoveOne_Right_Y_N();
			delay_ms(500);
			MoveOne_Left_Y_P();
			delay_ms(500);
			MoveOne_Left_Y_P();
			delay_ms(500);
			
			if(car.order>=ORDER_RGB && car.order<=ORDER_BGR)
				CarSetFinishedPoint();//���������
			else
			{
				MoveOne_Right_Y_N();
				MoveOne_Right_Y_N();
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);
				MoveOne_Left_Y_P();
				SendAndWaitMV(ORDER_SCANCOLOR);			
				
				CarSetFinishedPoint();
			}
		}
		
		CarSetPipelinePoint_B();//���ð��˵�˳��
		
		car.terminalPoint=ppc[0];
	}
//	else if(equal(car.currentPoint,ppc[0]))//���ӹ����ö���1
	else if(car.pos==10)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[1];
	}
//	else if(equal(car.currentPoint,ppc[1]))//��������Ŷ���1
	else if(car.pos==11)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[2];
	}
	//else if(equal(car.currentPoint,ppc[2]))//���ӹ����ö���2
	else if(car.pos==12)
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[3];
	}
	//else if(equal(car.currentPoint,ppc[3]))//��������Ŷ���2
	else if(car.pos==13)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=ppc[4];
	}
	else if(car.pos==14)
	//else if(equal(car.currentPoint,ppc[4]))//���ӹ����ö���3
	{		
		CarFineTuningPro_Y_P();
		delay_ms(500);
		CarFineTuningPro_Y_N();
		car.terminalPoint=ppc[5];
	}
	//else if(equal(car.currentPoint,ppc[5]))//��������Ŷ���3
	else if(car.pos==15)
	{		
		CarFineTuningFhd_X_N();
		delay_ms(500);
		CarFineTuningFhd_X_P();
		car.terminalPoint=Point_InitAeraEnd;
	}
//	else if(equal(car.currentPoint,Point_InitAeraEnd))//�س�
	else if(car.pos==16)
	{	
		CarTurnRight();
		while(1)
		{
			delay_ms(1);
			CarRunRight(400);
			if(TSB1)
				break;
		}
		delay_ms(500);
		CarRightBrake_WithLeft();
		
		CarTurnBackward();
		while(1)
		{
			delay_ms(1);
			CarRunBackward(300);
			if((TSB7||TSB8))
				break;
		}
		delay_ms(400);
		
		CarBackwardBrake_WithForward();
		
		
		delay_ms(3000);
		
		InitCar();
	}



}








void RunTask(void)
{
	
		if(car.cp==CP_InitToQRC)//ǰ��ɨ����
		{
			UpdatePoint_Forward_X_N_QRC();
			CarForwardPID();
		}
		else if(car.cp==CP_QRCToRaw)//ǰ��ԭ����
		{
			UpdatePoint_Backward_X_P();
			CarBackwardPID();
		}
		//ȥ�ӹ����Ŷ���1
		else if(car.cp==CP_RawToPro1)
		{
			UpdatePoint_Backward_Y_P();
			CarBackwardPID();
		}
		else if(car.cp==CP_ProToRaw1)
		{
			UpdatePoint_Forward_Y_N();
			CarForwardPID();
		}
		//ȥ�ӹ����Ŷ���2
		else if(car.cp==CP_RawToPro2)
		{
			UpdatePoint_Backward_Y_P();
			CarBackwardPID();
		}
		else if(car.cp==CP_ProToRaw2)
		{
			UpdatePoint_Forward_Y_N();
			CarForwardPID();
		}
		//ȥ�ӹ����Ŷ���3
		else if(car.cp==CP_RawToPro3)
		{
			UpdatePoint_Backward_Y_P();
			CarBackwardPID();
		}
		
		//ȥʶ�����������ɫ
		else if(car.cp==CP_ProToA)
		{
			UpdatePoint_Backward_X_N();
			CarBackwardPID();
		}
		//ȥɨ��
		else if(car.cp==CP_FhToQRC)
		{
			UpdatePoint_Backward_Y_N();
			CarBackwardPID();
		}
		//ȥ�ӹ���ȡ����1
		else if(car.cp==CP_QRCToC)
		{
			UpdatePoint_Backward_X_P();
			CarBackwardPID();
		}
		//ȥ�ӹ���ȡ����1
		else if(car.cp==CP_CToPro)
		{
			UpdatePoint_Forward_Y_P();
			CarForwardPID();
		}
		else if(car.cp==CP_ProToFh1)
		{
			UpdatePoint_Backward_X_N();
			CarBackwardPID();
		}
		//ȥ�ӹ���ȡ����2
		else if(car.cp==CP_FhToPro1)
		{
			UpdatePoint_Backward_Y_P();
			CarBackwardPID();
		}
		else if(car.cp==CP_ProToFh2)
		{
			UpdatePoint_Backward_X_N();
			CarBackwardPID();
		}
		//ȥ�ӹ���ȡ����3
		else if(car.cp==CP_FhToPro2)
		{
			UpdatePoint_Backward_Y_P();
			CarBackwardPID();
		}
		else if(car.cp==CP_ProToFh3)
		{
			UpdatePoint_Backward_X_N();
			CarBackwardPID();
		}
		//�س�
		else if(car.cp==CP_FhToB)
		{
			UpdatePoint_Backward_Y_N();
			CarBackwardPID();
		}
		else if(car.cp==CP_BToInit)
		{
			UpdatePoint_Backward_X_P();
			CarBackwardPID();
		}
		else
			CarStop();
}



