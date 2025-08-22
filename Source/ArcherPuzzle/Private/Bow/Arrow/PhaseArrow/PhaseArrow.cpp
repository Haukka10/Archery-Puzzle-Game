// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/PhaseArrow/PhaseArrow.h"

// Sets default values for this component's properties
UPhaseArrow::UPhaseArrow()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPhaseArrow::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhaseArrow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPhaseArrow::AddWall(AActor* Actor)
{
	M_WallActor = Actor;
	
	TArray<UStaticMeshComponent*> Comps;
	Actor->GetComponents<UStaticMeshComponent>(Comps);
	if (Comps.Num() > 0)
	{
		const UStaticMeshComponent* FoundComp = Comps[0];
		UMaterialInterface* Mat = FoundComp->GetMaterial(0);
		if (Mat)
		{
			M_PreWallMaterial = Mat;
		}
	}

	PrimComp = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (PrimComp)
	{
		M_WallCollision = PrimComp->GetCollisionEnabled();
	}
	ChangeProperty();
}

void UPhaseArrow::ResetWall()
{
	auto c= M_WallActor->GetComponentByClass<UStaticMeshComponent>();
	c->SetMaterial(0,M_PreWallMaterial);
	PrimComp->SetCollisionEnabled(M_WallCollision);
}

void UPhaseArrow::ChangeProperty() const
{
	//Set new material
	const auto Mat = M_WallActor->GetComponentByClass<UStaticMeshComponent>();
	Mat->SetMaterial(0 ,WallMaterial);
	
	//Set new Collision to NoCollision 
	PrimComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
