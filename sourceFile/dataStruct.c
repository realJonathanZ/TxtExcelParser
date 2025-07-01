#include "dataStruct.h"

// int main() {
//     DS* head = NULL;

//     // create first data section with limited format
//     DS* section1 = createDataSection();
//     addKeyValueLast(section1, "UID", "001");
//     addKeyValueLast(section1, "Name", "Motion Fitness Brighton");
//     addKeyValueLast(section1, "Address", "153 Gibson Bnd, Saskatoon, SK S7V 0P1, Canada");
//     addKeyValueLast(section1, "Rating", "4.4");
    
//     // create next data section with potential enlarged format
//     DS* section2 = createDataSection();
//     addKeyValueLast(section2, "UID", "002");
//     addKeyValueLast(section2, "Name", "Anytime Fitness");
//     addKeyValueLast(section2, "Address", "1804 McOrmond Dr #160, Saskatoon, SK S7S 0A6, Canada");
//     addKeyValueLast(section2, "Contact", "306-555-0123");
//     addKeyValueLast(section2, "MetaInfo", "24/7 access available");
//     addKeyValueLast(section2, "Website", "www.anytimefitness.com");
//     addKeyValueLast(section2, "Rating", "4.4");

//     addDataSectionLast(&head, section1);
//     addDataSectionLast(&head, section2);

//     printDataSections(head);
    
//     // Test getValue function
//     printf("Section 2 Contact: %s\n", getValue(section2, "Contact"));
//     printf("Section 1 Name: %s\n", getValue(section1, "Name"));

//     freeDataSections(head);
//     return 0;
// }

// to create empty data section
DS* createDataSection() {
    DS* section = (DS*)malloc(sizeof(DS));
    if (section == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    section->fields = NULL;
    section->next = NULL;
    return section;
}

// Create a key-value pair
KV* createKeyValue(const char* key, const char* value) {
    KV* kv = (KV*)malloc(sizeof(KV));
    if (kv == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(kv->key, key);
    strcpy(kv->value, value);
    kv->next = NULL;
    return kv;
}

// add a key-value pair to a data section, placed at the end of the linked list
void addKeyValueLast(DS* section, const char* key, const char* value) {
    KV* newKV = createKeyValue(key, value);
    if (newKV == NULL) return;
    
    if (section->fields == NULL) {
        section->fields = newKV;
        return;
    }
    
    KV* current = section->fields;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newKV;
}

// add data section to the end of the linked list of data sections
void addDataSectionLast(DS** head, DS* newSection) {
    if (*head == NULL) {
        *head = newSection;
        return;
    }

    DS* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newSection;
}

// get value by key from a data section
char* getValue(DS* section, const char* key) {
    KV* current = section->fields;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // if key not found, return NULL
}

// print all data sections
void printDataSections(DS* head) {
    DS* currentSection = head;
    int sectionIndex = 0;
    
    while (currentSection != NULL) {
        printf("Data Section %d as below:\n", sectionIndex);

        KV* currentKV = currentSection->fields;
        while (currentKV != NULL) {
            printf("%s:%s\n", currentKV->key, currentKV->value);
            currentKV = currentKV->next;
        }
        printf("\n");
        
        currentSection = currentSection->next;
        sectionIndex++;
    }
}

// free all
void freeDataSections(DS* head) {
    DS* currentSection = head;
    while (currentSection != NULL) {
        // free all key-value pairs in the current section
        KV* currentKV = currentSection->fields;
        while (currentKV != NULL) {
            KV* tempKV = currentKV;
            currentKV = currentKV->next;
            free(tempKV);
        }
        
        // Free the section itself
        DS* tempSection = currentSection;
        currentSection = currentSection->next;
        free(tempSection);

        // then in next loop iteration, free the next section, and all key-value pairs in it.
    }
}



