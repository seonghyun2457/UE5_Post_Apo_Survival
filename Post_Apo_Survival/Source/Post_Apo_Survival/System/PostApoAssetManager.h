// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Data/PostApoPrimaryAssetData.h"
#include "PostApoAssetManager.generated.h"

class UPostApoPrimaryAssetData;

DECLARE_DELEGATE_TwoParams(FAsyncLoadCompletedDelegate, const FName&/*AssetName or Label*/, UObject*/*LoadedAsset*/);

/**
 * 
 */
UCLASS()
class POST_APO_SURVIVAL_API UPostApoAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UPostApoAssetManager() = default;

	static UPostApoAssetManager& Get();

public:
	static void Initialize();

	template<typename AssetType>
	static AssetType* GetAssetByName(const FName& iAssetName);

	static void LoadSyncByPath(const FSoftObjectPath& iAssetPath);
	static void LoadSyncByName(const FName& iAssetName);
	static void LoadSyncByLabel(const FName& iLabel);

	static void LoadAsyncByPath(const FSoftObjectPath& iAssetPath, FAsyncLoadCompletedDelegate CompletedDelegate = FAsyncLoadCompletedDelegate());
	static void LoadAsyncByName(const FName& iAssetName, FAsyncLoadCompletedDelegate CompletedDelegate = FAsyncLoadCompletedDelegate());

	static void ReleaseByPath(const FSoftObjectPath& iAssetPath);
	static void ReleaseByName(const FName& iAssetName);
	static void ReleaseByLabel(const FName& iLabel);
	static void ReleaseAll();

private:
	void LoadPreloadAssets();
	void AddLoadedAsset(const FName& iAssetName, const UObject* iAsset);

private:
	UPROPERTY()
	TObjectPtr<UPostApoPrimaryAssetData> LoadedAssetData;

	UPROPERTY()
	TMap<FName, TObjectPtr<const UObject>> NameToLoadedAsset;
};

template<typename AssetType>
AssetType* UPostApoAssetManager::GetAssetByName(const FName& iAssetName)
{
	TObjectPtr<UPostApoPrimaryAssetData> AssetData = Get().LoadedAssetData;
	check(AssetData);

	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(iAssetName);
	if (AssetPath.IsValid())
	{
		LoadedAsset = Cast<AssetType>(AssetPath.ResolveObject());
		if (!LoadedAsset)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted sync loading because hadn't loaded yet [%s]."), *AssetPath.ToString());
			LoadedAsset = Cast<AssetType>(AssetPath.TryLoad());
		}
	}

	return LoadedAsset;
}