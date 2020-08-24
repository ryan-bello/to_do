#ifndef _GOAL_LIST_H
#define _GOAL_LIST_H

const int MAX_CHARS;
char * DATE_NO_TIME;
char * DATE_W_TIME;

typedef struct{
  struct tm date_set;
  struct tm date_target; //day the goal was initially intended to be completeted
  struct tm date_completed;
  char * name;
  char has_target; //boolean telling whether a target date is set
  char is_completed; //boolean that tells if it's been completed or not
  char is_expired; //true if the date_target has been passed but still hasn't been completed
} goal;

void check_errors(int error_status);
void print_date(struct tm * date, int display_time);
void add_goal(char ** argv, int argc);
int print_current_goals();
int print_past_goals();
int print_all_goals(); // is this function really necessary?
char **parse_args(char * arguments, int *argc);
void free_parsed_args(char **argv);

struct tm string_to_date(char * str);
goal create_goal(char * name, struct tm target_date, int has_target);
#endif
