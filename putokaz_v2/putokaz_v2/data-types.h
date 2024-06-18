#pragma once

typedef enum {
    CHOOSE_DEST = 1,	//1. izbor
    ADD_DEST,			//2. izbor
    UPDATE_DEST,		//3. izbor
    PRINT_DEST,			//4. izbor
    DELETE_DEST,		//5. izbor
    EXIT				//6. izbor
}menu_items_enum;

typedef enum {
    EUROPE = 1,
    ASIA,
    AFRICA,
    NORTH_AMERICA,
    SOUTH_AMERICA,
    AUSTRALIA,
    ANTARCTICA
} continent_enum;

typedef enum {
    CAR = 1,
    PLANE,
    TRAIN,
    BUS
} travel_option_enum;

typedef enum {
    SPRING = 1,
    SUMMER,
    AUTUMN,
    WINTER
} season_enum;

typedef struct {
    char name[100];
    char country[100];
    continent_enum continent;
    float distance;
} LOCATION;

typedef struct {
    int id;
    LOCATION location;
    float cost;
    travel_option_enum travel_options[4];
    int num_travel_options;
    season_enum season;
} DESTINATION;

typedef struct {
    float budget;
    continent_enum continent;
    travel_option_enum travel_option[4];
    int num_travel_options;
    season_enum season;
} USER_PREFERENCES;

