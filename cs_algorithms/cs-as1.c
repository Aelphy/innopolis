/*
 ============================================================================
 Name        : cs-as1.c
 Author      : Aelphy
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Team {
	char name[30];
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

unsigned int N = 0;

typedef int (*comparator)(const team *, const team *);

char* downcase(const char *str) {
	int i;
	char *str2 = calloc(30, sizeof(char));

	strcpy(str2, str);

	for(i = 0; str2[i]; i++) {
	  str2[i] = tolower(str2[i]);
	}

	return str2;
}

int case_insenitive_lexicographic_ordr_cmpr(const team *a, const team *b) {
	return strcmp(downcase(a->name), downcase(b->name));
}

int fewest_games_played_cmpr(const team *a, const team *b) {
	return ((b->wins + b->losses + b->ties) - (a->wins + a->losses + a->ties));
}

int most_goals_scored_cmpr(const team *a, const team *b){
	return (a->scored_goals_number - b->scored_goals_number);
}

int most_goal_difference_cmpr(const team *a, const team *b){
	return((a->scored_goals_number - a->against_goals_number) - (b->scored_goals_number - b->against_goals_number));
}

int most_wins_cmpr(const team *a, const team *b) {
	return(a->wins - b->wins - 1);
}

int most_points_cmpr(const team *a, const team *b) {
	return((a->wins * 3 + a->ties) - (b->wins * 3 + b->ties));
}

void swap(team *a, team *b){
	team buff = *a;

	*a = *b;
	*b = buff;
}

void bubble_sort(team *teams, unsigned int T, comparator cmpr) {
	int i, j;

	for(i = 0; i < T; ++i) {
		for(j = 0; j < T; ++j) {
			if (cmpr(&teams[i], &teams[j]) > 0) {
				swap(&teams[i], &teams[j]);
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

	for(i = 0; i < N; ++i) {
		printf("%s\n", tournaments[i].name);

		for(j = 0; j < tournaments[i].teams_number; ++j) {
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
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

		printf("\n");
	}
}

int get_data(tournament **data) {
	FILE *fp;
	int i, j, k, g;
	int team1_goals, team2_goals;
	char game[67];
	char team1_name[30], team2_name[30];
	char goals[4];
	char *substr;
	unsigned int T = 0;
	unsigned int G = 0;

	// open file
	if ((fp = fopen("data.txt", "r")) == NULL) {
		printf("File opening error.\n");
		exit(1);
	}

	// assign N
	if (fscanf(fp, "%d", &N) != 1) {
		printf("File read error.\n");
		exit(1);
	}

	// check N
	if (N > 0 && N < 1000) {
		printf("N is %d\n", N);
	} else {
		printf("N is wrong.\n");
		exit(1);
	}

	// define tournaments
	tournament *tournaments = calloc(N, sizeof(tournament));

	// fill tournaments
	for(i = 0; i < N; ++i) {
		if (fscanf(fp, " %30[^\n]", tournaments[i].name) != 1) {
			printf("File read error.\n");
			exit(1);
		}
		printf("Tournament %d - %s\n", i, tournaments[i].name);

		// assign T
		if (fscanf(fp, "%d", &T) != 1) {
			printf("File read error.\n");
			exit(1);
		}

		// check T
		if (T > 1 && T <= 30) {
//			printf("T is %d\n", T);
		} else {
			printf("T is wrong.\n");
			exit(1);
		}

		tournaments[i].teams_number = T;

		// assign teams
		for(j = 0; j < T; ++j) {
			if (fscanf(fp, " %30[^\n]", tournaments[i].teams[j].name) != 1) {
				printf("File read error.\n");
				exit(1);
			}

			tournaments[i].teams[j].scored_goals_number = 0;
			tournaments[i].teams[j].against_goals_number = 0;
			tournaments[i].teams[j].wins= 0;
			tournaments[i].teams[j].ties = 0;
			tournaments[i].teams[j].losses = 0;
		}

		// assign G
		if (fscanf(fp, "%d", &G) != 1) {
			printf("File read error.\n");
			exit(1);
		}

		// check G
		if (G <= 1000) {
			printf("G is %d\n", G);
		} else {
			printf("G is wrong.\n");
			exit(1);
		}

		// process games
		for(k = 0; k < G; ++k) {
			if (fscanf(fp, " %30[^\n]", game) != 1) {
				printf("File read error.\n");
				exit(1);
			}
//			printf("G %d - %s\n", k, game);

			substr = strtok(game, "#");
			strcpy(team1_name, substr);
			substr = strtok(NULL, "#");
			strcpy(goals, substr);
			substr = strtok(NULL, "#");
			strcpy(team2_name, substr);

			substr = strtok(goals, "@");
			team1_goals = atoi(substr);
			substr = strtok(NULL, "@");
			team2_goals = atoi(substr);

			// process score
			for(g = 0; g < G; ++g) {
				if (strcmp(tournaments[i].teams[g].name, team1_name) == 0) {
					tournaments[i].teams[g].scored_goals_number += team1_goals;
					tournaments[i].teams[g].against_goals_number += team2_goals;

					if (team1_goals > team2_goals) {
						tournaments[i].teams[g].wins += 1;
					} else if (team1_goals == team2_goals) {
						tournaments[i].teams[g].ties += 1;
					} else {
						tournaments[i].teams[g].losses +=1;
					}
				} else if (strcmp(tournaments[i].teams[g].name, team2_name) == 0) {
					tournaments[i].teams[g].scored_goals_number += team2_goals;
					tournaments[i].teams[g].against_goals_number += team1_goals;

					if (team2_goals > team1_goals) {
						tournaments[i].teams[g].wins += 1;
					} else if (team1_goals == team2_goals) {
						tournaments[i].teams[g].ties += 1;
					} else {
						tournaments[i].teams[g].losses +=1;
					}
				}
			}
		}

//		for(g = 0; g < T; ++g) {
//			printf("%s\n", tournaments[i].teams[g].name);
//			printf("%d\n", tournaments[i].teams[g].scored_goals_number);
//			printf("%d\n", tournaments[i].teams[g].against_goals_number);
//			printf("%d\n", tournaments[i].teams[g].wins);
//			printf("%d\n", tournaments[i].teams[g].ties);
//			printf("%d\n", tournaments[i].teams[g].losses);
//		}
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

	return 0;
}
