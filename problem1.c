#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// print all months and corresponding sales
// inputs: months array, sales array
void print_report(char months[12][10], double sales[12]) {
	printf("Month\t\tSales\n\n");
	for (int i = 0; i < 12; i++) {
		printf("%s\t\t$%.2lf\n", months[i], sales[i]);
	}
	return;
}

// gives back values of min and max indicies and avg sales
// inputs: min index, max index, average, and sales array
void min_max_avg(int* min_ind, int* max_ind, double* avg, double sales[12], char months[12][10]){
	double sum = 0;
	for (int i = 0; i < 12; i++) {
		// min
		if (sales[i] < sales[*min_ind]) {*min_ind = i;}
		// max
		if (sales[i] > sales[*max_ind]) {*max_ind = i;}
		// sum
		sum = sum + sales[i];
	}
	// avg
	*avg = sum / 12;

	printf("Sales summary:\n\n");
	printf("Minimum sales:\t$%.2lf\t(%s)\n", sales[*min_ind], months[*min_ind]);
	printf("Maximum sales:\t$%.2lf\t(%s)\n", sales[*max_ind], months[*max_ind]);
	printf("Average sales:\t$%.2lf\n", *avg);
	return;
}

// intermediate function to find six month avg given a starting index
double six_month_avg(const int* start_ind, double sales[12]) {
	double sum = 0;
	for (int i = *start_ind; i < *start_ind + 6; i++){
		sum = sum + sales[i];
	}
	return sum / 6;  // return six month avg
}

// evaluates and prints values of all six month moving averages
void moving_six_month_avg(double sales[12], char months[12][10]) {
	int start_ind = 0;
	printf("\nSix-Month Moving Average Report: \n\n");
	while (start_ind + 6 <= 12) {
		printf("%s\t-  %s\t\t$%.2lf\n", months[start_ind], months[start_ind+6-1], 
				six_month_avg(&start_ind, sales));
		start_ind++;
	}
	return;
}

// performs bubble sort on sales and months arrays in parallel
void sort_hi2lo_indices(double sales[12], int sorted_ind[12]){
    for (int i = 0; i < 12; i++){
        sorted_ind[i] = i;
    }
    double num1, num2;
    int temp, sorted;
    sorted = false;
    while(!sorted){
        sorted=true;
        for(int i = 0; i < 12-1; i++){
            num1 = sales[sorted_ind[i]];
            num2 = sales[sorted_ind[i + 1]];
            if (num2>num1){
                temp = sorted_ind[i];
                sorted_ind[i] = sorted_ind[i + 1];
                sorted_ind[i + 1] = temp;
                sorted = false;
            }
        }
    }
    return;
}


int main() {

	FILE *file;
 	double sales[12];
	char months[12][10] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	// open file
	file = fopen("sample.txt", "r");

	// ensure file opened successfully
	if (file == NULL) {
        	printf("Unable to open file.\n");
        	return 1;
    	}

	// read numbers into file
	int counter = 0;  // declare counter var to ensure we dont read more than 12 numbers in
	double number;
	while (fscanf(file, "%lf", &number) == 1) {
        	sales[counter] = number;
		counter++;
		if (counter >= 12) {break;}
    	}	

	// use prev written functions to produce desired outputs
	
	// part 1: sales + months
	printf("Monthly Sales Report for 2022:\n\n");
	print_report(months, sales);

	// part 2: min, max, avg sales
	int min_ind = 0;
	int max_ind = 0;
	double avg = 0;
	min_max_avg(&min_ind, &max_ind, &avg, sales, months);

	// part 3: six month moving avg report
	moving_six_month_avg(sales, months);

	// part 4: highest to lowest ordering
	int indices[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	printf("\nSales Report (Highest to Lowest):\n\n");
	sort_hi2lo_indices(sales, indices);
	
	printf("Month\t\tSales\n\n");
        for (int i = 0; i < 12; i++) {
                printf("%s\t\t$%.2lf\n", months[indices[i]], sales[indices[i]]);
        }

	return 0;
}
