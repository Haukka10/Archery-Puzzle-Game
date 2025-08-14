// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/BouncePad/BouncePadArrow.h"

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

void UBouncePadArrow::SpawnBouncePadObj()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	const FTransform OwnerTrans = this->GetOwner()->GetActorTransform();
	World->SpawnActor(BounceActor,&OwnerTrans);
}
