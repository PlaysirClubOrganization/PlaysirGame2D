// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "FunctionLibrary.h"

bool UFunctionLibrary::RoundedFloat(float low, float high, float valueIn, float &valueOut, bool isIncremented)
{
	if (!isIncremented)
	{
		if (valueIn > low)
			valueIn -= 0.05;
		else
		{
			valueOut = valueIn;
			return !isIncremented;
		}
	}
	else
	{
		if (valueIn < high)
			valueIn += 0.05;
		else
		{
			valueOut = valueIn;
			return !isIncremented;
		}
	}
	valueOut = valueIn;
	return isIncremented;
}