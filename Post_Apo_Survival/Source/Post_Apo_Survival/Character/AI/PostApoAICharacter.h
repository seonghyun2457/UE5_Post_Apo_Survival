// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PostApoCharacter.h"
#include "PostApoAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API APostApoAICharacter : public APostApoCharacter
{
	GENERATED_BODY()

public:
	APostApoAICharacter(const FObjectInitializer& objectInitializer);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
