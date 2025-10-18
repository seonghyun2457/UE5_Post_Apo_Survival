// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PostApoPrimaryAssetData.generated.h"

USTRUCT()
struct FPostApoAssetEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName AssetName;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> AssetLabels;
};

USTRUCT()
struct FPostApoAssetSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FPostApoAssetEntry> AssetEntries;
};

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API UPostApoPrimaryAssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

public:
	FSoftObjectPath GetAssetPathByName(const FName& iAssetName);
	const FPostApoAssetSet& GetAssetSetByLabel(const FName& iLabel);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FPostApoAssetSet> AssetGroupNameToSet;

	UPROPERTY()
	TMap<FName, FSoftObjectPath> AssetNameToPath;

	UPROPERTY()
	TMap<FName, FPostApoAssetSet> AssetLabelToSet;
};
