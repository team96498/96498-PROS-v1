

#include "main.h"

int RDerror;
int RDintegral;
int RDderivative;
int RDspeed;
int RDprevious_error;

int LDerror;
int LDintegral;
int LDderivative;
int LDspeed;
int LDprevious_error;

float DKp;
float DKi;
float DKd;
int LDtarget;
int RDtarget;

int pid;


void autoDrive(void* ignoreMe) {
	//Starts the PID Drive Control
	//need to insert parameters into bracket or startask does not work which is why we multiple void by ignoreMe
	while(true)
	{

		DKp=0.9; //refine PID Values
		DKi=0.16;
		DKd=12;


		if(pid == 2)
		{

      motorSet(7, LDspeed);
      motorSet(6, LDspeed);
      motorSet(5, RDspeed);
      motorSet(4, RDspeed);

			LDerror=LDtarget-encoderGet(LQuad);
			LDintegral=LDintegral+LDerror;
			RDerror=RDtarget-encoderGet(RQuad);
			RDintegral=RDintegral+RDerror;

			if(LDerror==0)
			{
				LDintegral=0;
			}

			if(abs(LDerror)>5)
			{
				LDintegral=0;
			}
			if(RDerror==0)
			{
				RDintegral=0;
			}

			if(abs(RDerror)>5)
			{
				RDintegral=0;
			}

			LDderivative=LDerror-LDprevious_error;
			LDprevious_error=LDerror;
			RDderivative=RDerror-RDprevious_error;
			RDprevious_error=RDerror;

			LDspeed=(DKp*LDerror)+(DKi*LDintegral)+(DKd*LDderivative);

			RDspeed=(DKp*RDerror)+(DKi*RDintegral)+(DKd*RDderivative);

			taskDelay(20);
		}
	}
}

void calculateVelocity(void* ignoreMe);

//IF ANYTHING GOES WRONG CHECK THE TASKHANDLE DELETE AT THE BOTTOM OF VOID PIDF
void PIDF(void* ignoreMe);
//everything above this is just configuration for PID Control/Regulations/Tasks
void autonomous() {
	if(analogRead(Potentiometer) <= 4095 && analogRead(Potentiometer) > 2048) //dial at the bottom
  {
  	pid = 0;
		//startTask(autoTurn);
  	encoderReset(LQuad);
		encoderReset(RQuad);
		TaskHandle PIDFHandle = taskCreate(PIDF, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGHEST);
		TaskHandle autoDriveHandle = taskCreate(autoDrive, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
		f_minPower = 70;
		f_targetVelocity = 550;
		wait(400);
		LDtarget = 100;
		RDtarget = 100;
		wait(6100);
		motorSet(m_Intake, 127);
		wait(2500);
		taskDelete(PIDFHandle);
		pid = 2;
		encoderReset(LQuad);
		encoderReset(RQuad);
		LDtarget = 700;
		RDtarget = 700;
		wait(2200);
		encoderReset(LQuad);
		encoderReset(RQuad);
		LDtarget = 360;
		RDtarget = -360;
		wait(900);
		motorSet(m_Lift, 50);
		wait(400);
		motorSet(m_Lift, 0);
		encoderReset(LQuad);
		encoderReset(RQuad);
		LDtarget = -1200;
		RDtarget = -1200;
		delay(100);
		taskDelete(autoDriveHandle);
  }
	if(analogRead(Potentiometer) >= 0 && analogRead(Potentiometer) < 2040) //dial at the top
  {
  	pid = 0;
		//startTask(autoTurn);
		encoderReset(LQuad);
		encoderReset(RQuad);
		TaskHandle PIDFHandle = taskCreate(PIDF, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGHEST);
	  TaskHandle autoDriveHandle = taskCreate(autoDrive, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
		f_minPower = 70;
		f_targetVelocity = 550;
		wait(400);
		LDtarget = 100;
		RDtarget = 100;
		wait(6100);
		motorSet(m_Intake, 127);
		wait(2500);
		taskDelete(PIDFHandle);
		pid = 2;
		encoderReset(LQuad);
		encoderReset(RQuad);
		LDtarget = 700;
		RDtarget = 700;
		wait(2200);
		encoderReset(LQuad);
		encoderReset(RQuad);
		LDtarget = -360;
		RDtarget = 360;
		wait(900);
		motorSet(m_Lift, 50);
		wait(400);
		motorSet(m_Lift, 0);
		encoderReset(LQuad);
		encoderReset(RQuad);
		LDtarget = -1200;
		RDtarget = -1200;
		taskDelete(autoDriveHandle);
		//IF ANY ORDER ISSUES ARE OCCURING CHECK WAIT VALUES AS THEY MAY HAVE BEEN CONVERTED FROM S TO MS
  }
}
