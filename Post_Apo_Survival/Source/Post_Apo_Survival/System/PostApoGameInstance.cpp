// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PostApoGameInstance.h"
#include "PostApoAssetManager.h"

UPostApoGameInstance::UPostApoGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UPostApoGameInstance::Init()
{
	Super::Init();
	UPostApoAssetManager::Initialize();
}

void UPostApoGameInstance::Shutdown()
{
	Super::Shutdown();
}
