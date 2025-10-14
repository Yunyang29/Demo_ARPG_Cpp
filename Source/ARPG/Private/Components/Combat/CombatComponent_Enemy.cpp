#include "Components/Combat/CombatComponent_Enemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "FunctionLibrary_Base.h"
#include "GameplayTags_Base.h"
#include "Characters/Character_Enemy.h"
#include "Components/BoxComponent.h"

void UCombatComponent_Enemy::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);
	bool bIsValidBlock = false;
	bool bIsPlayerBlocking = UFunctionLibrary_Base::NativeDoesActorHaveTag(HitActor, GameplayTags_Base::Player_Status_Blocking);
	bool bIsMyAttackUnblockable = UFunctionLibrary_Base::NativeDoesActorHaveTag(GetOwningPawn(), GameplayTags_Base::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UFunctionLibrary_Base::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, GameplayTags_Base::Player_Event_SuccessfulBlock, EventData);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), GameplayTags_Base::Shared_Event_MeleeHit, EventData);
	}
}

void UCombatComponent_Enemy::ToggleBodyCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	Super::ToggleBodyCollision(bShouldEnable, ToggleDamageType);
	ACharacter_Enemy* OwningChar = GetOwningPawn<ACharacter_Enemy>();
	check(OwningChar);

	UBoxComponent* LeftHandBox = OwningChar->GetLeftHandBox();
	UBoxComponent* RightHandBox = OwningChar->GetRightHandBox();
	check(LeftHandBox && RightHandBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
