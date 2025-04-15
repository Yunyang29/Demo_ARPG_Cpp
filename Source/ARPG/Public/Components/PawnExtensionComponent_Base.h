#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponent_Base.generated.h"

/**
 * Pawn扩展组件基类
 * 功能：为Pawn提供通用功能扩展，包括获取所属Pawn和Controller的便捷方法
 * 使用场景：当需要在组件中方便地访问所属Pawn或Controller时，可以继承此类
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARPG_API UPawnExtensionComponent_Base : public UActorComponent
{
	GENERATED_BODY()

protected:
	/**
	 * 获取所属Pawn的模板方法
	 * C++层面：
	 * - 使用模板参数T，允许获取特定类型的Pawn
	 * - static_assert确保模板参数T必须继承自APawn
	 * - CastChecked进行类型转换，如果转换失败会断言
	 *
	 * 功能层面：
	 * - 提供类型安全的Pawn获取方法
	 * - 确保获取的Pawn类型正确
	 */
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	/**
	 * 获取所属Pawn的非模板重载方法
	 * C++层面：
	 * - 提供非模板版本，简化调用
	 * - 内部调用模板版本，指定类型为APawn
	 *
	 * 功能层面：
	 * - 当不需要特定Pawn类型时，提供便捷访问方法
	 */
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	/**
	 * 获取所属Controller的模板方法
	 * C++层面：
	 * - 使用模板参数T，允许获取特定类型的Controller
	 * - static_assert确保模板参数T必须继承自AController
	 * - 通过Pawn获取Controller，再转换为指定类型
	 *
	 * 功能层面：
	 * - 提供类型安全的Controller获取方法
	 * - 确保获取的Controller类型正确
	 * - 通过Pawn间接获取Controller，符合UE的组件层级关系
	 */
	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
