/* testing for function inside structToCSV.c */

#include "dataStruct.h"
#include "structToCSV.h"

int main() {
    // for testing with unique keys
    DS* head = NULL;
    
    // section 1: has UID, Name, Address, Rating
    DS* section1 = createDataSection();
    addKeyValueLast(section1, "UID", "001");
    addKeyValueLast(section1, "Name", "Motion Fitness");
    addKeyValueLast(section1, "Address", "123 Main St");
    addKeyValueLast(section1, "Rating", "4.4");
    addDataSectionLast(&head, section1);
    
    // section 2: has UID, Name, Contact, Website 
    DS* section2 = createDataSection();
    addKeyValueLast(section2, "UID", "002");
    addKeyValueLast(section2, "Name", "Anytime Fitness");
    addKeyValueLast(section2, "Contact", "306-555-0123");
    addKeyValueLast(section2, "Website", "www.anytime.com");
    addDataSectionLast(&head, section2);
    
    // section 3: has UID, Hours, Rating 
    DS* section3 = createDataSection();
    addKeyValueLast(section3, "UID", "003");
    addKeyValueLast(section3, "Hours", "6AM-10PM");
    addKeyValueLast(section3, "Rating", "4.8");
    addDataSectionLast(&head, section3);
    
    printf("Created test data with 3 sections:\n");
    printf("Section 1 keys: UID, Name, Address, Rating\n");
    printf("Section 2 keys: UID, Name, Contact, Website\n");
    printf("Section 3 keys: UID, Hours, Rating\n");
    printf("Expected unique keys: UID, Name, Address, Rating, Contact, Website, Hours\n\n");
    
    // test for getAllUniqKeys() in structToCSV.c
    printf("*****Testing getAllUniqKeys*****\n");
    int unique_key_count = 0;
    printf("There is %d unique keys at first in the data sections.\n", unique_key_count);

    char** uniqueKeys = getAllUniqKeys(head, &unique_key_count);
    printf("There is %d unique keys after getAllUniqKeys() in the data sections.\n", unique_key_count);

    for (int i = 0; i < unique_key_count; i++) {
        printf("  %d: '%s'\n", i + 1, uniqueKeys[i]);
    }

    // test for isObtained()
    printf("\n*****Testing isObtained Function*****\n");
    printf("Testing if 'UID' exists, returning value %d\n", isObtained(uniqueKeys, unique_key_count, "UID") );
    printf("Testing if 'Name' exists, returning value %d\n", isObtained(uniqueKeys, unique_key_count, "Name") );
    printf("Testing if 'Bruh' exists, returning value %d\n", isObtained(uniqueKeys, unique_key_count, "NonExistent") );
}