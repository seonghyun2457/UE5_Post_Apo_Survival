// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PostApoInputData.h"

const UInputAction* UPostApoInputData::FindInputActionByTag(const FGameplayTag& iInputTag) const
{
	for (const FPostApoInputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == iInputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find input action for inputTag [%s]"), *iInputTag.ToString());
	return nullptr;
}
