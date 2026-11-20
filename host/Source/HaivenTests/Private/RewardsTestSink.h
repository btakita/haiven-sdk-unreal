#pragma once

#include "CoreMinimal.h"
#include "HaivenRewards.h"
#include "RewardsTestSink.generated.h"

class UHaivenSubsystem;

UCLASS()
class UHaivenRewardsTestSink : public UObject
{
	GENERATED_BODY()

public:
	void SetTarget(UHaivenSubsystem* InTarget) { Target = InTarget; }

	UFUNCTION()
	void LogoutAndStartNextPlayer(const FHaivenRewardClaimOutcome& Outcome);

	UFUNCTION()
	void RecordClaimed(const FHaivenRewardClaimOutcome& Outcome);

	/** Records a settled saved claim, and logs out from inside the delegate when bLogoutOnSettled. */
	UFUNCTION()
	void SettleAndMaybeLogout(const FHaivenRewardClaimOutcome& Outcome);

	UFUNCTION()
	void RecordFailed(const FHaivenRewardClaimOutcome& Outcome);

	int32 SubsystemClaimedCount = 0;
	int32 ActionClaimedCount = 0;
	int32 ActionFailedCount = 0;
	int32 SettledCount = 0;
	bool bLogoutOnSettled = false;
	bool bNextPlayerStarted = false;
	FString NextPlayerClaimId;
	FHaivenRewardClaimOutcome FailedOutcome;

private:
	UPROPERTY()
	TObjectPtr<UHaivenSubsystem> Target;
};
