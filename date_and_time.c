#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

const int MAX_CHARS = 20;
char * DATE_NO_TIME = "%x";
char * DATE_W_TIME = "%x - %I:%M%p";

int strn_to_int(char * str, int n)
{
  //converts a string of n characters to an integer
  char copied_str[n + 1];


  int i;
  for (i = 0; i < n && str[i] != '\0'; i++)
  {
    copied_str[i] = str[i];
  }

  copied_str[i] = '\0';

  return atoi(copied_str);
}


int is_num(char c)
{
  switch (c)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return 1;
    default:
      return 0;
  }
}

int is_dash_slash(char c)
{
  switch (c)
  {
    case '/':
    case '\\':
    case '-':
      return 1;
    default:
      return 0;
  }
}

int is_colon(char c){
  if (c == ':')
  {
    return 1;
  } else {
    return 0;
  }
}

int is_date(char * str)
{
  if (strlen(str) != 8)
  {
    printf("invalid date, date should be of format MM-DD-YY\n");
    return 0;
  }

  int length = strlen(str);
  char * cur_char = str;
  for (int i = 0; i < length; i++, cur_char++)
  {
    if ((i + 1) % 3 != 0)
    {
      if (!is_num(*cur_char)){
        printf("invalid date, date should be of format MM-DD-YY\n");
        return 0;
      }
    } else if (!is_dash_slash(*cur_char))
    {
      printf("invalid date, date should be of format MM-DD-YY\n");
      return 0;
    }

  }

  int month;
  int day;
  int year;

  month = strn_to_int(str, 2);
  if (month < 1 || month > 12)
  {
    printf("Error: %d is not a valid month\n", month);
    return 0;
  }

  year = strn_to_int(str + 6, 2) + 2000;

  day = strn_to_int(str + 3, 2);

  switch (month) //check if the day of the month is valid
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:

      if (day > 31 || day < 1)
      {
        printf("%d is not a valid day in month %d\n", day, month);
        return 0;
      }
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      if (day > 30 || day < 1)
      {
        printf("%d is not a valid day in month %d\n", day, month);
        return 0;
      }
      break;

    case 2:
      if (!(year % 4)){
        if (day > 29 || day < 1)
        {
          printf("%d is not a valid day in month %d of a leap year\n", day, month);
          return 0;
        }
      } else
      {
        if (day > 28 || day < 1)
        {
          printf("%d is not a valid day in month %d of a non-leap year\n", day, month);
          return 0;
        }
      }
      break;

    default:
      break;
  }
  return 1;
}

int is_time(char * str)
{
  if (strlen(str) != 7)
  {
    printf("invalid time, must be of format \"HH:MM(PM/AM)\" - EX: \"04:35PM\"\n");
    return 0;
  }

  if (!is_num(str[0]) || !is_num(str[1]) || !is_num(str[3]) || !is_num(str[4]))
  {
    printf("invalid time, must be of format \"HH:MM(PM/AM)\" - EX: \"04:35PM\"\n");
    return 0;
  }

  int hour = strn_to_int(str, 2);
  int minute = strn_to_int(str + 3, 2);
  if (hour < 1 || hour > 12 || minute < 0 || minute > 59)
  {
    printf("invalid time, must be of format \"HH:MM(PM/AM)\" - EX: \"04:35PM\"\n");
    return 0;
  }

  if (!is_colon(str[2]))
  {
    printf("invalid time, must be of format \"HH:MM(PM/AM)\" - EX: \"04:35PM\"\n");
    return 0;
  }

  if (strcmp(str + 5, "PM") != 0 && strcmp(str + 5, "AM") != 0)
  {
    printf("invalid time, must be of format \"HH:MM(PM/AM)\" - EX: \"04:35PM\"\n");
    return 0;
  }

  return 1;

}

void print_date(struct tm * date, int display_time){
  char * format_type = display_time == 0 ? DATE_NO_TIME : DATE_W_TIME;
  char date_string [MAX_CHARS];

  strftime(date_string, MAX_CHARS, format_type, date); //can i drop the size_t?

  printf("%s", date_string);
}

int get_wday(int month, int day, int year)
{
  int wday = year % 100;
  wday = wday / 4;
  wday += day;
  switch (month) //add the month's key value
  {
    case 1:
    case 10:
      wday += 1;
      break;
    case 2:
    case 3:
    case 11:
      wday += 4;
      break;
    case 5:
      wday += 2;
      break;
    case 6:
      wday += 5;
      break;
    case 8:
      wday += 3;
      break;
    case 9:
    case 12:
      wday += 6;
      break;
    case 4:
    case 7:
    default:
      break;
  }

  if (year / 100 == 20) //this is dependednt on the century... though I doubt anyone will use this in 100 years
  {
    wday += 6;
  }

  wday += (year % 100);

  wday -= 1;
  if (month <= 2 & !(year % 4)){
    wday -= 1;
  }
  wday = wday % 7;



  return wday;
}

int get_yday(int month, int day, int year)
{
  int yday = 0;

  for (int i = 1; i < month; i++)
  {
    switch(i)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:

        yday += 31;
        break;
      case 4:
      case 6:
      case 9:
      case 11:
        yday += 30;
        break;
      case 2:
        if (!(year % 4))
        {
          yday += 29;
        } else
        {
          yday += 28;
        }
        break;
      default:
        break;
    }
  }

  yday = yday + day - 1;
  return yday;
}

struct tm create_date(int month, int day, int year)
{

  struct tm new_date;

  new_date.tm_sec = 0;
  new_date.tm_min = 0;
  new_date.tm_hour = 0;

  new_date.tm_mday = day;
  new_date.tm_mon = month - 1;
  new_date.tm_year = year - 1900;

  new_date.tm_wday = get_wday(month, day, year);
  new_date.tm_yday = get_yday(month, day, year);

  return new_date;

}

int cmp_dates(struct tm * date_1, struct tm * date_2)
{ //return 1 if date_2 is later, 0 if equal, or -1 if date_1 is later

  if (date_2->tm_year > date_1->tm_year){
    return 1;
  } else if (date_2->tm_year == date_1->tm_year)
  {
    if (date_2->tm_yday > date_1->tm_yday)
    {
      return 1;
    } else if (date_2->tm_yday == date_1->tm_yday)
    {
      return 0;
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}

int cmp_dates_w_time(struct tm * date_1, struct tm * date_2)
{
  if (date_2->tm_year > date_1->tm_year){
    return 1;
  } else if (date_2->tm_year == date_1->tm_year)
  {
    if (date_2->tm_yday > date_1->tm_yday)
    {
      return 1;
    } else if (date_2->tm_yday == date_1->tm_yday)
    {
      if (date_2->tm_hour > date_1->tm_hour)
      {
        return 1;
      } else if (date_2->tm_hour == date_1->tm_hour)
      {
        if (date_2->tm_min > date_1->tm_min)
        {
          return 1;
        } else if (date_2->tm_min == date_1->tm_min)
        {
          return 0;
        } else {
          return -1;
        }
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}

struct tm create_date_w_time(int month, int day, int year, int hour, int minute, int pm)
{

  struct tm new_date;

  new_date.tm_sec = 0;
  new_date.tm_min = minute;
  new_date.tm_hour = hour;

  if (pm){
    new_date.tm_hour += 12;
  }

  new_date.tm_mday = day;
  new_date.tm_mon = month - 1;
  new_date.tm_year = year - 1900;

  new_date.tm_wday = get_wday(month, day, year);
  new_date.tm_yday = get_yday(month, day, year);

  return new_date;

}


struct tm string_to_date(char * str)
{
  //we assume this string has already been tested and shown to be valid
  int month;
  int day;
  int year;

  month = strn_to_int(str, 2);
  year = strn_to_int(str + 6, 2) + 2000;
  day = strn_to_int(str + 3, 2);

  struct tm new_date = create_date(month, day, year);
  return new_date;
}

struct tm string_to_date_w_time(char * date_str, char * time_str)
{
  int month;
  int day;
  int year;
  int hour;
  int minute;
  int pm;

  month = strn_to_int(date_str, 2);
  year = strn_to_int(date_str + 6, 2) + 2000;
  day = strn_to_int(date_str + 3, 2);

  hour = strn_to_int(time_str, 2);
  minute = strn_to_int(time_str + 3, 2);

  if (strcmp(time_str + 5, "PM") == 0)
  {
    pm = 1;
  } else {
    pm = 0;
  }

  struct tm new_date = create_date_w_time(month, day, year, hour, minute, pm);
  return new_date;
}

// File IO

void read_date(struct tm * date, FILE * ifp)
{
  date->tm_sec = getw(ifp);
  date->tm_min = getw(ifp);
  date->tm_hour = getw(ifp);
  date->tm_mday = getw(ifp);
  date->tm_mon = getw(ifp);
  date->tm_year = getw(ifp);
  date->tm_wday = getw(ifp);
  date->tm_yday = getw(ifp);
  date->tm_isdst = getw(ifp);
}

void write_date(struct tm * date, FILE * ofp)
{
  putw(date->tm_sec, ofp);
  putw(date->tm_min, ofp);
  putw(date->tm_hour, ofp);
  putw(date->tm_mday, ofp);
  putw(date->tm_mon, ofp);
  putw(date->tm_year, ofp);
  putw(date->tm_wday, ofp);
  putw(date->tm_yday, ofp);
  putw(date->tm_isdst, ofp);
}
