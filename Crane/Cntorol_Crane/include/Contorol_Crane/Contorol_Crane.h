// -*- C++ -*-
/*!
 * @file  Contorol_Crane.h
 * @brief Contorol_Crane
 * @date  2018.10.17
 * Version: 1.00
 * @author Koichi Yagihashi
 * $Id$
 */

#ifndef CONTOROL_CRANE_H
#define CONTOROL_CRANE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

////////////////include追加:開始///////////////////////

#include "Crane.h"

////////////////include追加:終了///////////////////////

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

/*!
* @class Contorol_Crane
* @brief Contorol_Crane
*
* コンポーネント概要
*このコンポーネントはアームに対してバケットの開閉、
*三次元空間における任意座標へバケットが鉛直下向きの状態
*となるように移動が行える。
* 
* コンポーネント：入力
* point:バケットの移動先の座標を表す。
*受け取る座標は初期状態のアームの根元を原点とし、
*アームから見てそれぞれ、右向きにｘ軸、前方にｙ軸、
*鉛直上向きにｚ軸をとり、単位は小数点を含むｃｍである。
*ただし、ここでのアームの根元は台座を含めないものとし、
*関節間の長さは根元側から順に8.2cm、9.5cm、12.5cmとする。
*
*inorder:アームが行う動作を指定する文字。
*対応可能な文字は以下の通りである。
*ｍまたはｔ：入力コンポーネントから入力された座標への移動。
*o：バケットを開く。
*ｃ：バケットを閉じる。
*ｒ：あらかじめ設定されている体制をとる。
*ｌ：標準出力画面で500カウントされるまでの間の動きを記憶する。
*ｐ：記憶した動きを実行する。
*
*コンポーネント：出力
*outorder:実行した動作に対応する文字。
*/



using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class Contorol_Crane
 * @brief Contorol_Crane
 *
 */
class Contorol_Crane
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Contorol_Crane(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Contorol_Crane();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

   /***
   * onActivated
   * 動作概要
   * コンフィギュレーション変数に入力されたポートへ接続し、
   *アームをあらかじめ設定された体制にする。また、角度計算と
   *命令受諾のフラグを下ろす。
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   * @pre onActivated
   * コンフィギュレーション変数を設定する。
   * 
   * @post onActivated
   * なし
   *
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

   /***
   * onDeactivated
   * なし
   * 
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   * @pre onDeactivated
   *なし
   * @post onDeactivated
   * なし
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

   /***
   * onExecute
   * 動作概要
   * 座標の入力があれば角度計算を行い、計算フラグを立てる。
   * 動作を指定する文字が入力されたら動作指定のフラグを立てる。
   * 動作の実行に座標または文字を使用した場合、それに対応する
   * フラグを下ろす。
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   * @pre onExecute
   * なし
   * @post onExecute
   * なし
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

	 // Configuration variable declaration
	 // <rtc-template block="config_declare">
	 /*!
	 * portの概要説明
	 * アームを接続するUSBポートの番号
	 * - Name: port 
	 * - DefaultValue: 11
	 * - Unit: なし
	 * - Range: なし
	 * - Constraint: なし
	 */

  std::string m_port;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">

  /*!
  * 3Dpointの概要説明
  * 三次元空間における座標を持つ構造体、ｘ、ｙ、ｚはそれぞれの
  * 座標を表す。軸の定義はヘッダーのコンポーネント概要を参照。
  * - Type: TimedPoint3D
  * - Number: 4
  * - Semantics: 三次元空間における座標。
  * - Unit: ｃｍ
  */
  RTC::TimedPoint3D m_point;
  
  InPort<RTC::TimedPoint3D> m_pointIn;
  RTC::TimedChar m_inorder;
  /*!
  * inorderの概要説明
  * アームに指定する動作に対応する文字。
  * 対応する文字はヘッダーのコンポーネント概要を参照。
  * - Type: TimedChar
  * - Number: 2
  * - Semantics: アームに指定する動作に対応する文字。
  * - Unit: なし
  */
  InPort<RTC::TimedChar> m_inorderIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedChar m_outorder;
  /*!
  * outorderの概要説明
  * アームが行った動作に対応する文字。
  * - Type: TimedChar
  * - Number: 2
  * - Semantics: アームが行った動作に対応する文字。
  * - Unit: なし
  */
  OutPort<RTC::TimedChar> m_outorderOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">


 ///////////////////グローバル変数追加：開始/////////////
	 const int learn_length = 500;
	 Crane craneArm;
	 t_arm arm;
	 //同時に値を取得するため
	 double	theta0, theta1, theta2, theta3;	//値を保存するため
	 char	order;							//値を保存するため
	 bool	iscal_fin;				//角度計算終了のフラグ
	 bool	ishave_order;				//命令待ちがあるかのフラグ

	 ///////////////////グローバル変数追加：終了/////////////
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void Contorol_CraneInit(RTC::Manager* manager);
};

#endif // CONTOROL_CRANE_H
