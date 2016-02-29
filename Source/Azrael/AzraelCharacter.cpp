// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Azrael.h"
#include "AzraelCharacter.h"



//////////////////////////////////////////////////////////////////////////
// AAzraelCharacter 


/*
* FConstructorStatics will automatically load the different sprite of the any character by giving
* the right id in the init function.
*
* @warning : The project must bu construct
*/
struct FConstructorStatics
{
	TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>*> AnimationInstance;
	FConstructorStatics(FString Character)
		: AnimationInstance(TArray<ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>*>())
	{
		FString myFString = ("/Game/Azrael/Sprites/Enemy/" + Character);
		auto t = myFString.GetCharArray();
		TCHAR * r = NULL;
		for (int i = 0; i < t.Num(); ++i)
		{
			*r += t[i];
		}

		//TODO boucle for sur les flipbook
		AnimationInstance.Push(new ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook>(r));
	}
	~FConstructorStatics()
	{
		for (int i = 0; i < AnimationInstance.Num(); i++)
		{
			delete AnimationInstance[i];
		}
	}

};

void AAzraelCharacter::init()
{
	static FConstructorStatics ConstructorStatics(_identity);
	for (int i = 0; i < ConstructorStatics.AnimationInstance.Num(); i++)
	{
		getAnimationPaper().Add(i, ConstructorStatics.AnimationInstance[i]->Get());
	}

}

void AAzraelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

TMap<uint8, UPaperFlipbook *> AAzraelCharacter::getAnimationPaper()
{
	return m_animationMap;
}

UPaperFlipbook * AAzraelCharacter::getFlipbook(uint8 idAnim)
{
	return (UPaperFlipbook *)getAnimationPaper().Find((AnimationState)idAnim);
}


