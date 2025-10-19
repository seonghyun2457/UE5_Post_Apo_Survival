// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PostApoPlayerController.h"

// InputMapping
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Data Asset
#include "System/PostApoAssetManager.h"
#include "Data/PostApoInputData.h"
#include "System/PostApoGamePlayTags.h"

// Math Library
#include "Kismet/KismetMathLibrary.h"

// PlayerCharacter
#include "PostApoPlayerCharacter.h"

#include "Engine/Engine.h"

APostApoPlayerController::APostApoPlayerController(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{

}

void APostApoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UPostApoInputData> InputData = UPostApoAssetManager::GetAssetByName<UPostApoInputData>("InputData");
	if (!InputData)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't retrieve UPostApoInputData instance"));
		return;
	}

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!SubSystem) {
		UE_LOG(LogTemp, Error, TEXT("Can't retrieve UEnhancedInputLocalPlayerSubsystem instance"));
		return;
	}
	SubSystem->AddMappingContext(InputData->InputMappingContext, 0);
}

void APostApoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UPostApoInputData> InputData = UPostApoAssetManager::GetAssetByName<UPostApoInputData>("InputData");
	if (!InputData)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't retrieve UPostApoInputData instance"));
		return;
	}

	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	const UInputAction* Action1 = InputData->FindInputActionByTag(PostApoGameplayTags::Input_Action_Move);
	EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::InputMove);

	const UInputAction* Action2 = InputData->FindInputActionByTag(PostApoGameplayTags::Input_Action_Turn);
	EnhancedInputComponent->BindAction(Action2, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);

	const UInputAction* Action3 = InputData->FindInputActionByTag(PostApoGameplayTags::Input_Action_Run);
	EnhancedInputComponent->BindAction(Action3, ETriggerEvent::Triggered, this, &ThisClass::InputRun);

	const UInputAction* Action4 = InputData->FindInputActionByTag(PostApoGameplayTags::Input_Action_Attack);
	EnhancedInputComponent->BindAction(Action4, ETriggerEvent::Triggered, this, &ThisClass::InputAttack);

	const UInputAction* Action5 = InputData->FindInputActionByTag(PostApoGameplayTags::Input_Action_Zoom);
	EnhancedInputComponent->BindAction(Action5, ETriggerEvent::Started, this, &ThisClass::InputZoom);

	const UInputAction* Action6 = InputData->FindInputActionByTag(PostApoGameplayTags::Input_Action_Jump);
	EnhancedInputComponent->BindAction(Action6, ETriggerEvent::Started, this, &ThisClass::InputJump);
}

void APostApoPlayerController::InputMove(const FInputActionValue& inputValue)
{
	FVector2D MovementVector = inputValue.Get<FVector2D>();

	if (MovementVector.X != 0.0) {
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.f, Rotator.Yaw, 0.f));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0.0) {
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0.f, Rotator.Yaw, 0.f));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void APostApoPlayerController::InputTurn(const FInputActionValue& inputvalue)
{
	FVector2D TurnVector = inputvalue.Get<FVector2D>();

	/*
	if (GEngine) {
		FString DebugMessage = FString::Printf(TEXT("Turn Vector: [%f, %f]"), TurnVector.X, TurnVector.Y);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);
	}
	*/

	if (TurnVector.X != 0.0) {
		AddYawInput(TurnVector.X);
	}

	if (TurnVector.Y != 0.0) {
		AddPitchInput(-TurnVector.Y);
	}
}

void APostApoPlayerController::InputRun(const FInputActionValue& inputvalue)
{
	if (GEngine) {
		FString DebugMessage = FString::Printf(TEXT("InputRun triggered"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);
	}
}

void APostApoPlayerController::InputAttack(const FInputActionValue& inputvalue)
{
	if (GEngine) {
		FString DebugMessage = FString::Printf(TEXT("InputAttack triggered."));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);
	}
}

void APostApoPlayerController::InputZoom(const FInputActionValue& inputvalue)
{
	if (GEngine) {
		FString DebugMessage = FString::Printf(TEXT("InputZoom triggered."));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);
	}
}

void APostApoPlayerController::InputJump(const FInputActionValue& inputvalue)
{
	if (GEngine) {
		FString DebugMessage = FString::Printf(TEXT("InputJump triggered."));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage);
	}

	TObjectPtr<APostApoPlayerCharacter> PlayerCharacter = Cast<APostApoPlayerCharacter>(GetPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController doesn't possess any pawn"));
		return;
	}

	PlayerCharacter->Jump();
}
