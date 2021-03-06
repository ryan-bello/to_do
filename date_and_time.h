#ifndef _DATE_AND_TIME_H
#define _DATE_AND_TIME_H

const int MAX_CHARS;
char * DATE_NO_TIME;
char * DATE_W_TIME;

void print_date(struct tm * date, int display_time);
void print_goal_array(goal array[], int size);

//File IO
void read_date(struct tm * date, FILE * ifp);
void write_date(struct tm * date, FILE * ofp);

int is_num(char c);
int is_dash_slash(char c);
int is_colon(char c);
int is_date(char * str);
int is_time(char * str);

int strn_to_int(char * str, int n);
int get_wday(int month, int day, int year);
int get_yday(int month, int day, int year);
int cmp_dates(struct tm * date_1, struct tm * date_2);
int cmp_dates_w_time(struct tm * date_1, struct tm * date_2);

struct tm string_to_date(char * str);
struct tm string_to_date_w_time(char * date_str, char * time_str);
struct tm create_date(int month, int day, int year);
struct tm create_date_w_time(int month, int day, int year, int hour, int minute, int pm);


#endif
