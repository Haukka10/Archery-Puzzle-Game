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

void ABouncePadObj::AddBounce(AActor* Actor)
{
	const auto UPrim = IsHasPhysics(Actor);
	if (UPrim == nullptr)
		return;
	
	const auto PlayerLuch = Cast<AArcherPuzzleCharacter>(Actor);
	if (PlayerLuch == nullptr)
	{
		UPrim->AddImpulse({0, 0, 500},NAME_None,false);
		return;
	}
	
	PlayerLuch->LaunchCharacter({0,0,5000},false,false);
}

UPrimitiveComponent* ABouncePadObj::IsHasPhysics(AActor* Act)
{
	if (const auto Prim = Cast<UPrimitiveComponent>(Act); Prim == nullptr)
		return Prim;
	
	return nullptr;
}

