//
// Created by Sunny on 24-10-12.
//

#include "can_task.h"

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
	rotate_speed_ = temporar_speed;

	// 实际转矩电流
	uint16_t current_gao= rx_data[4];
	uint16_t current_di= rx_data[5];
	uint16_t temporar_current = (current_gao<< 8) | current_di; // 合并
	current_ = linearMapping(temporar_current, -16384, 16384, -20, 20); // 映射

	// 电机温度
	temprature_ = rx_data[6];
}

void canTaskInit()
{
	CAN_FilterTypeDef filterConfig = {
		.FilterIdHigh = 0x0000,
		.FilterIdLow = 0x0000,
		.FilterMaskIdHigh = 0x0000,
		.FilterMaskIdLow = 0x0000,
		.FilterFIFOAssignment = CAN_FILTER_FIFO0,
		.FilterBank = 0,
		.FilterMode = CAN_FILTERMODE_IDMASK,
		.FilterScale = CAN_FILTERSCALE_32BIT,
		.FilterActivation = ENABLE
	};
	HAL_CAN_ConfigFilter(&hcan1, &filterConfig);
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

uint8_t rxData[8];
CAN_RxHeaderTypeDef rxHeader;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
	if (hcan == &hcan1)
	{
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, rxData);
	}
}