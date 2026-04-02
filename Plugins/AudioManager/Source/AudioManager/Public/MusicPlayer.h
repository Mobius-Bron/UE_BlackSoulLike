// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AUDIOMANAGER_API UMusicPlayer : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "Sound Manager")
    void PlayBGM(USoundBase* Sound, bool bWithFade = true);

    UFUNCTION(BlueprintCallable, Category = "Sound Manager")
    void StopBGM(bool bWithFade = true);

    UFUNCTION(BlueprintCallable, Category = "Sound Manager")
    void PauseBGM();

    UFUNCTION(BlueprintCallable, Category = "Sound Manager")
    void ResumeBGM();

    UFUNCTION(BlueprintCallable, Category = "Sound Manager")
    bool IsBGMPlaying() const;

    UFUNCTION(BlueprintCallable, Category = "Sound Manager")
    USoundBase* GetCurrentBGM() const;

private:
    UPROPERTY()
    TObjectPtr<UAudioComponent> AudioComponent;

    UPROPERTY()
    TObjectPtr<USoundBase> PendingSound;

    UPROPERTY()
    FTimerHandle FadeOutTimerHandle;

    float FadeInTime = 2.0f;
    float FadeOutTime = 2.0f;

    float CurrVolume = 1.0f;

    bool bIsFadingOut = false;

    UAudioComponent* CreateAudioComponent();
    void Cleanup();

    // 淡出完成的回调函数
    void OnFadeOutComplete();

    // 实际播放音乐的函数
    void PlayPendingSound();
};
