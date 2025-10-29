// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Bow/Arrow/Explosion/ExplosionArrow.h"

#include "ArcherPuzzleCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UExplosionArrow::UExplosionArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExplosionArrow::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExplosionArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
///
/// Make a sphere for the explosion 
///
void UExplosionArrow::CheckSphere() const
{
	//Setup things
	const UWorld* World = GetWorld();
	const AActor* Owner = GetOwner();
	const FVector Start = Owner->GetActorLocation();
	const FVector End = Owner->GetActorLocation();
	//Add actors to ingore
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(GetOwner());
	
	TArray<FHitResult> HitResults;
	if (World == nullptr)
		return;
	
	//Spawn a sphere trace for checks
	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(World,Start,End,Radius,UEngineTypes::ConvertToTraceType(ECC_Camera),false
		,ActorToIgnore,EDrawDebugTrace::ForDuration,HitResults,true);

	if (bHit)
	{
		for (const FHitResult& HitRes : HitResults)
		{
			FVector CenterVector = Owner->GetActorLocation();
			if (const auto c = Cast<AArcherPuzzleCharacter>(HitRes.GetActor()))
			{
				//check for a velocity is less them max velocity
				if (c->GetVelocity().Z <= M_MaxVelocity)
				{
					const float MinStrengthOfImpulse = StrengthOfImpulse - 10;
					float StrengthOfImpulsePlayer = FMath::Clamp(MinStrengthOfImpulse,0,StrengthOfImpulse);
					
					if (StrengthOfImpulse > 0)
						StrengthOfImpulsePlayer -= FVector::Dist(CenterVector,HitRes.ImpactPoint) * Multiplayer;
					
					c->LaunchCharacter({0,0,StrengthOfImpulsePlayer},false,false);
				}
			}
			//Get a PrimitiveComponent for non-character
			UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(HitRes.GetActor()->GetRootComponent());
			AddImpulse(CenterVector,PrimComp);
		}
	}
}

/// Add Radial impulse to obj with physics
/// @param Center - Center of the vector
/// @param UPrimitive - PrimitiveComponent form actor
void UExplosionArrow::AddImpulse(const FVector& Center, UPrimitiveComponent* UPrimitive) const
{
	//Check for sim physics
	if (UPrimitive && UPrimitive->IsSimulatingPhysics())
	{
		UPrimitive->AddRadialImpulse(Center,Radius,StrengthOfImpulse,ERadialImpulseFalloff::RIF_Linear,true);
	}
}