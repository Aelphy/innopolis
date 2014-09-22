/*
 ============================================================================
 Name        : hw1
 Author      : Usvyatsov Mikhail
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hw1.h"

unsigned int N = 0;

char* downcase(const char *str) {
    int i;
    char *str2 = (char*)malloc(31 * sizeof(char));

    strcpy(str2, str);

    for(i = 0; str2[i]; i++) { str2[i] = tolower(str2[i]); }

    return str2;
}

// It was tested by giving team names with anti right order with capital and litaral way
int case_insenitive_lexicographic_ordr_cmpr(const team *a, const team *b) {
    char *lowA = downcase(a->name);
    char *lowB = downcase(b->name);

    int val = strcmp(lowA, lowB);

    free(lowA);
    free(lowB);

    return -val;
}

// It was tested by general test with Brazil
int fewest_games_played_cmpr(const team *a, const team *b) {
    return ((b->wins + b->losses + b->ties) - (a->wins + a->losses + a->ties));
}

// It was tested by special test case with two teams and different score
int most_goals_scored_cmpr(const team *a, const team *b) {
    return (a->scored_goals_number - b->scored_goals_number);
}

// It was tested with special test case included three teams with equal number of wins
int most_goal_difference_cmpr(const team *a, const team *b) {
    return((a->scored_goals_number - a->against_goals_number) - (b->scored_goals_number - b->against_goals_number));
}

// It was tested by general test with Brazil
int most_wins_cmpr(const team *a, const team *b) {
    return(a->wins - b->wins);
}

// It was tested with general test with Brazil
int most_points_cmpr(const team *a, const team *b) {
    return((a->wins * 3 + a->ties) - (b->wins * 3 + b->ties));
}

void swap(team *a, team *b) {
    team buff = *a;

    *a = *b;
    *b = buff;
}

void bubble_sort(team *teams, unsigned int T, comparator cmpr) {
    int i;
    int sorted = 0;

    while (!sorted)	{
        sorted = 1;
        for (i = 0; i < T - 1; ++i) {
            if (cmpr(&teams[i], &teams[i+1]) < 0) {
                swap(&teams[i], &teams[i+1]);
                sorted = 0;
            }
        }
    }

}

void sort(tournament *tournaments) {
    int i;

    for(i = 0; i < N; ++i) {
        bubble_sort(tournaments[i].teams, tournaments[i].teams_number, case_insenitive_lexicographic_ordr_cmpr);
        bubble_sort(tournaments[i].teams, tournaments[i].teams_number, fewest_games_played_cmpr);
        bubble_sort(tournaments[i].teams, tournaments[i].teams_number, most_goals_scored_cmpr);
        bubble_sort(tournaments[i].teams, tournaments[i].teams_number, most_goal_difference_cmpr);
        bubble_sort(tournaments[i].teams, tournaments[i].teams_number, most_wins_cmpr);
        bubble_sort(tournaments[i].teams, tournaments[i].teams_number, most_points_cmpr);
    }
}

void output(tournament *tournaments) {
    int i, j;
    FILE *f = fopen("out.txt", "w");

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0; i < N; ++i) {
        fprintf(f, "%s\n", tournaments[i].name);

        for(j = 0; j < tournaments[i].teams_number; ++j) {
            fprintf(f, "%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                    j + 1,
                    tournaments[i].teams[j].name,
                    tournaments[i].teams[j].wins * 3 + tournaments[i].teams[j].ties,
                    tournaments[i].teams[j].wins + tournaments[i].teams[j].losses + tournaments[i].teams[j].ties,
                    tournaments[i].teams[j].wins,
                    tournaments[i].teams[j].ties,
                    tournaments[i].teams[j].losses,
                    tournaments[i].teams[j].scored_goals_number - tournaments[i].teams[j].against_goals_number,
                    tournaments[i].teams[j].scored_goals_number,
                    tournaments[i].teams[j].against_goals_number);
        }
    }

    fclose(f);
}

/*
This function parses input file and inititalizes structures.
It was tested by various input data.
*/
int get_data(tournament **data) {
    FILE *fp;
    int i, j, k, g;
    int team1_goals, team2_goals;
    char game[67];
    char team1_name[31], team2_name[31];
    char goals[4];
    char *substr;
    unsigned int T = 0;
    unsigned int G = 0;

    // open file
    // if there is no input file then exit with error code
    if ((fp = fopen("in.txt", "r")) == NULL) {
        printf("File opening error.\n");
        exit(1);
    }

    // assign N
    // if there is no N in input file then exit with error code
    if (fscanf(fp, "%d", &N) != 1) {
        printf("Cannot read N. File read error.\n");
        exit(1);
    }

    // check N
    // check that N has valid value
    if (!(N > 0 && N < 1000)) {
        printf("N is wrong.\n");
        exit(1);
    }

    // define tournaments
    tournament *tournaments = (tournament*)malloc(N * sizeof(tournament));

    // fill tournaments
    for(i = 0; i < N; ++i) {
        // assign toruanment's name
        // check that toruanment's name is 100 symbols length
        if (fscanf(fp, " %100[^\n]", tournaments[i].name) != 1) {
            printf("File read error.\n");
            exit(1);
        }

        // assign T
        // if there is no T in input file then exit with error code
        if (fscanf(fp, "%d", &T) != 1) {
            printf("Cannot read T. File read error.\n");
            exit(1);
        }

        // check T
        // check that T has valid value
        if (!(T > 1 && T <= 30)) {
            printf("T is wrong.\n");
            exit(1);
        }

        tournaments[i].teams_number = T;

        // assign teams
        for(j = 0; j < T; ++j) {
            // assign team's name
            // check that team's name is 30 symbols length
            if (fscanf(fp, " %30[^\n]", tournaments[i].teams[j].name) != 1) {
                printf("File read error.\n");
                exit(1);
            }

            // initilize values of team
            tournaments[i].teams[j].scored_goals_number = 0;
            tournaments[i].teams[j].against_goals_number = 0;
            tournaments[i].teams[j].wins= 0;
            tournaments[i].teams[j].ties = 0;
            tournaments[i].teams[j].losses = 0;
        }

        // assign G
        // if there is no G in input file then exit with error code
        if (fscanf(fp, "%d", &G) != 1) {
            printf("File read error.\n");
            exit(1);
        }

        // check G
        // check that G has valid value
        if (!(G <= 1000)) {
            printf("G is wrong.\n");
            exit(1);
        }

        // process games
        for(k = 0; k < G; ++k) {
            // assign game
            // check that game is 30 symbols length
            if (fscanf(fp, " %30[^\n]", game) != 1) {
                printf("File read error.\n");
                exit(1);
            }

            /* ATTANTION: strtok is not very good function
              It remebers the current position in the string, so it is bad idea to use it in multy-thred applications
              moreover it means that we have to parse the string by first separator and only after that start parsing
              by second separator.
            */
            // parse game string by '#' symbol
            substr = strtok(game, "#");
            strcpy(team1_name, substr);
            substr = strtok(NULL, "#");
            strcpy(goals, substr);
            substr = strtok(NULL, "#");
            strcpy(team2_name, substr);

            // parse gols substring by '@' symbol
            substr = strtok(goals, "@");
            team1_goals = atoi(substr);
            substr = strtok(NULL, "@");
            team2_goals = atoi(substr);

            // process score
            for (g = 0; g < G; ++g) {
                // chack that team didn't play with itself
                if (strcmp(team1_name, team2_name) != 0) {
                    if (strcmp(tournaments[i].teams[g].name, team1_name) == 0) {
                        tournaments[i].teams[g].scored_goals_number += team1_goals;
                        tournaments[i].teams[g].against_goals_number += team2_goals;

                        if (team1_goals > team2_goals) {
                            tournaments[i].teams[g].wins += 1;
                        } else if (team1_goals == team2_goals) {
                            tournaments[i].teams[g].ties += 1;
                        } else {
                            tournaments[i].teams[g].losses += 1;
                        }
                    } else if (strcmp(tournaments[i].teams[g].name, team2_name) == 0) {
                        tournaments[i].teams[g].scored_goals_number += team2_goals;
                        tournaments[i].teams[g].against_goals_number += team1_goals;

                        if (team2_goals > team1_goals) {
                            tournaments[i].teams[g].wins += 1;
                        } else if (team1_goals == team2_goals) {
                            tournaments[i].teams[g].ties += 1;
                        } else {
                            tournaments[i].teams[g].losses += 1;
                        }
                    }
                } else {
                    printf("Wrong game string.\n");
                    exit(1);
                }
            }
        }
    }

    fclose(fp);

    *data = tournaments;

    return 0;
}

int main(void) {
    tournament *tournaments;

    get_data(&tournaments);
    sort(tournaments);
    output(tournaments);

    free(tournaments);

    return 0;
}
