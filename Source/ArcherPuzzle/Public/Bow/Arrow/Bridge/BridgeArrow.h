// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BridgeArrow.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCHERPUZZLE_API UBridgeArrow : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBridgeArrow();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> BridgeActor;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	double OffSet = 20;

	UFUNCTION(BlueprintCallable)
	void SpawnBridgeActor() const;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Texture2D;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	
	UPROPERTY()
	FRotator M_NewRotator;
		
};
