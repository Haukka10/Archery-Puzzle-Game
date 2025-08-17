// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/BouncePad/BouncePadObj/BouncePadObj.h"

#include "ArcherPuzzleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABouncePadObj::ABouncePadObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABouncePadObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncePadObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABouncePadObj::BounceComponent(AActor* Actor)
{
	// Get Up Vector
	const FVector BounceNormal = Actor->GetActorUpVector();
	// Check if this actor is a physics actor
	const auto UPrim = IsHasPhysics(Actor);
	if (UPrim)
	{
		const FVector Velocity = BounceStrength(UPrim->GetComponentVelocity(), UPrim->GetForwardVector());
		UPrim->SetPhysicsLinearVelocity(Velocity, false);
	}
	//Check if this actor is a Character
	if (const ACharacter* Char = Cast<ACharacter>(Actor))
	{
		//Set new bounce strength
		const FVector NewVel = BounceStrength(Actor->GetVelocity(),BounceNormal);

		if (UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			// Adds new speed to the character
			MoveComp->Velocity = NewVel;
		}
	}
}

/// Check is actor have a PrimitiveComponent
/// @param Act 
/// @return nullptr or primitiveComponent
UPrimitiveComponent* ABouncePadObj::IsHasPhysics(AActor* Act)
{
	const auto Prim = Cast<UPrimitiveComponent>(Act);
	if (Prim == nullptr)
		return nullptr;
	
	return Prim;
}

/// Calculation new bounce strength
/// @param Velocity Current velocity 
/// @param UpVector Up Vector of the actor
/// @return New Velocity
FVector ABouncePadObj::BounceStrength(const FVector& Velocity, const FVector& UpVector)
{

	const float SpeedIntoPad = FVector::DotProduct(Velocity, -UpVector);
	const float BounceSpeed = FMath::Max(SpeedIntoPad * 1.20, 20);

	const FVector TangentVelocity = Velocity - FVector::DotProduct(Velocity, UpVector) * UpVector;
	const FVector NewVelocity = TangentVelocity + UpVector * BounceSpeed;
	
	if (Velocity.Z >= -1700.F)
		return NewVelocity;
	
	return {0,0,1800};
}

