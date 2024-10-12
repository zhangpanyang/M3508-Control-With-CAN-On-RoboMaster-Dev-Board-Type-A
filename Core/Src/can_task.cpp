//
// Created by Sunny on 24-10-12.
//

#include "can_task.h"
#include "M3508_Motor.h"

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

M3508_Motor motor;

uint8_t rxData[8];
CAN_RxHeaderTypeDef rxHeader;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
	if (hcan == &hcan1)
	{
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, rxData);
		motor.canRxMsgCallback_v2(rxData);
	}
}

CAN_TxHeaderTypeDef txHeader={
.StdId = 0x200,
.ExtId = 0x200,
.IDE = CAN_ID_STD,
.RTR = CAN_RTR_DATA,
.DLC = 8,
.TransmitGlobalTime = DISABLE
};
uint32_t txMailbox;
uint8_t txData[8];

void SetMotorCurrent(float current)
{
	int currentData = linearMapping(current, -20.0f, 20.0f, -16384, 16384);
	for (int i = 0; i < 8; i++)
	{
		txData[i] = (i&1) ? (currentData>>8) : (currentData&0xff);
	}
	HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox);
}