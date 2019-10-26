// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "ObjectMacros.h"
#include "GridCoord.generated.h"


USTRUCT(BlueprintType)
struct SAIL_API FHexCoord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Z;

	FORCEINLINE FHexCoord();

	FORCEINLINE FHexCoord(int32 InX, int32 InY, int32 InZ);
};

USTRUCT(BlueprintType)
struct SAIL_API FGridCoord
{
	GENERATED_BODY()

	// Classic coord system
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;

	FORCEINLINE FGridCoord();

	FORCEINLINE FGridCoord(int32 InX, int32 InY);

	FORCEINLINE FGridCoord(const FHexCoord& hexCoord);

	FORCEINLINE FGridCoord operator+(const FGridCoord& V) const;

	FORCEINLINE FGridCoord operator-(const FGridCoord& V) const;

	float length()
	{
		return FMath::Abs(X) + FMath::Abs(Y);
	}

	float distance(const FGridCoord& o)
	{
		return (*this - o).length();
	}

	FHexCoord toHex() const;

	//float hexDistance(const FGridCoord& o)
	//{
	//	return (*this - o).length();
	//}

	//FORCEINLINE FGridCoord operator-(const FGridCoord& V) const;
};


UCLASS()
class SAIL_API UFGridCoordLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GridCoord + GridCoord", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|GridCoord")
	static FGridCoord Add_FGridCoordFGridCoord(FGridCoord a, FGridCoord b)
	{
		return a+b;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GridCoord - GridCoord", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Math|GridCoord")
	static FGridCoord Subtract_FGridCoordFGridCoord(FGridCoord a, FGridCoord b)
	{
		return a-b;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Distance GridCoord GridCoord", CompactNodeTitle = "Dist", Keywords = "distance", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|GridCoord")
	static float Distance(FGridCoord a, FGridCoord b)
	{
		return a.distance(b);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To HexCoord", CompactNodeTitle = "HexCoord", Keywords = "hex coord"), Category = "Math|GridCoord")
	static FHexCoord ToHex(FGridCoord a)
	{
		return a.toHex();
	}
};