// Fill out your copyright notice in the Description page of Project Settings.

#include "Azrael.h"
#include "Item.h"
#include "Kismet/KismetMathLibrary.h"




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

bool AItem::DestroyOnActor(UClass *ClassTarget,AActor* actorBeginOverlap, AActor * ActorToDestroy)
{
	if (!actorBeginOverlap || !ActorToDestroy)
		return false;
	bool res = UKismetMathLibrary::EqualEqual_ClassClass(ClassTarget, actorBeginOverlap->GetClass());

	if (res)
		ActorToDestroy->Destroy();
	return res;
}

bool AItem::SelfDestroyOnActor(UClass *ClassTarget, AActor* actorBeginOverlap)
{
	bool res = UKismetMathLibrary::EqualEqual_ClassClass(ClassTarget, actorBeginOverlap->GetClass());

	if (res)
		Destroy();
	return res;
}
