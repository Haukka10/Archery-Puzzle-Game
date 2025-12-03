// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Base/BowComponent.h"

#include "Bow/LockArrows/LockArrows.h"
#include "Kismet/GameplayStatics.h"

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
/// @return True or false if player can shoot the arrow
bool UBowComponent::CanShoot() const
{
	if (M_CurrentArrowShoot == nullptr)
		return false;
	if (M_ArrowActors.IsEmpty())
		return false;
	
	return true;
}

///
/// Check for the changing arrow 
/// @return true or false according to the checks
bool UBowComponent::CanChangeArrow(const TSubclassOf<AActor>& SelArrow)
{

	if (M_IndexOfArrow > M_ArrowActors.Num())
	{
		M_IndexOfArrow = 0;
		UE_LOG(LogTemp, Log, TEXT("Change index to 0"));
	}
	
	if (SelArrow == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ArrowActor does not exist"));
		return false;
	}
	
	return true;
}

///
/// fuc for Change arrow
/// @param Index index of the arrow 
void UBowComponent::ChangeArrow(const int Index)
{
	const TSubclassOf<AActor>& CurrentArrowShootBuffer = M_ArrowActors[Index];

	//Check for lock arrow
	if (LockArrows->IsLockArrow(CurrentArrowShootBuffer))
	{
		UE_LOG(LogTemp, Log, TEXT("Arrow Lock"));
		return;
	}
	
	if (CanChangeArrow(CurrentArrowShootBuffer))
	{
		M_IndexOfArrow = Index;
		M_CurrentArrowShoot = CurrentArrowShootBuffer;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Change failed"));
	}
}
// Make a Timer Handle
FTimerHandle TimerHandle;
///
/// Set a timer time to cooldown arrow shoot
///
void UBowComponent::IsTimerStart() const
{
	M_IsCanShoot = false;
	const auto CooldownTime = ArrowCooldown.Find(M_CurrentArrowShoot);
	
	if (CooldownTime == nullptr)
		return;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBowComponent::IsTimerDone, *CooldownTime, false);
}
///
/// Setting an M_IsCanShoot to true and clear timer
///
void UBowComponent::IsTimerDone() const
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	M_IsCanShoot = true;
}
///
///	Fun for shooting the arrows and spawn actor for the arrows
///
void UBowComponent::ShootArrow() const
{
	//Check for sound class is not a nullptr
	if (SoundClass == nullptr)
		return;
	//Check for if player can shoot
	if (!M_IsCanShoot)
		return;
	
	if (!CanShoot())
	{
		UE_LOG(LogTemp,Error,TEXT("Can't Shoot a bow :("));
		return;
	}
	
	UWorld* World = GetWorld();
	
	if (World == nullptr)
		return;

	const FActorSpawnParameters SpawnParams;
	World->SpawnActor<AActor>(M_CurrentArrowShoot,ArrowSpawnTrans, SpawnParams);
	// Check for a sound class is not a nullptr, if not setting a volume, pitch and start time 
	UGameplayStatics::PlaySound2D(GetWorld(),SoundClass,1,100,0);
	
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

