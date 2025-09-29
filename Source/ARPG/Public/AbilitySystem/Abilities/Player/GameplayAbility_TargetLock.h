#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbility_Player.h"
#include "GameplayAbility_TargetLock.generated.h"

class UWidget_Base;

/**
 * 
 */
UCLASS()
class ARPG_API UGameplayAbility_TargetLock : public UGameplayAbility_Player
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();

	void CancelTargetLockAbility();
	void CleanUp();

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float BoxTraceDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	FVector BoxTraceSize = FVector(5000.f, 5000.f, 3000.f);

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TSubclassOf<UWidget_Base> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurLockedActor;

	UPROPERTY()
	UWidget_Base* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
};
