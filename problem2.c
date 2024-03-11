#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// defining macro to make score calculation faster
#define cur_score (td*6+fg*3+sf*2+ex_2*8+ex_fg*7)

# define true 1
# define false 0

//  i will be using sets for solving this problem to ensure unique combinations

// defining Set
struct Set{
	int score_breakdown[1000][5];  // assuming we cant have more than 1000 combos
	int len;

};

// defining append
void append(struct Set* set_val, int* arr, int arr_len) {
	// check if combo exists in set already
	int in_set = false;
	for (int i = 0; i < set_val->len; i++) {  // check against every combo
		int is_same = true;
		for (int j = 0; j < arr_len; j++) {
		if (set_val->score_breakdown[i][j]!=arr[j]){  // check against every value in the combo
			is_same = false;
		}
		}
		if (is_same) {
			in_set = true;
			break;
		}
	}

	if (!in_set) {
		for (int i = 0; i < arr_len; i++) {
			set_val->score_breakdown[set_val->len][i] = arr[i];
		}
		set_val->len++;
	}
} 

// recursive function to find score combos
int rec_score(struct Set* set_val, int score, int td, int fg, int sf, int ex_2, int ex_fg) {
	int tmp[5] = {ex_2,ex_fg,td,fg,sf};
	if (cur_score == score){  // if combo equals entered score, append it
		append(set_val, tmp, 5);
	}
	if (cur_score<score){  // if not, recurse
		return
		rec_score(set_val, score, td+1, fg, sf, ex_2, ex_fg)|
		rec_score(set_val,score, td, fg+1, sf, ex_2, ex_fg)|
		rec_score(set_val,score, td, fg, sf+1, ex_2, ex_fg)|
		rec_score(set_val,score, td, fg, sf, ex_2+1, ex_fg)|
		rec_score(set_val,score, td, fg, sf, ex_2, ex_fg+1);
	}
	return 0; // if score combos get bigger than score, terminate
}

// defining function for set printing
void print_set(struct Set* set) {
	for(int i = 0; i < set->len; i++){
		printf("%i TD + 2pt, %i TD + FG, %i TD, %i 3pt FG, %i Safety\n",
		set->score_breakdown[i][0],
		set->score_breakdown[i][1],
		set->score_breakdown[i][2],
		set->score_breakdown[i][3],
		set->score_breakdown[i][4]);
		}
}


int main() {
	// initial values
	int stop, score;
	struct Set score_combos;
	score_combos.len=0;

	// main loop
	while(true){
		printf("Enter 0 or 1 to STOP: ");
		scanf("%d",&stop);
		if(stop==0 || stop==1){
			break;
		}
		printf("Enter the NFL score: ");
		scanf("%d",&score);
		printf("\nPossible combinations of scoring plays: \n");

		rec_score(&score_combos, score, 0, 0, 0, 0, 0);

		// print set with all score combos
		print_set(&score_combos);
	}

	return 0;
}
