#include <xlsxwriter.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void csvToExcel(const char* csvFile, const char* excelFile) {
    lxw_workbook* workbook = workbook_new(excelFile);
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
    
    FILE* file = fopen(csvFile, "r");
    if (!file) {
        printf("Error opening CSV file: %s\n", csvFile);
        workbook_close(workbook);
        return;
    }
    printf("execution happening in csvToExcel function body\n");
}

int main() {
    csvToExcel("./csvMiddleOutput/example.csv", "./output/example.xlsx");
    return 0;
}