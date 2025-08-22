// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhaseArrow.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCHERPUZZLE_API UPhaseArrow : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhaseArrow();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* WallMaterial;

	UFUNCTION(BlueprintCallable)
	void AddWall(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void ResetWall() const;
	
private:
	
	UFUNCTION()
	void ChangeProperty() const;

	UPROPERTY()
	AActor* M_WallActor = nullptr;

	UPROPERTY()
	UMaterialInterface* M_PreWallMaterial = nullptr;
	
	ECollisionEnabled::Type	M_WallCollision = ECollisionEnabled::Type::QueryAndPhysics;
	
	UPROPERTY()
	UPrimitiveComponent* PrimComp = nullptr;
};
