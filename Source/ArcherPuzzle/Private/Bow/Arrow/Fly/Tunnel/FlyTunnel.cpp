// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow/Arrow/Fly/Tunnel/FlyTunnel.h"

#include "ArcherPuzzleCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFlyTunnel::AFlyTunnel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlyTunnel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every framea
void AFlyTunnel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlyTunnel::FlyTunnelStartEffect(AActor* Actor)
{
	const auto Character = Cast<AArcherPuzzleCharacter>(Actor);
	if (Character != nullptr)
	{
		Character->GetCharacterMovement()->GravityScale = 0.01;
		Character->LaunchCharacter(FVector(0,0,150),false,false);
		//TODO: Add UI to show movement lock.
		Character->bMovementLock = true;
		return;
	}
	const auto Arrow = Actor->FindComponentByClass<UProjectileMovementComponent>();
	if (Arrow != nullptr)
	{
		//Arrow->ProjectileGravityScale = 0.001;
		M_OldVelocity = Arrow->MaxSpeed;
		Arrow->MaxSpeed += BoostObj;
		
		//Boost velocity in the current direction
		const FVector Direction = Arrow->Velocity.GetSafeNormal();
		const FVector BoostedVelocity = Arrow->Velocity + Direction * BoostObj;
		Arrow->Velocity = BoostedVelocity;
		
		Arrow->UpdateComponentVelocity();
		return;
	}
	const auto Psy = Cast<UPrimitiveComponent>(Actor);
	if (Psy != nullptr)
	{
		Psy->SetEnableGravity(false);
	}
	
}

void AFlyTunnel::FlyTunnelEndEffect(AActor* Actor)
{
	const auto Character = Cast<AArcherPuzzleCharacter>(Actor);
	if (Character != nullptr)
	{
		Character->GetCharacterMovement()->GravityScale = 0.95;
		Character->bMovementLock = false;
		return;
	}
	const auto Psy = Cast<UPrimitiveComponent>(Actor);
	if (Psy != nullptr)
	{
		Psy->SetEnableGravity(true);
	}
}
