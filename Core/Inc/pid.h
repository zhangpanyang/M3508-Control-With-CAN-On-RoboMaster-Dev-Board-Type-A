//
// Created by Sunny on 24-10-12.
//

#ifndef PID_H
#define PID_H

#define INRANGE(NUM, MIN, MAX)\
{\
if(NUM<MIN){\
NUM=MIN;\
}else if(NUM>MAX){\
NUM=MAX;\
}\
}

typedef struct
{
	float Kp;  // 比例增益
	float Ki;  // 积分增益
	float Kd;  // 微分增益
	float outputMax;
	float pMax;
	float integralMax;
} PIDInitializer;

class PID
{
public:
	float Kp;  // 比例增益
	float Ki;  // 积分增益
	float Kd;  // 微分增益
	float outputMax;
	float pMax;
	float integralMax;
	float prevError;  // 前一次误差
	float integral;   // 积分项累积

	explicit PID(PIDInitializer* initializer);
	float compute(float controlValue, float actualValue, float deltaTime);

private:
};

#endif //PID_H
