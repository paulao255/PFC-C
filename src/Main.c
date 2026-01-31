/* Importations: */
#include "C-Utils/cutils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


/* PFC version variables: */
#define PFC_FULL_VERSION  20260130 /* PFC full version variable (2026/01/30). */
#define PFC_MAJOR_VERSION 2026     /* PFC major version variable (2026).      */
#define PFC_MINOR_VERSION 1        /* PFC minor version variable (01).        */
#define PFC_PATCH_VERSION 30       /* PFC patch version variable (30).        */

/* Global variables: */
static char global_font_of_money[8192] = ""; /* Font of money variable.    */
static int global_date[3] = {0, 0, 0};       /* Global date variable.      */
static long double global_money = 0.0L;      /* Global money variable.     */
static long double global_new_money = 0.0L;  /* Global new money variable. */

/* Functions prototypes: */
static int save_data(const char *filepath, const long double money, const long double new_money, const char *font_of_money, const int *date);
static int save_complete_data(void);
static int load_data(const char *filepath);

/* Main code: */
int main(void)
{
	/* Main variables: */
	char option[8192] = "";                          /* Option variable.                     */
	char font_of_money[8192] = "";                   /* Font of money.                       */
	int loop = 1;                                    /* loop variable.                       */
	int date[3] = {0, 0, 0};                         /* YYYY-MM-DD variable.                 */
	struct tm current_date = current_time();         /* Current time variable.               */
	long double new_money[2] = {0.0L, 0.0L};         /* Revenue and expense money variables. */

	/* Load data: */
	load_data("data/data.csv");

	while(loop == 1)
	{
		clear_stdout();
		puts("=======================================");
		printf("=========== PFC v%4d-%2d-%2d ===========\n", PFC_MAJOR_VERSION, PFC_MINOR_VERSION, PFC_PATCH_VERSION);
		puts("=======================================");
		puts("  [ 0 ] Config.");
		puts("  [ 1 ] Record revenue.");
		puts("  [ 2 ] Record expenses.");
		puts("  [ 3 ] View financial summary.");
		puts("  [ 4 ] Set budget by category.");
		puts("  [ 5 ] Analyze financial status.");
		fputs("\tYour answer: ", stdout);
		scanf("%s", option);

		if(strcmp(option, "0") == 0)
		{
			++loop;
			clear_stdout();

			while(loop == 2)
			{
				puts("============================");
				puts("========== Config ==========");
				puts("============================");
				puts("  [ 0 ] Go back.");
				puts("  [ 1 ] Save and quit.");
				puts("  [ 2 ] Quit without save");
				fputs("\tYour answer: ", stdout);
				scanf("%s", option);

				if(strcmp(option, "0") == 0)
				{
					--loop;
				}

				else if(strcmp(option, "1") == 0)
				{
					clear_stdout();

					if(save_complete_data() != 0)
					{
						perror("Error");
					}

					loop = 0;
				}

				else if(strcmp(option, "2") == 0)
				{
					clear_stdout();
					loop = 0;
				}
			}
		}

		else if(strcmp(option, "1") == 0)
		{
			clear_stdout();
			fputs("Revenue amount: ", stdout);
			scanf("%Lf", &new_money[0]);

			if(new_money[0] <= 0.0L)
			{
				puts("Invalid revenue amount!");
				paktc();
			}

			else
			{
				clear_stdin();
				fputs("Font type (\"Salary\" or \"Extra income\"): ", stdout);
				fgets(font_of_money, sizeof(font_of_money), stdin);
				font_of_money[strcspn(font_of_money, "\n")] = 0;

				if(strcmp(font_of_money, "Salary") == 0 || strcmp(font_of_money, "Extra income") == 0)
				{
					printf("Date (Actual date: %04d-%02d-%02d): ", current_date.tm_year + 1900, current_date.tm_mon + 1, current_date.tm_mday);
					scanf("%4d-%2d-%2d", &date[0], &date[1], &date[2]);

					if(!validate_date(date[0], date[1], date[2]))
					{
						global_money += new_money[0];
						global_new_money += new_money[0];
						strcat(global_font_of_money, font_of_money);
						global_date[0] = date[0];
						global_date[1] = date[1];
						global_date[2] = date[2];
					}

					else
					{
						puts("Invalid date!");
						paktc();
					}
				}

				else
				{
					puts("Invalid font type!");
					paktc();
				}
			}
		}

		else if(strcmp(option, "2") == 0)
		{
			clear_stdout();
			fputs("Expense amount: ", stdout);
			scanf("%Lf", &new_money[1]);

			if(new_money[1] >= 0.0L)
			{
				fputs("Expense type (\"Food\", \"Transport\", \"Health\", \"Education\", \"Leisure\" or \"Others\"): ", stdout);
				scanf("%s", font_of_money);

				if(strcmp(font_of_money, "Food") == 0 || strcmp(font_of_money, "Transport") == 0 || strcmp(font_of_money, "Health") == 0 || strcmp(font_of_money, "Education") == 0 || strcmp(font_of_money, "Leisure") == 0 || strcmp(font_of_money, "Others") == 0)
				{
					fputs("Date (YYYY-MM-DD): ", stdout);
					scanf("%4d-%2d-%2d", &date[0], &date[1], &date[2]);

					if(!validate_date(date[0], date[1], date[2]))
					{
						global_money -= new_money[1];
						global_new_money -= new_money[1];
						strcat(global_font_of_money, font_of_money);
						global_date[0] = date[0];
						global_date[1] = date[1];
						global_date[2] = date[2];
					}

					else
					{
						puts("Invalid date!");
						paktc();
					}
				}

				else
				{
					puts("Invalid expense type!");
					paktc();
				}
			}

			else
			{
				puts("Invalid expense amount!");
				paktc();
			}
		}

		else if(strcmp(option, "3") == 0)
		{
			clear_stdout();
		}

		else if(strcmp(option, "4") == 0)
		{
			clear_stdout();
		}

		else if(strcmp(option, "5") == 0)
		{
			clear_stdout();
		}
	}

	return 0;
}

static int save_data(const char *filepath, const long double money, const long double new_money, const char *font_of_money, const int *date)
{
	FILE *file = fopen(filepath, "a");

	if(!file)
	{
		perror("Error");

		return 1;
	}

	else
	{
		fprintf(file, "%Lf, %Lf, %s, %d-%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);

		if(fclose(file) != 0)
		{
			perror("Error");

			return 1;
		}

		else
		{
			return 0;
		}
	}
}

static int save_complete_data(void)
{
	if(make_directory("data", 0755) != 0)
	{
		perror("Error");

		return 1;
	}

	else
	{
		if(save_data("data/data.csv", global_money, global_new_money, global_font_of_money, global_date) != 0)
		{
			perror("Error");

			return 1;
		}

		else
		{
			return 0;
		}
	}
}

static int load_data(const char *filepath)
{
	FILE *file = fopen(filepath, "r");

	if(!file)
	{
		perror("Error");

		return 1;
	}

	else
	{
		fscanf(file, "%Lf", &global_money);

		if(fclose(file) != 0)
		{
			perror("Error");

			return 1;
		}

		else
		{
			return 0;
		}
	}
}