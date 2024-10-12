//
// Created by Sunny on 24-10-12.
//

#ifndef M3508_MOTOR_H
#define M3508_MOTOR_H

#include "main.h"

float linearMapping(int in,int in_min,int in_max,float out_min,float out_max);
int linearMapping(float in,float in_min,float in_max,int out_min,int out_max);

class M3508_Motor
{
private:

public:
	float ratio_; // 电机减速比
	float angle_; // deg 输出端累计转动角度
	float delta_angle_; // deg 输出端新转动的角度
	float ecd_angle_; // deg 当前电机编码器角度
	float last_ecd_angle_; // deg 上次电机编码器角度
	float delta_ecd_angle_; // deg 编码器端新转动的角度
	float rotate_speed_; // dps 反馈转子转速
	float current_;
	float temprature_;

	M3508_Motor();
	void canRxMsgCallback_v2(uint8_t rx_data[8]);
};

#endif //M3508_MOTOR_H
