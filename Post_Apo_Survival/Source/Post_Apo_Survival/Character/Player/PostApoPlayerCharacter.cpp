// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PostApoPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APostApoPlayerCharacter::APostApoPlayerCharacter(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	// Set Skeletal Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
	if (!SkeletalMeshFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to find skeletal mesh for player character."))
	}

	GetMesh()->SetSkeletalMesh(SkeletalMeshFinder.Object);

	// Set SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 700.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	// Use PawnControlRoation
	SpringArm->bUsePawnControlRotation = true;

	// Set Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Set Controller Rotations
	bUseControllerRotationYaw = true;
	//bUseControllerRotationPitch = true;
}
