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


void UBridgeArrow::SpawnBridgeActor() const
{
	FTransform OwnerTrans = this->GetOwner()->GetActorTransform();
	auto br = GetWorld()->SpawnActor<AActor>(BridgeActor);
	br->SetActorRotation(FRotator(0, 90, 0));
	br->SetActorLocation(FVector(OwnerTrans.GetTranslation().X + 20, OwnerTrans.GetTranslation().Y, OwnerTrans.GetTranslation().Z));
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

