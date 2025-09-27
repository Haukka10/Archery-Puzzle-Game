// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChange/LevelChangeTrigger.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelChangeTrigger::ALevelChangeTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelChangeTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelChangeTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelChangeTrigger::ChangeLevel() const
{
	if (LevelName.IsNone())
	{
		UE_LOG(LogTemp,Error,TEXT("Name of the level is None"));
		return;
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
