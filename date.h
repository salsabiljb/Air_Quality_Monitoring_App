#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#define FORMAT_DATE "%d-%d-%d %d:%d:%d"
#define DATE_INPUT_LENGTH 20



typedef struct Date 
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Date;


//fonction permettant de creer une date
Date* creer_date(int year, int month, int day, int hour, int minute, int second);

//fonction permettant de saisir une date
Date* saisir_date() ;

//fonction permettant d'afficher une date
void afficher_date(const Date* date) ;

//fonction permettant de convertir une date en une chaine de caractere
void date_to_string(const Date* date, char* str);

//fonction permettant de convertir une chaine de caractere en une structure date
int string_to_date(const char* str, Date* date);

#endif // DATE_H_INCLUDED
