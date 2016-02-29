// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "Enemy.h"




void AEnemy::initEnemy()
{
	/*_pawnSensing = NewObject<UPawnSensingComponent>(this, UPawnSensingComponent::StaticClass());
	_pawnSensing->SetPeripheralVisionAngle(45.0f);
	_pawnSensing->SetSensingInterval(.24f);
	_pawnSensing->AddToRoot();*/
}

void AEnemy::UpdateAnimation()
{
	//if(_pawnSensing->)

}

void AEnemy::MoveRight(float Value)
{

}

void AEnemy::UpdateCharacter()
{
}

void AEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}
