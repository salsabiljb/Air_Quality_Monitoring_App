#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

//fonction permettant de creer une date
Date* creer_date(int year, int month, int day, int hour, int minute, int second) {
    Date* date = malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    date->hour = hour;
    date->minute = minute;
    date->second = second;
    return date;
}

//************************************************************************************************************


//fonction permettant de saisir une date
Date* saisir_date() {
    int year, month, day, hour, minute, second;
    char input[DATE_INPUT_LENGTH];

    while (fgets(input, DATE_INPUT_LENGTH, stdin)!= NULL) {
        printf("Entrer la date et heure (YYYY-MM-DD HH:MM:SS): ");
        fflush(stdin);
        fgets(input, DATE_INPUT_LENGTH, stdin);
        if (sscanf(input, FORMAT_DATE, &year, &month, &day, &hour, &minute, &second) == 6) {
            if (year >= 1900 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31 && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
                break;
            }
        }
        else
        printf("Invalid input. Please try again.\n");
    }
    return creer_date(year, month, day, hour, minute, second);
}

//************************************************************************************************************


//fonction permettant d'afficher une date
void afficher_date(const Date* date) {
    printf("%d-%02d-%02d %02d:%02d:%02d", date->year, date->month, date->day, date->hour, date->minute, date->second);
}

//************************************************************************************************************


//fonction permettant de convertir une date en une chaine de caractere
void date_to_string(const Date* date, char* str) {
    snprintf(str, DATE_INPUT_LENGTH, "%d-%02d-%02d %02d:%02d:%02d", date->year, date->month, date->day, date->hour, date->minute, date->second);
}

//************************************************************************************************************


//fonction permettant de convertir une chaine de caractere en une structure date
int string_to_date(const char* str, Date* date) {
    return sscanf(str, FORMAT_DATE, &date->year, &date->month, &date->day, &date->hour, &date->minute, &date->second) == 6;
}

//************************************************************************************************************
