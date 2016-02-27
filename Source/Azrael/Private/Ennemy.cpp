// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "Ennemy.h"
#include "EngineGlobals.h"




void AEnnemy::initEnemy()
{
	_pawnSensing = NewObject<UPawnSensingComponent>(this,UPawnSensingComponent::StaticClass());
	_pawnSensing->SetPeripheralVisionAngle(45.0f);
	_pawnSensing->SetSensingInterval(.24f);
	_pawnSensing->AddToRoot();
}

void AEnnemy::UpdateAnimation()
{
	//if(_pawnSensing->)

}

void AEnnemy::MoveRight(float Value)
{

}

void AEnnemy::UpdateCharacter()
{
}

void AEnnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}
