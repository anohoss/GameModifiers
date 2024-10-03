// Copyright (c) 2024 Anoho All rights reserved.

#pragma once

#include "CoreMinimal.h"

// Include headers in Engine module.
#include "Subsystems/EngineSubsystem.h"

#include "GameModifiersLevelRegistry.generated.h"

/*
* 任意のレベルに対してストリーミングされるレベルの情報
*/
USTRUCT(BlueprintType)
struct GAMEMODIFIERS_API FGameModifiersStreamLevel
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FName LongPackageName;

public:

	// NOTE:これを等価とすると問題が出るかもしれない
	//		LevelNameToStreamLevels の TArray<FGameModifiersStreamLevel> の中に同じレベルが含まれなければ問題ないはず
	bool operator==(const FGameModifiersStreamLevel& Other) const { return LongPackageName == Other.LongPackageName; }

	bool operator!=(const FGameModifiersStreamLevel& Other) const { return !(*this == Other); }

	FString GetLongPackageNameStr() const { return LongPackageName.ToString(); };
};

/*
* 任意のレベルを上書きするレベルに関する情報
*/
USTRUCT(BlueprintType)
struct GAMEMODIFIERS_API FGameModifiersLevelOverride
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FName LongPackageName;

public:

	// NOTE:これを等価とすると問題が出るかもしれない
	//		LevelNameToLevelOverride の中に同じレベルが含まれなければ問題ないはず
	bool operator==(const FGameModifiersLevelOverride& Other) const { return LongPackageName == Other.LongPackageName; }

	bool operator!=(const FGameModifiersLevelOverride& Other) const { return !(*this == Other); }

	FString GetLongPackageNameStr() const { return LongPackageName.ToString(); };
};

/**
 * 
 */
UCLASS(BlueprintType)
class GAMEMODIFIERS_API UGameModifiersLevelRegistry : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Level")
	FGameModifiersLevelOverride GetLevelOverrideByName(FName OriginalLevelName) const;

	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Level")
	void GetStreamLevelsByName(FName LevelName, TArray<FGameModifiersStreamLevel>& OutStreamLevels);

	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Level")
	void RegisterLevelOverrideByName(FName OriginalLevelName, FName OverrideLevelName);

	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Level")
	void RegisterStreamLevelByName(FName LevelName, FName StreamLevelName);

	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Level")
	void UnregisterLevelOverrideByName(FName OriginalLevelName);

	UFUNCTION(BlueprintCallable, Category = "GameModifiers|Level")
	void UnregisterStreamLevelByName(FName LevelName, FName StreamLevelName);

private:

	static FName MakeLongPackageName(const FName& LevelName);

private:

	TMap<FName /*LevelName*/, FGameModifiersLevelOverride> LevelNameToLevelOverride;

	TMap<FName /*LevelName*/, TArray<FGameModifiersStreamLevel>> LevelNameToStreamLevels;
};
