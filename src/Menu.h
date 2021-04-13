#ifndef MENU_H
#define MENU_H

typedef struct {
  const char *title;
  void (*function)();
  bool is_section_header;
} FunctionRecord;

extern const FunctionRecord STAFF_MENU[];
extern const FunctionRecord STUDENT_MENU[];
extern const int NUM_STAFF_MENU;
extern const int NUM_STUDENT_MENU;

#endif
