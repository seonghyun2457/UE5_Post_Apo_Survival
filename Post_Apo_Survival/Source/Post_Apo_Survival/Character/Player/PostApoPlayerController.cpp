// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PostApoPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Engine/Engine.h"

APostApoPlayerController::APostApoPlayerController(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{

}

void APostApoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputSystem) {
		if (InputMappingContext) {
			InputSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APostApoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::InputTurn);
	}
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
		AddPitchInput(TurnVector.Y);
	}
}
