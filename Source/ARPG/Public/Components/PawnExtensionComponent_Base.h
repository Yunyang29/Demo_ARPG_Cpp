#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponent_Base.generated.h"

/**
 * Pawn扩展组件基类
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARPG_API UPawnExtensionComponent_Base : public UActorComponent
{
	GENERATED_BODY()

protected:
	/**
	 * 获取所属Pawn的模板方法
	 */
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	/**
	 * 获取所属Pawn的非模板重载方法
	 */
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	/**
	 * 获取所属Controller的模板方法
	 */
	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
