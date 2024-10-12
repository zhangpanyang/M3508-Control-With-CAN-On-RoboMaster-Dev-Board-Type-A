//
// Created by Sunny on 24-10-12.
//

#include "M3508_Motor.h"

M3508_Motor::M3508_Motor(){
	ratio_ = 3591.0 / 187;
	angle_ = 0;
	delta_angle_ = 0;
	ecd_angle_ = 0;
	last_ecd_angle_ = 0;
	delta_ecd_angle_ = 0;
	rotate_speed_ = 0;
	current_ = 0.87;
	temprature_ = 0;
}

float linearMapping(int in,int in_min,int in_max,float out_min,float out_max) {
	return (out_max-out_min)*(float)(in-in_min)/(float)(in_max-in_min)+out_min;
}
int linearMapping(float in,float in_min,float in_max,int out_min,int out_max) {
	return (out_max-out_min)*(in-in_min)/(in_max-in_min)+out_min;
}

void M3508_Motor::canRxMsgCallback_v2(uint8_t rx_data[8]) {
	// 转子机械角度
	int ecd_angle = ((int)rx_data[0] << 8) | rx_data[1];
	ecd_angle_ = linearMapping(ecd_angle, 0, 8191, 0, 360); // 映射

	delta_ecd_angle_ = ecd_angle_ - last_ecd_angle_;	//计算增量

	if (delta_ecd_angle_ > 180) delta_ecd_angle_ -= 360;
	if (delta_ecd_angle_ < -180) delta_ecd_angle_ += 360;

	last_ecd_angle_ = ecd_angle_;	//更新

	// 转子转速
	int rotate_speed = ((int)rx_data[2]<< 8) | rx_data[3];
	rotate_speed_ = rotate_speed * 6;

	// 实际转矩电流
	int current = ((int)rx_data[4]<< 8) | rx_data[5]; // 合并
	current_ = linearMapping(current, -16384, 16384, -20, 20); // 映射

	// 电机温度
	temprature_ = rx_data[6];
}
