#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data-types.h"
#include "user-input.h"

extern int g_update_count; // Deklaracija vanjske varijable


void find_best_destinations(const DESTINATION* dest_array, int dest_count, const USER_PREFERENCES* preferences) {
    printf("Destinacije koje odgovaraju unesenim uvjetima: \n");
    int found = 0; // Varijabla za provjeru je li pronadena neka destinacija

    for (int i = 0; i < dest_count; i++) {
        if (dest_array[i].cost <= preferences->budget &&
            dest_array[i].location.continent == preferences->continent &&
            dest_array[i].season == preferences->season) {

            int matches_travel_option = 0;

            // Usporedivanje svakog korisnickog preferiranog prijevoznog sredstva s prijevoznim sredstvima destinacije
            for (int j = 0; j < preferences->num_travel_options; j++) {
                for (int k = 0; k < dest_array[i].num_travel_options; k++) {
                    if (dest_array[i].travel_options[k] == preferences->travel_option[j]) {
                        matches_travel_option = 1;
                        break;
                    }
                }
                if (matches_travel_option) break;
            }

            if (matches_travel_option) {
                print_destination(&dest_array[i]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Nema destinacija koje odgovaraju unesenim uvjetima.\n");
    }
}

void write_destinations_to_file(const char* filename, const DESTINATION* dest_array, int dest_count) {
    FILE* file = fopen(filename, "ab");
    if (!file) {
        perror("Ne mogu otvoriti datoteku za pisanje");
        exit(EXIT_FAILURE);
    }

    fwrite(dest_array, sizeof(DESTINATION), dest_count, file);
    fclose(file);
}

void read_destinations_from_file(const char* filename, DESTINATION** dest_array, int* dest_count) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        *dest_array = NULL;
        *dest_count = 0;
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *dest_count = file_size / sizeof(DESTINATION);
    *dest_array = (DESTINATION*)malloc(file_size);
    if (!*dest_array) {
        perror("\nNeuspjesno alociranje memorije.");
        exit(EXIT_FAILURE);
    }

    fread(*dest_array, sizeof(DESTINATION), *dest_count, file);
    fclose(file);
}

void add_destination(DESTINATION** dest_array, int* dest_count, const char* filename) {
    *dest_array = realloc(*dest_array, (*dest_count + 1) * sizeof(DESTINATION));
    if (*dest_array == NULL) {
        perror("\nRealociranje memorije nije uspjelo.\n");
        exit(EXIT_FAILURE);
    }

    DESTINATION* new_dest = &(*dest_array)[*dest_count];

    FILE* file = fopen(filename, "ab");
    if (!file) {
        perror("\nOtvaranje datoteke za pisanje nije uspjelo.\n");
        exit(EXIT_FAILURE);
    }

    new_dest->id = *dest_count + 1;

    printf("Unesite naziv destinacije: ");
    scanf(" %99[^\n]%*c", new_dest->location.name);

    printf("Unesite naziv drzave: ");
    scanf(" %99[^\n]%*c", new_dest->location.country);

    print_continent_options();
    int continent_choice;
    printf("Odaberite kontinent: ");
    scanf("%d", &continent_choice);
    new_dest->location.continent = (continent_enum)continent_choice;

    printf("Unesite udaljenost (u km): ");
    scanf("%f", &new_dest->location.distance);

    printf("Unesite cijenu (u eurima): ");
    scanf("%f", &new_dest->cost);

    print_travel_options();
    int travel_option_choice;
    new_dest->num_travel_options = 0;
    char more_options;
    do {
        printf("Unesite odabir prijevoznog sredstva: ");
        scanf("%d", &travel_option_choice);
        new_dest->travel_options[new_dest->num_travel_options++] = (travel_option_enum)travel_option_choice;
        if (new_dest->num_travel_options < 4) {
            printf("Zelite li dodati jos jedno prijevozno sredstvo? (Y/N): ");
            scanf(" %c", &more_options);
        }
        else {
            more_options = 'N';
        }
    } while ((more_options == 'Y' || more_options == 'y') && new_dest->num_travel_options < 4);


    print_season_options();
    int season_choice;
    printf("Odaberite najbolje godisnje doba za posjet destinacije: ");
    scanf("%d", &season_choice);
    new_dest->season = (season_enum)season_choice;

    fwrite(new_dest, sizeof(DESTINATION), 1, file);
    fclose(file);

    (*dest_count)++;
}

const char* get_continent_name(continent_enum continent) {
    switch (continent) {
    case EUROPE: return "Europa";
    case ASIA: return "Azija";
    case AFRICA: return "Afrika";
    case NORTH_AMERICA: return "Sjeverna Amerika";
    case SOUTH_AMERICA: return "Juzna Amerika";
    case AUSTRALIA: return "Australija";
    case ANTARCTICA: return "Antarktika";
    default: return "Nepoznato";
    }
}

const char* get_travel_option_name(travel_option_enum option) {
    switch (option) {
    case CAR: return "Automobil";
    case PLANE: return "Avion";
    case TRAIN: return "Vlak";
    case BUS: return "Autobus";
    default: return "Nepoznato";
    }
}

const char* get_season_name(season_enum season) {
    switch (season) {
    case SPRING: return "Proljece";
    case SUMMER: return "Ljeto";
    case AUTUMN: return "Jesen";
    case WINTER: return "Zima";
    default: return "Nepoznato";
    }
}

void print_destination(const DESTINATION* dest) {
    printf("\nID: %d, \nDestinacija: %s, \nDrzava: %s, \nKontinent: %s, \nUdaljenost: %.2f km, \nCijena: %.2f EUR, \nGodisnje doba: %s, \nPrijevozna sredstva: ",
        dest->id,
        dest->location.name,
        dest->location.country,
        get_continent_name(dest->location.continent),
        dest->location.distance,
        dest->cost,
        get_season_name(dest->season));

    for (int i = 0; i < dest->num_travel_options; i++) {
        printf("%s", get_travel_option_name(dest->travel_options[i]));
        if (i < dest->num_travel_options - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void print_destinations(const DESTINATION* dest_array, int dest_count) {
    for (int i = 0; i < dest_count; i++) {
        print_destination(&dest_array[i]);
    }
    printf("----------------------------------------------------------------------------\n");
}

void delete_destination(DESTINATION** dest_array, int* dest_count, int delete_id, const char* filename) {
    int found = 0;
    for (int i = 0; i < *dest_count; i++) {
        if ((*dest_array)[i].id == delete_id) {
            found = 1;
            for (int j = i; j < *dest_count - 1; j++) {
                (*dest_array)[j] = (*dest_array)[j + 1];
            }
            (*dest_count)--;
            *dest_array = realloc(*dest_array, (*dest_count) * sizeof(DESTINATION));
            if (*dest_array == NULL && *dest_count > 0) {
                perror("\nRealociranje memorije nije uspjelo.");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }

    if (!found) {
        printf("\nDestinacija s ID-om %d nije pronadena.\n", delete_id);
        return;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("\nDatoteka za pisanje nije uspjesno otvorena.");
        exit(EXIT_FAILURE);
    }

    fwrite(*dest_array, sizeof(DESTINATION), *dest_count, file);
    fclose(file);

    printf("\nDestinacija s ID-em %d uspjesno izbrisana.\n", delete_id);
}

void sort_destinations_by_price(DESTINATION* dest_array, int dest_count, int ascending) {
    if (ascending) {
        qsort(dest_array, dest_count, sizeof(DESTINATION), compare_asc);
    }
    else {
        qsort(dest_array, dest_count, sizeof(DESTINATION), compare_desc);
    }
}

//static fcija jer se koristi samo unutar ove dat
static int compare_asc(const void* a, const void* b) {
    const DESTINATION* destA = (const DESTINATION*)a;
    const DESTINATION* destB = (const DESTINATION*)b;
    if (destA->cost < destB->cost) return -1;
    if (destA->cost > destB->cost) return 1;
    return 0;
}

//static fcija jer se koristi samo unutar ove dat
static int compare_desc(const void* a, const void* b) {
    return compare_asc(b, a); // Reversing order for descending
}

void update_destination_distance(DESTINATION* dest_array, int dest_count, int update_id, const char* filename) {
    int found = 0;
    for (int i = 0; i < dest_count; i++) {
        if (dest_array[i].id == update_id) {
            found = 1;
            printf("Unesite novu udaljenost (u km) za destinaciju %s: ", dest_array[i].location.name);
            scanf("%f", &dest_array[i].location.distance);

            // Azuriranje datoteke
            FILE* file = fopen(filename, "wb");
            if (!file) {
                perror("\nNeuspjesno otvaranje datoteke za pisanje.");
                exit(EXIT_FAILURE);
            }
            fwrite(dest_array, sizeof(DESTINATION), dest_count, file);
            fclose(file);

            printf("Udaljenost za destinaciju %s je uspjesno azurirana.\n", dest_array[i].location.name);
            g_update_count++; // Povecaj brojac azuriranja
            printf("Broj azuriranja do sada: %d\n", g_update_count); // Ispis broja azuriranja
            break;
        }
    }

    if (!found) {
        printf("Destinacija s ID-om %d nije pronadena.\n", update_id);
    }
}

// Rekurzivna funkcija koja računa ukupnu cijenu svih destinacija
float calculate_total_cost(const DESTINATION* dest_array, int dest_number) {
    if (dest_number == 0) {
        return 0.0f;
    }
    return dest_array[0].cost + calculate_total_cost(dest_array + 1, dest_number - 1);
}

float calculate_average_cost(const DESTINATION* dest_array, int dest_count) {
    if (dest_count == 0) {
        return 0.0f;
    }
    float total_cost = calculate_total_cost(dest_array, dest_count);
    return total_cost / dest_count;
}