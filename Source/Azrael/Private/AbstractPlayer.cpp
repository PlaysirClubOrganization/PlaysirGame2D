// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "AzraelSaver.h"
#include "SpiritCharacter.h"
#include "AbstractPlayer.h"

void AAbstractPlayer::Init()
{
	Super::Init();
	_identity = Identity::Skeleton;
	_life = 50;
	
	for (int i = 0; i < AnimationState::MAX_ENUM_ANIMATION_STATE; ++i)
	{
		FString path = ENEMY_PATH_FOLDER;
		path += GetTypeAsFString() + GetAnimationNameAsFString(i);
		GetAnimationPaper()->Add(LoadFlipbook(*path));
	}
}


void AAbstractPlayer::AddCoin()
{
	_coin++;
}

void AAbstractPlayer::SaveData(UAzraelSaver * saver)
{
	saver->life = _life;
	saver->count = _coin;
	saver->level = ++_level;

}

void AAbstractPlayer::LoadData(UAzraelSaver * saver)
{
 	_life = saver->life;
	_coin = saver->count;
	_level = saver->level;
}
/************************************************************************/
/* Spirit Player Manager												*/
/************************************************************************/
void AAbstractPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAction("SpiritAttack", IE_Pressed, this, &AAbstractPlayer::TriggerTimeAttack);
	InputComponent->BindAction("SpiritAttack", IE_Released, this, &AAbstractPlayer::StopAttack);

}

void AAbstractPlayer::TriggerTimeAttack()
{
	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	for ( int i = 0; i < arrayOfActor.Num();i++)
	{
		arrayOfActor[i]->CustomTimeDilation = .1f;
	}
	_spiritCharacter->CustomTimeDilation = 1.0f;
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), .05f);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
						&AAbstractPlayer::StopAttack, 2.0f, false);
	_spiritCharacter->SetAttacking(true);
}

void AAbstractPlayer::StopAttack()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	_spiritCharacter->SetAttacking(false);

	TArray<AActor*> arrayOfActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), arrayOfActor);

	for ( int i = 0; i < arrayOfActor.Num(); i++)
	{
		arrayOfActor[i]->CustomTimeDilation = 1.0f;
	}

}
