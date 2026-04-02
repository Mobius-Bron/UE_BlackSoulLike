// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "SteamSessionsSubsystem.generated.h"

// 自定义会话数据结构
USTRUCT(BlueprintType)
struct FSessionData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	FString SessionName;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	FString HostName;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 CurrentPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 MaxPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	bool bIsLAN;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	FString ServerName;

	FSessionData()
	{
		SessionName = FString(TEXT(""));
		HostName = FString(TEXT(""));
		CurrentPlayers = 0;
		MaxPlayers = 0;
		bIsLAN = false;
		ServerName = FString(TEXT(""));
	}
};

// 自定义委托（避免与引擎委托冲突）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnFindSessionsComplete, const TArray<FSessionData>&, SessionResults);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiplayerOnDestroySessionComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);

UCLASS()
class MULTIPLAYERSESSIONMANAGER_API USteamSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USteamSessionsSubsystem();

	/* Subsystem */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/* Subsystem */

	// 会话管理函数
	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void CreateSession(const FString& ServerName, const FString& HostName, int32 MaxPlayers, bool bIsLAN = false);

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void FindSessions(bool bIsLAN = false);

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void FindSessionByName(const FString& SessionName, bool bIsLAN = false);

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void JoinSession(int32 SessionIndex);

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void JoinSessionByAddress(const FString& IPAddress);

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void DestroySession();

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	void StartSession();

	// 获取当前会话信息
	UFUNCTION(BlueprintCallable, Category = "Session Management")
	bool IsSessionValid() const { return SessionInterface.IsValid() && !CurrentSessionName.IsEmpty(); }

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	FString GetCurrentSessionName() const { return CurrentSessionName; }

	UFUNCTION(BlueprintCallable, Category = "Session Management")
	int32 GetCurrentPlayers() const { return CurrentPlayers; }

	// 委托（蓝图可绑定）
	UPROPERTY(BlueprintAssignable, Category = "Session Management")
	FMultiplayerOnCreateSessionComplete OnCreateSessionComplete;

	UPROPERTY(BlueprintAssignable, Category = "Session Management")
	FMultiplayerOnFindSessionsComplete OnFindSessionsComplete;

	UPROPERTY(BlueprintAssignable, Category = "Session Management")
	FMultiplayerOnJoinSessionComplete OnJoinSessionComplete;

	UPROPERTY(BlueprintAssignable, Category = "Session Management")
	FMultiplayerOnDestroySessionComplete OnDestroySessionComplete;

	UPROPERTY(BlueprintAssignable, Category = "Session Management")
	FMultiplayerOnStartSessionComplete OnStartSessionComplete;

private:
	// 调试辅助函数
	UFUNCTION(BlueprintCallable, Category = "Debug")
	static void PrintString(const FString& Message, FColor Color = FColor::Red, float Duration = 5.0f);

	// 会话回调函数（使用正确的引擎委托签名）
	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsCompleted(bool bWasSuccessful);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnStartSessionCompleted(FName SessionName, bool bWasSuccessful);

	// 辅助函数
	void SetSessionSettings(FOnlineSessionSettings& SessionSettings, const FString& ServerName, const FString& HostName, int32 InMaxPlayers, bool bIsLAN);
	void UpdateCurrentPlayerCount();

private:
	IOnlineSubsystem* OnlineSubsystem;
	IOnlineSessionPtr SessionInterface;

	// 会话搜索结果
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	TArray<FSessionData> SessionResults;

	// 当前会话信息
	FString CurrentSessionName;
	int32 CurrentPlayers;
	int32 MaxPlayers;

	// 委托句柄
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
};