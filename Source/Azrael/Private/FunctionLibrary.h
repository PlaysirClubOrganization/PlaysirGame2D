// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Selected)
	static bool RoundedFloat(float low, float high, float valueIn, float &valueOut, bool isIncremented);

	UFUNCTION(BlueprintCallable, Category = Math)
	static float AngleBetweenVector(FVector vectorOne, FVector vectorTwo);
};
