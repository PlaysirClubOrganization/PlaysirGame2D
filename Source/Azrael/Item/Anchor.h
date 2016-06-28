// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item/Item.h"
#include "PaperSpriteComponent.h"
#include "Private/FunctionLibrary.h"
#include "Anchor.generated.h"

/**
 * 
 */
UCLASS()
class AZRAEL_API AAnchor : public AItem
{
	GENERATED_BODY()
public:
	bool GetIsSelected();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anchor )
	uint32 _isSelected : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anchor)
	uint32 _isIncremented: 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anchor)
	float _value;
	
};
