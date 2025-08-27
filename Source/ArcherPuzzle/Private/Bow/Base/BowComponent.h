// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBowComponent();
	
	UFUNCTION()
	void ShootArrow() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Arrows|List")
	TMap<TSubclassOf<AActor>,float> ArrowCooldown; // List of the Actor to spawn arrow when player shooting

	UFUNCTION()
	void ChangeArrow(int index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Arrows|SpawnTrnas")
	FTransform ArrowSpawnTrans;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<AActor> M_CurrentArrowShoot = nullptr;

	UPROPERTY()
	TArray<TSubclassOf<AActor>> M_ArrowActors;

	UPROPERTY()
	uint8 M_IndexOfArrow = 0;

	UPROPERTY()
	mutable bool M_IsCountDown = false;

	UPROPERTY()
	mutable bool M_IsCanShoot = true;
	
	UFUNCTION()
	bool CanShoot() const;

	UFUNCTION()
	bool CanChangeArrow();
	
	UFUNCTION()
	bool IsTimerStart() const;
	
	UFUNCTION()
	void IsTimerDone() const;
};
