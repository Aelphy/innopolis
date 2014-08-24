/*
 ============================================================================
 Name        : cs-as1.c
 Author      : Aelphy
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team {
	char name[30];
	int scored_goals_number;
	int against_goals_number;
	int wins_number;
};

struct tournament {
	char name[100];
	struct team teams[30];
};

unsigned int N = 0;
unsigned int T = 0;
unsigned int G = 0;

//void exchange(char *init, char *result) {
//  char *buff;
//
//  buff = init;
//  init = result;
//  result = buff;
//}
//
//void quicksort(char A[], int L, int R) {
//  int i, j, pivot;
//
//  if ( R > L) {
//    i = L; j = R;
//    pivot = A[i];
//
//    do {
//      while (strcmp(A[i], pivot) <= 0) i = i + 1;
//      while ((strcmp(A[j], pivot) >= 0) && (j > L)) j = j - 1;
//
//      if (i < j) {
//        exchange(A[i],A[j]);
//        i = i + 1; j = j - 1;
//      }
//    } while (i <= j);
//
//    exchange(A[L], A[j]);
//    quicksort(A, L, j);
//    quicksort(A, i, R);
//  }
//}

int fill_data(unsigned int N, unsigned int T, unsigned int G){
	FILE *fp;
	int i, j, k, g;
	char game[67];
	char team1_name[30], team2_name[30];
	char *substr;
	char goals[4];
	int team1_goals, team2_goals;

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
	struct tournament tournaments[N];

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
			printf("T is %d\n", T);
		} else {
			printf("T is wrong.\n");
			exit(1);
		}

		// assign teams
		for(j = 0; j < T; ++j) {
			if (fscanf(fp, " %30[^\n]", tournaments[i].teams[j].name) != 1) {
				printf("File read error.\n");
				exit(1);
			}
			printf("Team %d - %s\n", j, tournaments[i].teams[j].name);

			tournaments[i].teams[j].scored_goals_number = 0;
			tournaments[i].teams[j].against_goals_number = 0;
			tournaments[i].teams[j].wins_number = 0;
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
			printf("G %d - %s\n", k, game);

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


//			printf ("%s\n", team1_name);
//			printf ("%d\n", team1_goals);
//			printf ("%d\n", team2_goals);
//			printf ("%s\n", team2_name);

			// process score
			for(g = 0; g < G; ++g) {
				if (strcmp(tournaments[i].teams[g].name, team1_name) == 0) {
					tournaments[i].teams[g].scored_goals_number += team1_goals;
					tournaments[i].teams[g].against_goals_number += team2_goals;

					if (team1_goals > team2_goals) {
						tournaments[i].teams[g].wins_number += 1;
					}
				} else if (strcmp(tournaments[i].teams[g].name, team2_name) == 0) {
					tournaments[i].teams[g].scored_goals_number += team2_goals;
					tournaments[i].teams[g].against_goals_number += team1_goals;

					if (team2_goals > team1_goals) {
						tournaments[i].teams[g].wins_number += 1;
					}
				}
			}
		}
	}

  fclose(fp);

  return 0;
}

int main(void) {
  fill_data(N, T, G);

  return 0;
}
