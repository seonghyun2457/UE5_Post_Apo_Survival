// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PostApoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API APostApoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APostApoGameMode(const FObjectInitializer& objectInitializer);

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
