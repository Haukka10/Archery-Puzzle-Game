// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/BouncePad/BouncePadArrow.h"

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

/// Spawn a bounce pad in the world 
/// @param SpawnVector get vector where to spawn a bounce pad
void UBouncePadArrow::SpawnBouncePadObj(const FVector SpawnVector) const
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FActorSpawnParameters SpawnInfo;
	World->SpawnActor<AActor>(BounceActor,SpawnVector,FRotator(0, 90, 0), SpawnInfo);
}
