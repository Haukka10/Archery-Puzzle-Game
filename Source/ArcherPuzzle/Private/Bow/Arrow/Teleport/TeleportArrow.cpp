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
	//Check fot valid pos to teleport
	if (!IsValidPos(TeleLoc))
		GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Not Teleporting (not valid pos)")));

	// Teleport to new pos
	PlayerToTele->SetActorLocation(TeleLoc);
}

///
/// check for valid location
/// @param TeleLoc - Location for change a pos
/// @return true/false - true when Location is valid, otherwise false
bool UTeleportArrow::IsValidPos(const FVector& TeleLoc) const
{
	const auto GWorld = GetWorld();
	if (GWorld == nullptr)
		return false;
	
	FHitResult HitResult;
	
	const FVector Start = {TeleLoc.X + M_Offset,TeleLoc.Y + M_Offset,TeleLoc.Z + M_Offset};
	const FVector End = {TeleLoc.X, TeleLoc.Y, TeleLoc.Z - M_OffsetEnd};
	
	const auto HitBool = GWorld->LineTraceSingleByChannel(HitResult,Start,End,ECollisionChannel::ECC_Visibility);
	
	GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Start Line %s"),*Start.ToString()));
	GEngine->AddOnScreenDebugMessage(-1,2.F,FColor::Cyan,FString::Printf(TEXT("Hit on loc: %s"),*HitResult.Location.ToString()));
	
	return HitBool;
}

