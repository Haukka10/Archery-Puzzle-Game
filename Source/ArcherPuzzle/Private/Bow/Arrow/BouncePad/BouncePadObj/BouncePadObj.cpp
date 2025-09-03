// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/BouncePad/BouncePadObj/BouncePadObj.h"

#include "ArcherPuzzleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	BounceMultiplier = 1.32f;
	MinBounceSpeed = 25;
	const auto UPrim = IsHasPhysics(Actor);
	// Check if this actor is an Arrows
	if (const auto Arrow = Actor->FindComponentByClass<UProjectileMovementComponent>())
	{
		const FVector BoostedVelocity = BounceStrength(Arrow->Velocity, Arrow->UpdatedComponent->GetForwardVector());
		
		Arrow->Velocity = BoostedVelocity;
		Arrow->UpdateComponentVelocity();
	}
	// Check if this actor is a physics actor
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
	if (Act == nullptr)
		return nullptr;
	
	UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Act->GetRootComponent());
	if (Prim && Prim->IsSimulatingPhysics())
		return Prim;
	
	return nullptr;
}

/// Calculation new bounce strength
/// @param Velocity Current velocity 
/// @param UpVector Up Vector of the actor
/// @return New Velocity
FVector ABouncePadObj::BounceStrength(const FVector& Velocity, const FVector& UpVector) const
{
	
	const float SpeedIntoPad = FVector::DotProduct(Velocity, -UpVector);
	const float BounceSpeed = FMath::Max(SpeedIntoPad * BounceMultiplier, MinBounceSpeed);

	const FVector TangentVelocity = Velocity - FVector::DotProduct(Velocity, UpVector) * UpVector;
	const FVector NewVelocity = TangentVelocity + UpVector * BounceSpeed;
	
	if (FMath::IsNaN(NewVelocity.Z) && FMath::IsNaN(NewVelocity.X) && FMath::IsNaN(NewVelocity.Y))
		return UpVector;
	
	if (Velocity.Z >= -1700.F)
		return NewVelocity;

	return {0,0,1800};
}

