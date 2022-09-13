// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordObject.h"

// Discord Functions

void UDiscordObject::CreateDiscord()
{
	result = discord::Core::Create(1019125134340128849, DiscordCreateFlags_Default, &core);

	activity.SetApplicationId(1019125134340128849);
	activity.SetType(discord::ActivityType::Playing);
	activity.GetAssets().SetLargeImage("retro_presence");
	activity.GetAssets().SetLargeText("RETRO HORROR");
	//CallUpdateTimer();
}

void UDiscordObject::DestroyDiscord()
{
	core->ActivityManager().ClearActivity([](discord::Result result) {
		});
	core->~Core();
}

void UDiscordObject::UpdatePresence(FString newState, FString newDetails)
{
	activity.SetDetails(StringCast<ANSICHAR>(*newDetails).Get());
	activity.SetState(StringCast<ANSICHAR>(*newState).Get());
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
}

void UDiscordObject::SetStartTime(int newTime)
{
	discord::Timestamp dTime = (discord::Timestamp)newTime;
	activity.GetTimestamps().SetStart(dTime);
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
}

void UDiscordObject::RunCallback()
{
	core->RunCallbacks();
}

// Tick Functions

void UDiscordObject::Tick(float DeltaTime)
{
	if (!core) return;

	time += DeltaTime;
	if ((int)(time / unitTime) == 1)
	{
		time = 0;
		OnTimeUpdate.Broadcast();
		GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, "Discord Time Updated!");
	}

	RunCallback();
}

bool UDiscordObject::IsTickable() const
{
	return true;
}

bool UDiscordObject::IsTickableInEditor() const
{
	return false;
}

bool UDiscordObject::IsTickableWhenPaused() const
{
	return true;
}

TStatId UDiscordObject::GetStatId() const
{
	return TStatId();
}

UWorld* UDiscordObject::GetWorld() const
{
	return GetOuter()->GetWorld();
}