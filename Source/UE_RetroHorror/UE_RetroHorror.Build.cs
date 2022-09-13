// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UE_RetroHorror : ModuleRules
{
	public UE_RetroHorror(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.Add("C:\\dev\\Game Projects\\Retro Horror Game\\UE_RetroHorror\\Source\\UE_RetroHorror\\discord-files\\");

		PublicAdditionalLibraries.Add("C:\\dev\\Game Projects\\Retro Horror Game\\UE_RetroHorror\\Binaries\\Win64\\discord_game_sdk.dll.lib");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
