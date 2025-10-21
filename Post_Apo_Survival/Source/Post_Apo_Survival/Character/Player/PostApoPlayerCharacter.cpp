// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PostApoPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APostApoPlayerCharacter::APostApoPlayerCharacter(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	// Set Skeletal Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Megan/Meshes/Megan.Megan'"));
	if (!SkeletalMeshFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to find skeletal mesh for player character."))
	}

	GetMesh()->SetSkeletalMesh(SkeletalMeshFinder.Object);

	// Set SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 250.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	// Use PawnControlRoation
	SpringArm->bUsePawnControlRotation = true;

	// Set Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Set Orient Rotation To Movement to true
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	if (!CharacterMovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Player character doesn't have character component."));
		return;
	}

	CharacterMovementComponent->bOrientRotationToMovement = true;

	// Set Controller Rotations
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Set Walk/Run Speed
	RunSpeed = 600.f;
	WalkSpeed = 300.f;
	CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
}

void APostApoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APostApoPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const float APostApoPlayerCharacter::GetRunSpeed() const
{
	return RunSpeed;
}

const float APostApoPlayerCharacter::GetWalkSpeed() const
{
	return WalkSpeed;
}
