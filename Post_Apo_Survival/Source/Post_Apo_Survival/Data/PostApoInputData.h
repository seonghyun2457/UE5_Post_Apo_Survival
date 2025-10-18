// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PostApoInputData.generated.h"


class UInputAction;
class UInputMappingContext;

USTRUCT()
struct  FPostApoInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
};

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API UPostApoInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindInputActionByTag(const FGameplayTag& iInputTag) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TArray<FPostApoInputAction> InputActions;
};
