/* Importations: */
#include "C-Utils/cutils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


/* PFC version variables: */
#define PFC_FULL_VERSION  20260131           /* PFC full version variable (2026/01/31). */
#define PFC_MAJOR_VERSION 2026               /* PFC major version variable (2026).      */
#define PFC_MINOR_VERSION 1                  /* PFC minor version variable (01).        */
#define PFC_PATCH_VERSION 31                 /* PFC patch version variable (31).        */

/* Global variables: */
static char global_font_of_money[8192] = ""; /* Font of money variable.    */
static int global_date[3] = {0, 0, 0};       /* Global date variable.      */
static long double global_money = 0.0L;      /* Global money variable.     */
static long double global_new_money = 0.0L;  /* Global new money variable. */

/* Functions prototypes: */
static int save_data(const char *filepath, const long double money, const long double new_money, const char *font_of_money, const int *date);
static int load_data(const char *filepath);

/* Main code: */
int main(void)
{
	/* Main variables: */
	char option[8192] = "";                  /* Option variable.       */
	char font_of_money[8192] = "";           /* Font of money.         */
	int loop = 1;                            /* loop variable.         */
	int date[3] = {0, 0, 0};                 /* YYYY-MM-DD variable.   */
	struct tm current_date = current_time(); /* Current time variable. */

	/* Load data: */
	load_data("data/data.csv");

	while(loop == 1)
	{
		clear_stdout();
		puts("=======================================");
		printf("=========== PFC v%d-0%d-%d ===========\n", PFC_MAJOR_VERSION, PFC_MINOR_VERSION, PFC_PATCH_VERSION);
		puts("=======================================");
		puts("  [ 0 ] Config.");
		puts("  [ 1 ] Record revenue.");
		puts("  [ 2 ] Record expenses.");
		puts("  [ 3 ] View financial summary.");
		puts("  [ 4 ] Set budget by category.");
		puts("  [ 5 ] Analyze financial status.");
		fputs("\tYour answer: ", stdout);
		scanf("%8191s", option);

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
				puts("  [ 1 ] Quit.");
				fputs("\tYour answer: ", stdout);
				scanf("%8191s", option);

				if(strcmp(option, "0") == 0)
				{
					--loop;
				}

				else if(strcmp(option, "1") == 0)
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
			scanf("%Lf", &global_new_money);

			if(global_new_money <= 0.0L)
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
						global_money += global_new_money;

						if(save_data("data/data.csv", global_money, global_new_money, font_of_money, date) != 0)
						{
							perror("Error");
						}
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
			scanf("%Lf", &global_new_money);

			if(global_new_money <= 0.0L)
			{
				puts("Invalid expense amount!");
				paktc();
			}

			else
			{
				global_new_money = -global_new_money;

				fputs("Expense type (\"Food\", \"Transport\", \"Health\", \"Education\", \"Leisure\" or \"Others\"): ", stdout);
				scanf("%8191s", font_of_money);

				if(strcmp(font_of_money, "Food") == 0 || strcmp(font_of_money, "Transport") == 0 || strcmp(font_of_money, "Health") == 0 || strcmp(font_of_money, "Education") == 0 || strcmp(font_of_money, "Leisure") == 0 || strcmp(font_of_money, "Others") == 0)
				{
					printf("Date (Actual date: %04d-%02d-%02d): ", current_date.tm_year + 1900, current_date.tm_mon + 1, current_date.tm_mday);
					scanf("%4d-%2d-%2d", &date[0], &date[1], &date[2]);

					if(!validate_date(date[0], date[1], date[2]))
					{
						global_money += global_new_money;

						if(save_data("data/data.csv", global_money, global_new_money, font_of_money, date) != 0)
						{
							perror("Error");
						}
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
	FILE *file;

	if(!make_directory("data", 0755))
	{
		file = fopen(filepath, "a");

		if(!file)
		{
			perror("Error");

			return 1;
		}

		else
		{
			if(!font_of_money)
			{
				fputs("Font is empty...", stdout);
				paktc();

				return 1;
			}

			else
			{
				if(date[1] <= 9)
				{
					if(date[2] <= 9)
					{
						if(new_money > 0.0L)
						{
							fprintf(file, "%Lf, +%Lf, %s, %d-0%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}

						else
						{
							fprintf(file, "%Lf, %Lf, %s, %d-0%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}
					}

					else
					{
						if(new_money > 0.0L)
						{
							fprintf(file, "%Lf, +%Lf, %s, %d-0%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}

						else
						{
							fprintf(file, "%Lf, %Lf, %s, %d-0%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}
					}
				}

				else
				{
					if(date[2] <= 9)
					{
						if(new_money > 0.0L)
						{
							fprintf(file, "%Lf, +%Lf, %s, %d-%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}

						else
						{
							fprintf(file, "%Lf, %Lf, %s, %d-%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}
					}

					else
					{
						if(new_money > 0.0L)
						{
							fprintf(file, "%Lf, +%Lf, %s, %d-%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}

						else
						{
							fprintf(file, "%Lf, %Lf, %s, %d-%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
						}
					}
				}

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
	}

	else
	{
		if(errno != EEXIST)
		{
			perror("Error");

			return 1;
		}

		else
		{
			file = fopen(filepath, "a");

			if(!file)
			{
				perror("Error");

				return 1;
			}

			else
			{
				if(!font_of_money)
				{
					fputs("Font is empty...", stdout);
					paktc();

					return 1;
				}

				else
				{
					if(date[1] <= 9)
					{
						if(date[2] <= 9)
						{
							if(new_money > 0.0L)
							{
								fprintf(file, "%Lf, +%Lf, %s, %d-0%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}

							else
							{
								fprintf(file, "%Lf, %Lf, %s, %d-0%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}
						}

						else
						{
							if(new_money > 0.0L)
							{
								fprintf(file, "%Lf, +%Lf, %s, %d-0%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}

							else
							{
								fprintf(file, "%Lf, %Lf, %s, %d-0%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}
						}
					}

					else
					{
						if(date[2] <= 9)
						{
							if(new_money > 0.0L)
							{
								fprintf(file, "%Lf, +%Lf, %s, %d-%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}

							else
							{
								fprintf(file, "%Lf, %Lf, %s, %d-%d-0%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}
						}

						else
						{
							if(new_money > 0.0L)
							{
								fprintf(file, "%Lf, +%Lf, %s, %d-%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}

							else
							{
								fprintf(file, "%Lf, %Lf, %s, %d-%d-%d\n", money, new_money, font_of_money, date[0], date[1], date[2]);
							}
						}
					}

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
		if(global_date[1] <= 9)
		{
			if(global_date[2] <= 9)
			{
				fscanf(file, "%Lf, %Lf, %s, %d-0%d-0%d", &global_money, &global_new_money, global_font_of_money, &global_date[0], &global_date[1], &global_date[2]);
			}

			else
			{
				fscanf(file, "%Lf, %Lf, %s, %d-0%d-%d", &global_money, &global_new_money, global_font_of_money, &global_date[0], &global_date[1], &global_date[2]);
			}
		}

		else
		{
			if(global_date[2] <= 9)
			{
				fscanf(file, "%Lf, %Lf, %s, %d-%d-0%d", &global_money, &global_new_money, global_font_of_money, &global_date[0], &global_date[1], &global_date[2]);
			}

			else
			{
				fscanf(file, "%Lf, %Lf, %s, %d-%d-%d", &global_money, &global_new_money, global_font_of_money, &global_date[0], &global_date[1], &global_date[2]);
			}
		}

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