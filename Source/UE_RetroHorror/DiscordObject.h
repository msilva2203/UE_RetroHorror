// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "discord-files/discord.h"
#include "DiscordObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);

UCLASS(BlueprintType, Blueprintable)
class UE_RETROHORROR_API UDiscordObject : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Discord")
		void CreateDiscord();

		UFUNCTION(BlueprintCallable, Category = "Discord")
		void DestroyDiscord();

		UFUNCTION(BlueprintCallable, Category = "Discord")
		void UpdatePresence(FString newState, FString newDetails);

		UFUNCTION(BlueprintCallable, Category = "Discord")
		void SetStartTime(int time);

		UFUNCTION(Category = "Discord")
		void RunCallback();

		UPROPERTY(BlueprintAssignable, Category = "Discord")
		FTestDelegate OnTimeUpdate;

public:
	discord::Core* core{};
	discord::Activity activity{};
	discord::Result result;

	float time = 0;
	float unitTime = 60.0f;

	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

	UWorld* GetWorld() const override;
};
