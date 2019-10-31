// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "ObjectMacros.h"
#include "GridCoord.generated.h"


USTRUCT(BlueprintType)
struct SAIL_API FSquareCoord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Y;

	FORCEINLINE FSquareCoord();

	FORCEINLINE FSquareCoord(int32 InX, int32 InY);

	FORCEINLINE FHexCoord toHex() const;

	FORCEINLINE FString ToString() const;
};

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

	FORCEINLINE FSquareCoord toSquare() const;

	FORCEINLINE FString ToString() const;
};

USTRUCT(BlueprintType)
struct SAIL_API FGridCoord
{
	GENERATED_BODY()

	// Classic coord system
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSquareCoord SquareCoord;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHexCoord HexCoord;

	FORCEINLINE FGridCoord();

	FORCEINLINE FGridCoord(const FSquareCoord& sc);
	FORCEINLINE FGridCoord(const FHexCoord& hc);

	FORCEINLINE FGridCoord(const int32 _X, const int32 _Y);
	FORCEINLINE FGridCoord(const int32 _X, const int32 _Y, const int32 _Z);

	FORCEINLINE FGridCoord operator+(const FGridCoord& V) const;

	FORCEINLINE FGridCoord operator-(const FGridCoord& V) const;

	FORCEINLINE void setSquareCoord(const FSquareCoord& sc);

	FORCEINLINE void setHexCoord(const FHexCoord& hc);
	
	FORCEINLINE FString ToString() const;

	float length()
	{
		return FMath::Abs(SquareCoord.X) + FMath::Abs(SquareCoord.Y);
	}

	float distance(const FGridCoord& o)
	{
		return (*this - o).length();
	}

private:
	void updateSquare();
	void updateHex();

	//float hexDistance(const FGridCoord& o)
	//{
	//	return (*this - o).length();
	//}

	//FORCEINLINE FGridCoord operator-(const FGridCoord& V) const;
};


UCLASS()
class SAIL_API UFSquareCoordLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To HexCoord", CompactNodeTitle = "HexCoord", Keywords = "hex coord"), Category = "Math|GridCoord")
	static FHexCoord ToHex(FSquareCoord sc)
	{
		return sc.toHex();
	}

	//UFUNCTION(BlueprintPure, meta = (DisplayName = "To String", CompactNodeTitle = "String", Keywords = "string"), Category = "Math|GridCoord")
	//static FString ToString(const FSquareCoord sc)
	//{
	//	return sc.ToString();
	//}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (SquareCoord)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Math|GridCoord")
	static FString Conv_SquareCoordToString(FSquareCoord sc)
	{
		return sc.ToString();
	}
};

UCLASS()
class SAIL_API UFHexCoordLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To SquareCoord", CompactNodeTitle = "SquareCoord", Keywords = "square coord"), Category = "Math|GridCoord")
	static FSquareCoord ToSquare(FHexCoord hc)
	{
		return hc.toSquare();
	}

	//UFUNCTION(BlueprintPure, meta = (DisplayName = "To String", CompactNodeTitle = "String", Keywords = "string"), Category = "Math|GridCoord")
	//static FString ToString(const FHexCoord sc)
	//{
	//	return sc.ToString();
	//}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (HexCoord)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Math|GridCoord")
		static FString Conv_HexCoordToString(FHexCoord hc)
	{
		return hc.ToString();
	}
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

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (GridCoord)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Math|GridCoord")
	static FString Conv_HexCoordToString(FGridCoord gc)
	{
		return gc.ToString();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make GridCoord From Square", CompactNodeTitle = "GridCoord", Keywords = "make grid coord"), Category = "Math|GridCoord")
	static void MakeGridCoordFromSquare(FGridCoord& own, const FSquareCoord& sc)
	{
		own.setSquareCoord(sc);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make GridCoord From Hex", CompactNodeTitle = "GridCoord", Keywords = "make grid coord"), Category = "Math|GridCoord")
	static void MakeGridCoordFromHex(FGridCoord& own, const FHexCoord& hc)
	{
		own.setHexCoord(hc);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Set Square Coord", CompactNodeTitle = "Set Square", Keywords = "set square coord"), Category = "Math|GridCoord")
	static FGridCoord setSquareCoord(FGridCoord gc, const FSquareCoord& sc)
	{
		return FGridCoord(sc);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Set Hex Coord", CompactNodeTitle = "Set Hex", Keywords = "set hex coord"), Category = "Math|GridCoord")
		static FGridCoord setHexCoord(FGridCoord gc, const FHexCoord& hc)
	{
		return FGridCoord(hc);
	}
};