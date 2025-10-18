// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PostApoCharacter.h"

// Sets default values
APostApoCharacter::APostApoCharacter(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void APostApoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APostApoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APostApoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

