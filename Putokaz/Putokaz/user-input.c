#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data-types.h"
#include "user-input.h"


void print_continent_options() {
    printf("\tPonudeni kontinenti:\n");
    printf("\t1. Europa\n");
    printf("\t2. Azija\n");
    printf("\t3. Afrika\n");
    printf("\t4. Sjeverna Amerika\n");
    printf("\t5. Juzna Amerika\n");
    printf("\t6. Australija\n");
    printf("\t7. Antarktika\n");
}

void print_travel_options() {
    printf("\tPonudena prijevozna sredstva:\n");
    printf("\t1. Automobil\n");
    printf("\t2. Avion\n");
    printf("\t3. Vlak\n");
    printf("\t4. Autobus\n");
}

void print_season_options() {
    printf("\tPonudena godisnja doba:\n");
    printf("\t1. Proljece\n");
    printf("\t2. Ljeto\n");
    printf("\t3. Jesen\n");
    printf("\t4. Zima\n");
}

void dest_print_question(const DESTINATION* dest_array, int dest_count) {
    char choice = 0;
    do {
        printf("\nZelite li prije odabira destinacije ispisati sve dostupne destinacije? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');	//brisanje starih podataka iz medjuspremnika

        if (choice == 'Y' || choice == 'y') {
            print_destinations(dest_array, dest_count);
        }
    } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
}

void gather_user_preferences(USER_PREFERENCES* preferences) {
    printf("\nUnesite svoj budzet (u eurima): ");
    scanf("%f", &preferences->budget);

    print_continent_options();
    int continent_choice;
    printf("Unesite svoj odabir: ");
    scanf("%d", &continent_choice);
    preferences->continent = (continent_enum)continent_choice;

    print_travel_options();
    int travel_option_choice;
    preferences->num_travel_options = 0;
    char more_options;
    do {
        printf("Unesite odabir prijevoznog sredstva: ");
        scanf("%d", &travel_option_choice);
        preferences->travel_option[preferences->num_travel_options++] = (travel_option_enum)travel_option_choice;
        if (preferences->num_travel_options < 4) {
            printf("Zelite li dodati jos jedno prijevozno sredstvo? (Y/N): ");
            scanf(" %c", &more_options);
        }
        else {
            more_options = 'N';
        }
    } while ((more_options == 'Y' || more_options == 'y') && preferences->num_travel_options < 4);


    print_season_options();
    int season_choice;
    printf("Unesite svoj odabir: ");
    scanf("%d", &season_choice);
    preferences->season = (season_enum)season_choice;
}

