// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PostApoCharacter.h"
#include "PostApoPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API APostApoPlayerCharacter : public APostApoCharacter
{
	GENERATED_BODY()
public:
	APostApoPlayerCharacter(const FObjectInitializer& objectInitializer);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;
};
