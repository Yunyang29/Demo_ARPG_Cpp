#pragma once

#include "CoreMinimal.h"
#include "GameModes/GameMode_Base.h"
#include "GameMode_Survival.generated.h"

class ACharacter_Enemy;

UENUM(BlueprintType)
enum class EGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<ACharacter_Enemy> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeStateChangedDelegate, EGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class ARPG_API AGameMode_Survival : public AGameMode_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

	UPROPERTY()
	EGameModeState CurrentGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameModeStateChangedDelegate OnGameModeStateChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "A_MY|WaveDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "A_MY|WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 TotalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "A_MY|WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "A_MY|WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float WaitTimeToSpawnNewWave = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "A_MY|WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float DelayTimeToSpawnEnemies = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "A_MY|WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float WaitTimeToWaveCompleted = 5.f;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY()
	TMap<TSoftClassPtr<ACharacter_Enemy>, UClass*> PreLoadedEnemyClassMap;

	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;

	UPROPERTY()
	TArray<AActor*> TargetPointsArray;

	void SetCurrentGameModeState(EGameModeState InState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<ACharacter_Enemy*>& InEnemiesToRegister);
};
