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

////////////////include�ǉ�:�J�n///////////////////////

#include "Crane.h"

////////////////include�ǉ�:�I��///////////////////////

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
* �R���|�[�l���g�T�v
*���̃R���|�[�l���g�̓A�[���ɑ΂��ăo�P�b�g�̊J�A
*�O������Ԃɂ�����C�Ӎ��W�փo�P�b�g�������������̏��
*�ƂȂ�悤�Ɉړ����s����B
* 
* �R���|�[�l���g�F����
* point:�o�P�b�g�̈ړ���̍��W��\���B
*�󂯎����W�͏�����Ԃ̃A�[���̍��������_�Ƃ��A
*�A�[�����猩�Ă��ꂼ��A�E�����ɂ����A�O���ɂ����A
*����������ɂ������Ƃ�A�P�ʂ͏����_���܂ނ����ł���B
*�������A�����ł̃A�[���̍����͑�����܂߂Ȃ����̂Ƃ��A
*�֐ߊԂ̒����͍��������珇��8.2cm�A9.5cm�A12.5cm�Ƃ���B
*
*inorder:�A�[�����s��������w�肷�镶���B
*�Ή��\�ȕ����͈ȉ��̒ʂ�ł���B
*���܂��͂��F���̓R���|�[�l���g������͂��ꂽ���W�ւ̈ړ��B
*o�F�o�P�b�g���J���B
*���F�o�P�b�g�����B
*���F���炩���ߐݒ肳��Ă���̐����Ƃ�B
*���F�W���o�͉�ʂ�500�J�E���g�����܂ł̊Ԃ̓������L������B
*���F�L���������������s����B
*
*�R���|�[�l���g�F�o��
*outorder:���s��������ɑΉ����镶���B
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
   * ����T�v
   * �R���t�B�M�����[�V�����ϐ��ɓ��͂��ꂽ�|�[�g�֐ڑ����A
   *�A�[�������炩���ߐݒ肳�ꂽ�̐��ɂ���B�܂��A�p�x�v�Z��
   *���ߎ���̃t���O�����낷�B
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   * @pre onActivated
   * �R���t�B�M�����[�V�����ϐ���ݒ肷��B
   * 
   * @post onActivated
   * �Ȃ�
   *
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

   /***
   * onDeactivated
   * �Ȃ�
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
   *�Ȃ�
   * @post onDeactivated
   * �Ȃ�
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

   /***
   * onExecute
   * ����T�v
   * ���W�̓��͂�����Ίp�x�v�Z���s���A�v�Z�t���O�𗧂Ă�B
   * ������w�肷�镶�������͂��ꂽ�瓮��w��̃t���O�𗧂Ă�B
   * ����̎��s�ɍ��W�܂��͕������g�p�����ꍇ�A����ɑΉ�����
   * �t���O�����낷�B
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   * @pre onExecute
   * �Ȃ�
   * @post onExecute
   * �Ȃ�
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
	 * port�̊T�v����
	 * �A�[����ڑ�����USB�|�[�g�̔ԍ�
	 * - Name: port 
	 * - DefaultValue: 11
	 * - Unit: �Ȃ�
	 * - Range: �Ȃ�
	 * - Constraint: �Ȃ�
	 */

  std::string m_port;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">

  /*!
  * 3Dpoint�̊T�v����
  * �O������Ԃɂ�������W�����\���́A���A���A���͂��ꂼ���
  * ���W��\���B���̒�`�̓w�b�_�[�̃R���|�[�l���g�T�v���Q�ƁB
  * - Type: TimedPoint3D
  * - Number: 4
  * - Semantics: �O������Ԃɂ�������W�B
  * - Unit: ����
  */
  RTC::TimedPoint3D m_point;
  
  InPort<RTC::TimedPoint3D> m_pointIn;
  RTC::TimedChar m_inorder;
  /*!
  * inorder�̊T�v����
  * �A�[���Ɏw�肷�铮��ɑΉ����镶���B
  * �Ή����镶���̓w�b�_�[�̃R���|�[�l���g�T�v���Q�ƁB
  * - Type: TimedChar
  * - Number: 2
  * - Semantics: �A�[���Ɏw�肷�铮��ɑΉ����镶���B
  * - Unit: �Ȃ�
  */
  InPort<RTC::TimedChar> m_inorderIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedChar m_outorder;
  /*!
  * outorder�̊T�v����
  * �A�[�����s��������ɑΉ����镶���B
  * - Type: TimedChar
  * - Number: 2
  * - Semantics: �A�[�����s��������ɑΉ����镶���B
  * - Unit: �Ȃ�
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


 ///////////////////�O���[�o���ϐ��ǉ��F�J�n/////////////
	 const int learn_length = 500;
	 Crane craneArm;
	 t_arm arm;
	 //�����ɒl���擾���邽��
	 double	theta0, theta1, theta2, theta3;	//�l��ۑ����邽��
	 char	order;							//�l��ۑ����邽��
	 bool	iscal_fin;				//�p�x�v�Z�I���̃t���O
	 bool	ishave_order;				//���ߑ҂������邩�̃t���O

	 ///////////////////�O���[�o���ϐ��ǉ��F�I��/////////////
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void Contorol_CraneInit(RTC::Manager* manager);
};

#endif // CONTOROL_CRANE_H
