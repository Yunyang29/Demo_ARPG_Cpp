#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/Combat/CombatComponent_Base.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/EnumType_Base.h"
#include "FunctionLibrary_Base.generated.h"

class UAbilitySystemComponent_Base;
class UPawnCombatInterface;
struct FScalableFloat;

/**
 *
 */
UCLASS()
class ARPG_API UFunctionLibrary_Base : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UAbilitySystemComponent_Base* NativeGetASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary", meta=(DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EConfirmType& OutConfirmType);

	static UCombatComponent_Base* NativeGetCCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary", meta=(DisplayName = "Get Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UCombatComponent_Base* BP_GetCombatComponentFromActor(AActor* InActor, EValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "A_My|FunctionLibrary")
	static bool IsTargetPawnHostile(const APawn* QueryPawn, const APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "A_My|FunctionLibrary", meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "A_My|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(const AActor* InAttacker, const AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "A_My|FunctionLibrary")
	static bool IsValidBlock(const AActor* InAttacker, const AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary", meta=(Latent, WorldContext="WorldContextObject", LatentInfo="LatenInfo",
		ExpandEnumAsExecs="CountdownInput|CountdownOutput", TotalTime="1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject,
	                      float totalTime,
	                      float UpdateInterval,
	                      float& OutRemainingTime,
	                      ECountdownActionInput CountdownInput,
	                      UPARAM(DisplayName="Output")
	                      ECountdownActionOutput& CountdownOutput,
	                      FLatentActionInfo LatenInfo);
};
