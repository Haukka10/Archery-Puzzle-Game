// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/BouncePad/BouncePadObj/BouncePadObj.h"

#include "ArcherPuzzleCharacter.h"

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
	const auto UPrim = IsHasPhysics(Actor);
	if (UPrim == nullptr)
		return;
	
	FVector Vel = UPrim->GetComponentVelocity();
	FVector BounceNormal = Actor->GetActorForwardVector().GetSafeNormal();

	const float SpeedIntoBounce = FVector::DotProduct(Vel, BounceNormal);
	const float BounceSpeed = FMath::Max(SpeedIntoBounce * 1.25,25);

	const FVector TangentVelocity = Vel - FVector::DotProduct(Vel, BounceNormal) * BounceNormal;

	const FVector NewVelocity = TangentVelocity + BounceNormal * BounceSpeed;

	UPrim->SetPhysicsLinearVelocity(NewVelocity, false);
}

UPrimitiveComponent* ABouncePadObj::IsHasPhysics(AActor* Act)
{
	const auto Prim = Cast<UPrimitiveComponent>(Act);
	if (Prim == nullptr)
		return nullptr;
	
	return Prim;
}

