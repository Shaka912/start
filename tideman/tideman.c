#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i= 0; i<candidate_count; i++)
    {
        if(strcmp(candidates[i], name)==0)
        {
            ranks[i] = i;
            for(int j=0; j<candidate_count; j++)
            {
                return true;
            }
        }

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int voter = 0;
    for(int i=0; i<candidate_count; i++)
    {
        for(int j = i+1; j< candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pair=0;
    for(int i =0; i< candidate_count; i++)
    {
        for(int j = 1; j< candidate_count; j++)
        {
            if( preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner =i;
                pairs[pair_count].loser =j;
                pair_count++;
            }
        }
    }
    return;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for(int i=0; i< pair_count -1; i++) // or maybe pair_count
    {
        pair swap;
        int min = 0;
        min = i;
        for( int j =i+1 ; j< pair_count; j++) // or maybe pairs[i].winner
        {
            int a = preferences[pairs[i].winner][pairs[i].loser]- preferences[pairs[i].loser][pairs[i].winner];
            int b = preferences[pairs[j].winner][pairs[j].loser]- preferences[pairs[j].loser][pairs[j].winner];
            if( a < b )//pairs[i].winner - pairs[i].loser > pairs[j].winner - pairs[j].loser
            {
                min = j;
            }
        }
        //swap pairs with correct positions
        if ( min != i)
        {
            swap = pairs[i];
            pairs[i] =pairs[i+1];
            pairs[i+1] = swap;
        }
    }
    return;
}
bool is_cycle(int winner, int loser);
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i =0; i<pair_count; i++)
    {
        if(is_cycle(pairs[i].winner, pairs[i].loser)==false)
        {
            locked[pairs[i].winner][pairs[i].loser] =true;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] =false;
        }
    }
    return;
}
bool is_winner(int winner, int loser);
// Print the winner of the election
void print_winner(void)
{
    bool winner;
    int can_index =0;
   //to print the winnner first we neeed to find the source of th lockedi,j graph
    //to find the source first we will iterate over every locked i,j pair and check if there is any candidate who doesnt
    // have any locked edge over him. or who has no arrows pointing at them
    for(int i =0; i< candidate_count; i++)
    {
        winner = true;
        for(int j =0; j<candidate_count; j++)
        {
            if(locked[j][i]== true)
            {
                winner =false;
                break;
            }
        }
        if(winner ==true)
        {
            can_index =i;
            break;
        }
    }
    if(winner ==true)
    {
        printf("%s\n", candidates[can_index]);
    }
    return;
}
bool is_cycle(int winner, int loser)
{
    //base case
    if( winner == loser)
    {
        return true;
    }
    // first we will check if a loser is winning in another pair
    for(int i =0; i< pair_count; i++)
    {
        if(pairs[i].winner == loser && locked[pairs[i].winner][pairs[i].loser]==true)
        {
            if(pairs[i].loser == winner)
            {
                return true;
            }
            else
            {
                if(is_cycle(winner, pairs[i].loser)== true)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool is_winner(int winner, int loser)
{
    //base case
    if( winner == loser)
    {
        return true;
    }
    // first we will check if a loser is winning in another pair
    for(int i =0; i< pair_count; i++)
    {
        if(pairs[i].winner != loser && locked[pairs[i].winner][pairs[i].loser]==false)
        {
            if(pairs[i].loser != winner)
            {
                return true;
            }
            else
            {
                if(is_cycle(winner, pairs[i].loser)== false)
                {
                    return true;
                }
            }
        }
    }
    return false;
}