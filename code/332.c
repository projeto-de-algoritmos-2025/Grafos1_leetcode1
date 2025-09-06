#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[4];
    char** destinations;
    int dest_count;
    int capacity;
    int next_ticket_idx;
} Airport;

#define HASH_TABLE_SIZE 300
Airport* graph[HASH_TABLE_SIZE];

unsigned int hash(const char* key) {
    unsigned int hash_value = 0;
    for (int i = 0; i < 3; i++) {
        hash_value = 31 * hash_value + key[i];
    }
    return hash_value % HASH_TABLE_SIZE;
}

Airport* findOrCreateAirport(const char* name) {
    unsigned int index = hash(name);
    while (graph[index] != NULL && strcmp(graph[index]->name, name) != 0) {
        index = (index + 1) % HASH_TABLE_SIZE;
    }

    if (graph[index] != NULL) {
        return graph[index];
    }

    Airport* new_airport = (Airport*)malloc(sizeof(Airport));
    strcpy(new_airport->name, name);
    new_airport->destinations = NULL;
    new_airport->dest_count = 0;
    new_airport->capacity = 0;
    new_airport->next_ticket_idx = 0;
    graph[index] = new_airport;
    return new_airport;
}

void addDestination(Airport* airport, const char* dest) {
    if (airport->dest_count >= airport->capacity) {
        airport->capacity = (airport->capacity == 0) ? 4 : airport->capacity * 2;
        airport->destinations = (char**)realloc(airport->destinations, airport->capacity * sizeof(char*));
    }
    airport->destinations[airport->dest_count++] = strdup(dest);
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void dfs(const char* airport_name, char** itinerary, int* itinerary_count) {
    Airport* airport = findOrCreateAirport(airport_name);

    while (airport->next_ticket_idx < airport->dest_count) {
        char* next_destination = airport->destinations[airport->next_ticket_idx];
        airport->next_ticket_idx++;
        dfs(next_destination, itinerary, itinerary_count);
    }
    itinerary[(*itinerary_count)++] = strdup(airport_name);
}

void freeGraph() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (graph[i] != NULL) {
            for (int j = 0; j < graph[i]->dest_count; j++) {
                free(graph[i]->destinations[j]);
            }
            free(graph[i]->destinations);
            free(graph[i]);
            graph[i] = NULL;
        }
    }
}

