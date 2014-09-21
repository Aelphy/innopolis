typedef struct Team {
    char name[31];
    int scored_goals_number;
    int against_goals_number;
    int wins;
    int ties;
    int losses;
} team;

typedef struct Tournament {
    char name[100];
    int teams_number;
    team teams[30];
} tournament;

// The type of pointer to comparator function
typedef int (*comparator)(const team *, const team *);

// Downcase the input string
char* downcase(const char *str);

// Case insenitive lexicographic order comparator
int case_insenitive_lexicographic_ordr_cmpr(const team *a, const team *b);

// Fewest games played comparator
int fewest_games_played_cmpr(const team *a, const team *b);

// Most goals played comparator
int most_goals_scored_cmpr(const team *a, const team *b);

// Most goals difference comparator
int most_goal_difference_cmpr(const team *a, const team *b);

// Most wins comparator
int most_wins_cmpr(const team *a, const team *b);

// most points comparator
int most_points_cmpr(const team *a, const team *b);

// Swap elements
void swap(team *a, team *b);

// Bubble sort
void bubble_sort(team *teams, unsigned int T, comparator cmpr);

// Sort function to call one by one all comparators
void sort(tournament *tournaments);

// Output the data
void output(tournament *tournaments);

// Get data from input
int get_data(tournament **data);
