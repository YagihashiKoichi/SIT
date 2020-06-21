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
* コンフィギュレーション変数に入力されたポートへ接続し、
*アームをあらかじめ設定された体制にする。また、角度計算と
*命令受諾のフラグを下ろす。
*/
RTC::ReturnCode_t Contorol_Crane::onActivated(RTC::UniqueId ec_id)
{
	std::string	buff;
	buff = "\\\\.\\COM" + m_port;
	craneArm.Initialize(buff.c_str(), learn_length);	//ポート接続
	craneArm.initArm(arm);								//初期値を設定
	craneArm.setArmStatus(arm);							//初期体勢
	iscal_fin = false;				//角度計算終了のフラグ
	ishave_order = false;			//命令待ちがあるかのフラグ

  return RTC::RTC_OK;
}

/*!
* onDeactivated
* 動作概要
* なし
*/
RTC::ReturnCode_t Contorol_Crane::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
* onExecute
* 動作概要
* 座標の入力があれば角度計算を行い、計算フラグを立てる。
* 動作を指定する文字が入力されたら動作指定のフラグを立てる。
* 動作の実行に座標または文字を使用した場合、それに対応する
* フラグを下ろす。
*/
RTC::ReturnCode_t Contorol_Crane::onExecute(RTC::UniqueId ec_id)
{

	double	x, y, d, z;
	double	 L, d3, z3, a, cosa, sina, zeta, cosb, sinb, b;
	int	position;

	if (m_pointIn.isNew()){		//新しい座標が入力されたら
		m_pointIn.read();
		x = m_point.data.x;	//x座標を取得
		y = m_point.data.y;	//y座標を取得
		z = m_point.data.z;	//z座標を取得

		theta0 = atan(y / x) * 180 / M_PI;		//弧度法から度数に一時変換
	

		if ((x<0 && 0<y) || (x<0 && y<0)){	//第２、第３象限
			theta0 = theta0 + 180;			//-pi/2<tan<pi/2なので
		}

		else if (0<x&&y<0){				    //第４象限
			theta0 = theta0 + 360;			//-pi/2<tan<pi/2なので
		}

		if (0 <= y){		//第１、第２象限
			position = 1;
		}
		else{
			position = -1; //第３、第４象限

		}


		d = sqrt(x*x + y*y);    //目標までの距離を算出

		if (position == -1)
			d = -d;

		d3 = d - L3*cos(theta*M_PI / 180);
		z3 = z - L3*sin(theta*M_PI / 180);

		if (position == -1){
			d3 = d + L3*cos(theta*M_PI / 180);	//バケットの根元の間接座標
			z3 = z - L3*sin(theta*M_PI / 180);	//バケットの根元の間接座標
		}

		L = sqrt(d3*d3 + z3*z3);

		cosa = (L1*L1 + L2*L2 - L*L) / (2 * L1*L2);

		if ((cosa  < -1.0) && (1.0 < cosa)){	//異常なcosの値可動域外
			std::cout << "計算途中の座標が可動域外です。" << std::endl;
		}

		else if ((-0.0000009 <= cosa) && (cosa <= 0.0000009)){	//ルートの誤差の訂正
			cosa = 0.0;
		}

		sina = -sqrt(1 - cosa*cosa);	//前方と仮定し負の方を採用

		if (position == -1)
			sina = -sina;				//後方なので修正

		a = atan2(sina, cosa);

		theta2 = -180 - a * 180 / M_PI;	//sina:負の方を採用したたため

		if (position == -1)				//sina:正だった場合
			theta2 = theta2 + 360;

		zeta = atan2(z3, d3);

		cosb = (L1*L1 + L*L - L2*L2) / (2 * L1*L);
		sinb = sqrt(1 - cosb*cosb);					//常に正
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

		if (position == -1)			//第３、第４象限
			theta0 = theta0 - 180;

		if ((theta0<60)||(240<theta0))
			std::cout << "theta0が可動域外です:" << theta0 << std::endl;

		if ((theta1<46) || (250<theta1))
			std::cout << "theta1が可動域外です:" << theta1 << std::endl;

		if ((theta2<5) || (288<theta2))
			std::cout << "theta2が可動域外です:" << theta2 << std::endl;

		if ((theta3<48) || (232<theta3))
			std::cout << "theta3が可動域外です:" << theta3 << std::endl;

		iscal_fin = true;			//計算終了フラグを建てる
	}

	if (m_inorderIn.isNew()){	//新しい動作を指定する文字が入力されたら
		
		m_inorderIn.read();
		order = m_inorder.data;	//動作する文字を取得
		ishave_order = true;
	}

	if (ishave_order){	//待ちの命令があるとき（文字）

		m_outorder.data = order;
		setTimestamp(m_outorder);

		switch (order)
		{
			
		case 'l':	//動きを記憶
			std::cout << "start learning" << std::endl;
			craneArm.learning();
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 'p':	//記憶した動きを実行
			std::cout << "start playing" << std::endl;
			craneArm.playback();
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 'm':	//目標座標へ移動
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

		case 'c':	//バケット閉じる
			std::cout << "start closing" << std::endl;
			arm.servo[4].write.Angle = 150;
			craneArm.setArmStatus(arm);
			ishave_order = false;
			std::cout << "cのm_outorder.data:" << m_outorder.data << std::endl;
			m_outorderOut.write();
			break;

		case 'o':	//バケットを開く
			std::cout << "start openning" << std::endl;
			arm.servo[4].write.Angle = 220;
			craneArm.setArmStatus(arm);
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 'r':	//同じ初期体勢をとる
			std::cout << "ready" << std::endl;
			craneArm.initArm(arm);
			craneArm.setArmStatus(arm);
			ishave_order = false;
			m_outorderOut.write();
			break;

		case 't':	//目標座標へ移動(ゴミ箱上へ)
			if (iscal_fin){
				std::cout << "start throwning" << std::endl;
				arm.servo[3].write.Angle = theta3;
				craneArm.setArmStatus(arm);	
				Sleep(1000);	//ゴミ巻き込み防止のため先に曲げる
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
			std::cout << "設定されていない文字入力です:" <<order<< std::endl;
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


