#pragma once

#include "CoreMinimal.h"
#include "HaivenChat.h"
#include "ChatChangedTestSink.generated.h"

class UHaivenSubsystem;

/** A game's OnOutgoingChatChanged listener: it ends the account from inside the broadcast. */
UCLASS()
class UHaivenChatChangedTestSink : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void HandleChatChanged(const FHaivenOutgoingChatMessage& Message);

	UPROPERTY()
	TObjectPtr<UHaivenSubsystem> Target;

	/** true: SetAccessToken (account replacement); false: Logout. */
	bool bReplaceAccount = false;
	FString Token;
	FDateTime ExpiresAtUtc;
	TArray<FHaivenOutgoingChatMessage> Changes;
};
