//
// Created by Sunny on 24-10-12.
//

#include "pid.h"

PID::PID(PIDInitializer* initializer)
{
	Kp = initializer->Kp;
	Ki = initializer->Ki;
	Kd = initializer->Kd;
	outputMax = initializer->outputMax;
	pMax = initializer->pMax;
	iMax = initializer->iMax;
	prevError = 0;
	integral = 0;
}

float PID::compute(float controlValue, float actualValue, float deltaTime)
{
	float error = controlValue - actualValue;
	integral += error;
	float compP = Kp * error;
	float compI = Ki * integral;
	float compD = Kd * (error - prevError) / deltaTime;
	INRANGE(compP, 0 ,pMax);
	INRANGE(compI, 0, iMax);
	float output = compP + compI + compD;
	INRANGE(output, 0, outputMax);

	prevError = error;
	return output;
}