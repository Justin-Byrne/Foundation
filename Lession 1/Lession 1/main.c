// @File:       main.c
// @Project:    Street Dice
// @Author:     Justin Byrne
// @Date:       September 11, 2022
// @Copyright:  Copyright (c) 2022 Justin Byrne

#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // rand(), srand()
#include <time.h>       // time()
#include <stdbool.h>    // bool
#include <unistd.h>     // sleep()

// GLOBAL VARIABLES
char shooter[100];
char players_name[100];

int  players_funds = 0;
int  hi_low  = 0;
int  players_bet_amount;
int  players_throw_total;

int  computer_funds = 500;
int  computer_bet_amount;
int  computers_throw_total;

int  pot = 0;

bool player_is_shooter;

// FORWARD DECLARATIONS
int get_random_number   ( int MIN, int MAX );
int get_players_throw   ( void );
int get_computers_throw ( void );
int is_pot_good         ( void );

// Setters . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  //

void set_players_name ( void )
{
    printf ( "Enter Player's Name: " );
    
    // Read: input from standard in (stdin) ... %s == string
    scanf  ( "%s", players_name );                                              // Set: 'players_name' variable

    printf ( "Player's name is: " );
    printf ( "%s", players_name );                                              // Display: player's name
    printf ( "\n\n" );
}

void set_players_funds ( void )
{
    printf ( "Enter %s's Total Starting Funds: ", players_name );
    
    // Read: input from standard in (stdin) ... %d == int
    scanf  ( "%d", & players_funds );                                           // Set: 'players_funds'

    printf ( "Total funds are: " );
    printf ( "$%d", players_funds );                                            // Display: player's funds
    printf ( "\n\n" );
}

void set_hi_low ( void )
{
    printf ( "Let's Pick a Shooter !\n" );
    
    do
    {
        printf ( "%s, please choose high or low values ! \n 1 (Low) || 2 (High): ", players_name );
        
        // Read: input from standard in (stdin) ... %d == int
        scanf  ( "%d", & hi_low );                                              // Set: 'hi_low' variable
    }
    while ( hi_low < 1 || hi_low > 2 );                                         // Loop: until 'hi_low' value is not less than 1, or greater than 2

    printf ( "\n [ Player picks: " );                                           // Display pick
    
    if ( hi_low == 1 )
        printf ( "Low ]" );
    else
        printf ( "High ]" );
    
    printf ( "\n\n" );
    
    sleep ( 2 );                                                                // Sleep: for 2 seconds
}

void set_players_bet ( void )
{
    printf ( "%s's Bet !\n", players_name );                                    // Display: that it's the player's bet
    printf ( "Avaliable Funds: $%d\n", players_funds );                         // Display: player's available funds
    
    do                                                                          // Do: body operations; at least once !
    {
        printf ( "Bet Amount: " );
        
        // Read: input from standard in (stdin)
        scanf  ( "%d", & players_bet_amount );                                  // Set: 'players_bet_amount' variable
        
        if ( players_bet_amount > players_funds )                               // If: player's bet amount is greater than funds
        {
            printf ( "\n [ You don't have enough to place that bet... try again ! ] \n\n" );
        }
        
        if ( players_bet_amount < 1 )                                           // If: player's bet amount is less than 1
        {
            printf ( "\n [ You can't bet less than $1... try again ! ] \n\n" );
        }
    }
    while ( players_bet_amount <= 0 || players_bet_amount > players_funds );    // Loop: while "either" of these conditions are true
    
    printf ( "\n [ %s Bets: $%d ] \n", players_name, players_bet_amount );      // Display: player's name and bet amount
    
    sleep ( 2 );                                                                // Sleep: for 2 seconds
}

void set_computers_bet ( void )
{
    printf ( "Computer Bets !\n" );                                             // Display: that it's the computer's bet
    printf ( "Avaliable Funds: $%d", computer_funds );                          // Display: computer's available funds
    
    computer_bet_amount = 0;                                                    // Reset: computer bet amount ... to clear left over values
    
    if ( players_bet_amount > 0 )                                               // If: player's bet is set
        computer_bet_amount = players_bet_amount;                               // Match: player
    else
        computer_bet_amount = get_random_number ( 10, 20 );                     // Bet: random value between 10 - 20
    
    printf ( "\n\n [ Computer Bets: $%d ] \n", computer_bet_amount );
    
    sleep ( 2 );                                                                // Sleep: for 2 seconds
}

void set_bet_amounts ( void )
{
    printf ( "////////////////////////////////////////////////////\n\n" );
    
    if ( player_is_shooter )                                                    // If: 'is_computer_first' is '0' ... 0 == true in this case
    {
        set_players_bet ( );                                                    // PLAYER
        
        printf ( "\n Computer matches ! \n\n" );
        
        sleep ( 2 );                                                            // Sleep: for 2 seconds
        
        set_computers_bet ( );
    }
    else
    {
        set_computers_bet ( );                                                  // COMPUTER
        
        printf ( "\n >> %s, Match or Raise ? \n\n", players_name );
        
        sleep ( 2 );                                                            // Sleep: for 2 seconds
        
        set_players_bet ( );
    }
    
    printf ( "\n\n" );
    
    sleep ( 3 );                                                                // Sleep: for 3 seconds
}

void set_shooter ( void )
{
    bool no_shooter = true;
    
    while ( no_shooter )                                                        // Loop: while 'no_shooter' equals 'true'
    {
        int players_throw_total   = get_players_throw   ( );
        int computers_throw_total = get_computers_throw ( );
        
        if ( players_throw_total == computers_throw_total  )                    // Check: whetehr both throw totals are identical totals
        {
            continue;                                                           // if they are, 'continue' to get new throw totals
        }
        else
        {
            if ( hi_low == 2 )                                                  // If: 'hi_low' == High
            {
                player_is_shooter =
                    ( players_throw_total > computers_throw_total )             // If: player's total is higher
                        ? true
                        : false;

                break;
            }
            else
            {
                player_is_shooter =
                    ( players_throw_total < computers_throw_total )             // If: player's total is lower
                       ? true
                       : false;

                break;
            }
        }
        
        no_shooter = false;                                                     // Set: 'no_shooter' to false, to escape loop
    }
    
    printf ( "Shooter is: %s \n\n", ( player_is_shooter ) ? players_name : "Computer" );
    
    sleep ( 3 );                                                                // Sleep: for 3 seconds
}

// Getters . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  //

int get_random_number ( int MIN, int MAX )
{
    int result = ( rand ( ) % ( MAX - MIN + 1 ) ) + MIN;                        // Generate: random value and store it in result
    
    return result;                                                              // Return: 'result' to caller
}

int get_pot_amount ( void )
{
    if ( is_pot_good ( ) == false )
    {
        while ( players_bet_amount != computer_bet_amount )                     // While: uneven pot
        {
            if ( players_bet_amount > computer_bet_amount )                     // If: player bets more
            {
                computer_bet_amount = players_bet_amount;                       // Computer automatically matches
            }
            else                                                                // If: computer bets more
            {
                while ( players_bet_amount < computer_bet_amount )              // Player can match or raise
                {
                    printf ( "////////////////////////////////////////////////////\n\n" );
                    
                    printf ( "Computer bet: $%d \n", computer_bet_amount );
                    printf ( "%s bet: $%d \n\n", players_name, players_bet_amount );
                    printf ( "Match or Raise ?: \n" );
                
                    printf ( "Amount to add to bet: " );
                
                    int additional_bet = 0;                                     // Declare: 'additional_bet' variable, and set to 0
                
                    scanf  ( "%d", &additional_bet );                           // Read: input from standard in (stdin)
                
                    players_bet_amount = players_bet_amount + additional_bet;   // Set: 'players_bet_amount' as it's value plus 'additional_bet'
                }
            }
        }
    }
    
    return players_bet_amount;                                                  // Return: 'players_bet_amount' to caller
}

int get_players_throw ( void )
{
    int players_throws[2];                                                      // Declare: variable for 2 throws
    
    players_throws[0] = get_random_number ( 1, 6 );                             // Set: first throw
    players_throws[1] = get_random_number ( 1, 6 );                             // Set: second throw
    
    players_throw_total = players_throws[0] + players_throws[1];                // Set: total of first and second throws
    
    // Display results
    printf ( " %s's throw: [%d] [%d] ... total: %d \n\n", players_name, players_throws[0], players_throws[1], players_throw_total );
    
    return players_throw_total;                                                 // Return: player's throw total
}

int get_computers_throw ( void )
{
    int computer_throws[2];                                                     // Declare: variable for 2 throws
    
    computer_throws[0] = get_random_number ( 1, 6 );                            // Set: first throw
    computer_throws[1] = get_random_number ( 1, 6 );                            // Set: second throw
    
    computers_throw_total = computer_throws[0] + computer_throws[1];            // Set: total of first and second throws
    
    // Display results
    printf ( " %s's throw: [%d] [%d] ... total: %d \n\n", "Computer", computer_throws[0], computer_throws[1], computers_throw_total );
    
    return computers_throw_total;                                               // Return: computer's throw total
}

// Display . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  //

void display_players_pick ( void )
{
    printf ( "////////////////////////////////////////////////////\n\n" );
    
    if ( hi_low == 1 )                                                          // If: 'hi_low' equals 1 ... display 'Low'
        printf ( "%s picked: Low", players_name );
    else
        printf ( "%s picked: High", players_name );
    
    printf ( "\n\n" );
    
    sleep ( 3 );                                                                // Sleep: for 3 seconds !
}

void display_round_info ( int round_number )
{
    printf ( "////////////////////////////////////////////////////\n\n" );
    
    printf ( "Round: %d \n", round_number );                                    // Display: round number
    printf ( "Pot is: $%d \n\n", pot );                                         // Display: pot amount
    
    if ( player_is_shooter )                                                    // If: player is shooter
        printf ( "%s is the shooter ! \n\n", players_name );                    // PLAYER
    else
        printf ( "Computer is the shooter ! \n\n" );                            // COMPUTER
    
    sleep ( 3 );                                                                // Sleep: for 3 seconds !
}

// Validators . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . //

int is_pot_good ( void )
{
    int result = 0;                                                             // Declare: 'result' variable, and set to 0
    
    if ( players_bet_amount == computer_bet_amount )                            // If: player's bet equals computer's bet
        result = 1;                                                             // Set: 'result' to 1 ... typically equals 'true'
    else
        result = 0;                                                             // Set: 'result' to 0 ... typically equals 'false'
    
    return result;                                                              // Return: 'result' value to caller
}

int is_win_by_pass ( int throw_total )
{
    int result = 0;                                                             // Declare: 'result' variable, and set to 0 ...  equals 'false'
    
    int pass_values[2] = { 7, 11 };                                             // Set: pass values
    
    for ( int i = 0; i < 2; i++ )                                               // Loop: twice
    {
        if ( throw_total == pass_values[i] )                                    // Check: pass values
        {
            result = 1;                                                         // Set: result as 1 ... equals to 'true'
            
            break;
        }
    }
    
    return result;                                                              // Return: 'result' value to caller
}

int is_loss_by_crap ( int throw_total )
{
    int result = 0;                                                             // Declare: 'result' variable, and set to 0 ... equals 'false'
    
    int crap_values[3] = { 2, 3, 12 };                                          // Set: crap values
    
    for ( int i = 0; i < 3; i++ )                                               // Loop: thrice
    {
        if ( throw_total == crap_values[i] )                                    // Check: crap values
        {
            result = 1;                                                         // Set: result as 1 ... equals to 'true'
            
            break;
        }
    }
    
    return result;                                                              // Return: 'result' value to caller
}

// Misc . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . //

void distribute_funds_to_player ( bool choice )
{
    if ( choice )                                                               // If: 'choice' is 'true', distribute funds to player
    {
        players_funds  = players_funds  + pot;
        computer_funds = computer_funds - pot;
    }
    else
    {
        players_funds  = players_funds  - pot;
        computer_funds = computer_funds + pot;
    }
    
    players_bet_amount = computer_bet_amount = 0;                               // Reset: bet amounts
    
    if ( player_is_shooter )                                                    // Switch: players
        player_is_shooter = false;
    else
        player_is_shooter = true;
}

int point = 0;

void throw_dice ( void )
{
    while ( true )
    {
        if ( player_is_shooter )                                                // If: 'player_is_shooter' == true
        {
            if ( point == 0 )
            {
                players_throw_total = get_players_throw ( );                    // Get: player's throw total
                
                if ( is_win_by_pass ( players_throw_total ) )                   // If: player's throw total is a pass ... they win !
                {
                    printf ( " * %s passed ! *", players_name );
                    
                    printf ( " [ %s is winner ! ]\n\n", players_name );

                    distribute_funds_to_player ( true );
                    
                    break;
                }
            
                if ( is_loss_by_crap ( players_throw_total ) )                  // If: player's throw total is a crap ... they loose !
                {
                    printf ( " ~ %s crapped out ! ~", players_name );
                    
                    printf ( " [ %s is winner ! ]\n\n", "Computer" );
                    
                    distribute_funds_to_player ( false );
                    
                    break;
                }
            
                point = players_throw_total;
            }
            else
            {
                printf ( "Point is %d \n\n", point );
                
                players_throw_total = get_players_throw ( );                    // Get: player's throw total
                
                if ( players_throw_total == 7 )                                 // If: player's throw total is a crap ... they loose !
                {
                    printf ( " ~ %s crapped out ! ~", players_name );
                    
                    printf ( " [ %s is winner ! ]\n\n", "Computer" );
                    
                    distribute_funds_to_player ( false );
                    
                    point = 0;                                                  // Reset: point
                    
                    break;
                }
                
                if ( players_throw_total == point )                             // If: player's throw total matches point ... they win !
                {
                    printf ( " * %s passed ! *", players_name );
                    
                    printf ( " [ %s is winner ! ]\n\n", players_name );

                    distribute_funds_to_player ( true );
                    
                    point = 0;                                                  // Reset: point
                    
                    break;
                }
            }
            
            sleep ( 3 );                                                        // Sleep: for 3 seconds
        }
        else
        {
            if ( point == 0 )
            {
                computers_throw_total = get_computers_throw ( );                // Get: computer's throw total
                
                if ( is_win_by_pass ( computers_throw_total ) )                 // If: computer's throw total is a pass ... they win !
                {
                    printf ( " * %s passed ! *", "Computer" );
                    
                    printf ( " [ %s is winner ! ]\n\n", "Computer" );

                    distribute_funds_to_player ( false );
                    
                    break;
                }
            
                if ( is_loss_by_crap ( computers_throw_total ) )                // If: computer's throw total is a crap ... they loose !
                {
                    printf ( " ~ Computer crapped out ! ~");
                    
                    printf ( " [ %s is winner ! ]\n\n", players_name );
                    
                    distribute_funds_to_player ( true );
                    
                    break;
                }
            
                point = computers_throw_total;
            }
            else
            {
                printf ( "Point is %d \n\n", point );
                
                computers_throw_total = get_computers_throw ( );                // Get: computer's throw total
                
                if ( computers_throw_total == 7 )                               // If: computer's throw total is a crap ... they loose !
                {
                    printf ( " ~ Computer crapped out ! ~");
                    
                    printf ( " [ %s is winner ! ]\n\n", players_name );
                    
                    distribute_funds_to_player ( true );
                    
                    point = 0;                                                  // Reset: point
                    
                    break;
                }
                
                if ( computers_throw_total == point )                           // If: computer's throw total matches point ... they win !
                {
                    printf ( " * %s passed ! *", "Computer" );
                    
                    printf ( " [ %s is winner ! ]\n\n", "Computer" );

                    distribute_funds_to_player ( false );
                    
                    point = 0;                                                  // Reset: point
                    
                    break;
                }
            }
            
            sleep ( 3 );                                                        // Sleep: for 3 seconds
        }
    }
}

// Main . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . //

int main ( int argc, const char * argv[] )
{
    // INITIALIZE
    set_players_name  ( );
    set_players_funds ( );
    set_hi_low  ( );

    srand ( time ( 0 ) );                                                       // Seed randomizer

    // IDENTIFY THE SHOOTER
    display_players_pick ( );
    set_shooter  ( );

    // ROUND(S)
    int round = 1;

    bool game_loop = true;
    
    while ( game_loop )                                                         // Core game loop !
    {
        set_bet_amounts ( );
        pot = get_pot_amount ( );
        
        display_round_info ( round );
        
        throw_dice ( );
        
        if ( computer_funds < 1 || players_funds < 1 )                          // If: either player has no mor funds, game over !
        {
            game_loop = false;                                                  // Trip: game loop
            
            printf ( "////////////////////////////////////////////////////\n\n"
                    "Sorry, end of game ! \n\n [ %s ran out of money ! ] ",
                    ( players_funds < 1 )
                        ? players_name
                        : "Computer"
                    );
            printf( "\n\n////////////////////////////////////////////////////" );
        }

        round++;                                                                // Advance: round
    }
    
    return 0;
}

// STREET DICE
    // INITIALIZE
        // SET PLAYER'S NAME
        // SET PLAYER'S TOTAL FUNDS
    // ACTION
        // IDENTIFY THE SHOOTER
            // SET PLAYER'S PICK FOR HI or LOW
            // THROW DICE
            // IDENTIFY WHO'S THE SHOOTER || HI vs. LOW
        // ROUND(S)
            // SET PLAYER'S BET AMOUNT
                // MATCH OR RAISE
            // IF ( PLAYER'S ROLL == [ 7, 11 ] )
                // PLAYER WINS POT
            // IF ( PLAYER'S ROLL == [ 2, 3, 12 ] )
                // PLAYER LOOSES POT
            // ELSE
                // PLAYER GET'S A POINT | FROM VALUE ROLLED
                // ROLL AGAIN
                    // IF ( PLAYER ROLLS SAME AS POINT ( VALUE ROLLED )
                        // PLAYER WINS POT
                    // IF ( PLAYER ROLLS A 7 )
                        // PLAYER LOOSES POT
            // DISTRIBUTE FUNDS
            // DICE SWITCH
            // NEW ROUND !
                

// TERMINOLOGY
    // SHOOTER:   PLAYER WHO ROLLS DICE
    // COME OUT:  INIITIAL ROLL
    // PASS:      ROLL 7, or 11 ON THE COME OUT
    // CRAP:      ROLL 2, 3, or 12 ON THE COMEOUT
    // POINT:     ANY VALUE BETWEEN 4 and 10 ROLLED ON THE COME OUT
    // SEVEN OUT: ROLL 7 PRIOR TO ROLLING A POINT
