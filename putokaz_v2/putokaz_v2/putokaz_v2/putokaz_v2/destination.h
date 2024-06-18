#pragma once
#include "data-types.h"
#include "user-input.h"

void find_best_destinations(const DESTINATION* dest_array, int dest_count, const USER_PREFERENCES* preferences);
void write_destinations_to_file(const char* filename, const DESTINATION* dest_array, int dest_count);
void read_destinations_from_file(const char* filename, DESTINATION** dest_array, int* dest_count);
void add_destination(DESTINATION** dest_array, int* dest_count, const char* filename);
void print_destination(const DESTINATION* dest);
void print_destinations(const DESTINATION* dest_array, int dest_count);
void delete_destination(DESTINATION** dest_array, int* dest_count, int delete_id, const char* filename);
void sort_destinations_by_price(DESTINATION* dest_array, int dest_count, int ascending);
void update_destination_distance(DESTINATION* dest_array, int dest_count, int update_id, const char* filename);
static int compare_asc(const void* a, const void* b);
static int compare_desc(const void* a, const void* b);
float calculate_total_cost(const DESTINATION* dest_array, int dest_number);
float calculate_average_cost(const DESTINATION* dest_array, int dest_count);
