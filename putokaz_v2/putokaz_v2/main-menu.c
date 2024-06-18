#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "data-types.h"
#include "destination.h"
#include "user-input.h"

int g_update_count = 0; // definicija vanjske varijable

static int delete_attempt_count = 0; // statièka varijabla za brojanje pokušaja brisanja destinacija


int main_menu(char* dest_file) {
	DESTINATION* dest_field = NULL;
	int dest_count = 0;

	read_destinations_from_file(dest_file, &dest_field, &dest_count);

	while (1) {
		printf("\t=====================================\t\t");
		printf("\n\t\t======\tPUTOKAZ\t======\t\t\n");
		printf("\n\t\t1. Odabir destinacije\t\t\n");
		printf("\n\t\t2. Dodavanje destinacije\t\t\n");
		printf("\n\t\t3. Azuriranje destinacije\t\t\n");
		printf("\n\t\t4. Ispis destinacija\t\t\n");
		printf("\n\t\t5. Brisanje destinacije\t\t\n");
		printf("\n\t\t6. Izlaz iz programa\t\t\n");
		printf("\t=====================================\t\t\n");

		int main_choice = 0;
		PRINT_AND_READ_PROMPT("Unesite svoj odabir: ", main_choice);

		switch (main_choice) {
		case CHOOSE_DEST:
			dest_print_question(dest_field, dest_count);
			USER_PREFERENCES preferences;
			gather_user_preferences(&preferences);
			find_best_destinations(dest_field, dest_count, &preferences);
			break;

		case ADD_DEST:
			add_destination(&dest_field, &dest_count, dest_file);
			break;

		case UPDATE_DEST:
			dest_print_question(dest_field, dest_count);
			int update_id = 0;
			PRINT_AND_READ_PROMPT("\nUnesite ID destinacije koju želite azurirati: ", update_id);
			update_destination_distance(dest_field, dest_count, update_id, dest_file);
			break;

		case PRINT_DEST:
			printf("1. Ispis svih destinacija\n");
			printf("2. Ispis sortiranih destinacija po cijeni (uzlazno)\n");
			printf("3. Ispis sortiranih destinacija po cijeni (silazno)\n");

			int print_choice = 0; 
			PRINT_AND_READ_PROMPT("Unesite svoj odabir: ", print_choice);

			switch (print_choice) {
			case 1:
				print_destinations(dest_field, dest_count);
				break;
			case 2:
				sort_destinations_by_price(dest_field, dest_count, 1); // uzlazno sortiranje
				print_destinations(dest_field, dest_count);
				break;
			case 3:
				sort_destinations_by_price(dest_field, dest_count, 0); // silazno sortiranje
				print_destinations(dest_field, dest_count);
				break;
			default:
				printf("Neispravan odabir za ispis.\n");
				break;
			}
			break;

		case DELETE_DEST:
			dest_print_question(dest_field, dest_count);
			int delete_id = 0;
			PRINT_AND_READ_PROMPT("\nUnesite ID destinacije koju zelite izbrisati: ", delete_id);

			delete_attempt_count++;
			delete_destination(&dest_field, &dest_count, delete_id, dest_file);
			break;

		case EXIT:
			free(dest_field);
			dest_field = NULL;
			printf("\nU ovoj iteraciji programa ste pokusali %d puta izbrisati destinaciju.", delete_attempt_count);
			return 0;

		default:
			printf("\nNeispravan odabir. Unesite jednu od ponudenih opcija: ");
		}
	}

	return 0;
}