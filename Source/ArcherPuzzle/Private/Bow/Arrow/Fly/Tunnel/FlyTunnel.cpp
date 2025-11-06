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
		FlyTunnelEffectCharacter(Character);
		return;
	}
	const auto Arrow = Actor->FindComponentByClass<UProjectileMovementComponent>();
	if (Arrow != nullptr)
	{
		FlyTunnelEffectProjectile(Arrow);
		return;
	}
	
	const auto Psy = Cast<UPrimitiveComponent>(Actor);
	
	if (Psy == nullptr)
		return;
	
	Psy->SetEnableGravity(false);
	
}

void AFlyTunnel::FlyTunnelEndEffect(AActor* Actor)
{
	const auto Character = Cast<AArcherPuzzleCharacter>(Actor);
	if (Character != nullptr)
	{
		Character->GetCharacterMovement()->GravityScale = 0.95;
		return;
	}
	const auto Psy = Cast<UPrimitiveComponent>(Actor);
	if (Psy != nullptr)
	{
		Psy->SetEnableGravity(true);
	}
}

void AFlyTunnel::FlyTunnelEffectCharacter(AArcherPuzzleCharacter* Character) const
{
	Character->GetCharacterMovement()->GravityScale = 0;
	Character->LaunchCharacter(LaunchVelocity,false,false);
}

void AFlyTunnel::FlyTunnelEffectProjectile(UProjectileMovementComponent* Projectile)
{
	M_OldVelocity = Projectile->MaxSpeed;
	Projectile->MaxSpeed += BoostObj;
	
	const FVector ProjectileVelocity = Projectile->Velocity;
	
	//Boost velocity in the current direction
	const FVector Direction = ProjectileVelocity.GetSafeNormal();
	Projectile->Velocity = ProjectileVelocity + Direction * BoostObj;
		
	Projectile->UpdateComponentVelocity();
}
