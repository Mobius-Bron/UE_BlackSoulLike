// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamSessionsSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSubsystem.h"

void USteamSessionsSubsystem::PrintString(const FString& Message, FColor Color, float Duration)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
    }
}

USteamSessionsSubsystem::USteamSessionsSubsystem()
{
    OnlineSubsystem = IOnlineSubsystem::Get();
    if (OnlineSubsystem)
    {
        UE_LOG(LogTemp, Log, TEXT("SteamSessionsSubsystem: Using OnlineSubsystem: %s"), *OnlineSubsystem->GetSubsystemName().ToString());
        SessionInterface = OnlineSubsystem->GetSessionInterface();

        if (SessionInterface.IsValid())
        {
            UE_LOG(LogTemp, Log, TEXT("SteamSessionsSubsystem: SessionInterface successfully created"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("SteamSessionsSubsystem: Failed to get SessionInterface"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SteamSessionsSubsystem: Failed to get OnlineSubsystem"));
    }
}

void USteamSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("SteamSessionsSubsystem initialized"));

    CurrentPlayers = 0;
    MaxPlayers = 0;
}

void USteamSessionsSubsystem::Deinitialize()
{
    // 移除所有委托
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
        SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
        SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
    }

    Super::Deinitialize();
    UE_LOG(LogTemp, Log, TEXT("SteamSessionsSubsystem deinitialized"));
}

void USteamSessionsSubsystem::SetSessionSettings(FOnlineSessionSettings& SessionSettings, const FString& ServerName, const FString& HostName, int32 InMaxPlayers, bool bIsLAN)
{
    SessionSettings.bIsLANMatch = bIsLAN;
    SessionSettings.bShouldAdvertise = true;
    SessionSettings.bUsesPresence = true;
    SessionSettings.bAllowJoinViaPresence = true;
    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.bAllowInvites = true;
    SessionSettings.bUseLobbiesIfAvailable = true;
    SessionSettings.NumPublicConnections = InMaxPlayers;

    // 自定义设置
    SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    SessionSettings.Set(FName("HOST_NAME"), HostName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    SessionSettings.Set(FName("CURRENT_PLAYERS"), 1, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
}

void USteamSessionsSubsystem::CreateSession(const FString& ServerName, const FString& HostName, int32 InMaxPlayers, bool bIsLAN)
{
    if (!SessionInterface.IsValid())
    {
        PrintString("Session Interface is not valid!", FColor::Red);
        OnCreateSessionComplete.Broadcast(false);
        return;
    }

    // 如果已有会话，先销毁
    if (IsSessionValid())
    {
        DestroySession();
    }

    // 创建会话设置
    FOnlineSessionSettings SessionSettings;
    SetSessionSettings(SessionSettings, ServerName, HostName, InMaxPlayers, bIsLAN);

    // 添加创建会话委托
    OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(
        FOnCreateSessionCompleteDelegate::CreateUObject(this, &USteamSessionsSubsystem::OnCreateSessionCompleted)
    );

    // 获取本地玩家ID
    ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
    {
        PrintString("No local player found!", FColor::Red);
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
        OnCreateSessionComplete.Broadcast(false);
        return;
    }

    // 创建会话
    if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), FName(ServerName), SessionSettings))
    {
        PrintString("Failed to create session!", FColor::Red);
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
        OnCreateSessionComplete.Broadcast(false);
    }
}

void USteamSessionsSubsystem::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

    if (bWasSuccessful)
    {
        CurrentSessionName = SessionName.ToString();
        CurrentPlayers = 1;

        PrintString(FString::Printf(TEXT("Session created successfully: %s"), *SessionName.ToString()), FColor::Green);

        // 自动开始会话
        StartSession();
    }
    else
    {
        PrintString("Failed to create session!", FColor::Red);
    }

    OnCreateSessionComplete.Broadcast(bWasSuccessful);
}

void USteamSessionsSubsystem::FindSessions(bool bIsLAN)
{
    if (!SessionInterface.IsValid())
    {
        PrintString("Session Interface is not valid!", FColor::Red);
        OnFindSessionsComplete.Broadcast(TArray<FSessionData>());
        return;
    }

    // 创建搜索对象
    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->bIsLanQuery = bIsLAN;
    SessionSearch->MaxSearchResults = 100;
    SessionSearch->QuerySettings.Set(FName(TEXT("PRESENCESEARCH")), true, EOnlineComparisonOp::Equals);

    // 添加查找会话委托
    OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(
        FOnFindSessionsCompleteDelegate::CreateUObject(this, &USteamSessionsSubsystem::OnFindSessionsCompleted)
    );

    // 获取本地玩家ID
    ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
    {
        PrintString("No local player found!", FColor::Red);
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
        OnFindSessionsComplete.Broadcast(TArray<FSessionData>());
        return;
    }

    // 查找会话
    if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef()))
    {
        PrintString("Failed to find sessions!", FColor::Red);
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
        OnFindSessionsComplete.Broadcast(TArray<FSessionData>());
    }
}

void USteamSessionsSubsystem::FindSessionByName(const FString& SessionName, bool bIsLAN)
{
    // 首先查找所有会话
    FindSessions(bIsLAN);
}

void USteamSessionsSubsystem::OnFindSessionsCompleted(bool bWasSuccessful)
{
    SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

    SessionResults.Empty();

    if (!bWasSuccessful || !SessionSearch.IsValid() || SessionSearch->SearchResults.Num() == 0)
    {
        PrintString("No sessions found!", FColor::Yellow);
        OnFindSessionsComplete.Broadcast(SessionResults);
        return;
    }

    PrintString(FString::Printf(TEXT("Found %d sessions"), SessionSearch->SearchResults.Num()), FColor::Green);

    // 处理搜索结果
    for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
    {
        FSessionData SessionData;

        // 获取会话信息
        SessionData.SessionName = Result.Session.OwningUserName;
        SessionData.CurrentPlayers = Result.Session.SessionSettings.NumPublicConnections - Result.Session.NumOpenPublicConnections;
        SessionData.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
        SessionData.bIsLAN = Result.Session.SessionSettings.bIsLANMatch;

        // 获取自定义设置
        FString ServerName;
        if (Result.Session.SessionSettings.Get(FName("SERVER_NAME"), ServerName))
        {
            SessionData.ServerName = ServerName;
        }

        FString HostName;
        if (Result.Session.SessionSettings.Get(FName("HOST_NAME"), HostName))
        {
            SessionData.HostName = HostName;
        }

        // 按名称过滤（如果FindSessionByName被调用）
        static bool bFilterByName = false;
        static FString TargetSessionName;

        if (bFilterByName && SessionData.ServerName != TargetSessionName)
        {
            continue;
        }

        SessionResults.Add(SessionData);
    }

    OnFindSessionsComplete.Broadcast(SessionResults);
}

void USteamSessionsSubsystem::JoinSession(int32 SessionIndex)
{
    if (!SessionInterface.IsValid() || !SessionSearch.IsValid() || !SessionSearch->SearchResults.IsValidIndex(SessionIndex))
    {
        PrintString("Invalid session index!", FColor::Red);
        OnJoinSessionComplete.Broadcast(false);
        return;
    }

    // 添加加入会话委托
    OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(
        FOnJoinSessionCompleteDelegate::CreateUObject(this, &USteamSessionsSubsystem::OnJoinSessionCompleted)
    );

    // 获取本地玩家ID
    ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
    {
        PrintString("No local player found!", FColor::Red);
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
        OnJoinSessionComplete.Broadcast(false);
        return;
    }

    // 加入会话
    FName SessionName = FName(*SessionResults[SessionIndex].SessionName);
    if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), SessionName, SessionSearch->SearchResults[SessionIndex]))
    {
        PrintString("Failed to join session!", FColor::Red);
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
        OnJoinSessionComplete.Broadcast(false);
    }
}

void USteamSessionsSubsystem::JoinSessionByAddress(const FString& IPAddress)
{
    // 注意：Steam不支持直接通过IP加入，这里需要实现其他逻辑
    PrintString("Direct IP join not supported on Steam! Use FindSessions instead.", FColor::Red);
    OnJoinSessionComplete.Broadcast(false);
}

void USteamSessionsSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

    bool bWasSuccessful = (Result == EOnJoinSessionCompleteResult::Success);

    if (bWasSuccessful)
    {
        CurrentSessionName = SessionName.ToString();

        // 获取连接字符串并客户端旅行
        FString ConnectionString;
        if (SessionInterface->GetResolvedConnectString(SessionName, ConnectionString))
        {
            PrintString(FString::Printf(TEXT("Joining session: %s"), *ConnectionString), FColor::Green);

            // 获取玩家控制器并客户端旅行
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->ClientTravel(ConnectionString, TRAVEL_Absolute);
            }
        }
    }
    else
    {
        FString ErrorMsg;
        switch (Result)
        {
        case EOnJoinSessionCompleteResult::SessionIsFull:
            ErrorMsg = "Session is full!";
            break;
        case EOnJoinSessionCompleteResult::SessionDoesNotExist:
            ErrorMsg = "Session does not exist!";
            break;
        case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
            ErrorMsg = "Could not retrieve address!";
            break;
        default:
            ErrorMsg = "Unknown error!";
        }
        PrintString(FString::Printf(TEXT("Failed to join session: %s"), *ErrorMsg), FColor::Red);
    }

    OnJoinSessionComplete.Broadcast(bWasSuccessful);
}

void USteamSessionsSubsystem::DestroySession()
{
    if (!SessionInterface.IsValid() || !IsSessionValid())
    {
        OnDestroySessionComplete.Broadcast();
        return;
    }

    // 添加销毁会话委托
    OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(
        FOnDestroySessionCompleteDelegate::CreateUObject(this, &USteamSessionsSubsystem::OnDestroySessionCompleted)
    );

    if (!SessionInterface->DestroySession(FName(*CurrentSessionName)))
    {
        PrintString("Failed to destroy session!", FColor::Red);
        SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
        OnDestroySessionComplete.Broadcast();
    }
}

void USteamSessionsSubsystem::OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful)
{
    SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

    if (bWasSuccessful)
    {
        CurrentSessionName = FString();
        CurrentPlayers = 0;
        MaxPlayers = 0;

        PrintString("Session destroyed successfully", FColor::Green);
    }
    else
    {
        PrintString("Failed to destroy session!", FColor::Red);
    }

    OnDestroySessionComplete.Broadcast();
}

void USteamSessionsSubsystem::StartSession()
{
    if (!SessionInterface.IsValid() || !IsSessionValid())
    {
        OnStartSessionComplete.Broadcast(false);
        return;
    }

    // 添加开始会话委托
    OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(
        FOnStartSessionCompleteDelegate::CreateUObject(this, &USteamSessionsSubsystem::OnStartSessionCompleted)
    );

    if (!SessionInterface->StartSession(FName(*CurrentSessionName)))
    {
        PrintString("Failed to start session!", FColor::Red);
        SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
        OnStartSessionComplete.Broadcast(false);
    }
}

void USteamSessionsSubsystem::OnStartSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);

    if (bWasSuccessful)
    {
        PrintString("Session started successfully", FColor::Green);
    }
    else
    {
        PrintString("Failed to start session!", FColor::Red);
    }

    OnStartSessionComplete.Broadcast(bWasSuccessful);
}

void USteamSessionsSubsystem::UpdateCurrentPlayerCount()
{
    if (!SessionInterface.IsValid() || !IsSessionValid())
    {
        return;
    }

    // 获取当前会话信息
    FNamedOnlineSession* Session = SessionInterface->GetNamedSession(FName(*CurrentSessionName));
    if (Session)
    {
        CurrentPlayers = Session->SessionSettings.NumPublicConnections - Session->NumOpenPublicConnections;
        MaxPlayers = Session->SessionSettings.NumPublicConnections;
    }
}