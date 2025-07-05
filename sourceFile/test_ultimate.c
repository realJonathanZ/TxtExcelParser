#include "dataStruct.h"
#include "structToCSV.h"
#include "csvToXlsx.h"
#include "parserToStruct.h"

int main() {
    printf("test for directly generate xlsx from input txt.\n");
    printf("while maintaining the middle output csv file in where it should stay.\n");
    printf("B*r*u*h*B*r*u*h*B*r*u*h*B*r*u*h*B*r*u*h*");

    // parse TXT file
    printf("parsing input file...\n");
    DS* gymData = parseInputFile("./input/gym_20250629_180150.txt");
    
    if (gymData == NULL) {
        printf("Error: Could not parse input file\n");
        return 1;
    }
    
    // convert to CSV
    printf("converting to CSV...\n");
    generateCSV(gymData, "./csvMiddleOutput/gym_20250629_180150.csv");

    // convert to Excel sheet (.xlsx)
    printf("converting to Excel sheet (.xlsx)...\n");
    csvToExcel("./csvMiddleOutput/gym_20250629_180150.csv", "./output/gym_20250629_180150.xlsx");

    // cleanup dynam-mem
    freeDataSections(gymData);
    
    printf("Conversion complete.\n");
    printf("Output: ./output/gym_20250629_180150.xlsx\n");

    return 0;
}