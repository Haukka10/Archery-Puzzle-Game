// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/Bridge/BridgeArrow.h"

// Sets default values for this component's properties
UBridgeArrow::UBridgeArrow(): M_NewRotator(0,0,0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

///
/// Spawn bridge at 'OwnerTrans' with offset
///
void UBridgeArrow::SpawnBridgeActor() const
{
	const FTransform OwnerTrans = this->GetOwner()->GetActorTransform();
	const auto Br = GetWorld()->SpawnActor<AActor>(BridgeActor);
	// Set rotation and locations for the bridge
	Br->SetActorRotation(ActorRotation);
	const FVector NewLocation = FVector(OwnerTrans.GetTranslation().X + OffSet, OwnerTrans.GetTranslation().Y, OwnerTrans.GetTranslation().Z);
	Br->SetActorLocation(NewLocation);
}

// Called when the game starts
void UBridgeArrow::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBridgeArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

