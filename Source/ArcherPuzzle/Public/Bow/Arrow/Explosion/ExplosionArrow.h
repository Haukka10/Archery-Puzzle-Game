// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExplosionArrow.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCHERPUZZLE_API UExplosionArrow : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExplosionArrow();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void CheckSphere() const;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Impulse|Radius Impulse")
	float Radius;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Impulse|Strength Impulse")
	float StrengthOfImpulse ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Impulse|Multiplayer")
	float Multiplayer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* Texture2D;

private:

	UFUNCTION()
	void AddImpulse(const FVector& Center, UPrimitiveComponent* UPrimitive) const;

	UFUNCTION()
	static float FindDistance(const FVector& OnePoint, const FVector& SecPoint);

	UPROPERTY()
	double M_MaxVelocity = 350;

};
