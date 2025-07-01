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
    printf("execution happening in csvToExcel function body before trying to write to sheet\n");

    worksheet_write_string(worksheet, 0, 0, "Bruh", NULL);  // A1 = "Bruh"
    worksheet_write_string(worksheet, 0, 1, "hurB", NULL);  // B1 = "hurB"
    worksheet_write_string(worksheet, 1, 0, "Hey", NULL);   // A2 = "Hey"
    worksheet_write_string(worksheet, 1, 1, "yeH", NULL);   // B2 = "yeH"
    printf("execution done: writing to sheet\n");

    fclose(file);
    workbook_close(workbook);
}

int main() {
    csvToExcel("./csvMiddleOutput/example.csv", "./output/example.xlsx");
    return 0;
}