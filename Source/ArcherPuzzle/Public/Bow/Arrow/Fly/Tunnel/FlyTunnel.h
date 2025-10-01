// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyTunnel.generated.h"

UCLASS()
class ARCHERPUZZLE_API AFlyTunnel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyTunnel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void FlyTunnelStartEffect(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static void FlyTunnelEndEffect(AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoostObj;
	
private:
	
	UPROPERTY()
	float M_OldVelocity;
};
