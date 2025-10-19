// Fill out your copyright notice in the Description page of Project Settings.


#include "System/PostApoAssetManager.h"

UPostApoAssetManager& UPostApoAssetManager::Get()
{
	UPostApoAssetManager* Singleton = Cast<UPostApoAssetManager>(GEngine->AssetManager);
	if (Singleton) {
		return *Singleton;
	}

	UE_LOG(LogTemp, Fatal, TEXT("Can't find UPostApoAssetManager"));

	return *NewObject<UPostApoAssetManager>();
}

void UPostApoAssetManager::Initialize()
{
	Get().LoadPreloadAssets();
}

void UPostApoAssetManager::LoadSyncByPath(const FSoftObjectPath& iAssetPath)
{
	if (iAssetPath.IsValid())
	{
		UObject* LoadedAsset = iAssetPath.ResolveObject();
		if (!LoadedAsset)
		{
			if (UAssetManager::IsInitialized())
			{
				LoadedAsset = UAssetManager::GetStreamableManager().LoadSynchronous(iAssetPath, false);
			}
			else
			{
				LoadedAsset = iAssetPath.TryLoad();
			}
		}

		if (LoadedAsset)
		{
			Get().AddLoadedAsset(iAssetPath.GetAssetFName(), LoadedAsset);
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *iAssetPath.ToString());
		}
	}
}

void UPostApoAssetManager::LoadSyncByName(const FName& iAssetName)
{
	UPostApoPrimaryAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(iAssetName);
	LoadSyncByPath(AssetPath);
}

void UPostApoAssetManager::LoadSyncByLabel(const FName& iLabel)
{
	if (!UAssetManager::IsInitialized())
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	UPostApoPrimaryAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	TArray<FSoftObjectPath> AssetPaths;

	const FPostApoAssetSet& AssetSet = AssetData->GetAssetSetByLabel(iLabel);
	for (const FPostApoAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		LoadSyncByPath(AssetPath);
		if (AssetPath.IsValid())
		{
			AssetPaths.Emplace(AssetPath);
		}
	}

	GetStreamableManager().RequestSyncLoad(AssetPaths);

	for (const FPostApoAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
		if (AssetPath.IsValid())
		{
			if (UObject* LoadedAsset = AssetPath.ResolveObject())
			{
				Get().AddLoadedAsset(AssetEntry.AssetName, LoadedAsset);
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Failed to load asset [%s]"), *AssetPath.ToString());
			}
		}
	}
}

void UPostApoAssetManager::LoadAsyncByPath(const FSoftObjectPath& iAssetPath, FAsyncLoadCompletedDelegate CompletedDelegate)
{
	if (!UAssetManager::IsInitialized())
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	if (iAssetPath.IsValid())
	{
		if (UObject* LoadedAsset = iAssetPath.ResolveObject())
		{
			Get().AddLoadedAsset(iAssetPath.GetAssetFName(), LoadedAsset);
		}
		else
		{
			TArray<FSoftObjectPath> AssetPaths;
			AssetPaths.Add(iAssetPath);

			TSharedPtr<FStreamableHandle> Handle = GetStreamableManager().RequestAsyncLoad(AssetPaths);

			Handle->BindCompleteDelegate(FStreamableDelegate::CreateLambda([AssetName = iAssetPath.GetAssetFName(), iAssetPath, CompleteDelegate = MoveTemp(CompletedDelegate)]()
				{
					UObject* LoadedAsset = iAssetPath.ResolveObject();
					Get().AddLoadedAsset(AssetName, LoadedAsset);
					if (CompleteDelegate.IsBound())
						CompleteDelegate.Execute(AssetName, LoadedAsset);
				}));
		}
	}
}

void UPostApoAssetManager::LoadAsyncByName(const FName& iAssetName, FAsyncLoadCompletedDelegate CompletedDelegate)
{
	if (!UAssetManager::IsInitialized())
	{
		UE_LOG(LogTemp, Error, TEXT("AssetManager must be initialized"));
		return;
	}

	UPostApoPrimaryAssetData* AssetData = Get().LoadedAssetData;
	check(AssetData);

	const FSoftObjectPath& AssetPath = AssetData->GetAssetPathByName(iAssetName);
	LoadAsyncByPath(AssetPath, CompletedDelegate);
}

void UPostApoAssetManager::ReleaseByPath(const FSoftObjectPath& iAssetPath)
{
	FName AssetName = iAssetPath.GetAssetFName();
	ReleaseByName(AssetName);
}

void UPostApoAssetManager::ReleaseByName(const FName& iAssetName)
{
	UPostApoAssetManager& AssetManager = Get();
	if (AssetManager.NameToLoadedAsset.Contains(iAssetName))
	{
		AssetManager.NameToLoadedAsset.Remove(iAssetName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't find loaded asset by asset name [%s]."), *iAssetName.ToString());
	}
}

void UPostApoAssetManager::ReleaseByLabel(const FName& iLabel)
{
	UPostApoAssetManager& AssetManager = Get();
	UPostApoPrimaryAssetData* LoadedAssetData = AssetManager.LoadedAssetData;
	const FPostApoAssetSet& AssetSet = LoadedAssetData->GetAssetSetByLabel(iLabel);

	for (const FPostApoAssetEntry& AssetEntry : AssetSet.AssetEntries)
	{
		const FName& AssetName = AssetEntry.AssetName;
		if (AssetManager.NameToLoadedAsset.Contains(AssetName))
		{
			AssetManager.NameToLoadedAsset.Remove(AssetName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find loaded asset by assetName [%s]."), *AssetName.ToString());
		}
	}
}

void UPostApoAssetManager::ReleaseAll()
{
	UPostApoAssetManager& AssetManager = Get();
	AssetManager.NameToLoadedAsset.Reset();
}

void UPostApoAssetManager::LoadPreloadAssets()
{
	if (LoadedAssetData) {
		return;
	}

	UPostApoPrimaryAssetData* AssetData = nullptr;
	FPrimaryAssetType PrimaryAssetType(UPostApoPrimaryAssetData::StaticClass()->GetFName());
	TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(PrimaryAssetType);
	if (Handle.IsValid())
	{
		Handle->WaitUntilComplete(0.f, false);
		AssetData = Cast<UPostApoPrimaryAssetData>(Handle->GetLoadedAsset());
	}

	if (AssetData)
	{
		LoadedAssetData = AssetData;
		LoadSyncByLabel("Preload");
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to load AssetData asset type [%s]."), *PrimaryAssetType.ToString());
	}
}

void UPostApoAssetManager::AddLoadedAsset(const FName& iAssetName, const UObject* iAsset)
{
	if (iAssetName.IsValid() && iAsset)
	{
		//FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);

		if (NameToLoadedAsset.Contains(iAssetName) == false)
		{
			NameToLoadedAsset.Add(iAssetName, iAsset);
		}
	}
}
