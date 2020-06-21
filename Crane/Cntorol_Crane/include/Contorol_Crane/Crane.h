/********* About This Source *********/
/*
This sample source code is designed for robot arm "CRANE" of RT Corporation.
You can use your research and educational purpose without any permission with RT Corporation.
If you use this for commercial, please contact us.

Company: RT Corporation
Version: 1.00
Contact: shop@rt-net.jp

Modified by Takeshi Sasaki
            Koichi Yagihashi
*/


#ifndef __CONTROL_CRANE__
#define __CONTROL_CRANE__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
//#include<ctime>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <winsock.h>
#include <stdint.h> // portable: uint64_t   MSVC: __int64 
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif

#define L1  8.2		//ÉAÅ[ÉÄÇPÇÃí∑Ç≥
#define L2  9.5		//ÉAÅ[ÉÄÇQÇÃí∑Ç≥
#define L3  12.5	//ÉAÅ[ÉÄÇRÇÃí∑Ç≥
#define theta  -90	//ëÊÇPÅAëÊÇQè€å¿Ç≈íÕÇﬁäpìx
#define thetaAlter  270	//ëÊÇRÅAëÊÇSè€å¿Ç≈íÕÇﬁäpìx

#if defined(_WIN32) || defined(_WIN64)
int gettimeofday(struct timeval * tp, struct timezone * tzp);
#endif

const int ARM_FREEDOM = 5; //Arm freedom (CRANE has 5 freedom)



// Servomotor's data to write
struct t_servoWrite
{
	bool LED;
	bool TorqueON;

	int CW_ComplianceMargin;
	int CCW_ComplianceMargin;

	int CW_ComplianceSlope;
	int CCW_ComplianceSlope;

	double Angle;	//degree
	double Speed;	//rpm
	double Torque;	//%
};


// Servomotor's data to read
struct t_servoRead
{
	double Angle;	//degree
	double Speed;	//rpm
	double Torque;	//%
};

// Servomotor's information
struct t_servo
{
	int id;	//âΩî‘ñ⁄ÇÃä÷êﬂÇ»ÇÃÇ©
	t_servoWrite write;
	t_servoRead read;
};


// ARMrobot's information
struct t_arm
{
	t_servo servo[ARM_FREEDOM];
};


class Crane{
#if defined(_WIN32) || defined(_WIN64)
	HANDLE hSerial;
#else
	int fd;
#endif

	std::vector<t_arm> armdata; //Learned data (real_time = 0.05 * armdata.size() [sec])

	// communication functions
	int serialWrite(unsigned char *buf, size_t length);

	unsigned char calcRobotisCheckSum(unsigned char *buf, int sizeofArray);
	int GetStatusPacket(unsigned char *recv);
	inline int CheckStatusPacket(void){
		unsigned char buf[256];
		return GetStatusPacket(buf);
	};
	void WriteData2Bytes(unsigned char *buf, t_servoWrite data);
	void initPacket(unsigned char *buf);
	int RegWrite(int id, t_servoWrite data);

private:
	void Action(void);
private:
	void GetStatus(t_servo &servo);

	//initialize
public:
	void initServo(int id, t_servo &servo);

public:
	void initArm(t_arm &arm);

	// Time management functions
private:
	double time_diff(struct timeval pre, struct timeval post);
	void wait_ms(struct timeval start, int ms);

public:
	Crane();
	~Crane();

	bool isConnected();

	//initialize and finalize
	int Initialize(const char* port_name, size_t length);
	void Close();

	// Application functions
	void TorqueOff(void);
	void getArmStatus(t_arm &arm);
	void setArmStatus(t_arm &arm);	//é©ï™Ç≈ê›íËÇ∑ÇÈÇ»ÇÁÇ±Ç±ÇÃÇ›
	void copyArmData(t_arm &arm);

	void playback(void);
	void learning(void);
};


#endif