// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PostApoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API UPostApoGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UPostApoGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
	virtual void Shutdown() override;
};
