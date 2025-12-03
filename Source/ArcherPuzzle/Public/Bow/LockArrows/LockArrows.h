// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockArrows.generated.h"

UCLASS()
class ARCHERPUZZLE_API ALockArrows : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockArrows();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category = "LockArrows")
	TArray<TSubclassOf<AActor>> M_ArrowsList;
	
	UFUNCTION()
	bool IsLockArrow(const TSubclassOf<AActor>& Arrow);
};
