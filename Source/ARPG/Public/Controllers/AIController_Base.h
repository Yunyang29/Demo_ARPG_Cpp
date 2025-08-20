#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController_Base.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class ARPG_API AAIController_Base : public AAIController
{
	GENERATED_BODY()

public:
	AAIController_Base(const FObjectInitializer& ObjectInitializer);

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override; // IGenericTeamAgentInterface Interface

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* SelfPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config", meta=(EditCondition="bEnableDetourCrowdAvoidance", UIMax="4", UIMin="1"))
	int32 DetourCrowdAvoidQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config", meta=(EditCondition="bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;
};
