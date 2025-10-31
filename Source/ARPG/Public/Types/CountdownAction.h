#pragma once

#include "CoreMinimal.h"
#include "DebugHelper.h"
#include "EnumType_Base.h"

class FCountdownAction : public FPendingLatentAction
{
public:
	FCountdownAction(float InTotalCountdownTime, float InUpdatedInterval, float& InOutRemainingTime, ECountdownActionOutput& InCountdownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false),
		  TotalCountdownTime(InTotalCountdownTime),
		  UpdateInterval(InUpdatedInterval),
		  OutRemainingTime(InOutRemainingTime),
		  CountdownOutput(InCountdownOutput),
		  ExecutionFunction(LatentInfo.ExecutionFunction),
		  OutputLink(LatentInfo.Linkage),
		  CallbackTarget(LatentInfo.CallbackTarget),
		  ElapsedInterval(0.f),
		  ElapsedTimeSinceStart(0.f)
	{
		// Debug::Print("New Countdown Action");
	}

	void CancelAction();

	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	bool bNeedToCancel;
	float TotalCountdownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	ECountdownActionOutput& CountdownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};
