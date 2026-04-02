// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicPlayer.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"

void UMusicPlayer::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    AudioComponent = CreateAudioComponent();
}

void UMusicPlayer::Deinitialize()
{
    Cleanup();
    Super::Deinitialize();
}

void UMusicPlayer::PlayBGM(USoundBase* Sound, bool bWithFade)
{
    if (!Sound)
    {
        return;
    }

    // 确保音频组件存在
    if (!AudioComponent)
    {
        AudioComponent = CreateAudioComponent();
        if (!AudioComponent) return;
    }

    if (AudioComponent->Sound == Sound && AudioComponent->IsPlaying())
    {
        return;
    }

    PendingSound = Sound;

    if (AudioComponent->IsPlaying())
    {
        if (bWithFade)
        {
            bIsFadingOut = true;
            AudioComponent->FadeOut(FadeOutTime, 0.0f);

            // 设置定时器，在淡出完成后播放新音乐
            UWorld* World = GetWorld();
            if (World)
            {
                World->GetTimerManager().SetTimer(
                    FadeOutTimerHandle,
                    this,
                    &UMusicPlayer::OnFadeOutComplete,
                    FadeOutTime,
                    false
                );
            }
        }
        else
        {
            AudioComponent->Stop();
            PlayPendingSound();
        }
    }
    else
    {
        PlayPendingSound();
    }
}

void UMusicPlayer::OnFadeOutComplete()
{
    bIsFadingOut = false;
    if (FadeOutTimerHandle.IsValid())
    {
        UWorld* World = GetWorld();
        if (World)
        {
            World->GetTimerManager().ClearTimer(FadeOutTimerHandle);
        }
    }

    // 播放待播放的音乐
    PlayPendingSound();
}

void UMusicPlayer::PlayPendingSound()
{
    if (!AudioComponent || !PendingSound)
    {
        return;
    }

    // 设置新音乐
    AudioComponent->SetSound(PendingSound);

    // 重置待播放音效
    PendingSound = nullptr;

    // 播放音乐（默认使用淡入效果）
    AudioComponent->FadeIn(FadeInTime, CurrVolume);
}

void UMusicPlayer::StopBGM(bool bWithFade)
{
    if (!AudioComponent || !AudioComponent->IsPlaying())
    {
        return;
    }

    // 清除待播放的音乐
    PendingSound = nullptr;

    // 清除定时器
    if (FadeOutTimerHandle.IsValid())
    {
        UWorld* World = GetWorld();
        if (World)
        {
            World->GetTimerManager().ClearTimer(FadeOutTimerHandle);
        }
        bIsFadingOut = false;
    }

    if (bWithFade)
    {
        AudioComponent->FadeOut(FadeOutTime, 0.0f);
    }
    else
    {
        AudioComponent->Stop();
    }
}

void UMusicPlayer::PauseBGM()
{
    AudioComponent->SetPaused(true);
}

void UMusicPlayer::ResumeBGM()
{
    AudioComponent->SetPaused(false);
}

bool UMusicPlayer::IsBGMPlaying() const
{
    return AudioComponent && AudioComponent->IsPlaying() && !AudioComponent->bIsPaused;
}

USoundBase* UMusicPlayer::GetCurrentBGM() const
{
    return AudioComponent->Sound;
}

UAudioComponent* UMusicPlayer::CreateAudioComponent()
{
    UWorld* World = GetWorld();

    UAudioComponent* NewAudioComponent = NewObject<UAudioComponent>(World);
    if (NewAudioComponent)
    {
        NewAudioComponent->RegisterComponent();
        NewAudioComponent->SetVolumeMultiplier(1.0f);
        NewAudioComponent->bAutoActivate = true;
        NewAudioComponent->bIsUISound = true;
    }

    return NewAudioComponent;
}

void UMusicPlayer::Cleanup()
{
    if (FadeOutTimerHandle.IsValid())
    {
        UWorld* World = GetWorld();
        if (World)
        {
            World->GetTimerManager().ClearTimer(FadeOutTimerHandle);
        }
    }

    if (AudioComponent)
    {
        AudioComponent->Stop();
        AudioComponent = nullptr;
    }

    PendingSound = nullptr;
    bIsFadingOut = false;
}