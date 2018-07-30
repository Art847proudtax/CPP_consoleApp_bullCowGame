// This is the console executable that makes use of the BullCow class.
// This acts as the view in a MVC pattern, and it's responsible for all user interaction.
// Fot game logic see the FBullCowGame.cpp class file and the class' header FBullCowGame.h

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

FBullCowGame bullCowGame; // instantiate a new game

//semicallon functions prototypes to make the method work
void PrintIntro();
bool GamePlay();
FText GettingValidGuess();
bool AskToPlayAgain();
void Victory();
void Defeat();
void SelectWordLength();
FText StringToLower(FText);
//SEMICALLON


//main function of application
int main()
{
	//intro
	PrintIntro();

	do { GamePlay(); } while (AskToPlayAgain() == true); //here is called the method that asks to the user if he wants to play again. If he accepts the return value will be 1 (true), so the cycle repeats. Else the function will return 0 (false) exiting from while

	return 0; //EXIT
}
//MAIN

//plays a single game
bool GamePlay()
{
	bullCowGame.Reset();

	SelectWordLength();

	std::cout << "\n\n--------------------------------------START-------------------------------------\n\n";
	std::cout << "I'm thinking an isogram with " << bullCowGame.GetHiddenIsogram().length() << " different letters. Can you guess this word?" << std::endl;

	std::cout << "You have "<< bullCowGame.GetMaxTries() << " attempts\n\n";

	FText guess = "";
	while (bullCowGame.GetCurrentTry() <= bullCowGame.GetMaxTries())	//loops for every turn
	{
		std::cout << "_____\n\nAttempt " << bullCowGame.GetCurrentTry() << " of " << bullCowGame.GetMaxTries() << ": ";	//prints the attempt number

		guess = GettingValidGuess();	//takes the input guess

		std::cout << std::endl << std::endl << "Your guess was: " << guess << std::endl;	//repeats the guess to the user

		//check the victory, the bulls and the cows
		FbullCowCount bullsAndCows = bullCowGame.SubmitGuess(guess);	//counts the bulls & the cows
		if (bullCowGame.IsGameWon(bullsAndCows.bulls, guess))
		{
			Victory();
			return bullCowGame.GetVictoryStatus();														// END OF THE GAME WON If the player solves the riddle, the GamePlay function returns true
		}
		else //it's not reccomended to avoid braces {}, like what happens here in this else, because in future they may be useful
		std::cout << "There are " << bullsAndCows.bulls << " bulls and " << bullsAndCows.cows << " cows.\n" << std::endl; //else the game prints the number of bulls and cows
		int32 remainingAttempts = (bullCowGame.GetMaxTries() - bullCowGame.GetCurrentTry()) + 1;
		if (remainingAttempts != 0 && remainingAttempts <= (bullCowGame.GetMaxTries() / 3)) //if the player has only 1/3 of remaining attempts, the game alerts the player how much attempts remains before the end
		{
			std::cout << "---\nONLY " << remainingAttempts;
			if (remainingAttempts != 1)
				std::cout << " REMAINING ATTEMPTS!\n---\n";
			else
				std::cout << " REMAINING ATTEMPT!\n---\n";
		}
	}
	//if there are no more attempts, the game ends
	Defeat(); 
	return bullCowGame.GetVictoryStatus(); // GAME LOST If the player doesn't solve the riddle in the last attempt, the GamePlay function returns false
}

void PrintIntro()
{
	//intro
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "A fun word game!" << std::endl;

	std::cout << R"(                                       /;    ;\          ,           ,)" << std::endl;
	std::cout << R"(                                   __  \\____//         /             \)" << std::endl;
	std::cout << R"(	                          /{_\_/   `'\____     ((__-^^-,-^^-__)))" << std::endl;
	std::cout << R"(                                  \___   (o)  (o  }     `-_---' `---_-')" << std::endl;
	std::cout << R"(       _____________________________/          :--'      <__|o` 'o|__>)" << std::endl;
	std::cout << R"(   ,-,'`@@@@@@@@       @@@@@@         \_    `__\            \  `  /)" << std::endl;
	std::cout << R"(  ;:(  @@@@@@@@@        @@@             \___(o'o)            ): :()" << std::endl;
	std::cout << R"(  :: )  @@@@          @@@@@@        ,'@@(  `===='            :o_o:)" << std::endl;
	std::cout << R"(  :: : @@@@@:          @@@@         `@@@:                     "-")" << std::endl;
	std::cout << R"(  :: \  @@@@@:       @@@@@@@)    (  '@@@')" << std::endl;
	std::cout << R"(  ;; /\      /`,    @@@@@@@@@\   :@@@@@))" << std::endl;
	std::cout << R"(  ::/  )    {_----------------:  :~`,~~;)" << std::endl;
	std::cout << R"( ;;'`; :   )                  :  / `; ;)" << std::endl;
	std::cout << R"(;;;; : :   ;                  :  ;  ; :)" << std::endl;
	std::cout << R"(`'`' / :  :                   :  :  : :)" << std::endl;
	std::cout << R"(    )_ \__;                   :_ ;  \_\)" << std::endl;
	std::cout << R"(    :__\  \                   \  \  :  \)" << std::endl;
	std::cout << R"(        `^'                    `^'  `-^-'   -art from Bill Ames-)" << std::endl; //I just picked another already done, sorry!
	std::cout << "\n";
	
	return;
}

//gets a guess from the player
FText GettingValidGuess()
{
	FText guess = "";
	EGuessStatus status = EGuessStatus::WrongLength;
	do
	{
		std::getline(std::cin, guess); //getline catches all the string in a row

		guess = StringToLower(guess); //turns all the guess' upperchase characters to lowercase

		status = bullCowGame.CheckGuessValidity(guess);

		switch (status)
		{
			case EGuessStatus::WrongLength:
				std::cout << "\nWrite a " << bullCowGame.GetHiddenIsogram().length() << " letters isogram: ";
				break;
			case EGuessStatus::WrongCharacters:
				std::cout << "\nPlease, don't type numbers or symbols: ";
				break;
			case EGuessStatus::Not_isogram:
				std::cout << "\nRemember that it's an isogram! It has all different letters: ";
				break;										//if the guess is valid the function will return it
			default: break;
		}
	} while (status != EGuessStatus::OK); //if the word is correct, the function can return the input word

	return guess;
}

bool AskToPlayAgain()
{
	std::cout << "If you want to play again, press Y" << std::endl;
	std::string playAgain = "";
	std::getline(std::cin, playAgain);
	return (playAgain[0] == 'y' || playAgain[0] == 'Y');
}

FText StringToLower(FText word)
{
	int32 i = 0;
	for (char character : word)	//range based for loop
	{
		if (character >= 64 && character <= 90) word[i] += 32;	//if the letter is upper (char value between 64 and 90), make it lower (value between 97 and 122) (adding 32 to the char value. View the ASCII table to see the values of the ASCII characters in decimal)
		i++;
	}
	//guess[i] = tolower(guess[i]); //This is also a simplier way to turn a character to lowercase, but works only with one character at a time
	return word;
}

void Defeat()
{
	std::cout << R"(Bad luck! No more attempts. The hidden word was ")" << bullCowGame.GetHiddenIsogram() << R"(")" << std::endl;
	std::cout << "\n\n-----------------------------------GAME OVER------------------------------------\n\n";
	return;
}

void SelectWordLength()
{
	int32 difficulty_choosenWordLength = 0;
	FText string_number = "0";

	std::cout << "\nHow long do you want the hidden word to be? ";

	int32 errors = 0;
	for (errors = 3; errors > 0; errors--)
	{
		std::getline(std::cin, string_number);
		if (string_number[0] >= '2' && string_number[0] <= '7') { break; }
		else
		{
			std::cout << "\nWrite a number from 2 to 7 characters to choose the length. ";
		}
	}; //if the user digits 3 times wrong length or input, the game will start with default difficulty

	if (errors > 0) //if the user digits a correct number it will be sent to the class to select an isogram word with this length
	{
		difficulty_choosenWordLength = std::stoi(string_number, 0, 10); // sTRINGtoiNT (string, first character, base of the number). Turns a string to an integer number
		bullCowGame.SelectWordLength(difficulty_choosenWordLength);
	}
	else
	{
		std::cout << "\n\n\nOverly wrong errors. I'll use the default length (" << bullCowGame.GetHiddenIsogram().length() << " letters)";
		std::cin.ignore(1024, '\n');
	}

	return;
}

void Victory()
{
	std::cout << std::endl << "Congratulations! You guessed it!\n\n";
	std::cout << "\n\n------------------------------------YOU WON-------------------------------------\n\n";
	return;
}