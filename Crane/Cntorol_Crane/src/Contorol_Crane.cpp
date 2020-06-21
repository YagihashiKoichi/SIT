// -*- C++ -*-
/*!
* @file  Contorol_Crane.cpp
* @brief Contorol_Crane
* @date 2018.10.17
* @author Koichi Yagihashi
* Version: 1.00
* $Id$
*/



#include "Contorol_Crane.h"


// Module specification
// <rtc-template block="module_spec">
static const char* contorol_crane_spec[] =
  {
    "implementation_id", "Contorol_Crane",
    "type_name",         "Contorol_Crane",
    "description",       "Contorol_Crane",
    "version",           "1.0.0",
    "vendor",            "yagihashi",
    "category",          "Mobile robo",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.port", "11",
    // Widget
    "conf.__widget__.port", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Contorol_Crane::Contorol_Crane(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pointIn("point", m_point),
    m_inorderIn("inorder", m_inorder),
    m_outorderOut("outorder", m_outorder)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Contorol_Crane::~Contorol_Crane()
{
}



RTC::ReturnCode_t Contorol_Crane::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("point", m_pointIn);
  addInPort("inorder", m_inorderIn);
  
  // Set OutPort buffer
  addOutPort("outorder", m_outorderOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("port", m_port, "11");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Contorol_Crane::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Contorol_Crane::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Contorol_Crane::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
* onActivated
* �R���t�B�M�����[�V�����ϐ��ɓ��͂��ꂽ�|�[�g�֐ڑ����A
*�A�[�������炩���ߐݒ肳�ꂽ�̐��ɂ���B�܂��A�p�x�v�Z��
*���ߎ���̃t���O�����낷�B
*/
RTC::ReturnCode_t Contorol_Crane::onActivated(RTC::UniqueId ec_id)
{
	std::string	buff;
	buff = "\\\\.\\COM" + m_port;
	craneArm.Initialize(buff.c_str(), learn_length);	//�|�[�g�ڑ�
	craneArm.initArm(arm);								//�����l��ݒ�
	craneArm.setArmStatus(arm);							//�����̐�
	iscal_fin = false;				//�p�x�v�Z�I���̃t���O
	ishave_order = false;			//���ߑ҂������邩�̃t���O

  return RTC::RTC_OK;
}

/*!
* onDeactivated
* ����T�v
* �Ȃ�
*/
RTC::ReturnCode_t Contorol_Crane::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
* onExecute
* ����T�v
* ���W�̓��͂�����Ίp�x�v�Z���s���A�v�Z�t���O�𗧂Ă�B
* ������w�肷�镶�������͂��ꂽ�瓮��w��̃t���O�𗧂Ă�B
* ����̎��s�ɍ��W�܂��͕������g�p�����ꍇ�A����ɑΉ�����
* �t���O�����낷�B
*/
RTC::ReturnCode_t Contorol_Crane::onExecute(RTC::UniqueId ec_id)
{

	double	x, y, d, z;
	double	 L, d3, z3, a, cosa, sina, zeta, cosb, sinb, b;
	int	position;

	if (m_pointIn.isNew()){		//�V�������W�����͂��ꂽ��
		m_pointIn.read();
		x = m_point.data.x;	//x���W���擾
		y = m_point.data.y;	//y���W���擾
		z = m_point.data.z;	//z���W���擾

		theta0 = atan(y / x) * 180 / M_PI;		//�ʓx�@����x���Ɉꎞ�ϊ�
	

		if ((x<0 && 0<y) || (x<0 && y<0)){	//��Q�A��R�ی�
			theta0 = theta0 + 180;			//-pi/2<tan<pi/2�Ȃ̂�
		}

		else if (0<x&&y<0){				    //��S�ی�
			theta0 = theta0 + 360;			//-pi/2<tan<pi/2�Ȃ̂�
		}

		if (0 <= y){		//��P�A��Q�ی�
			position = 1;
		}
		else{
			position = -1; //��R�A��S�ی�

		}


		d = sqrt(x*x + y*y);    //�ڕW�܂ł̋������Z�o

		if (position == -1)
			d = -d;

		d3 = d - L3*cos(theta*M_PI / 180);
		z3 = z - L3*sin(theta*M_PI / 180);

		if (position == -1){
			d3 = d + L3*cos(theta*M_PI / 180);	//�o�P�b�g�̍����̊Ԑڍ��W
			z3 = z - L3*sin(theta*M_PI / 180);	//�o�P�b�g�̍����̊Ԑڍ��W
		}

		L = sqrt(d3*d3 + z3*z3);

		cosa = (L1*L1 + L2*L2 - L*L) / (2 * L1*L2);

		if ((cosa  < -1.0) && (1.0 < cosa)){	//�ُ��cos�̒l����O
			std::cout << "�v�Z�r���̍��W������O�ł��B" << std::endl;
		}

		else if ((-0.0000009 <= cosa) && (cosa <= 0.0000009)){	//���[�g�̌덷�̒���
			cosa = 0.0;
		}

		sina = -sqrt(1 - cosa*cosa);	//�O���Ɖ��肵���̕����̗p

		if (position == -1)
			sina = -sina;				//����Ȃ̂ŏC��

		a = atan2(sina, cosa);

		theta2 = -180 - a * 180 / M_PI;	//sina:���̕����̗p����������

		if (position == -1)				//sina:���������ꍇ
			theta2 = theta2 + 360;

		zeta = atan2(z3, d3);

		cosb = (L1*L1 + L*L - L2*L2) / (2 * L1*L);
		sinb = sqrt(1 - cosb*cosb);					//��ɐ�
		b = atan2(sinb, cosb);

		theta1 = (zeta + b) * 180 / M_PI;
		if (position == -1)
			theta1 = (zeta - b) * 180 / M_PI;
		
		if (position == 1)
			theta3 = theta - theta1 - theta2;
		else
			theta3 = thetaAlter - theta1 - theta2;

		theta0 = theta0 + 60;
		theta1 = -theta1 + 240;
		theta2 = theta2 + 150;
		theta3 = theta3 + 150;

		if (position == -1)			//��R�A��S�ی�
			theta0 = theta0 - 180;

		if ((theta0<60)||(240<theta0))
			std::cout << "theta0������O�ł�:" << theta0 << std::endl;

		if ((theta1<46) || (250<theta1))
			std::cout << "theta1������O�ł�:" << theta1 << std::endl;

		if ((theta2<5) || (288<theta2))
			std::cout << "theta2������O�ł�:" << theta2 << std::endl;

		if ((theta3<48) || (232<theta3))
			std::cout << "theta3������O�ł�:" << theta3 << std::endl;

		iscal_fin = true;			//�v�Z�I���t���O�����Ă�
	}

	if (m_inorderIn.isNew()){	//�V����������w�肷�镶�������͂��ꂽ��
		
		m_inorderIn.read();
		order = m_inorder.data;	//���삷�镶�����擾
		ishave_order = true;
	}

	if (ishave_order){	//�҂��̖��߂�����Ƃ��i�����j

		m_outorder.data = order;
		setTimestamp(m_outorder);

		switch (order)
		{
			
		case 'l':	//�������L��
			std::cout << "start learning" << std::endl;
			craneArm.learning();
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 'p':	//�L���������������s
			std::cout << "start playing" << std::endl;
			craneArm.playback();
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 'm':	//�ڕW���W�ֈړ�
			if (iscal_fin){
				std::cout << "start moving" << std::endl;
				arm.servo[3].write.Angle = theta3;
				craneArm.setArmStatus(arm);
				Sleep(1000);
				arm.servo[0].write.Angle = theta0;
				arm.servo[1].write.Angle = theta1;
				arm.servo[2].write.Angle = theta2;
				craneArm.setArmStatus(arm);

				iscal_fin = false;
				ishave_order = false;
				m_outorderOut.write();
			}
			break;

		case 'c':	//�o�P�b�g����
			std::cout << "start closing" << std::endl;
			arm.servo[4].write.Angle = 150;
			craneArm.setArmStatus(arm);
			ishave_order = false;
			std::cout << "c��m_outorder.data:" << m_outorder.data << std::endl;
			m_outorderOut.write();
			break;

		case 'o':	//�o�P�b�g���J��
			std::cout << "start openning" << std::endl;
			arm.servo[4].write.Angle = 220;
			craneArm.setArmStatus(arm);
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 'r':	//���������̐����Ƃ�
			std::cout << "ready" << std::endl;
			craneArm.initArm(arm);
			craneArm.setArmStatus(arm);
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 't':	//�ڕW���W�ֈړ�(�S�~�����)
			if (iscal_fin){
				std::cout << "start throwning" << std::endl;
				arm.servo[3].write.Angle = theta3;
				craneArm.setArmStatus(arm);	
				Sleep(1000);	//�S�~�������ݖh�~�̂��ߐ�ɋȂ���
				arm.servo[0].write.Angle = theta0;
				arm.servo[1].write.Angle = theta1;
				arm.servo[2].write.Angle = theta2;

				craneArm.setArmStatus(arm);

				iscal_fin = false;
				ishave_order = false;
				m_outorderOut.write();
			}
			break;

		default:
			std::cout << "�ݒ肳��Ă��Ȃ��������͂ł�:" <<order<< std::endl;
			m_outorderOut.write();
			break;
		}

	}





  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Contorol_Crane::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Contorol_Crane::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Contorol_Crane::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Contorol_Crane::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Contorol_Crane::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Contorol_CraneInit(RTC::Manager* manager)
  {
    coil::Properties profile(contorol_crane_spec);
    manager->registerFactory(profile,
                             RTC::Create<Contorol_Crane>,
                             RTC::Delete<Contorol_Crane>);
  }
  
};


