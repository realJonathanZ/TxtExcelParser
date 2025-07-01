#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Key-Value pair structure (dictionary). One single dictionary containing info for one data section.
typedef struct KeyValue {
    char key[50];           // example "UID", "Name", "Address", "Rating"(or even more)
    char value[200];        // actual value corresponding to the key
    struct KeyValue* next;  // pointer to next key-value-pair
} KV;

// assume input file contains an infoHeader and all sections can be viewed as a DataSection
typedef struct DataSection {
    KV* fields;               // linked list of key-value pairs
    struct DataSection* next; // pointer to next data section
} DS;

// Function prototypes
DS* createDataSection();
KV* createKeyValue(const char* key, const char* value);
void addKeyValueLast(DS* section, const char* key, const char* value);
void addDataSectionLast(DS** head, DS* newSection);
char* getValue(DS* section, const char* key);
void printDataSections(DS* head);
void freeDataSections(DS* head);

#endif // DATASTRUCT_H