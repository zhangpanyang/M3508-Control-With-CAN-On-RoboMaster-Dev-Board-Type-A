//
// Created by Sunny on 24-10-26.
//

#ifndef FILTER_H
#define FILTER_H

#include "main.h"
#include <queue>

class FilterMovingAverage
{
private:
	std::queue<float> valueQueue_;
	float sum_;
public:
	uint32_t len_;

	FilterMovingAverage(uint32_t len);
	void push(float value);
	float getResult();
};

#endif //FILTER_H
