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

#include "Crane.h"


#if defined(_WIN32) || defined(_WIN64)
int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
	// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
	static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;

	tp->tv_sec = (long)((time - EPOCH) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
	return 0;
}
#endif

//constructor
Crane::Crane(){
#if defined(_WIN32) || defined(_WIN64)
	hSerial = INVALID_HANDLE_VALUE;
#else
	fd = 0;
#endif
}

//destructor
Crane::~Crane(){
	if (isConnected()){
		Close();
	}
}


bool Crane::isConnected(){
#if defined(_WIN32) || defined(_WIN64)
	if (hSerial != INVALID_HANDLE_VALUE){
#else
	if (fd>0){
#endif
		return true;
	}
	else{
		return false;
	}
	}


void Crane::Close(){
	if (isConnected()){
#if defined(_WIN32) || defined(_WIN64)
		CloseHandle(hSerial);
		hSerial = INVALID_HANDLE_VALUE;
#else
		close(fd);
		fd = 0;
#endif
	}
}

int Crane::Initialize(const char* port_name, size_t length){
	Close(); //close port if already opened

#if defined(_WIN32) || defined(_WIN64)
	//Open serial port
	hSerial = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial == INVALID_HANDLE_VALUE){
		if (GetLastError() == ERROR_FILE_NOT_FOUND){
			//serial port does not exist.
			std::cerr << "cannot open port" << std::endl;
		}
		char lastError[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
		std::cerr << "Error in initialize(): " << lastError << std::endl;
		return -1;
	}

	//Setting serial port parameters
	DCB dcbSerialParams = { 0 };

	dcbSerialParams.DCBlength = sizeof(DCB);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		char lastError[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
		std::cerr << "Error in initialize(): " << lastError << std::endl;
		return -2;
	}

	dcbSerialParams.BaudRate = 1000000;
	//	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	//flow control off
	dcbSerialParams.fOutxCtsFlow = FALSE;
	dcbSerialParams.fOutxDsrFlow = FALSE;
	dcbSerialParams.fDtrControl = DTR_CONTROL_DISABLE;
	dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
	dcbSerialParams.fOutX = FALSE;
	dcbSerialParams.fInX = FALSE;

	if (!SetCommState(hSerial, &dcbSerialParams)){
		char lastError[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
		std::cerr << "Error in initialize(): " << lastError << std::endl;
		return -3;
	}

	//Set timeout
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutConstant = 5000;
	timeouts.ReadTotalTimeoutMultiplier = 100;
	timeouts.WriteTotalTimeoutConstant = 5000;
	timeouts.WriteTotalTimeoutMultiplier = 100;
	if (!SetCommTimeouts(hSerial, &timeouts)){
		char lastError[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
		std::cerr << "Error in initialize(): " << lastError << std::endl;
		return -4;
	}
#else
	struct termios setting;

	fd = open(port_name, O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		std::cout << "Error in Crane::Initialize(): cannot open port" << std::endl;
		return -1;
	}

	setting.c_cflag = B1000000 | CS8 | CLOCAL | CREAD;

	setting.c_cc[VTIME] = 10;
	setting.c_cc[VMIN] = 10;
	setting.c_lflag = 0;
	setting.c_iflag = IGNPAR;
	setting.c_oflag = 0;	//RAW mode

	tcflush(fd, TCIOFLUSH);
	tcsetattr(fd, TCSANOW, &setting);
#endif

	//initialize arm
	armdata.resize(length);
	for (size_t i = 0; i<armdata.size(); i++){
		initArm(armdata[i]);
	}
	TorqueOff();

	return 0;
}


//send bytes
int Crane::serialWrite(unsigned char *buf, size_t length)
{
	if (isConnected()){
#if defined(_WIN32) || defined(_WIN64)
		DWORD dwBytes;
		if (!WriteFile(hSerial, buf, length, &dwBytes, NULL)){
			char lastError[1024];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
			std::cerr << "Error in serialWrite(): " << lastError << std::endl;
			return -1;
		}
		return 0;
#else
		int res;
		res = write(fd, buf, length);
		tcflush(fd, TCOFLUSH);
		return res;
#endif
	}
	std::cerr << "Error in serialWrite(): device not connected." << std::endl;
	return -2;
}

//calc checksum
unsigned char Crane::calcRobotisCheckSum(unsigned char *buf, int sizeofArray)
{
	int sum = 0;
	buf += 2;	//skip 0xff 0xff
	for (int i = 2; i<(sizeofArray - 1); i++)
	{
		sum += *buf;
		buf++;
	}
	return 0xff & (~sum);
}


// get status packet
int Crane::GetStatusPacket(unsigned char *recv)
{
#if defined(_WIN32) || defined(_WIN64)
	DWORD dwBytes = 0;
	if (!ReadFile(hSerial, recv, 4, &dwBytes, NULL)){
		char lastError[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
		std::cerr << "Error in SendCommand(): " << lastError << std::endl;
		return -1;
	}
#else
	read(fd, recv, 4);
#endif
	if ((recv[0] & recv[1] & 0xff) != 0xff)
	{
		std::cerr << "Error in Crane::GetStatusPacket(): invalid return value:" << (int)recv[0] << ' ' << (int)recv[1] << ' ' << (int)recv[2] << ' ' << (int)recv[3] << std::endl;
		return -1;
	}

#if defined(_WIN32) || defined(_WIN64)
	if (!ReadFile(hSerial, recv + 4, recv[3], &dwBytes, NULL)){
		char lastError[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lastError, 1024, NULL);
		std::cerr << "Error in SendCommand(): " << lastError << std::endl;
		return -1;
	}
#else
	read(fd, recv + 4, recv[3]);
	tcflush(fd, TCIFLUSH);
#endif

	return 4 + recv[3];
}


// data structure to byte array
void Crane::WriteData2Bytes(unsigned char *buf, t_servoWrite data)
{
	int angle = (int)(1024.0 * (data.Angle / 300.0));
	int speed = (int)(data.Speed / 0.111);
	int torque = (int)(data.Torque * 1024.0);

	buf[0] = data.TorqueON;
	buf[1] = data.LED;
	buf[2] = data.CW_ComplianceMargin;
	buf[3] = data.CCW_ComplianceMargin;
	buf[4] = data.CW_ComplianceSlope;
	buf[5] = data.CCW_ComplianceSlope;
	buf[6] = angle & 0xff;
	buf[7] = (angle >> 8) & 0xff;
	buf[8] = speed & 0xff;
	buf[9] = (speed >> 8) & 0xff;
	buf[10] = torque & 0xff;
	buf[11] = (torque >> 8) & 0xff;

	return;
}


//initialize packet data
void Crane::initPacket(unsigned char *buf)
{
	buf[0] = 0xff;
	buf[1] = 0xff;
}


//register write
int Crane::RegWrite(int id, t_servoWrite data)
{
	int res;
	unsigned char buf[19] = { 0 };

	initPacket(buf);
	buf[2] = id & 0xff;
	buf[3] = 15;
	buf[4] = 4;
	buf[5] = 24;

	WriteData2Bytes(buf + 6, data);
	buf[18] = calcRobotisCheckSum(buf, sizeof(buf));

	res = serialWrite(buf, sizeof(buf));

	if (res<0){
		return res;
	}
	else{
		return CheckStatusPacket();
	}
}


//get status
void Crane::GetStatus(t_servo &servo)
{
	unsigned char buf[8] = { 0 };
	unsigned char recv[256] = { 0 };
	int tmp;

	initPacket(buf);
	buf[2] = servo.id;
	buf[3] = 4;
	buf[4] = 2;
	buf[5] = 36;
	buf[6] = 6;
	buf[7] = calcRobotisCheckSum(buf, sizeof(buf));

	serialWrite(buf, sizeof(buf));

	GetStatusPacket(recv);

	servo.read.Angle = 300.0 * (recv[5] | (recv[6] << 8)) / 1024.0;

	tmp = (recv[7] + (recv[8] << 8)) & 1023;

	if (recv[8] & 4)
	{
		servo.read.Speed = -0.111 * tmp;
	}
	else
	{
		servo.read.Speed = 0.111 * tmp;
	}

	tmp = (recv[9] + (recv[10] << 8)) & 1023;
	if (recv[10] & 4)
	{
		servo.read.Torque = -tmp / 1024.0;
	}
	else
	{
		servo.read.Torque = tmp / 1024.0;
	}
}


//send action packet
void Crane::Action(void)
{
	unsigned char buf[] = { 0xff, 0xff, 254, 2, 5, 0 };
	buf[sizeof(buf) - 1] = calcRobotisCheckSum(buf, sizeof(buf));

	serialWrite(buf, sizeof(buf));
}


//initialize servo data
void Crane::initServo(int id, t_servo &servo)
{
	servo.id = id;

	servo.write.TorqueON = true;
	servo.write.LED = false;
	servo.write.CW_ComplianceMargin = 1;
	servo.write.CCW_ComplianceMargin = 1;
	servo.write.CW_ComplianceSlope = 32;
	servo.write.CCW_ComplianceSlope = 32;
	if (id == 5)				//バケットの開閉角度を指定
		servo.write.Angle = 220;
	else
		servo.write.Angle = 150;	//直立状態
	servo.write.Speed = 20;
	servo.write.Torque = 0.95;
}


//initialize arm data
void Crane::initArm(t_arm &arm)
{
	for (int i = 0; i<ARM_FREEDOM; i++)
	{
		initServo(i + 1, arm.servo[i]);
	}
}


//! Calc diff
double Crane::time_diff(struct timeval pre, struct timeval post)
{
	return (post.tv_usec - pre.tv_usec) + (1000000.0 * (post.tv_sec - pre.tv_sec));
}


// Wait ms from start time
void Crane::wait_ms(struct timeval start, int ms)
{
	struct timeval now;

	do
	{
		gettimeofday(&now, NULL);
	} while (time_diff(start, now) < (ms * 1000.0));

}


// Read data from arm
void Crane::getArmStatus(t_arm &arm)
{
	for (int i = 0; i<ARM_FREEDOM; i++)
	{
		GetStatus(arm.servo[i]);
	}
}

// Send data to arm
void Crane::setArmStatus(t_arm &arm)
{
	for (int i = 0; i<ARM_FREEDOM; i++)
	{
		RegWrite(arm.servo[i].id, arm.servo[i].write);
	}
	Action();
}

// Learn action that occures by human hand
void Crane::learning(void)
{
	struct timeval pre;

	TorqueOff();
	std::cout << "torque off" << std::endl;
	for (size_t i = 0; i<armdata.size(); i++)
	{
		gettimeofday(&pre, NULL);
		getArmStatus(armdata[i]);
		std::cout << i + 1 << '/' << armdata.size() << std::endl;
		wait_ms(pre, 50);
	}

}

// Copy angle data
void Crane::copyArmData(t_arm &arm)
{
	for (int i = 0; i<ARM_FREEDOM; i++)
	{
		arm.servo[i].write.Angle = arm.servo[i].read.Angle;
		std::cout << i << ":" << arm.servo[i].read.Angle << std::endl;
	}
}

// Playback learned action
void Crane::playback(void)
{
	struct timeval pre;

	std::cout << "torque on" << std::endl;
	for (size_t i = 0; i<armdata.size(); i++)
	{
		gettimeofday(&pre, NULL);
		copyArmData(armdata[i]);
		setArmStatus(armdata[i]);
		std::cout << i + 1 << '/' << armdata.size() << std::endl;
		wait_ms(pre, 50);
	}
}

// Release torque
void Crane::TorqueOff(void)
{
	t_servo servo[5];

	for (int i = 0; i<5; i++)
	{
		initServo(i + 1, servo[i]);
		servo[i].write.Torque = 0;
		RegWrite(servo[i].id, servo[i].write);
	}
	Action();
}
