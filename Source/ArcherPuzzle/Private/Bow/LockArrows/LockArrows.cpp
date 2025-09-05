// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/LockArrows/LockArrows.h"

// Sets default values
ALockArrows::ALockArrows()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALockArrows::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALockArrows::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

///
/// Check for the lock arrows 
/// @param Arrow get all arrows
/// @return true/false
bool ALockArrows::IsLockArrow(const TSubclassOf<AActor>& Arrow) const
{
	return ArrowsList.Contains(Arrow);
}
