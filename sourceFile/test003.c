#include "dataStruct.h"
#include "structToCSV.h"
#include "parserToStruct.h"

int main() {
    printf("This is the test for parsing real txt from ./input and generate csv from that txt, to see if the correct csv is outputted?\n\n");
    
    // parse the txt file
    printf("Step 1: parsing input txt file...\n");
    DS* txtData = parseInputFile("./input/gym_20250629_180150.txt");
    
    if (txtData == NULL) {
        printf("Error: Could not parse txt input file!\n");
        return 1;
    }
    
    printf("successfully parsed gym data!\n");

    // display parsed data for verification
    printf("\nStep 2: displaying parsed data:\n");
    printDataSections(txtData);
    
    // generate CSV from parsed data
    printf("\nStep 3: generating CSV file...\n");
    generateCSV(txtData, "./csvMiddleOutput/gym_data.csv");
    
    // test individual functions
    printf("\nfunction unit tests..\n");
    
    // Test getAllUniqKeys
    int keyCount = 0;
    char** uniqueKeys = getAllUniqKeys(txtData, &keyCount);

    printf("[test]Unique keys found: %d\n", keyCount);
    for (int i = 0; i < keyCount; i++) {
        printf("  %d: '%s'\n", i + 1, uniqueKeys[i]);
    }
    
    // Test isObtained
    printf("\ntest isObtained():\n");
    printf("  'Name' exists: %s\n", isObtained(uniqueKeys, keyCount, "Name") ? "YES" : "NO");
    printf("  'Address' exists: %s\n", isObtained(uniqueKeys, keyCount, "Address") ? "YES" : "NO");
    printf("  'NonExistent' exists: %s\n", isObtained(uniqueKeys, keyCount, "NonExistent") ? "YES" : "NO");
    
    // Test helper functions
    printf("\ntest helper functions:\n");
    char testStr[100] = "Test";
    printf("  Before addComma: '%s'\n", testStr);
    addComma(testStr);
    printf("  After addComma: '%s'\n", testStr);
    addNewline(testStr);
    printf("  After addNewline: '%s'\n", testStr);
    
    // Cleanup
    printf("\nStep 4: cleaning up memory...\n");
    freeUniqKeys(uniqueKeys, keyCount);
    freeDataSections(txtData);

    printf("\ntest completed\n");

    
    return 0;
}