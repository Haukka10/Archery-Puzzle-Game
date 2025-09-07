// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialog/AudioSystem/AudioDialogSystem.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

// Sets default values
AAudioDialogSystem::AAudioDialogSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioDialogSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioDialogSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioDialogSystem::PlayAudio() const
{
	UGameplayStatics::PlaySound2D(GetWorld(),SoundClass,1,100,0);
}
