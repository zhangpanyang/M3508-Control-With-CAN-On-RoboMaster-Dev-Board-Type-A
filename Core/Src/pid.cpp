//
// Created by Sunny on 24-10-12.
//

#include "pid.h"

// 初始化 PID 控制器
void PID_Init(PIDController *pid, float Kp, float Ki, float Kd) {
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->prevError = 0;
	pid->integral = 0;
}

// 计算 PID 输出
float PID_Compute(PIDController *pid, float setpoint, float actualValue, float deltaTime) {
	// 计算误差
	float error = setpoint - actualValue;

	// 计算比例项
	float Pout = pid->Kp * error;

	// 计算积分项
	pid->integral += error * deltaTime;
	float Iout = pid->Ki * pid->integral;

	// 计算微分项
	float derivative = (error - pid->prevError) / deltaTime;
	float Dout = pid->Kd * derivative;

	// 保存当前误差供下一次计算
	pid->prevError = error;

	// 计算最终输出
	float output = Pout + Iout + Dout;
	return output;
}