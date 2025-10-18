// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PostApoPrimaryAssetData.h"
#include "UObject/ObjectSaveContext.h"

void UPostApoPrimaryAssetData::PreSave(FObjectPreSaveContext ObjectSaveContext)
{
	Super::PreSave(ObjectSaveContext);

	AssetNameToPath.Empty();
	AssetLabelToSet.Empty();

	AssetGroupNameToSet.KeySort([](const FName& A, const FName& B) { return A.Compare(B) < 0 ; });

	for (const auto& it : AssetGroupNameToSet)
	{
		const FPostApoAssetSet& AssetSet = it.Value;
		for (FPostApoAssetEntry AssetEntry : AssetSet.AssetEntries)
		{
			FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
			const FString& AssetName = AssetPath.GetAssetName();

			if (AssetName.StartsWith(TEXT("BP_")) || AssetName.StartsWith(TEXT("B_")) ||
				AssetName.StartsWith(TEXT("GE_")) || AssetName.StartsWith(TEXT("GA_"))) 
			{
				FString AssetPathString = AssetPath.GetAssetPathString();
				AssetPathString.Append(TEXT("_C"));
				AssetPath = FSoftObjectPath(AssetPathString);
			}

			AssetNameToPath.Emplace(AssetEntry.AssetName, AssetEntry.AssetPath);

			for (const FName& Label : AssetEntry.AssetLabels)
			{
				AssetLabelToSet.FindOrAdd(Label).AssetEntries.Emplace(AssetEntry);
			}
		}
	}
}

FSoftObjectPath UPostApoPrimaryAssetData::GetAssetPathByName(const FName& iAssetName)
{
	FSoftObjectPath* AssetPath = AssetNameToPath.Find(iAssetName);
	ensureAlwaysMsgf(AssetPath, TEXT("Can't find AssetPath from AssetName [%s]"), *iAssetName.ToString());
	return *AssetPath;
}

const FPostApoAssetSet& UPostApoPrimaryAssetData::GetAssetSetByLabel(const FName& iLabel)
{
	const FPostApoAssetSet* AssetSet = AssetLabelToSet.Find(iLabel);
	ensureAlwaysMsgf(AssetSet, TEXT("Can't find AssetPath from Label [%s]"), *iLabel.ToString());
	return *AssetSet;
}
