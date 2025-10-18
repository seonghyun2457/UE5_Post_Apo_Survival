// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PostApoGameMode.h"
#include "UObject/ConstructorHelpers.h"

APostApoGameMode::APostApoGameMode(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	// Set Default Pawn Class
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (!PlayerPawnClassFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to find player pawn class."))
		return;
	}

	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Set Player Controller Class
	ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_PlayerController.BP_PlayerController_C'"));
	if (!PlayerControllerClassFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to find player controller class."))
		return;
	}
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}

void APostApoGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}
