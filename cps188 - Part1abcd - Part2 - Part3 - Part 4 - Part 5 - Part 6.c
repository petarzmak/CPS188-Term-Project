#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void
csvtotxt(){
	char clean[3];
	FILE *in, *out;
	
	in = fopen("statscan_diabetes.csv", "r");
	out = fopen("clean.txt", "w");
	
	
	while (!feof(in)){
		
		fscanf(in, "%c", &clean[0]);

		//Replaces all empty values with a ~ character
		if (clean[0] == '"' && clean[1] == '"'){
			clean[1] = '~';
			fprintf(out, "%c", clean[1]);
		}
		
		// Gets rid of all " and unecessary spaces
		if(clean[0] == '"'){
		}
		else if(clean[0] == ' '){
		}
		else if(clean[0] == ','){
			clean[0] = ' ';
			fprintf(out, "%c", clean[0]);
		}
		else
			fprintf(out, "%c", clean[0]);
			
		// Necessary for the first if statement	
		clean[1] = clean[0];
			
	}
	fclose(in);
	fclose(out);
}

int
main (void){

	char yearchar[300][5];
	char headers[18][17];
	char location[300][30];
	char age[300][20];
	char sex[300][10];
	char valuechar[300][5];
	char empty[300][50];
	
	int i, k, g;
	int year[300];
	int ls_years[7];
	double value[300];
	
	//Part 1A and 1B
	double proavg[5] = {0, 0, 0, 0, 0};
	int avgcount[5] = {0, 0, 0, 0, 0};
	
	//Part 1C
	double ont_yearlyavg[7] = {0, 0, 0, 0, 0, 0, 0};
	double que_yearlyavg[7] = {0, 0, 0, 0, 0, 0, 0};
	double bc_yearlyavg[7] = {0, 0, 0, 0, 0, 0, 0};
	double alb_yearlyavg[7] = {0, 0, 0, 0, 0, 0, 0};
	double cad_yearlyavg[7] = {0, 0, 0, 0, 0, 0, 0};
	int ont_yearlyavgcount[7] = {0, 0, 0, 0, 0, 0, 0};
	int que_yearlyavgcount[7] = {0, 0, 0, 0, 0, 0, 0};
	int bc_yearlyavgcount[7] = {0, 0, 0, 0, 0, 0, 0};
	int alb_yearlyavgcount[7] = {0, 0, 0, 0, 0, 0, 0};
	int cad_yearlyavgcount[7] = {0, 0, 0, 0, 0, 0, 0};
	
	//Part 1D
	double proavg_on[3] = {0, 0, 0};
	double proavg_que[3] = {0, 0, 0};
	double proavg_ab[3] = {0, 0, 0};
	double proavg_bc[3] = {0, 0, 0};
	double proavg_cad[3] = {0, 0, 0};
	
	int avgcount_on[3] = {0, 0, 0};
	int avgcount_que[3] = {0, 0, 0};
	int avgcount_ab[3] = {0, 0, 0};
	int avgcount_bc[3] = {0, 0, 0};
	int avgcount_cad[3] = {0, 0, 0};
	
	//Part 2
	double provmax, provmin;
	char provname[5][40];
	char provmaxmin[2][30];
	
	//Part 3
	double avg_above[4];
	double avg_below[4];
	char pro_above[4][25];
	char pro_below[4][25];
	
	//Part 4
	double avg_max;
	int year_max;
	char provname_max[5][40];
	
	double avg_min;
	int year_min;
	char provname_min[11][40];
	
	
	
	FILE *cleaned;
	
	//Calls function that converts csv file to txt file
	csvtotxt();
	
	cleaned = fopen("clean.txt", "r");
	
	// Reads headers row
	for (i = 0; i < 18; i++){
		fscanf(cleaned, "%s", headers[i]);
		}
		
	// Reads all the necessary values and places them into their respective arrays
	k = 0;	
	while (!feof(cleaned)){
		
		for (i = 0; i < 18; i++){
			if(i == 0){
				fscanf(cleaned, "%s", yearchar[k]);
				year[k] = atof(yearchar[k]);
			}
			else if(i == 1)
				fscanf(cleaned, "%s", location[k]);
			else if(i == 3)
				fscanf(cleaned, "%s", age[k]);
			else if(i == 4)
				fscanf(cleaned, "%s", sex[k]);
			else if(i == 13){
				fscanf(cleaned, "%s", valuechar[k]);
				value[k] = atof(valuechar[k]);
			}
			else
				fscanf(cleaned, "%s", empty[k]);
				}
			k++;	
	}
	fclose(cleaned);
	
//Fills Array that contains all of the years
	g = 0;
	for (i = 0; i < k; i++){
		if(g < 7){
			if(year[i] != ls_years[g])
				ls_years[g] = year[i];
			g++;
		}
	}	

//Part 1A and Calculation for 1B
	
	//checks for the location, and then calculates the sum of all the percentages at that location 
	//Note: if the percentage is zero, the program skips over it
	for (i = 0; i < k; i++){
		if(strcmp(location[i], "Ontario") == 0){
			if(value[i] != 0){
				proavg[0] = proavg[0] + value[i];
				avgcount[0] = avgcount[0] + 1;
				strcpy(provname[0], "Ontario");
			} 
		}
		else if(strcmp(location[i], "Quebec") == 0){
			if(value[i] != 0){
				proavg[1] = proavg[1] + value[i];
				avgcount[1] = avgcount[1] + 1;
				strcpy(provname[1], "Quebec");
			}
		}
		else if(strcmp(location[i], "BritishColumbia") == 0){
			if(value[i] != 0){
				proavg[2] = proavg[2] + value[i];
				avgcount[2] = avgcount[2] + 1;
				strcpy(provname[2], "British Columbia");
			}
		}
		else if(strcmp(location[i], "Alberta") == 0){
			if(value[i] != 0){
				proavg[3] = proavg[3] + value[i];
				avgcount[3] = avgcount[3] + 1;
				strcpy(provname[3], "Alberta");
			}
		}
		//Part 1B Calculation
		else if(strcmp(location[i], "Canada(excludingterritories)") == 0){
			if(value[i] != 0){
				proavg[4] = proavg[4] + value[i];
				avgcount[4] = avgcount[4] + 1;
				strcpy(provname[4], "Canada(excluding territories)");
			}
		}
	}
	
	// Calculates the average of each sum
	for (i = 0; i < 5; i++){
		proavg[i] = proavg[i]/avgcount[i];
	}
	
	//Prints output
	printf("Part 1A:\n");
	for (i = 0; i < 4; i++)
		printf("%s Average: %.2lf%%\n", provname[i], proavg[i]);
	

//Part 1B
	//Code for Part 1B is same as Part 1A
	//Prints National Average
	printf("\n\nPart 1B:\n");
	printf("National Average: %.2lf%%\n", proavg[4]);	


// Part 1C
	// loops through every row 
	for (int i = 0; i < 300; i++)
	{
		// checks if the location is Ontario
		if(strcmp(location[i], "Ontario") == 0){
			/* depending on what year it is, if the percentage value exists, 
				adds the percentage value to its respective index in the ont_yearlyavg array, 
				as well as, add +1 to its respective index in the ont_yearlyavgcount 
				array which counts the number of values added to the ont_yearlyavg array. */
			if (year[i] == 2015)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[0] = ont_yearlyavgcount[0] + 1;
					ont_yearlyavg[0] = ont_yearlyavg[0] + value[i];
				}
			}
			else if (year[i] == 2016)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[1] = ont_yearlyavgcount[1] + 1;
					ont_yearlyavg[1] = ont_yearlyavg[1] + value[i];
				}
			}
			else if (year[i] == 2017)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[2] = ont_yearlyavgcount[2] + 1;
					ont_yearlyavg[2] = ont_yearlyavg[2] + value[i];
				}
			}
			else if (year[i] == 2018)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[3] = ont_yearlyavgcount[3] + 1;
					ont_yearlyavg[3] = ont_yearlyavg[3] + value[i];
				}
			}
			else if (year[i] == 2019)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[4] = ont_yearlyavgcount[4] + 1;
					ont_yearlyavg[4] = ont_yearlyavg[4] + value[i];
				}
			}
			else if (year[i] == 2020)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[5] = ont_yearlyavgcount[5] + 1;
					ont_yearlyavg[5] = ont_yearlyavg[5] + value[i];
				}
			}
			else if (year[i] == 2021)
			{
				if (value[i] != 0)
				{
					ont_yearlyavgcount[6] = ont_yearlyavgcount[6] + 1;
					ont_yearlyavg[6] = ont_yearlyavg[6] + value[i];
				}
			}
		}
		// checks if the location is Quebec
		else if(strcmp(location[i], "Quebec") == 0){
			/* depending on what year it is, if the percentage value exists, 
				adds the percentage value to its respective index in the que_yearlyavg array, 
				as well as, add +1 to its respective index in the que_yearlyavgcount 
				array which counts the number of values added to the que_yearlyavg array. */
			if (year[i] == 2015)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[0] = que_yearlyavgcount[0] + 1;
					que_yearlyavg[0] = que_yearlyavg[0] + value[i];
				}
			}
			else if (year[i] == 2016)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[1] = que_yearlyavgcount[1] + 1;
					que_yearlyavg[1] = que_yearlyavg[1] + value[i];
				}
			}
			else if (year[i] == 2017)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[2] = que_yearlyavgcount[2] + 1;
					que_yearlyavg[2] = que_yearlyavg[2] + value[i];
				}
			}
			else if (year[i] == 2018)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[3] = que_yearlyavgcount[3] + 1;
					que_yearlyavg[3] = que_yearlyavg[3] + value[i];
				}
			}
			else if (year[i] == 2019)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[4] = que_yearlyavgcount[4] + 1;
					que_yearlyavg[4] = que_yearlyavg[4] + value[i];
				}
			}
			else if (year[i] == 2020)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[5] = que_yearlyavgcount[5] + 1;
					que_yearlyavg[5] = que_yearlyavg[5] + value[i];
				}
			}
			else if (year[i] == 2021)
			{
				if (value[i] != 0)
				{
					que_yearlyavgcount[6] = que_yearlyavgcount[6] + 1;
					que_yearlyavg[6] = que_yearlyavg[6] + value[i];
				}
			}
		}
		// checks if the location is British Columbia
		else if(strcmp(location[i], "BritishColumbia") == 0){
			/* depending on what year it is, if the percentage value exists, 
				adds the percentage value to its respective index in the bc_yearlyavg array, 
				as well as, add +1 to its respective index in the bc_yearlyavgcount 
				array which counts the number of values added to the bc_yearlyavg array. */
			if (year[i] == 2015)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[0] = bc_yearlyavgcount[0] + 1;
					bc_yearlyavg[0] = bc_yearlyavg[0] + value[i];
				}
			}
			else if (year[i] == 2016)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[1] = bc_yearlyavgcount[1] + 1;
					bc_yearlyavg[1] = bc_yearlyavg[1] + value[i];
				}
			}
			else if (year[i] == 2017)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[2] = bc_yearlyavgcount[2] + 1;
					bc_yearlyavg[2] = bc_yearlyavg[2] + value[i];
				}
			}
			else if (year[i] == 2018)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[3] = bc_yearlyavgcount[3] + 1;
					bc_yearlyavg[3] = bc_yearlyavg[3] + value[i];
				}
			}
			else if (year[i] == 2019)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[4] = bc_yearlyavgcount[4] + 1;
					bc_yearlyavg[4] = bc_yearlyavg[4] + value[i];
				}
			}
			else if (year[i] == 2020)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[5] = bc_yearlyavgcount[5] + 1;
					bc_yearlyavg[5] = bc_yearlyavg[5] + value[i];
				}
			}
			else if (year[i] == 2021)
			{
				if (value[i] != 0)
				{
					bc_yearlyavgcount[6] = bc_yearlyavgcount[6] + 1;
					bc_yearlyavg[6] = bc_yearlyavg[6] + value[i];
				}
			}
		}
		// checks if the location is Alberta
		else if(strcmp(location[i], "Alberta") == 0){
			/* depending on what year it is, if the percentage value exists, 
				adds the percentage value to its respective index in the alb_yearlyavg array, 
				as well as, add +1 to its respective index in the alb_yearlyavgcount 
				array which counts the number of values added to the alb_yearlyavg array. */
			if (year[i] == 2015)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[0] = alb_yearlyavgcount[0] + 1;
					alb_yearlyavg[0] = alb_yearlyavg[0] + value[i];
				}
			}
			else if (year[i] == 2016)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[1] = alb_yearlyavgcount[1] + 1;
					alb_yearlyavg[1] = alb_yearlyavg[1] + value[i];
				}
			}
			else if (year[i] == 2017)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[2] = alb_yearlyavgcount[2] + 1;
					alb_yearlyavg[2] = alb_yearlyavg[2] + value[i];
				}
			}
			else if (year[i] == 2018)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[3] = alb_yearlyavgcount[3] + 1;
					alb_yearlyavg[3] = alb_yearlyavg[3] + value[i];
				}
			}
			else if (year[i] == 2019)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[4] = alb_yearlyavgcount[4] + 1;
					alb_yearlyavg[4] = alb_yearlyavg[4] + value[i];
				}
			}
			else if (year[i] == 2020)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[5] = alb_yearlyavgcount[5] + 1;
					alb_yearlyavg[5] = alb_yearlyavg[5] + value[i];
				}
			}
			else if (year[i] == 2021)
			{
				if (value[i] != 0)
				{
					alb_yearlyavgcount[6] = alb_yearlyavgcount[6] + 1;
					alb_yearlyavg[6] = alb_yearlyavg[6] + value[i];
				}
			}
		}
		// checks if the location is Canada (excluding territories)
		else if(strcmp(location[i], "Canada(excludingterritories)") == 0){
			/* depending on what year it is, if the percentage value exists, 
				adds the percentage value to its respective index in the cad_yearlyavg array, 
				as well as, add +1 to its respective index in the cad_yearlyavgcount 
				array which counts the number of values added to the cad_yearlyavg array. */
			if (year[i] == 2015)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[0] = cad_yearlyavgcount[0] + 1;
					cad_yearlyavg[0] = cad_yearlyavg[0] + value[i];
				}
			}
			else if (year[i] == 2016)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[1] = cad_yearlyavgcount[1] + 1;
					cad_yearlyavg[1] = cad_yearlyavg[1] + value[i];
				}
			}
			else if (year[i] == 2017)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[2] = cad_yearlyavgcount[2] + 1;
					cad_yearlyavg[2] = cad_yearlyavg[2] + value[i];
				}
			}
			else if (year[i] == 2018)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[3] = cad_yearlyavgcount[3] + 1;
					cad_yearlyavg[3] = cad_yearlyavg[3] + value[i];
				}
			}
			else if (year[i] == 2019)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[4] = cad_yearlyavgcount[4] + 1;
					cad_yearlyavg[4] = cad_yearlyavg[4] + value[i];
				}
			}
			else if (year[i] == 2020)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[5] = cad_yearlyavgcount[5] + 1;
					cad_yearlyavg[5] = cad_yearlyavg[5] + value[i];
				}
			}
			else if (year[i] == 2021)
			{
				if (value[i] != 0)
				{
					cad_yearlyavgcount[6] = cad_yearlyavgcount[6] + 1;
					cad_yearlyavg[6] = cad_yearlyavg[6] + value[i];
				}
			}
		}
	}

	/* this for-loop calculates the provincial yearly averages
        by dividing the sum of the yearly percentage values by their 
        respective yearly average counts */
	for (i = 0; i < 7; i++)
	{
		ont_yearlyavg[i] = ont_yearlyavg[i] / ont_yearlyavgcount[i];
		que_yearlyavg[i] = que_yearlyavg[i] / que_yearlyavgcount[i];
		bc_yearlyavg[i] = bc_yearlyavg[i] / bc_yearlyavgcount[i];
		alb_yearlyavg[i] = alb_yearlyavg[i] / alb_yearlyavgcount[i];
		cad_yearlyavg[i] = cad_yearlyavg[i] / cad_yearlyavgcount[i];
	}

	// displays the yearly percentage averages for diabetes in Ontario
	printf("\n\nPart 1C:\n");
	printf("Ontario Yearly Average: \n");
	printf("Year 2015 Average: %.2lf%%\n", ont_yearlyavg[0]);
	printf("Year 2016 Average: %.2lf%%\n", ont_yearlyavg[1]);
	printf("Year 2017 Average: %.2lf%%\n", ont_yearlyavg[2]);
	printf("Year 2018 Average: %.2lf%%\n", ont_yearlyavg[3]);
	printf("Year 2019 Average: %.2lf%%\n", ont_yearlyavg[4]);
	printf("Year 2020 Average: %.2lf%%\n", ont_yearlyavg[5]);
	printf("Year 2021 Average: %.2lf%%\n", ont_yearlyavg[6]);

	// displays the yearly percentage averages for diabetes in Quebec
	printf("\nQuebec Yearly Average: \n");
	printf("Year 2015 Average: %.2lf%%\n", que_yearlyavg[0]);
	printf("Year 2016 Average: %.2lf%%\n", que_yearlyavg[1]);
	printf("Year 2017 Average: %.2lf%%\n", que_yearlyavg[2]);
	printf("Year 2018 Average: %.2lf%%\n", que_yearlyavg[3]);
	printf("Year 2019 Average: %.2lf%%\n", que_yearlyavg[4]);
	printf("Year 2020 Average: %.2lf%%\n", que_yearlyavg[5]);
	printf("Year 2021 Average: %.2lf%%\n", que_yearlyavg[6]);
	
	// displays the yearly percentage averages for diabetes in British Columbia
	printf("\nBritish Columbia Yearly Average: \n");
	printf("Year 2015 Average: %.2lf%%\n", bc_yearlyavg[0]);
	printf("Year 2016 Average: %.2lf%%\n", bc_yearlyavg[1]);
	printf("Year 2017 Average: %.2lf%%\n", bc_yearlyavg[2]);
	printf("Year 2018 Average: %.2lf%%\n", bc_yearlyavg[3]);
	printf("Year 2019 Average: %.2lf%%\n", bc_yearlyavg[4]);
	printf("Year 2020 Average: %.2lf%%\n", bc_yearlyavg[5]);
	printf("Year 2021 Average: %.2lf%%\n", bc_yearlyavg[6]);

	// displays the yearly percentage averages for diabetes in Alberta
	printf("\nAlberta Yearly Average: \n");
	printf("Year 2015 Average: %.2lf%%\n", alb_yearlyavg[0]);
	printf("Year 2016 Average: %.2lf%%\n", alb_yearlyavg[1]);
	printf("Year 2017 Average: %.2lf%%\n", alb_yearlyavg[2]);
	printf("Year 2018 Average: %.2lf%%\n", alb_yearlyavg[3]);
	printf("Year 2019 Average: %.2lf%%\n", alb_yearlyavg[4]);
	printf("Year 2020 Average: %.2lf%%\n", alb_yearlyavg[5]);
	printf("Year 2021 Average: %.2lf%%\n", alb_yearlyavg[6]);

	/* displays the yearly percentage averages for diabetes in Canada (excluding territories) */
	printf("\nCanada(excluding territories) Yearly Average: \n");
	printf("Year 2015 Average: %.2lf%%\n", cad_yearlyavg[0]);
	printf("Year 2016 Average: %.2lf%%\n", cad_yearlyavg[1]);
	printf("Year 2017 Average: %.2lf%%\n", cad_yearlyavg[2]);
	printf("Year 2018 Average: %.2lf%%\n", cad_yearlyavg[3]);
	printf("Year 2019 Average: %.2lf%%\n", cad_yearlyavg[4]);
	printf("Year 2020 Average: %.2lf%%\n", cad_yearlyavg[5]);
	printf("Year 2021 Average: %.2lf%%\n", cad_yearlyavg[6]);


//Part 1d 
		//loops through every row in the cleaned text file 
		for (i = 0; i < k; i++){
			/*if statements for Ontario*/
			/*checking if the location is Ontario*/
			if(strcmp(location[i], "Ontario") == 0){
				/*depending on which of the 3 age groups is read, and if the diabetes percentage value exists, 
				that percentage value will be added to the array (proavg_on) that contains the values for Ontario, 
				also +1 will be added to the array (avgcount_on) which tracks the number of elements added to the array (proavg_on) */ 
				
				if (strcmp(age[i], "35to49years") == 0) {
					if(value[i] != 0){ 
						proavg_on[0] = proavg_on[0] + value[i];
						avgcount_on[0] = avgcount_on[0] + 1;
					} 
				} else if (strcmp(age[i], "50to64years") == 0) {
					if(value[i] != 0){
						proavg_on[1] = proavg_on[1] + value[i];
						avgcount_on[1] = avgcount_on[1] + 1;
					} 
				} else if (strcmp(age[i], "65yearsandover") == 0) {
					if(value[i] != 0){
						proavg_on[2] = proavg_on[2] + value[i];
						avgcount_on[2] = avgcount_on[2] + 1;
					}
				}
		
			} /*end of the outer if statement for Ontario*/  
	
			/*if statements for Quebec*/ 
			/*checking if the location is Quebec*/
			if(strcmp(location[i], "Quebec") == 0){
				/*depending on which of the 3 age groups is read, and if the diabetes percentage value exists, 
				that percentage value will be added to the array (proavg_que) that contains the values for Quebec, 
				also +1 will be added to the array (avgcount_que) which tracks the number of elements added to the array (proavg_que) */
				
				if (strcmp(age[i], "35to49years") == 0) {
					if(value[i] != 0){
						proavg_que[0] = proavg_que[0] + value[i];
						avgcount_que[0] = avgcount_que[0] + 1;
					} 
				} else if (strcmp(age[i], "50to64years") == 0) {
					if(value[i] != 0){
						proavg_que[1] = proavg_que[1] + value[i];
						avgcount_que[1] = avgcount_que[1] + 1;
					} 
				} else if (strcmp(age[i], "65yearsandover") == 0) {
					if(value[i] != 0){
						proavg_que[2] = proavg_que[2] + value[i];
						avgcount_que[2] = avgcount_que[2] + 1;
					}
				}
			} /*end of the outer if statement for Quebec*/ 

			/*if statements for Alberta*/ 
			/*checking if the location is Alberta*/
			if(strcmp(location[i], "Alberta") == 0){
				/*depending on which of the 3 age groups is read, and if the diabetes percentage value exists, 
				that percentage value will be added to the array (proavg_ab) that contains the values for Alberta, 
				also +1 will be added to the array (avgcount_ab) which tracks the number of elements added to the array (proavg_ab) */
				
				if (strcmp(age[i], "35to49years") == 0) {
					if(value[i] != 0){
						proavg_ab[0] = proavg_ab[0] + value[i];
						avgcount_ab[0] = avgcount_ab[0] + 1;
					} 
				} else if (strcmp(age[i], "50to64years") == 0) {
					if(value[i] != 0){
						proavg_ab[1] = proavg_ab[1] + value[i];
						avgcount_ab[1] = avgcount_ab[1] + 1;
					} 
				} else if (strcmp(age[i], "65yearsandover") == 0) {
					if(value[i] != 0){
						proavg_ab[2] = proavg_ab[2] + value[i];
						avgcount_ab[2] = avgcount_ab[2] + 1;
					}
				}
			} /*end of the outer if statement for Alberta*/ 
	
			/*if statements for British Columbia*/
			/*checking if the location is British Columbia*/
			if(strcmp(location[i], "BritishColumbia") == 0){
				/*depending on which of the 3 age groups is read, and if the diabetes percentage value exists, 
				that percentage value will be added to the array (proavg_bc) that contains the values for British Columbia, 
				also +1 will be added to the array (avgcount_bc) which tracks the number of elements added to the array (proavg_bc) */
				
				if (strcmp(age[i], "35to49years") == 0) {
					if(value[i] != 0){
						proavg_bc[0] = proavg_bc[0] + value[i];
					avgcount_bc[0] = avgcount_bc[0] + 1;
					} 
				} else if (strcmp(age[i], "50to64years") == 0) {
					if(value[i] != 0){
						proavg_bc[1] = proavg_bc[1] + value[i];
						avgcount_bc[1] = avgcount_bc[1] + 1;
					} 
				} else if (strcmp(age[i], "65yearsandover") == 0) {
					if(value[i] != 0){
						proavg_bc[2] = proavg_bc[2] + value[i];
						avgcount_bc[2] = avgcount_bc[2] + 1;
					}
				}
			} /*end of the outer if statement for British Columbia*/ 

			/*if statements Canada(excluding territories)*/
			/*checking if the location is Canada(excluding territories)*/
			if(strcmp(location[i], "Canada(excludingterritories)") == 0){
				/*depending on which of the 3 age groups is read, and if the diabetes percentage value exists, 
				that percentage value will be added to the array (proavg_cad) that contains the values for Canada(excluding territories), 
				also +1 will be added to the array (avgcount_cad) which tracks the number of elements added to the array (proavg_cad) */
				
				if (strcmp(age[i], "35to49years") == 0) {
					if(value[i] != 0){
						proavg_cad[0] = proavg_cad[0] + value[i];
						avgcount_cad[0] = avgcount_cad[0] + 1;
					} 
				} else if (strcmp(age[i], "50to64years") == 0) {
					if(value[i] != 0){
						proavg_cad[1] = proavg_cad[1] + value[i];
						avgcount_cad[1] = avgcount_cad[1] + 1;
					} 
				} else if (strcmp(age[i], "65yearsandover") == 0) {
					if(value[i] != 0){
						proavg_cad[2] = proavg_cad[2] + value[i];
						avgcount_cad[2] = avgcount_cad[2] + 1;
					}
				}
			} /*end of the outer if statement for Canada*/ 

		} /*end of the outer for loop*/	
	
	/*5 separate for loops that calculate the average diabetes percentage for each age group, for each of the 5 locations,
	the average is calculated by dividing the sum of the provinal/national average percentage values by their 
    respective yearly average counts */ 
	for (i = 0; i < 3; i++)
		proavg_on[i] = proavg_on[i]/avgcount_on[i];
	
	for (i = 0; i < 3; i++)
		proavg_que[i] = proavg_que[i]/avgcount_que[i];
	
	for (i = 0; i < 3; i++)
		proavg_ab[i] = proavg_ab[i]/avgcount_ab[i];
	
	for (i = 0; i < 3; i++)
		proavg_bc[i] = proavg_bc[i]/avgcount_bc[i];
	
	for (i = 0; i < 3; i++)
		proavg_cad[i] = proavg_cad[i]/avgcount_cad[i];
	
	
	//outputting the averages for the 3 different age categories, for each province and Canada as a whole 
	printf("\n\nQuestion 1D:\n");  
	printf("Ontario Average Diabetes Rate by Age Group\n");
	printf("35-49 years old: %.2lf%%\n", proavg_on[0]);
	printf("50-64 years old: %.2lf%%\n", proavg_on[1]);
	printf("65+ years old: %.2lf%%\n", proavg_on[2]);
	
	printf("\n");
	printf("Quebec Average Diabetes Rate by Age Group\n");
	printf("35-49 years old: %.2lf%%\n", proavg_que[0]);
	printf("50-64 years old: %.2lf%%\n", proavg_que[1]);
	printf("65+ years old: %.2lf%%\n", proavg_que[2]);
	
	printf("\n");
	printf("Alberta Average Diabetes Rate by Age Group\n");
	printf("35-49 years old: %.2lf%%\n", proavg_ab[0]);
	printf("50-64 years old: %.2lf%%\n", proavg_ab[1]);
	printf("65+ years old: %.2lf%%\n", proavg_ab[2]);
	
	printf("\n");
	printf("British Columbia Average Diabetes Rate by Age Group\n");
	printf("35-49 years old: %.2lf%%\n", proavg_bc[0]);
	printf("50-64 years old: %.2lf%%\n", proavg_bc[1]);
	printf("65+ years old: %.2lf%%\n", proavg_bc[2]);
	
	printf("\n");
	printf("Canada (excluding territories) Average Diabetes Rate by Age Group\n");
	printf("35-49 years old: %.2lf%%\n", proavg_cad[0]);
	printf("50-64 years old: %.2lf%%\n", proavg_cad[1]);
	printf("65+ years old: %.2lf%%\n", proavg_cad[2]);
	
	
// Part 2

	//Finds the largest provincial average
	provmax = proavg[0];
	for (i = 0; i < 4; i++){
		if (proavg[i] >= provmax){
			provmax = proavg[i];
			strcpy(provmaxmin[0], provname[i]);
		}
	}
	
	//Finds the smallest provincial average		
	provmin = proavg[0];
	for (i = 0; i < 4; i++){
		if (proavg[i] <= provmin){
			provmin = proavg[i];
			strcpy(provmaxmin[1], provname[i]);
		}
	}
	//Prints result
	printf("\n\nPart 2:\n");
	printf("%s has the largest provincial average with an average of: %.2lf%%\n", provmaxmin[0], provmax);
	printf("%s has the smallest provincial average with an average of: %.2lf%%\n", provmaxmin[1], provmin);
	
	
// Part 3

	// Compares which provincial averages are above the national average
	for (i = 0; i < 4; i++){
		if (proavg[i] > proavg[4]){
			avg_above[i] = proavg[i];
			strcpy(pro_above[i], provname[i]);
		}
	// Compares which provincial averages are below the national average		
		if (proavg[i] <= proavg[4]){
			avg_below[i] = proavg[i];
			strcpy(pro_below[i], provname[i]);
		}
	}
	
	//Prints Output
	printf("\n\nPart 3:\n");
	printf("Provinces above the national average(%.2lf%%):\n", proavg[4]);
	for (i = 0; i < 4; i++){
		if(avg_above[i] != 0)
			printf("%s: %.2lf%%\n", pro_above[i], avg_above[i]);
	}
		
	printf("\nProvinces below the national average(%.2lf%%):\n", proavg[4]);
	for (i = 0; i < 4; i++){
		if(avg_below[i] != 0)
			printf("%s: %.2lf%%\n", pro_below[i], avg_below[i]);
		}
		
		
// Part 4
	
	//Finds the largest provincial percentage and records which year and province it is in
	//Note: excluded National Percentages
	for (i = 0; i < k; i++){
		if(strcmp(location[i], "Canada(excludingterritories)") == 1){
			if (value[i] >= avg_max){
				avg_max = value[i];
				year_max = year[i];
				strcpy(provname_max[0], location[i]);
			}
		}
	}
	//Finds the smallest provincial percentage, records year and province
	avg_min = avg_max;
	for (i = 0; i < k; i++){
			if (value[i] < avg_min && value[i] != 0){
				avg_min = value[i];
				year_min = year[i];
				
				// BC from file is replaced with BC from array(includes a space)
				if(strcmp(location[i], "BritishColumbia") == 0)
					strcpy(provname_min[0], provname[2]);
				else
					strcpy(provname_min[0], location[i]);
			}
	}

	//Prints Reseult
	printf("\n\nPart 4:\n");
	printf("The Province(s) with the highest percentage of Diabetes is:\n");
	printf("%s in %d with a percentage of: %.2lf%%\n", provname_max[0], year_max, avg_max);
	
	printf("\nThe Province(s) with the lowest percentage of Diabetes is:\n");
	printf("%s in %d with a percentage of: %.2lf%%\n", provname_min[0], year_min, avg_min);


// Part 5

	//Creates file for Line Graph contataing all provincial averages for all years 
	FILE *graphs1;
	graphs1 = fopen("Question5.txt", "w");
	
	//Prints headers into file
	fprintf(graphs1, "Year\t");
	for(i = 0; i < 5; i++)
		fprintf(graphs1, "%s\t", provname[i]);
	fprintf(graphs1, "\n");
	
	//Prints all required values into the file
	for(i = 0; i < 7; i++)
		fprintf(graphs1, "%d\t%lf\t%lf\t%lf\t\t%lf\t%lf\n", ls_years[i], ont_yearlyavg[i], que_yearlyavg[i], bc_yearlyavg[i], alb_yearlyavg[i], cad_yearlyavg[i]);

	fclose(graphs1);


// Part 6

	//creating the text file that will be used to produce the bar graph 
    FILE *graphs2; 
    graphs2 = fopen("Question6_bar_graph.txt", "w");
    
	//arrays that contain the age group categories and their corresponding x-axis labels
    char age_group[3][6]= {"35-49", "50-64", "65+"}; 
    int nums[3] = {0, 1, 2}; 

	//printing the values into the file bar_graph.txt
    for (int i = 0; i < 3; i++)
        fprintf(graphs2, "%d\t%s\t\t%.2lf\n", nums[i], age_group[i], proavg_cad[i]); 


    fclose(graphs2);


	return 0;
}
