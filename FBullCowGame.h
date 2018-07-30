#pragma once

// This class represents the logic of the game (no view code or direct user interaction)

#include <string>

//Just to use the Unreal friendly syntax
using FString = std::string;
using int32 = int;

struct FbullCowCount
{
	//is reccomended to initialize to 0 the struct's integers
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_isogram,
	WrongLength,
	WrongCharacters
};

class FBullCowGame {
public:
	//PUBLIC METHODS Ideally only functions are public, all the class variable should be private
	FBullCowGame(); //declaration of the class' constructor

	//Getter methods
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	//int32 GetHiddenIsogramLength() const; //It is unnecessary, because it can be calculate typing the method that gets the hidden word and measure the length by this way: GetHiddenWord().length();
	FString GetHiddenIsogram() const;
	bool GetVictoryStatus() const;
	//GETTER METHODS
	
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon(int32,FString);
	void Reset();
	void SelectWordLength(int32);
	FbullCowCount SubmitGuess(FString);

private:
	int32 myCurrentTry;
	FString hiddenIsogram;
	bool bVictoryStatus;

	//PRIVATE METHODS
	bool IsIsogram(FString) const;
};