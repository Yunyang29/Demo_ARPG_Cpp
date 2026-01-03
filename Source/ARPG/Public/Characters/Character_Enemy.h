#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Base.h"
#include "Character_Enemy.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UUIComponent_Enemy;
class UCombatComponent_Enemy;
/**
 * 
 */
UCLASS()
class ARPG_API ACharacter_Enemy : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Enemy();
	virtual UCombatComponent_Base* GetCombatComponent() const override;
	virtual UUIComponent_Base*     GetUIComponent() const override;
	virtual UUIComponent_Enemy*    GetEnemyUIComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="A_My|Combat")
	UCombatComponent_Enemy* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="A_My|Combat")
	UBoxComponent* LeftHandBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="A_My|Combat")
	FName LeftHandBoxSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="A_My|Combat")
	UBoxComponent* RightHandBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="A_My|Combat")
	FName RightHandBoxSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|UI")
	UUIComponent_Enemy* UIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|UI")
	UWidgetComponent* HealthWidgetComponent;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UCombatComponent_Enemy* GetEnemyCombatComp() const
	{
		return CombatComponent;
	}

	FORCEINLINE UBoxComponent* GetLeftHandBox() const
	{
		return LeftHandBox;
	}

	FORCEINLINE UBoxComponent* GetRightHandBox() const
	{
		return RightHandBox;
	}
};
