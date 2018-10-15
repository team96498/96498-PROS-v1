
#include "main.h"
#include "FlywheelFunctions.h"

//PRE OPCON SHENANIGANS


void operatorControl() {
	while (1) {

		//if(abs(joystickGetAnalog(1, 1)) < 15) // exclusion zone, if motor power is low will not run.
		//{
			//motorSet(2, 0); //motor port 2 will get no power
		//}
		//else
		//{
			//motorSet(2, joystickGetAnalog(1, 1));
		//}
 		//personal reference
		//digitalWrite(1, LOW); //HIGH or LOW to port 1 in place of LOW
		//Set this to a command, right now it's just ere cuz can
		//delay(20);

		TaskHandle PIDFHandle;
		if(joystickGetDigital(j_Main, 6, JOY_UP)) //Flywheel On
				{
					PIDFHandle = taskCreate(PIDF, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGHEST);
					f_minPower = 80;
					f_targetVelocity = 600;
				}
		if(joystickGetDigital(j_Main, 6, JOY_DOWN)) // Flywheel Off
				{
					motorSet(m_Flywheel, 0);
					f_minPower = 0;
					f_targetVelocity = 0;
					taskDelete(PIDFHandle);
				}

						//If robot's front has been altered access F/B's setup and change LB <-> LF & RB <-> RF
					  //we multiply by 0.88 as the max stress a motor can take is 88% full power, and 127% will just
					  //burn out the motor, so this value is good for moderation, PROS however only accepts int values for motors and this is a float,
						//this means the efficiency will be slightly impacted.
						motorSet(m_LDFront, joystickGetAnalog(j_Main, 2) + joystickGetAnalog(j_Main, 1)*0.88 ); //7
						motorSet(m_LDBack, joystickGetAnalog(j_Main, 2) - joystickGetAnalog(j_Main, 1)*0.88); //6
						motorSet(m_RDFront, joystickGetAnalog(j_Main, 2) + joystickGetAnalog(j_Main, 1)*0.88); //5
						motorSet(m_RDBack, joystickGetAnalog(j_Main, 2) - joystickGetAnalog(j_Main, 1)*0.88); //4
						//IF ROBOT FRONT IS INCORRECT CHANGE LB AND LF AS WELL AS RB AND RF
						// RE-DO ARCADE CONTROL BEFORE BRAIN ANEURYSM


				 if(joystickGetDigital(j_Main,8, JOY_UP))
						{
							digitalWrite(1, HIGH); //write LOW to port 1 (Solenoid may be extended or retracted, set to HIGH to reverse)
						}
				 if(joystickGetDigital(j_Main,8, JOY_DOWN))
						{
							digitalWrite(1, LOW); //write LOW to port 1 (Solenoid may be extended or retracted, set to HIGH to reverse)
						}
						//SOLENOID VALUES NEED TO BE CHECKED SO THEY ARE MOVING IN THE CORRECT DIRECTION



					if(joystickGetDigital(j_Main, 7, JOY_UP)) //Intake
						{
							motorSet(m_Intake, 100); //Power is set to be less in intake than detake, so cap flipping is possible but ball clogging is not.
						}
					else if(joystickGetDigital(j_Main, 7, JOY_DOWN)) //Intake
						{
							motorSet(m_Intake, -127);
						}
					else
						{
							motorSet(m_Intake, 0);
						}



					if(joystickGetDigital(j_Main, 5, JOY_DOWN)) //Arms
						{
							motorSet(m_Lift, -100);
						}
					else if(joystickGetDigital(j_Main, 5, JOY_UP)) //Arms
						{
							motorSet(m_Lift, 100);
						}
					else
						{
							motorSet(m_Lift, 0);
						}



					if(joystickGetDigital(j_Main, 8, JOY_LEFT)) //RPI
						{
							motorSet(m_RPI, 100);
						}
					else if(joystickGetDigital(j_Main, 8, JOY_RIGHT)) //RPI
						{
							motorSet(m_RPI, -100);
						}
					else
						{
							motorSet(m_RPI, 0);
						}



	}
}
