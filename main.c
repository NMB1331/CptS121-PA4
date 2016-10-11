#include "craps.h"
#include "craps_functions.c"

//TO DO:
//-Code the last of the dumb mandatory functions
//-Touch things up- make it look pretty


int main(void) {
	//"Global" variables initialized; seed created for rand()
	char want_to_play_again = 'y', *play_again_ptr = &want_to_play_again;
	double balance = 0, *balance_ptr = &balance;
	int point = 0, *point_ptr = &point;
	int first_roll_result = 0;
	srand((unsigned int)(time NULL));

	//Initial information entered; rules printed
	print_game_rules();
	printf("\n");
	balance = get_bank_balance();

	do {
  	//First roll performed
		first_roll_result = first_roll(balance_ptr, point_ptr);

		//Point rolls performed
		if (!first_roll_result) {
			point_rolls(balance_ptr, point_ptr); }
		//Determines if the user has the funds/wants to play again
		if (balance >= 10.0) {
			printf("Your balance is now %.2lf\n", balance);
			want_to_play(play_again_ptr); }
		else {
			printf("Sorry! You're out of money...\n");
			break; }

	} while (want_to_play_again == 'y' && balance >= 10.0);
	//Thanks the user for playing
	printf("Thanks for playing! You're walking away with %.2lf dollars!\n", balance);
	return 0;
}
