#include "Items/PickUps/Stone_Base.h"

#include "GameplayTags_Base.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Characters/Character_Player.h"

void AStone_Base::Consume(UAbilitySystemComponent_Base* AbilitySystemComponent, int32 ApplyLevel)
{
	check(GameplayEffectClass);

	UGameplayEffect* EffectCDO = GameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, AbilitySystemComponent->MakeEffectContext());
	BP_OnStoneConsumed();
}

void AStone_Base::OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (ACharacter_Player* OverlappedChar = Cast<ACharacter_Player>(OtherActor))
	{
		OverlappedChar->GetCharacterAbilitySystemComponent()->TryActivateAbilityByTag(GameplayTags_Base::Player_Ability_PickUp_Stones);
	}
}
