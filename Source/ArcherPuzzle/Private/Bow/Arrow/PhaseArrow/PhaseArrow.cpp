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

/// Get all material and a mesh's form the actor
/// @param Actor - Get actor to get all mesh's 
void UPhaseArrow::GetWallActor(AActor* Actor)
{
	// Set a wall 
	M_WallActor = Actor;
	//Get all UStaticMeshComponent for the actor
	TArray<UStaticMeshComponent*> Comps;
	Actor->GetComponents<UStaticMeshComponent>(Comps);
	
	if (Comps.Num() == 0)
		return;
	
	//Get first components
	const UStaticMeshComponent* FoundComp = Comps[0];
	//Get Material form components
	if (UMaterialInterface* Mat = FoundComp->GetMaterial(0))
	{
		// Get wall material
		M_PreWallMaterial = Mat;
	}
	//Get a Primitive Component
	M_PrimComp = Actor->GetComponentByClass<UPrimitiveComponent>();
	//Check for the null ptr
	if (M_PrimComp)
		M_WallCollision = M_PrimComp->GetCollisionEnabled();
	
	ChangeProperty();
}
///
/// Reset all mesh - set old material and collision
///
void UPhaseArrow::ResetWall() const
{
	//Get a UStaticMeshComponent form a wall actor
	const auto StaticMeshComponent = M_WallActor->GetComponentByClass<UStaticMeshComponent>();
	//Set an old material
	StaticMeshComponent->SetMaterial(0,M_PreWallMaterial);
	//Set an old Wall collision
	M_PrimComp->SetCollisionEnabled(M_WallCollision);
}
///
/// Change a prop for wall (has collision or not)
///
void UPhaseArrow::ChangeProperty() const
{
	//Set new material
	const auto Mat = M_WallActor->GetComponentByClass<UStaticMeshComponent>();
	
	if (WallMaterial == nullptr)
		return;
	
	Mat->SetMaterial(0 ,WallMaterial);
	
	//Set new Collision to NoCollision 
	M_PrimComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
