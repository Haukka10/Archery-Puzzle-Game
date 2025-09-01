// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Base/BowComponent.h"

// Sets default values for this component's properties
UBowComponent::UBowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

///
/// Check for shooting arrow and length of the list 
/// @return 
bool UBowComponent::CanShoot() const
{
	if (M_CurrentArrowShoot == nullptr)
		return false;
	if (M_ArrowActors.Num() == 0)
		return false;
	
	return true;
}

///
/// Check for the changing arrow 
/// @return true or false according to the checks
bool UBowComponent::CanChangeArrow()
{

	if (M_IndexOfArrow > M_ArrowActors.Num())
	{
		M_IndexOfArrow = 0;
		UE_LOG(LogTemp, Log, TEXT("Change to index: 0"));
	}
	
	auto in = M_ArrowActors[M_IndexOfArrow];
	if (in == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ArrowActor does not exist"));
		return false;
	}
	
	return true;
}

///
/// fuc for Change arrow
/// @param index index of the arrow 
void UBowComponent::ChangeArrow(int index)
{
	M_IndexOfArrow = index;
	if (!CanChangeArrow())
	{
		UE_LOG(LogTemp, Error, TEXT("Change failed"));
		return;
	}
	M_CurrentArrowShoot = M_ArrowActors[M_IndexOfArrow];
}
// Make a Timer Handle
FTimerHandle MyTimerHandle;
bool UBowComponent::IsTimerStart() const
{
	M_IsCanShoot = false;
	auto Time = ArrowCooldown.Find(M_CurrentArrowShoot);
	
	if (Time == nullptr)
		return false;
	
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UBowComponent::IsTimerDone, *Time, false);
	return true;
}

void UBowComponent::IsTimerDone() const
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	M_IsCanShoot = true;
}
///
///	Fuc for shooting the arrows and spawn actor for the arrows
///
void UBowComponent::ShootArrow() const
{
	if (!M_IsCanShoot)
		return;
	
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
	IsTimerStart();
}

// Called when the game starts
void UBowComponent::BeginPlay()
{
	Super::BeginPlay();
	// Check for length of ArrowCooldown map to not break the game
	if (ArrowCooldown.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ArrowCooldown map is empty"));
		return;
	}
	// add all arrows to list
	for (auto const& [v,k] : ArrowCooldown)
	{
		M_ArrowActors.Add(v);
	}
	//Set default arrow (first item form the list of arrows) 
	M_CurrentArrowShoot = M_ArrowActors[0];
}

// Called every frame
void UBowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

