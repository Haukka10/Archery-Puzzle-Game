// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Base/BowComponent.h"

#include "Bow/Arrow/Bridge/BridgeArrow.h"

// Sets default values for this component's properties
UBowComponent::UBowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UBowComponent::CanShoot() const
{
	if (M_CurrentArrowShoot == nullptr)
		return false;
	if (ArrowActors.Num() == 0)
		return false;
	
	return true;
}

bool UBowComponent::CanChangeArrow()
{

	if (M_IndexOfArrow > ArrowActors.Num())
	{
		M_IndexOfArrow = 0;
		UE_LOG(LogTemp, Log, TEXT("Change to index: 0"));
	}
	
	auto in = ArrowActors[M_IndexOfArrow];
	if (in == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ArrowActor does not exist"));
		return false;
	}
	
	return true;
}

void UBowComponent::ChangeArrow(int index)
{
	M_IndexOfArrow = index;
	if (!CanChangeArrow())
	{
		UE_LOG(LogTemp, Error, TEXT("Change failed"));
		return;
	}
	M_CurrentArrowShoot = ArrowActors[M_IndexOfArrow];
}

// Called when the game starts
void UBowComponent::BeginPlay()
{
	Super::BeginPlay();
	if (ArrowActors.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ArrowActor does not exist"));
		return;
	}
	
	M_CurrentArrowShoot = ArrowActors[0];
}

void UBowComponent::ShootArrow() const
{
	const bool CheckIsSuccessful = CanShoot();
	if (!CheckIsSuccessful)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't Shoot a bow :("));
		return;
	}
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;
	
	FActorSpawnParameters SpawnParams;
	World->SpawnActor<AActor>(M_CurrentArrowShoot,ArrowSpawnTrans, SpawnParams);
}


// Called every frame
void UBowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

