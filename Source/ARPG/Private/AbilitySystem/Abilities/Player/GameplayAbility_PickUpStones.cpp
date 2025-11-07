#include "AbilitySystem/Abilities/Player/GameplayAbility_PickUpStones.h"

#include "Characters/Character_Player.h"
#include "Components/UI/UIComponent_Player.h"
#include "Items/PickUps/Stone_Base.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameplayAbility_PickUpStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GetPlayerUICompFromActorInfo()->OnStoneInteracted.Broadcast(true);
}

void UGameplayAbility_PickUpStones::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GetPlayerUICompFromActorInfo()->OnStoneInteracted.Broadcast(false);
}

void UGameplayAbility_PickUpStones::CollectStone()
{
	CollectedStones.Empty();

	TArray<FHitResult> Hits;

	ACharacter_Player* Char = GetPlayerCharacterFromActorInfo();
	FVector Start = Char->GetActorLocation();
	FVector End = Start + (-Char->GetActorUpVector() * TraceDistance);
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		Char,
		Start,
		End,
		TraceSize / 2.f,
		Char->GetActorRotation(), // 或使用所需朝向,
		TraceChannel,
		false,
		TArray<AActor*>(),
		bDrawnPersistentDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		Hits,
		true
	);

	for (const FHitResult& Hit : Hits)
	{
		if (AStone_Base* Stone = Cast<AStone_Base>(Hit.GetActor()))
		{
			CollectedStones.AddUnique(Stone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UGameplayAbility_PickUpStones::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AStone_Base* Stone : CollectedStones)
	{
		if (Stone)
		{
			Stone->Consume(GetAbilitySystemCompFromActorInfo(), GetAbilityLevel());
		}
	}
}
