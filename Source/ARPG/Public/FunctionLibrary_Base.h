// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Components/Combat/CombatComponent_Base.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types\EnumType_Base.h"
#include "FunctionLibrary_Base.generated.h"


/**
 *
 */
UCLASS()
class ARPG_API UFunctionLibrary_Base : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UAbilitySystemComponent_Base* NativeGetWarriorASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary", meta=(DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EConfirmType& OutConfirmType);

	static UCombatComponent_Base* NativeGetCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "A_My|FunctionLibrary", meta=(DisplayName = "Get Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UCombatComponent_Base* BP_GetCombatComponentFromActor(AActor* InActor, EValidType& OutValidType);
};
