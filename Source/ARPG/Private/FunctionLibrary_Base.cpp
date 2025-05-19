// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystemBlueprintLibrary.h"
#include "FunctionLibrary_Base.h"

UAbilitySystemComponent_Base* UFunctionLibrary_Base::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UAbilitySystemComponent_Base>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}


void UFunctionLibrary_Base::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UAbilitySystemComponent_Base* ASC = NativeGetWarriorASCFromActor(InActor);
	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UFunctionLibrary_Base::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UAbilitySystemComponent_Base* ASC = NativeGetWarriorASCFromActor(InActor);
	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UFunctionLibrary_Base::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UAbilitySystemComponent_Base* ASC = NativeGetWarriorASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UFunctionLibrary_Base::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EConfirmType::Yes : EConfirmType::No;
	
}
