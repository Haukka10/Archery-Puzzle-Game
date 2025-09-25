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
	if (M_ArrowActors.Num() == 0)
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
		UE_LOG(LogTemp, Log, TEXT("Change to index: 0"));
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
	const TSubclassOf<AActor> CurrentArrowShootBuffer  = M_ArrowActors[Index];
	if (!LockArrows->IsLockArrow(CurrentArrowShootBuffer))
	{
		M_IndexOfArrow = Index;
		if (!CanChangeArrow(CurrentArrowShootBuffer))
		{
			UE_LOG(LogTemp, Error, TEXT("Change failed"));
			return;
		}
		M_CurrentArrowShoot = CurrentArrowShootBuffer;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Arrow Lock"));
	}
}
// Make a Timer Handle
FTimerHandle MyTimerHandle;
void UBowComponent::IsTimerStart() const
{
	M_IsCanShoot = false;
	auto Time = ArrowCooldown.Find(M_CurrentArrowShoot);
	
	if (Time == nullptr)
		return;
	
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UBowComponent::IsTimerDone, *Time, false);
}

void UBowComponent::IsTimerDone() const
{
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	M_IsCanShoot = true;
}
///
///	Fun for shooting the arrows and spawn actor for the arrows
///
void UBowComponent::ShootArrow() const
{
	
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
	
	if (SoundClass != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(),SoundClass,1,100,0);
	}
	
	IsTimerStart();
}

// Called when the game starts
void UBowComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// add all arrows to list
	for (auto const& [v,k] : ArrowCooldown)
	{
		M_ArrowActors.Add(v);
	}
	
	// Check for length of ArrowCooldown map to not break the game
	if (ArrowCooldown.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ArrowCooldown map is empty"));
		return;
	}
	//Set default arrow (first item form the list of arrows) 
	M_CurrentArrowShoot = M_ArrowActors[0];
}

// Called every frame
void UBowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

