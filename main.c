#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Ore {
    char name[50];
    int quantity;
    int rarity;
    char color[10];
} Ore;

typedef struct Entry {
    char *key;
    Ore ore;
    struct Entry *next;
} Entry;

typedef struct HashTable {
    Entry **entries;
} HashTable;

unsigned int hash(const char *key) {
    unsigned long int hash = 0;
    int c;

    while ((c = *key++)) {
        hash = hash * 31 + c;
    }

    return hash % TABLE_SIZE;
}

HashTable *create_table() {
    HashTable *table = malloc(sizeof(HashTable));
    table->entries = malloc(sizeof(Entry *) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; i++) {
        table->entries[i] = NULL;
    }

    return table;
}

Entry *create_entry(const char *key, const Ore *ore) {
    Entry *entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->ore = *ore;
    entry->next = NULL;
    return entry;
}

void insert(HashTable *table, const char *key, const Ore *ore) {
    unsigned int index = hash(key);
    Entry *entry = table->entries[index];

    if (entry == NULL) {
        table->entries[index] = create_entry(key, ore);
        return;
    }

    Entry *prev = NULL;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->ore = *ore; // Update the ore information
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    prev->next = create_entry(key, ore);
}

Ore *search(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = table->entries[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return &entry->ore;
        }
        entry = entry->next;
    }

    return NULL;
}

void free_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = table->entries[i];
        while (entry != NULL) {
            Entry *prev = entry;
            entry = entry->next;
            free(prev->key);
            free(prev);
        }
    }
    free(table->entries);
    free(table);
}

void update_item(HashTable *table, const char id[], int quantity, int rarity, const char color[]) {
    Ore *ore = search(table, id);
    if (ore != NULL) {
        ore->quantity = quantity;
        ore->rarity = rarity;
        strcpy(ore->color, color);
        printf("Updated Ore with ID %s: Quantity: %d, Rarity: %d, Color: %s\n", id, ore->quantity, ore->rarity, ore->color);
    } else {
        printf("Ore with ID %s not found.\n", id);
    }
}

void create_item(HashTable *table, const char name[], const char id[], int quantity, int rarity, const char color[]) {
    Ore ore;
    strcpy(ore.name, name);
    ore.quantity = quantity;
    ore.rarity = rarity;
    strcpy(ore.color, color);

    insert(table, id, &ore);

    Ore *found_ore = search(table, id);
    if (found_ore != NULL) {
        printf("Ore name: %s, Quantity: %d, Rarity: %d, Color: %s\n", found_ore->name, found_ore->quantity, found_ore->rarity, found_ore->color);
    } else {
        printf("Ore not found.\n");
    }
}

int main() {
    HashTable *table = create_table();

    create_item(table, "Stone", "stone", 0, 0, "gray");
    create_item(table, "Coal", "coal_ore", 0, 1, "black");
    create_item(table, "Iron Ore", "iron_ore", 0, 2, "dark gray");
    create_item(table, "Iron Ingot", "iron_ingot", 0, 3, "silver");
    create_item(table, "Gold Ore", "gold_ore", 0, 4, "yellow");
    create_item(table, "Gold Ingot", "gold_ingot", 0, 5, "golden");
    create_item(table, "Silver Ore", "silver_ore", 0, 6, "silver");
    create_item(table, "Silver Ingot", "silver_ingot", 0, 7, "light gray");
    create_item(table, "Lead Ore", "lead_ore", 0, 8, "blue-gray");
    create_item(table, "Lead Ingot", "lead_ingot", 0, 9, "dark gray");
    create_item(table, "Tungsten Ore", "tungsten_ore", 0, 10, "silver");
    create_item(table, "Tungsten Ingot", "tungsten_ingot", 0, 11, "light silver");
    create_item(table, "Uranium Ore", "uranium_ore", 0, 12, "green");
    create_item(table, "Uranium Ingot", "uranium_ingot", 0, 13, "glowing green");
    create_item(table, "Diamond", "diamond", 0, 14, "blue");
    create_item(table, "Ruby", "ruby", 0, 15, "red");
    create_item(table, "Emerald", "emerald", 0, 16, "green");
    create_item(table, "Blue Garnet", "blue_garnet", 0, 17, "blue");

    char ch;

    printf("");

    while (1) {
        ch = getch();

        if (ch == 'q') {
            printf("Hello, World!\n");
        }
    }

    free_table(table);
    return 0;
}
