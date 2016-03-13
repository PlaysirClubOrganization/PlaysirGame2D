// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "Item.h"




AItem::AItem()
{

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AItem::DestroyOnActor(UClass *ClassTarger, AActor * ActorToDestroy)
{
	ClassTarger->GetClass()->is

	return true;
}

