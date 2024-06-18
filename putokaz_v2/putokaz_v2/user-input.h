#pragma once
#include "data-types.h"
#include "destination.h"

#define PRINT_AND_READ_PROMPT(prompt, var) \
    do { \
        printf(prompt); \
        scanf("%d", &var); \
    } while (0)


int main_menu(char* dest_file);
void print_continent_options();
void print_travel_options();
void print_season_options();
void dest_print_question(const DESTINATION* dest_array, int dest_count);
void gather_user_preferences(USER_PREFERENCES* preferences);
