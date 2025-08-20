#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBTService_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()
	UBTService_OrientToTargetActor();

	virtual void    InitializeFromAsset(UBehaviorTree& Asset) override; // UBTNode Interface
	virtual FString GetStaticDescription() const override; // UBTNode Interface

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category="Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category="Target")
	float RotationInterSpeed;
};
