// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/Teleport/TeleportArrow.h"

// Sets default values for this component's properties
UTeleportArrow::UTeleportArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTeleportArrow::BeginPlay()
{
	Super::BeginPlay();
	CachedWorld = GetWorld();
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
	if (!PlayerToTele)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerToTele is null"));
		return;
	}
	
	if (!IsValidPos(TeleLoc))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot teleport: invalid position"));
		return; // Exit early
	}

	PlayerToTele->SetActorLocation(TeleLoc);
}

///
/// check for valid location
/// @param TeleLoc - Location for change a pos
/// @return true/false - true when Location is valid, otherwise false
bool UTeleportArrow::IsValidPos(const FVector& TeleLoc) const
{
	
	if (CachedWorld == nullptr)
		return false;
	
	const FVector Start = {TeleLoc.X + M_Offset,TeleLoc.Y + M_Offset,TeleLoc.Z + M_Offset};
	const FVector End = {TeleLoc.X, TeleLoc.Y, TeleLoc.Z - M_OffsetEnd};
	
	FHitResult HitResult;
	
	const auto HitBool = GWorld->LineTraceSingleByChannel(HitResult,Start,End,ECollisionChannel::ECC_Visibility);
	
	GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Start Line %s"),*Start.ToString()));
	GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Hit on loc: %s"),*HitResult.Location.ToString()));
	
	return HitBool;
}

