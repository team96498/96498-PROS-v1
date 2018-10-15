
#ifndef MAIN_H_

#define MAIN_H_



#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FQUAD_TOP_PORT 1
#define FQUAD_BOTTOM_PORT 2

#define LQUAD_TOP_PORT 3
#define LQUAD_BOTTOM_PORT 4

#define RQUAD_TOP_PORT 5
#define RQUAD_BOTTOM_PORT 6

#define POTENTIOMETER_PORT 1

Encoder FQuad;
Encoder LQuad;
Encoder RQuad;

int firstSample;
int secondSample;
float f_derivative;
float f_error;
float f_finalPower;
//float f_Kp;
float f_Kd;
float f_ki;
float f_minPower;
float f_previousError;
float f_targetVelocity;
float currentVelocity;

enum MOTOR_CONFIG
{
	m_Flywheel = 2,
	m_Lift = 3,
	m_Intake = 8,
	m_RPI = 9,
	m_LDFront = 6, //needs to be confirmed
	m_LDBack = 7, //needs to be confirmed
	m_RDFront = 5, //needs to be confirmed
	m_RDBack = 4, //needs to be confirmed
};

enum JOYSTICK_CONFIG
{
	j_Main = 1,
	j_Partner = 2,
};


void autonomous();
/**
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO();
/**
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize();
/**
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl();

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
