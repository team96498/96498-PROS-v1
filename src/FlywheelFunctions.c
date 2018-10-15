#include "main.h"


void calculateVelocity(void* ignoreMe)
{
	while(true)
	{
		firstSample = encoderGet(FQuad);
		wait(100);
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
