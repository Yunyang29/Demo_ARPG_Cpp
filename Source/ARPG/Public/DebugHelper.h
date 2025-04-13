#pragma once

/**
 * @brief 调试辅助工具命名空间
 * 提供用于在游戏中显示调试信息的实用函数
 */
namespace Debug
{
	/**
	 * @brief 在屏幕上打印调试信息
	 * @param Msg 要显示的调试消息
	 * @param Color 消息的颜色，默认为随机颜色
	 * @param InKey 消息的唯一标识符，用于更新或删除特定消息，默认为-1
	 *
	 * 此函数会在屏幕上显示调试消息，同时也会将消息输出到日志中
	 * 如果GEngine实例存在，消息将显示7秒
	 */
	static void Print(const FString &Msg, const FColor &Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Msg);	// 在屏幕上显示调试消息，持续7秒
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);  // 将消息同时输出到日志系统
		}
	}
}
