// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS(abstract)
class AZRAEL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Item)
		virtual bool DestroyOnActor(UClass *ClassTarget, AActor* actorBeginOverlap, AActor * ActorToDestroy);
	UFUNCTION(BlueprintCallable, Category = Item)
		virtual bool SelfDestroyOnActor(UClass *ClassTarget, AActor* actorBeginOverlap);
	
};
