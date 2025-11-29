// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncePadObj.generated.h"

UCLASS()
class ARCHERPUZZLE_API ABouncePadObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePadObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BounceComponent(AActor* Actor) const;

private:
	static UPrimitiveComponent* IsHasPhysics(const AActor* Act);

	FVector BounceStrength(const FVector& Velocity, const FVector& UpVector) const;
	
	UPROPERTY()
	float BounceMultiplier = 1.32f;
	
	UPROPERTY()
	float MinBounceSpeed = 25;
};
