// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/BouncePad/BouncePadArrow.h"

#include "ArcherPuzzleCharacter.h"
// WORK IN PROGRESS
// Sets default values for this component's properties
UBouncePadArrow::UBouncePadArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBouncePadArrow::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBouncePadArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBouncePadArrow::CheckForCollision(AActor* ActorColl)
{
	if (IsHasPhysics(ActorColl))
	{
		const auto PlayerLuch = Cast<AArcherPuzzleCharacter>(ActorColl);
		if (PlayerLuch == nullptr)
		{
			const auto Prim = Cast<UPrimitiveComponent>(ActorColl);
			if (Prim == nullptr)
				return;

		}
		PlayerLuch->LaunchCharacter({0,0,5000},false,false);
	}
}

bool UBouncePadArrow::IsHasPhysics(AActor* Act)
{
	
	return true;
}

