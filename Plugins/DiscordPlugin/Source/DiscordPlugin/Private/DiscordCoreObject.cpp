// Fill out your copyright notice in the Description page of Project Settings.

#include "DiscordCoreObject.h"

// Discord Functions

void UDiscordCoreObject::CreateDiscord(FDiscordSettings settings)
{
	uint64 appID = FCString::Strtoui64(*(settings.ApplicationID), NULL, 10);
	char* largeImageKey = TCHAR_TO_ANSI(*(settings.LargeImageKey));
	char* largeText = TCHAR_TO_ANSI(*(settings.LargeText));
	char* smallImageKey = TCHAR_TO_ANSI(*(settings.SmallImageKey));
	char* smallText = TCHAR_TO_ANSI(*(settings.SmallText));

	result = discord::Core::Create(appID, DiscordCreateFlags_Default, &core);

	activity.SetApplicationId(appID);
	activity.SetType(discord::ActivityType::Playing);
	activity.GetAssets().SetLargeImage(largeImageKey);
	activity.GetAssets().SetLargeText(largeText);
	activity.GetAssets().SetSmallImage(smallImageKey);
	activity.GetAssets().SetSmallText(smallText);
}

void UDiscordCoreObject::DestroyDiscord()
{
	core->ActivityManager().ClearActivity([](discord::Result result) {
		});
	core->~Core();
}

void UDiscordCoreObject::UpdatePresence(FString newState, FString newDetails)
{
	char* state = TCHAR_TO_ANSI(*newState);
	char* details = TCHAR_TO_ANSI(*newDetails);
	activity.SetDetails(details);
	activity.SetState(state);
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
}

void UDiscordCoreObject::SetStartTime(int newTime)
{
	discord::Timestamp dTime = (discord::Timestamp)newTime;
	activity.GetTimestamps().SetStart(dTime);
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
}

void UDiscordCoreObject::RunCallback()
{
	core->RunCallbacks();
}

// Tick Functions

void UDiscordCoreObject::Tick(float DeltaTime)
{
	if (!core) return;

	time += DeltaTime;
	if ((int)(time / unitTime) == 1)
	{
		time = 0;
		OnTimeUpdate.Broadcast();
	}

	RunCallback();
}

bool UDiscordCoreObject::IsTickable() const
{
	return true;
}

bool UDiscordCoreObject::IsTickableInEditor() const
{
	return false;
}

bool UDiscordCoreObject::IsTickableWhenPaused() const
{
	return true;
}

TStatId UDiscordCoreObject::GetStatId() const
{
	return TStatId();
}

UWorld* UDiscordCoreObject::GetWorld() const
{
	return GetOuter()->GetWorld();
}