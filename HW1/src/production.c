/*
 * production.c
 *
 *  Created on: Nov 3, 2018
 *      Author: Katie Lin
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "production.h"
#include <math.h>

/**
 * Your production code goes in this function.
 *
 * @param argc Number of words on the command line
 * @param argv Array of pointers to character strings representing the words on the command line.
 * @return true if Program was able to print a calendar.
 *         false if User entered bad input.
 */
bool production(int argc, char* argv[])
{
	bool results = false;
		bool done = false;
		//get the year, Usage as needed.
		int year = -1;
		puts("CALENDAR");
		if(argc<2)
		{
			puts("Enter a year");
			scanf("%d",&year);
			if(year<1752)
			{
				printf("Usage: Year should be greater than 1751, received %d.\n",year);
				done = true;
			}
		}
		else
		{
			char* ptr=0;
			long year_l = strtol(argv[1],&ptr,10);
			year = (int)year_l;
			if(year<1752)
			{
				printf("Usage: Year should be greater than 1751, received %d.\n",year);
				done = true;
			}
		}
		if(!done)
		{
			//print month name
				//print the days of the week text
				//print the weeks

			for(int month = 0; month < 12; month++){ //month is the current month being printed out

					//do each month, print month name
					 print_month(month);

					 //print the days of the week
					puts("Sun  Mon  Tue  Wed  Thu  Fri  Sat");

					//and weeks for that month -- make function

					// what day of the week to start on, and how many days are in the month
					int day_of_week =  calculate_day_of_week(1, //first day of month is 1
										month, //uses 0 for January
										year);

					/*if(month == 2)
					{
						printf("March starts on %d\n", day_of_week);
					}*/

					// calculates how many days are in a given month for a given year.
					int days_in_month = calculate_days_in_month(year, month);

					// print the days of the week for the correct corresponding month
					print_days(days_in_month,day_of_week);

				}
		}
		if(!done)
		{
			results=true;
		}
		return results;

}

/**
 * Prints out the days in each given month.
 * @param days_in_month How many days are in a given month for a given year.
 * @param day_of_week The day of the week a particular date falls on.
 */
void print_days(int days_in_month, int day_of_week){


	for(int j = 0; j<day_of_week;j++) //j is the current week being looked at
	{
		if(j==0){
			printf("   "); //prints 3 spaces if current day of week is Sunday, or 0
		}else {
			printf("     "); //prints 5 spaces for for all other cases
		}
	}

	bool now_done = false;

	for(int day = 1; day <= days_in_month; day++){ //day is the current day in the month being printed

		int day_index = (day_of_week+day - 1)%7; // tracks the current day of week it is
											// i.e. Saturday, Monday...
		if(day_index==0){
			printf("%3d", day);  //prints the day with 3 spaces if the day of the week is Sunday
		} else {
			printf("%5d", day);  //prints the day with 5 spaces if the day of the week is not Sunday
		}

		if(day_index<0) { //If the current day of the week is negative, add 7
			day_index+= 7;
		}
		if((day_index==6)&&!(day == days_in_month)){  //If the current day of the week is Saturday, then start a new line
			printf("\n");
		}




	}

	/*if (day_index!=6){
		printf("\n");
	}*/

}

/**
 * Calculates how many days are in a given month for a given year.
 * @param year The year we are checking.
 * @param month The month we are checking. Range 0 through 11, where January = 0.
 * @return Day of the week. Range 0 through 6, where Sunday = 0.
 *         -1 if invalid input (e.g., year < 1752, month out of range).
 */
int calculate_days_in_month(int year, int month)
{
	int answer = -1;

	if (year < 1752){ //check for extraneous cases
		return -1;
	}

	switch(month)
	{
	case 0: answer = 31; break;
	case 1: 						 // special case for February
		if (!is_leap_year(year)){
			answer = 28;
		} else if (is_leap_year(year)){
			answer = 29;
		} break;
	case 2: answer = 31; break;
	case 3: answer = 30; break;
	case 4: answer = 31; break;
	case 5: answer = 30; break;
	case 6: answer = 31; break;
	case 7: answer = 31; break;
	case 8: answer = 30; break;
	case 9: answer = 31; break;
	case 10: answer = 30; break;
	case 11: answer = 31; break;
	default: answer = -1; break;

	}

	//printf("%d: %d\n",month, answer);
	return(answer);
}

/**
 * Test if a given year is a leap year or not.
 * @param year The year we are testing
 * @return 1 if it is a valid leap year.
 *         0 if a valid year, but not a leap year.
 *        -1 if not a valid year (i.e. before the calendar rule changed in 1752).
 */
int is_leap_year(int year)
{
	int ans = -5;
	bool done = false;

	if (year < 1752){							// less than 1752
		ans = -1;								// not a leap year
		done = true;
	} else if (!done && !(year%4 == 0)){ 		// does not divide by 0
		ans = 0; 								//not a leap year
		done = true;
	} else if (!done && (year%400 == 0)){ 		// does divide by 400
		ans = 1; 								// is a leap year
		done = true;
	} else if (!done && (year%100 == 0)){ 		// does divide by 100
		ans = 0;  								// not a leap year
		done = true;
	} else if(!done){
		ans = 1;
	}

	return ans;

}


/**
 * Determines what day of the week a particular date falls on.
 * @param day Day of the month, counting from 1.
 * @param month Range 0 through 11, where January = 0.
 * @param year The year.
 * @return -1 for invalid input (e.g., year < 1752, month out of range,
 *            day < 1 or > appropriate for that month & year
 *         0 through 6, where Sunday = 0.
 *
 */
int calculate_day_of_week(int day, //first day of month is 1
		int month, //uses 0 for January
		int year)
{//invalid input gets a -1 answer
	int ans = -1;

	if (year < 1752){  // check to see if it is valid year
		return -1;
	} else if ((month < 0) || (month > 12)){   // check to see if input is valid month
		return -1;
	} else if ((day < 0)|| (day > 31)){
		return -1;
	}

	// Y is the year minus 1 for Jan. or Feb, and the year for any other month
	int Y;
	if((month == 0)|| (month == 1)){
		Y = year - 1;
	}else {
		Y = year;
	}

	//y is the last two digits of Y
	int y = Y%100;

	//c is the first two digits of Y
	int c = Y/100;

	//d is the day of the month (1 to 31)
	int d = day;

	//m is the shifted month (March=1.. February= 12)
	int m;

	if(month == 0){ 		//if month is January
		m = 11;
	}else if(month == 1){   //if month is February
		m = 12;
	}else{
		m = month - 1;
	}

	//w is the day of the week
	int w;
	w = ((int)(d + floor(2.6*m-0.2)+ y+ floor(y/4)+ floor(c/4)- 2*c))%7;

	if(w < 0){
		w += 7;  // if w is negative, add 7 to answer
	}

	ans = w;
	return ans;
}


/**
 * Print the months for the calendar
 *@param month The index of the month that needs to be printed. Range 0 through 11, where January = 0.
 **/
void print_month(int month){

	switch(month) //prints out the correct month name
	{
	case 0: puts("January"); break;
	case 1: puts("\nFebruary"); break;
	case 2: puts("\nMarch"); break;
	case 3: puts("\nApril"); break;
	case 4: puts("\nMay"); break;
	case 5: puts("\nJune"); break;
	case 6: puts("\nJuly"); break;
	case 7: puts("\nAugust"); break;
	case 8: puts("\nSeptember"); break;
	case 9: puts("\nOctober"); break;
	case 10: puts("\nNovember"); break;
	case 11: puts("\nDecember"); break;
	default: puts("I will not be here"); break;

	}

}

