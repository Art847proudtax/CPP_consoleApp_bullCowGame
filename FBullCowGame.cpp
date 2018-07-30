#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map //TMap is an Unreal friendly syntax to instantiate maps

FBullCowGame::FBullCowGame() { Reset(); } //defined constructor. (main function of the class, executed when a class variable initializes)


//Getter methods
FString FBullCowGame::GetHiddenIsogram() const { return hiddenIsogram; }
bool FBullCowGame::GetVictoryStatus() const { return bVictoryStatus; }
int32 FBullCowGame::GetCurrentTry() const { return myCurrentTry; }
//GETTER METHODS


void FBullCowGame::Reset()
{
	//Private variables initialization
	bVictoryStatus = false;
	
	myCurrentTry = 1;

	const FString hIDDEN_ISOGRAM = "train";
	hiddenIsogram = hIDDEN_ISOGRAM;

	return;
}

void FBullCowGame::SelectWordLength(int32 selectedLength)
{
	TMap<int32, FString> hiddenIsograms { {2, "if"}, { 3,"new" }, { 4,"holy" }, { 5,"train" }, { 6,"unreal" }, { 7,"changes" }};
	hiddenIsogram = hiddenIsograms[selectedLength];
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> wordLengthToMaxTries{ {2,3}, {3,4}, {4,8}, {5,12}, {6,15}, {7,20} }; //<wordlength, maxtries> { {wordlength deserves n maxtries} }
	return wordLengthToMaxTries[hiddenIsogram.length()];

	//I could use a math operation to calculate the turns number, so every length can have his number of attempts. But the possible lengths goes from 2 to 7, so TMap is better because developers can customize the number of turns for each length
	//return (int32) std::pow(hiddenIsogram.length(),2) / 2;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (guess.length() == GetHiddenIsogram().length())
	{
		if (!IsIsogram(guess))
			return EGuessStatus::Not_isogram;

		for (int32 i = 0; i < guess.length(); i++)
		{
			if (guess[i] < 97 || guess[i]>122)
				return EGuessStatus::WrongCharacters;
		}
		return EGuessStatus::OK;
	}
	return EGuessStatus::WrongLength;
}

bool FBullCowGame::IsGameWon(int32 bulls, FString guess)
{
	if (bulls == GetHiddenIsogram().length() && guess == hiddenIsogram)
		bVictoryStatus = true;	//is better to save the victory status in the game class, because this class is the game
	else
		bVictoryStatus = false;
	return bVictoryStatus;
}

//it receives a valid guess, increments turn and returns the count of the bulls and cows
FbullCowCount FBullCowGame::SubmitGuess(FString guess)
{
	myCurrentTry++; //increment turn #
	FbullCowCount bullCowCount;	//setup return variable

	int32 loopsNumber = guess.length();
	if (hiddenIsogram.length() < loopsNumber)
		loopsNumber = hiddenIsogram.length(); //Just to avoid crash, if the method that checks the length of the word doesn't work

	for (int32 characterPosition = 0; characterPosition < loopsNumber; characterPosition++)
		//compare each letter looping through the string
	{
		bool bull = false, cow = false;
		if (guess[characterPosition] == hiddenIsogram[characterPosition])	// 1 bull for every letter in the same place
			
			bull = true;

		else for (int32 isThereACow_InHiddenIsogram = 0; isThereACow_InHiddenIsogram < loopsNumber; isThereACow_InHiddenIsogram++)
			// if the letter do not matches, checks if it's in the wrong position with a second cycle that compares the current guess' letter with every other hidden isogram's letters
		{
			if ((guess[characterPosition] == hiddenIsogram[isThereACow_InHiddenIsogram]) && (isThereACow_InHiddenIsogram != characterPosition))
				// 1 cow for every letter in the wrong place
			{
				cow = true;
			}
		}
		
		if (bull)
		{
			bullCowCount.bulls++;
			bull = false;
		}
		else if (cow)
		{
			bullCowCount.cows++;
			cow = false;
		}
	}
	return bullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() > 1) //one letter word must be an isogram
	{
		TMap<char, bool> LettersChecked;
		
		for (auto letter : word) //loop through the guess letter by letter
		{
			letter = tolower(letter);	// now the function can handle mixed cases of upper and lower characters
			if (LettersChecked[letter]) { return false; }	//if the character is already in the map and true, return false (is not an isogram word)
			else { LettersChecked[letter] = true; } //adds a letter to the map and checks it true
		}
	}
	return true;
}
