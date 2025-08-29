#include "Components/Combat/CombatComponent_Enemy.h"

#include "DebugHelper.h"

void UCombatComponent_Enemy::OnWeaponHitTargetActor(AActor* HitActor)
{
	Super::OnWeaponHitTargetActor(HitActor);
	if(HitActor)
	{
		Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" is hitting "+HitActor->GetActorNameOrLabel()));
	}
}
