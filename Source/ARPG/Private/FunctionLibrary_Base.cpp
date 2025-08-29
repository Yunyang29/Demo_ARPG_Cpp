#include "FunctionLibrary_Base.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"

#include "Interfaces/PawnCombatInterface.h"

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

UCombatComponent_Base* UFunctionLibrary_Base::NativeGetCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetCombatComponent();
	}

	return nullptr;
}

UCombatComponent_Base* UFunctionLibrary_Base::BP_GetCombatComponentFromActor(AActor* InActor, EValidType& OutValidType)
{
	UCombatComponent_Base* CombatComponent = NativeGetCombatComponentFromActor(InActor);
	OutValidType = CombatComponent ? EValidType::Valid : EValidType::Invalid;
	return CombatComponent;
}

bool UFunctionLibrary_Base::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn&&TargetPawn);
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if(QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}
