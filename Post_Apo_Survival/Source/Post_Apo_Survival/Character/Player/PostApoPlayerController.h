// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PostApoPlayerController.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UInputAction;

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API APostApoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APostApoPlayerController(const FObjectInitializer& objectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void InputMove(const FInputActionValue& inputValue);
	void InputTurn(const FInputActionValue& inputvalue);
	void InputRun(const FInputActionValue& inputvalue);
	void InputAttack(const FInputActionValue& inputvalue);
	void InputZoom(const FInputActionValue& inputvalue);
	void InputJump(const FInputActionValue& inputvalue);

protected:

};
