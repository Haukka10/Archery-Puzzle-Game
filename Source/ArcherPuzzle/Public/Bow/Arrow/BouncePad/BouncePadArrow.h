// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BouncePadArrow.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCHERPUZZLE_API UBouncePadArrow : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBouncePadArrow();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnBouncePadObj(FVector SpawnVector);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> BounceActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Texture2D;
};
