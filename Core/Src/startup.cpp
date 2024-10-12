//
// Created by Sunny on 24-10-12.
//

#include "startup.h"
#include "can_task.h"

void startup()
{
	canTaskInit();

	while(1)
	{
		// SetMotorCurrent(1);
		HAL_Delay(1000);
		// SetMotorCurrent(0);
		// HAL_Delay(1000);
	}
}