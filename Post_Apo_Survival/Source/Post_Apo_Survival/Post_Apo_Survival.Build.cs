// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Post_Apo_Survival : ModuleRules
{
	public Post_Apo_Survival(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Post_Apo_Survival",
			"Post_Apo_Survival/Variant_Horror",
			"Post_Apo_Survival/Variant_Horror/UI",
			"Post_Apo_Survival/Variant_Shooter",
			"Post_Apo_Survival/Variant_Shooter/AI",
			"Post_Apo_Survival/Variant_Shooter/UI",
			"Post_Apo_Survival/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
