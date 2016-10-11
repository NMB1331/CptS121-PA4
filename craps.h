//Guard code
#define CRAPS_H

//Library inclusions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constant definitions
#define MINIMUM_BET 10.0

//Function prototypes
/*************************************************************
* Function: want_to_play                                    *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Asks the user if they want to play           *
* Input parameters: None                                    *
* Returns: 1 if they want to play, 0 if they don't          *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void want_to_play(char *play_again);

/*************************************************************
* Function: print_game_rules                                *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Prints the rules of craps                    *
* Input parameters: None                                    *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void print_game_rules(void);

/*************************************************************
* Function: get_bank_balance                                *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Gets player's total amount of money          *
* Input parameters: None                                    *
* Returns: double balance                                   *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
double get_bank_balance(void);

/*************************************************************
* Function: get_wager_amount                                *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Prompts the user for a wager                 *
* Input parameters: None                                    *
* Returns: double wager;                                    *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
double get_wager_amount(void);

/*************************************************************
* Function: point_rolls_get_wager_amount                    *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Prompts the user for a wager (min 10 first time around, adds after that)
* Input parameters: Integer counter, pointer to balance     *
* Returns: double wager;                                    *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
double point_rolls_get_wager_amount(int counter, double *balance_ptr);

/*************************************************************
* Function: check_wager_amount                              *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Checks if the wager is less than the total   *
* Input parameters: double wager, double balance;           *
* Returns: 1 if valid bet, 0 if not                         *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int check_wager_amount(double wager, double balance);

/*************************************************************
* Function: roll_die                                        *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Simulates a dice rolling (random int, 1-6)   *
* Input parameters: None                                    *
* Returns: Sudo-random integer, 1-6                         *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int roll_die(void);

/*************************************************************
* Function: calculate_sum_dice                              *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Calculates the sum of 2 rolled die           *
* Input parameters: 2 die values (integers)                 *
* Returns: The integer sum of the 2 die values              *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int calculate_sum_dice(int die1, int die2);

/*************************************************************
* Function: is_win_loss_or_point                            *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Calculates the result of the first roll      *
* Input parameters: Integer sum of 2 rolled die             *
* Returns: 1 if sum = 7 or 11, 0 if 2,3,12, -1 otherwise    *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int is_win_loss_or_point(int sum_die);

/*************************************************************
* Function: is_point_loss_or_neither                        *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Determines the result of every other roll    *
* Input parameters: Integer die sum, integer point value    *
* Returns: 1 if sum = point_value, 0 if sum = 7, else -1    *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int is_point_loss_or_neither(int die_sum, int *point_ptr);

/*************************************************************
* Function: adjust_bank_balance                             *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Adjusts the bank balance after a round       *
* Input parameters: Double bank balance, double wager, int add or subtract
* Returns: The adjusted bank balance (double)               *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
//note: Not used, since my program uses pointers instead
double adjust_bank_balance(double bank_balance, double wager, int add_or_subtract);

/*************************************************************
* Function: chatter_messges                                 *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Tell's the user what's happening in the game *
* Input parameters: A bunch of crap (look at the prototype) *
* Returns: Prints a message to the user                     *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void chatter_messges(int die1, int die2, int sum_die, int *point_ptr);

/*************************************************************
* Function: first_roll                                      *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Plays the first roll                         *
* Input parameters: Pointers to the balance and point value *
* Returns: 1 if win/loss, 0 if moving on to point round     *
* Preconditions: calculate_sum_dice and is_win_loss_or_point
                 must be defined
* Postconditions: None                                      *
*************************************************************/
int first_roll(double *balance_ptr, int *point_ptr);

/*************************************************************
* Function: point_rolls                                     *
* Date Created: 10/02/2016                                  *
* Date Last Modified: 10/02/2016                            *
* Description: Plays any rolls after the first              *
* Input parameters: Pointers to the balance and point value *
* Returns: 1 if win/loss, 0 if moving on to point round     *
* Preconditions: calculate_sum_dice and is_point_loss_or_neither
                 must be defined
* Postconditions: None                                      *
*************************************************************/
void point_rolls(double *balance_ptr, int *point_ptr);
