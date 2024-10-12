//
// Created by Sunny on 24-10-12.
//

#include "can_task.h"
#include "can.h"

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