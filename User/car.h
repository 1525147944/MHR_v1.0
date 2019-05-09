#ifndef __CAR_H
#define __CAR_H

#include "sys.h"

typedef enum CoordinateDir
{
	DIR_NONE=0,
	DIR_X_P=1, //X������
	DIR_X_N, //X�ĸ���
	DIR_Y_P, //Y������
	DIR_Y_N //Y�ĸ���
} Dir;

typedef enum CoordinateRotateDir
{
	R_CW90=5, //˳ʱ����ת
	R_CCW90, //��ʱ����ת
	R_CW180,
} R_Dir;


typedef enum CarPathEnum
{
	CP_InitToQRC=1,
	CP_QRCToRaw,
	CP_RawToPro1,
	CP_ProToRaw1,
	CP_RawToPro2,
	CP_ProToRaw2,
	CP_RawToPro3,
	CP_ProToA,
	CP_FhToQRC,
	CP_QRCToC,
	CP_CToPro,
	CP_QRToA,
	CP_ProToFh1,
	CP_FhToPro1,
	CP_ProToFh2,
	CP_FhToPro2,
	CP_ProToFh3,
	CP_FhToB,
	CP_BToInit
} CarPath;


typedef enum CoordinateSpecialSetPosition
{
	SSP_RegularMode=0,
	SSP_InitPosition,
	SSP_ResetPosition,
	SSP_RawPosition,
	SSP_MoveToRawPosition,
	SSP_MoveToProcessPosition
} SpecialSetPosition;


typedef enum PositionModeEnum
{
	//λ��˳��:YN YP XN
	PM_RPF=1,
	PM_RFP,
	PM_PRF,
	PM_PFR,
	PM_FRP,
	PM_FPR
} PositionMode;


typedef struct Point{
	u8 x;
	u8 y;
} Point;


typedef struct{
	Point currentPoint;//��ǰ����
	Point terminalPoint;//�յ�����
	Point lastPoint;
	Dir dir;//��ǰ����
	Dir last_dir;
	u8 dir_m;//������еķ���
	R_Dir dir_r;
	bool isRotating;//�Ƿ�������ת
	bool isRun;//С���Ƿ���
	u16 speedA;//ǰ���������ߵ��ٶ�
	u16 speedB;//ǰ�������ұߵ��ٶ�
	u16 speedC;
	u16 speedBase;
	u8 flagBlockForward;//������ǰ�˶�
	u16 delayBlockForward;
	SpecialSetPosition flagSetPosition;
	char order;
	u8 pos;
	u8 flagRotation;
	u16 flagUpdatePoint;
	u16 flagReadyUpdatePoint;
	u16 flagHighSpeedDelay;
	
	PositionMode pm;
	
	
	bool isSendScanObj;
	
	CarPath cp;
} MyCar;


typedef struct TaskInformationStruct{
	char list[20];
	u8 currentPoint;
} TaskInf;


typedef struct MotorCounterStruct
{
	u16 MotorLF;
	u16 MotorRF;
	u16 MotorLR;
	u16 MotorRR;
} MotorCounter;


typedef struct MotorManagerStruct
{
	u32 MotorLF;
	u32 MotorRF;
	u32 MotorLR;
	u32 MotorRR;
} MotorSpeedManager;


#define CarRunForward(speed) CarForward(speed,speed,speed,speed)
#define CarRunBackward(speed) CarBack(speed,speed,speed,speed)
#define CarRunLeft(speed) CarLeft(speed,speed,speed,speed)
#define CarRunRight(speed) CarRight(speed,speed,speed,speed)

#define CarRunClockwise(speed) CarClockwise(speed,speed,speed,speed)
#define CarRunCounterClockwise(speed) CarCounterClockwise(speed,speed,speed,speed)

#define CarRun(speedLeft,speedRight) CarForward(speedLeft,speedRight,speedLeft,speedRight)


#define CarForwardSetFixedSpeed() CarForward(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
#define CarBackwardSetFixedSpeed() CarBack(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
#define CarLeftSetFixedSpeed() CarLeft(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
#define CarRightSetFixedSpeed() CarRight(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
#define CarClockwiseSetFixedSpeed() CarClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);
#define CarCounterClockwiseSetFixedSpeed() CarCounterClockwise(msm.MotorLF,msm.MotorRF,msm.MotorLR,msm.MotorRR);

#define BRAKE_TIME 100
#define BRAKE_SPEED 200
#define CarForwardBrake_WithBackward() CarTurnBackward();CarRunBackward(BRAKE_SPEED);delay_ms(BRAKE_TIME);CarStop();
#define CarBackwardBrake_WithForward() CarTurnForward();CarRunForward(BRAKE_SPEED);delay_ms(BRAKE_TIME);CarStop();
#define CarLeftBrake_WithRight() CarTurnRight();CarRunRight(BRAKE_SPEED);delay_ms(BRAKE_TIME);CarStop();
#define CarRightBrake_WithLeft() CarTurnLeft();CarRunLeft(BRAKE_SPEED);delay_ms(BRAKE_TIME);CarStop();

#define CarClockBrake_WithCounterClock() CarTurnCounterClockwise();CarRunCounterClockwise(BRAKE_SPEED);delay_ms(BRAKE_TIME);CarStop();
#define CarCounterClockBrake_WithClock() CarTurnClockwise();CarRunClockwise(BRAKE_SPEED);delay_ms(BRAKE_TIME);CarStop();

#define Abs(num) num<0?-num:num


//ԭ����
extern Point Point_RawMaterialArea;
extern Point Point_RawMaterialAreaFar;
extern Point Point_RawMaterialAreaStartMV;
extern Point Point_RawMaterialAreaFar;
//�����
extern Point Point_FinishedAeraRed;
extern Point Point_FinishedAeraGreen;
extern Point Point_FinishedAeraBlue;
extern Point Point_FinishedAeraA;
extern Point Point_FinishedAeraB;
extern Point Point_FinishedAeraC;

//�ӹ���
extern Point Point_ProcessingAera;
extern Point Point_ProcessingAeraRed;
extern Point Point_ProcessingAeraGreen;
extern Point Point_ProcessingAeraBlue;

extern Point Point_ProcessingAeraA;
extern Point Point_ProcessingAeraB;
extern Point Point_ProcessingAeraC;

//��ά����
extern Point Point_QRCodeAera;
extern Point Point_QRCodeAeraFar;
//������
extern Point Point_InitAera;
extern Point Point_InitAeraEnd;
extern Point Point_InitAeraStart;


extern MyCar car;
extern TaskInf taskInf;
extern MotorCounter mc;
extern MotorCounter mc_test;


extern float pitch;
extern float roll;
extern float yaw;


void InitCar(void);
void SetAeraCoordinate(void);


#endif
