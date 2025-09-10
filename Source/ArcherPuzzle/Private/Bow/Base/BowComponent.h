// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bow/LockArrows/LockArrows.h"
#include "Components/ActorComponent.h"
#include "BowComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBowComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBowComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Arrow|List")
	TMap<TSubclassOf<AActor>,float> ArrowCooldown; // List of the Actor to spawn arrow when player shooting

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Arrow|SpawnTrnas")
	FTransform ArrowSpawnTrans;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Arrow|Lock")
	ALockArrows* LockArrows = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Arrow|Audio")
	USoundBase* SoundClass;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ChangeArrow(int Index);
	
	UFUNCTION()
	void ShootArrow() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
	bool CanChangeArrow(const TSubclassOf<AActor>& SelArrow);
	
	UFUNCTION()
	void IsTimerStart() const;
	
	UFUNCTION()
	void IsTimerDone() const;
};
