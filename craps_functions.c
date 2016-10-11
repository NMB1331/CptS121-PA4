#include "craps.h"

//Function that prompts the user if they want to play
void want_to_play(char *play_again) {
	char play = '\0';
	while (play == '\0') {
		//system("cls");
		printf("Do you want to play a game of craps? [Y/N] ");
		scanf(" %c", &play);
		if (play == 'Y' || play == 'y') {
			*play_again = 'y';
			break; }

		else if (play == 'N' || play == 'n') {
			*play_again = 'n';
			break; }

		else {
			play = '\0'; }
	}
}

//Function that prints the game rules
void print_game_rules(void) {
	printf("Welcome to craps! It works like this:\n");
	printf("First you enter the amount of money you have to play with.\n");
	printf("Next, you make a bet (minimum 10 dollars.)\n");
	printf("After that, the fun begins! The dice are rolled, and the sum is displayed.\n");
	printf("For the first roll, if you roll a 7 or 11, you win even money! If you roll a 2,3, or 12, you lose even money.\n");
	printf("If you roll anything else, that sum becomes your point.\n");
	printf("Now you roll and bet until you get your point, or a 7. You win if you get your point. But if you roll a 7...you lose!\n");
	printf("It's important to know that your bets compound in this section. So if you don't want to bet any more, enter zero.\n");
	printf("At the end of this turn, you'll be prompted to play again, provided you have enough money. Good luck!\n");
}

//Function that gets the user's starting balance
double get_bank_balance(void) {
	double balance = 0.0;
	while (balance < MINIMUM_BET || balance > 500) {
		printf("Enter your starting balance (min 10, max 500): ");
		scanf("%lf", &balance);
	}
	return balance;
}

//Function that gets the wager amount
double get_wager_amount(void) {
	double wager = 0.0;
	while (wager < MINIMUM_BET || wager > 500) {
		printf("Enter the wager for this roll (min 10): ");
		scanf("%lf", &wager);
	}
	return wager;
}

//Function that gets the wager for the point rolls (Minimum bet of 10 the first time, 0 after that; wager compounds every prompt)
double point_rolls_get_wager_amount(int counter, double *balance_ptr) {
	double wager = 0;
	if (counter == 0) {
		wager = get_wager_amount();
		while (! check_wager_amount(wager, *balance_ptr)) {
			wager = get_wager_amount();
		}
	}
	else {
		do {
			printf("Enter a wager for this roll\n");
			printf("NOTE: Wager compounds. If you do not wish to increase your wager, enter zero: ");
			scanf("%lf", &wager);
		} while (wager >= *balance_ptr);

	}
	return wager;
	}

//Function that checks if a wager is valid
int check_wager_amount(double wager, double balance) {
	if (wager > balance || wager < MINIMUM_BET) { return 0; }
	else { return 1; }
}

//Function that simulates a dice rolling
int roll_die(void) {
	int die_value = 0;
	die_value = rand();
	return die_value % 6 + 1;
}

//Function that calculates the sum of 2 rolled die_value
int calculate_sum_dice(int die1, int die2) {
	int sum = die1 + die2;
	return sum;
}

//Function that determines the result of the first roll
int is_win_loss_or_point(int sum_die) {
	if (sum_die == 7 || sum_die == 11) {
		printf("Congrats! You win!\n");
		return 1;
	}
	else if (sum_die == 2 || sum_die == 3 || sum_die == 12) {
		printf("Craps! Sorry, you lose...\n");
		return 0;
	}
	else {
		printf("The point value is now %d\n", sum_die);
		return -1;
	}
}

//Function that determines the result of point rolls
int is_point_loss_or_neither(int sum_die, int *point_ptr) {
	if (sum_die == *point_ptr) {
		return 1;
	}
	else if (sum_die == 7) {
		return 0;
	}
	else {
		return -1;
	}
}

//Function that updates player
void chatter_messges(int die1, int die2, int sum_die, int *point_ptr) {
	printf("You rolled a %d and %d\n", die1, die2);
	printf("The sum is %d, and the point value is %d\n", sum_die, *point_ptr);
}


//Function that plays the first roll
int first_roll(double *balance_ptr, int *point_ptr) {
	//Variables initialized
	int die1 = 0, die2 = 0, first_roll_result = 0, first_sum = 0;
	double wager = 0;
	//User prompted for wager
	wager = get_wager_amount();
	while (! check_wager_amount(wager, *balance_ptr)) {
		wager = get_wager_amount();
	}

	//First roll performed; result calculated
	die1 = roll_die();
	die2 = roll_die();
	first_sum = calculate_sum_dice(die1, die2);
	printf("You rolled a %d and %d\n", die1, die2);
	printf("The sum is %d\n", first_sum);
	first_roll_result = is_win_loss_or_point(first_sum);

	//Determines whether or not a point round is necessary
	if (first_roll_result == 1) {
		*balance_ptr += wager;
		printf("Hell yeah! You won %.2lf dollars! Your balance is now %.2lf!\n", wager, *balance_ptr);
		return 1; }

	else if (first_roll_result == 0) {
		*balance_ptr -= wager;
		printf("Damn, sorry! You lost %.2lf dollars! Your balance is now %.2lf!\n", wager, *balance_ptr);
		return 1; }

	else {
		*point_ptr = first_sum;
		printf("Neither a win or a loss! It's time for the point round! The point is %d\n", *point_ptr);
		return 0; }
}

//Determines the result of any roll after the first one
void point_rolls(double *balance_ptr, int *point_ptr) {
	//Variables initialized
	int die1 = 0, die2 = 0, sum_die = 0, counter = 0, is_win_or_loss = -1;
	double wager = 0;
	//Proceeds rolling and betting until win or loss
	do {
		//Wager made
		wager += point_rolls_get_wager_amount(counter, balance_ptr);

		//Rolls and sums the die
		die1 = roll_die();
		die2 = roll_die();
		sum_die = calculate_sum_dice(die1, die2);

		//Updates the terminal with the result of the roll
		chatter_messges(die1, die2, sum_die, point_ptr);

		//Loop conditionals updated
		is_win_or_loss = is_point_loss_or_neither(sum_die, point_ptr);
		counter ++;
	} while (is_win_or_loss == -1);

	//Evaluates if the player won or lost; updates balance
	if (is_win_or_loss == 1) {
		printf("Congratulations! You won %.2lf dollars!\n", wager);
		*balance_ptr += wager;
		*point_ptr = 0;
	}
	else if (is_win_or_loss == 0) {
		printf("Damn! You lost %.2lf dollars....\n", wager);
		*balance_ptr -= wager;
		*point_ptr = 0;
	}
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
