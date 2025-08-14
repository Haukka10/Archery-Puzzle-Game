// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/Teleport/TeleportArrow.h"

// Sets default values for this component's properties
UTeleportArrow::UTeleportArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleportArrow::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTeleportArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTeleportArrow::TeleportPlayer(const FVector TeleLoc) const
{
	if (IsValidPos(TeleLoc))
	{
		PlayerToTele->SetActorLocation(TeleLoc);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Not Teleporting (not valid pos)")));
	}
}

bool UTeleportArrow::IsValidPos(const FVector& TeleLoc) const
{
	GWorld = GetWorld();
	if (GWorld == nullptr)
		return false;
	
	FHitResult HitResult;
	
	const FVector Start = {TeleLoc.X+50,TeleLoc.Y+50,TeleLoc.Z+50};
	const FVector c = {TeleLoc.X, TeleLoc.Y, TeleLoc.Z-250};
	
	const auto HitBool = GWorld->LineTraceSingleByChannel(HitResult,Start,c,ECollisionChannel::ECC_Visibility);
	
	GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Start Line %s"),*Start.ToString()));
	GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Hit on loc: %s"),*HitResult.Location.ToString()));
	
	return HitBool;
}

