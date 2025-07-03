#include "dataStruct.h"
#include "structToCSV.h"

int main() {
    printf("This is the test for manual created DS* head to see if correct csv is generated?\n\n");
    
    // create manual test data
    DS* head = NULL;
    
    // Gym 1: complete data
    DS* gym1 = createDataSection();
    addKeyValueLast(gym1, "UID", "001");
    addKeyValueLast(gym1, "Name", "Motion Fitness Brighton");
    addKeyValueLast(gym1, "Address", "153 Gibson Bnd, Saskatoon, SK S7V 0P1, Canada");
    addKeyValueLast(gym1, "Rating", "4.4");
    addKeyValueLast(gym1, "Contact", "306-555-0123");
    addDataSectionLast(&head, gym1);
    
    // Gym 2: missing some fields, has extras
    DS* gym2 = createDataSection();
    addKeyValueLast(gym2, "UID", "002");
    addKeyValueLast(gym2, "Name", "Anytime Fitness");
    addKeyValueLast(gym2, "Rating", "4.2");
    addKeyValueLast(gym2, "Website", "www.anytimefitness.com");
    addKeyValueLast(gym2, "Hours", "24/7");
    addDataSectionLast(&head, gym2);
    
    // Gym 3: different field combination
    DS* gym3 = createDataSection();
    addKeyValueLast(gym3, "UID", "003");
    addKeyValueLast(gym3, "Name", "Local Gym & Spa");
    addKeyValueLast(gym3, "Address", "456 Oak Ave, City, Province");
    addKeyValueLast(gym3, "Rating", "4.8");
    addKeyValueLast(gym3, "Amenities", "Pool, Sauna, Classes");
    addDataSectionLast(&head, gym3);
    
    printf("Created 3 test gym sections with different field combinations\n");
    
    // generate CSV
    generateCSV(head, "./csvMiddleOutput/manual_test.csv");
    
    
    // cleanup
    freeDataSections(head);

    printf("\n manual test is done. test002 \n");
    return 0;
}