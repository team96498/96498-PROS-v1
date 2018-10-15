
#include "main.h"

//PRE OPCON SHENANIGANS



void calculateVelocity(void* ignoreMe)
{
	while(true)
	{
		firstSample = encoderGet(FQuad);
		wait(0.1);
		secondSample = encoderGet(FQuad);
		currentVelocity = secondSample - firstSample;
		encoderReset(FQuad);
		taskDelay(20);
	}
}


//IF ANYTHING GOES WRONG CHECK THE TASKHANDLE DELETE AT THE BOTTOM OF VOID PIDF


void PIDF(void* ignoreMe) {
	taskCreate(calculateVelocity, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGHEST);
	//f_Kp=0.5; (Old Legacy Regulator System)
	f_ki=1.5; //Alter Values, decrease by 1 if needed
	f_Kd=0.8; //Alter Values, decrease bf 1 by needed
	f_minPower = 70;//60; // Ballpark range for the motor to go to, so the PID can tweak
	f_targetVelocity =450; //100;

	while(true)
	{

		f_previousError = f_error;
		f_error = f_targetVelocity - currentVelocity;

		f_derivative = f_previousError - f_error;


		if(currentVelocity < (f_targetVelocity - 25)) //runs at max power so when it reaches target velocity it decreases
		{
			motorSet(2, 127);
		}
		else if(currentVelocity > (f_targetVelocity - 25)) //runs adjustment
		{

			f_finalPower = f_minPower + (f_ki * f_error) + (f_Kd * f_derivative);
			motorSet(2, f_finalPower);
			}

		taskDelay(20);
}

}

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
		if(joystickGetDigital(1, 6, JOY_UP)) //Flywheel On
				{
					PIDFHandle = taskCreate(PIDF, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGHEST);
					f_minPower = 80;
					f_targetVelocity = 600;
				}
		if(joystickGetDigital(1, 6, JOY_DOWN)) // Flywheel Off
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
						motorSet(m_LDFront, joystickGetAnalog(1, 2) + joystickGetAnalog(1, 1)*0.88 ); //7
						motorSet(m_LDBack, joystickGetAnalog(1, 2) - joystickGetAnalog(1, 1)*0.88); //6
						motorSet(m_RDFront, joystickGetAnalog(1, 2) + joystickGetAnalog(1, 1)*0.88); //5
						motorSet(m_RDBack, joystickGetAnalog(1, 2) - joystickGetAnalog(1, 1)*0.88); //4
						//IF ROBOT FRONT IS INCORRECT CHANGE LB AND LF AS WELL AS RB AND RF
						// RE-DO ARCADE CONTROL BEFORE BRAIN ANEURYSM


				 if(joystickGetDigital(1,8, JOY_UP))
						{
							digitalWrite(1, HIGH); //write LOW to port 1 (Solenoid may be extended or retracted, set to HIGH to reverse)
						}
				 if(joystickGetDigital(1,8, JOY_DOWN))
						{
							digitalWrite(1, LOW); //write LOW to port 1 (Solenoid may be extended or retracted, set to HIGH to reverse)
						}
						//SOLENOID VALUES NEED TO BE CHECKED SO THEY ARE MOVING IN THE CORRECT DIRECTION



					if(joystickGetDigital(1, 7, JOY_UP)) //Intake
						{
							motorSet(m_Intake, 100); //Power is set to be less in intake than detake, so cap flipping is possible but ball clogging is not.
						}
					else if(joystickGetDigital(1, 7, JOY_DOWN)) //Intake
						{
							motorSet(m_Intake, -127);
						}
					else
						{
							motorSet(m_Intake, 0);
						}



					if(joystickGetDigital(1, 5, JOY_DOWN)) //Arms
						{
							motorSet(m_Lift, -100);
						}
					else if(joystickGetDigital(1, 5, JOY_UP)) //Arms
						{
							motorSet(m_Lift, 100);
						}
					else
						{
							motorSet(m_Lift, 0);
						}



					if(joystickGetDigital(1, 8, JOY_LEFT)) //RPI
						{
							motorSet(m_RPI, 100);
						}
					else if(joystickGetDigital(1, 8, JOY_RIGHT)) //RPI
						{
							motorSet(m_RPI, -100);
						}
					else
						{
							motorSet(m_RPI, 0);
						}



	}
}
