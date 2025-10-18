// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/Fly/FlyArrow.h"

// Sets default values for this component's properties
UFlyArrow::UFlyArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UFlyArrow::SpawnFlyTunnel(FVector FlyTunnelLoc) const
{
	if (FlyTunnel == nullptr)
		return;
	
	if (FlyTunnelLoc.IsZero() == true)
		return;
	
	AActor* FlyTun = GetWorld()->SpawnActor<AActor>(FlyTunnel);
	
	if (FlyTun == nullptr)
		return;
	
	const float ActorScale = FlyTun->GetSimpleCollisionHalfHeight();
	FlyTunnelLoc.Z += ActorScale;
	
	FlyTun->SetActorLocation(FlyTunnelLoc);
}


// Called when the game starts
void UFlyArrow::BeginPlay()
{
	Super::BeginPlay();

	if (FlyTunnel == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("FlyTunnel is null"));
	}
	
}


// Called every frame
void UFlyArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

