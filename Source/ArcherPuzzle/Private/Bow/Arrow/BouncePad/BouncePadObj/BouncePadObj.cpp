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
	FVector BounceNormal = Actor->GetActorUpVector(); // Default: pad faces upward
	FVector Velocity = FVector::ZeroVector;
	
	const auto UPrim = IsHasPhysics(Actor);
	if (UPrim)
	{
		/*FVector Vel = UPrim->GetComponentVelocity();
		FVector BounceNormal = Actor->GetActorForwardVector().GetSafeNormal();

		float SpeedIntoPad = FVector::DotProduct(Vel, BounceNormal);
		float BounceSpeed = FMath::Max(SpeedIntoPad * 1.25, 25);

		const FVector TangentVelocity = Vel - FVector::DotProduct(Vel, BounceNormal) * BounceNormal;

		const FVector NewVelocity = TangentVelocity + BounceNormal * BounceSpeed;

		UPrim->SetPhysicsLinearVelocity(NewVelocity, false);*/
	}
	
	if (const ACharacter* Char = Cast<ACharacter>(Actor))
	{
		Velocity = Char->GetVelocity();
		float SpeedIntoPad = FVector::DotProduct(Velocity, -BounceNormal);
		float BounceSpeed = FMath::Max(SpeedIntoPad * 1.35, 25);

		FVector TangentVelocity = Velocity - FVector::DotProduct(Velocity, BounceNormal) * BounceNormal;
		FVector NewVelocity = TangentVelocity + BounceNormal * BounceSpeed;

		if (UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			MoveComp->Velocity = NewVelocity;
		}
	}
}

UPrimitiveComponent* ABouncePadObj::IsHasPhysics(AActor* Act)
{
	const auto Prim = Cast<UPrimitiveComponent>(Act);
	if (Prim == nullptr)
		return nullptr;
	
	return Prim;
}

