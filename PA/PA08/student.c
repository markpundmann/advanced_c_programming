#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define MAXIMUM_LENGTH 80
/* You may use this constant in at most one place in this program */
/* You will use 1 point (25% of the full score) if you use it in two
   or more places */

/* You MUST NOT use any constant, such as 65 or 97, below.  If you
 * Need a constant, you must declare a symbol above.  You will lose
 * one point (25% of the full score) for each occurrence of a numeric
 * constant below.  
 * 
 * Reason: unexplained constants make programs difficult to understand
 * and difficult to debug.  When you write 96, what does it mean? Does
 * it mean 97 - 1 (the character before 'a')? Does it mean 3 * 32?
 */

/* 
 * You CANNOT use while, for, goto or anything similar in this
 * program.  If you need to traverse a linked list, you need to use
 * recursion.
 */

/*
 * ================================================
 */
Student *Student_create(int id, char *name)
{
  Student *student = malloc(sizeof(Student));
  if(student == NULL)
  {
    return NULL;
  }
  student->ID = id;
  student->name = strdup(name);
  student->next = NULL;
  return student;
}

void Student_destroy(Student *student)
{
  free(student->name);
  free(student);
}

Student *Student_insertfront(Student *head, Student *student)
{
  if(head == NULL)
  {
    return student;
  }
  student->next = head;
  return student;
}



Student * readStudent(char * infile)
/*
 * This function opens the file whose name is given as the
 * argument. If the file cannot be opened, the function returns NULL.
 * You must use NULL.  Do not use the numeric value 0 becaue they have
 * different meanings.
 *
 * If the file is opened successfully, the function reads the records.
 * Each student has an ID (integer) and a name (string).  For
 * simplicity, each student's name is only one string, not two for
 * first name and last name.  Each student's record uses one line;
 * i.e., two students use two differnet lines.
 * 
 * It is possible that a line has no record.  Please be careful that
 * this "empty" line may contain space or invisible characters. Your
 * program should discard the lines that do not include an integer and
 * a string.
 *
 * The program stores the students' records in a linked list.  You do
 * not have to sort the record inside this function.
 *
 * This function returns the first node of the linked list.  Please
 * remember a valid linked list should end with NULL.
 *
 */
{
  FILE *f = fopen(infile, "r");
  if(f == NULL)
  {
    return NULL;
  }

  int id;
  Student *head = NULL;
  char buffer[MAXIMUM_LENGTH];
  while(fscanf(f, "%d %s", &id, buffer) == 2)
  {
    Student *student = Student_create(id, buffer);
    head = Student_insertfront(head, student);
  }
  fclose(f);


  return head;
}

/*
 * ================================================
 */

int writeStudentRec(FILE *f, Student *head)
{
//base case
  if(head==NULL)
  {
    return EXIT_SUCCESS;
  }
  if(fprintf(f, "%d %s\n", head->ID, head->name) == 0)
  {
    return EXIT_FAILURE;
  }
  
//recursive calls
  return writeStudentRec(f, head->next);

}


int writeStudent(char * outfile, Student * stu)
/*
 * This function opens the file whose name is given as the first
 * argument. If the file cannot be opened, the function returns
 * EXIT_FAILURE.
 *
 * The second argument is the first node of a linked list. 
 *
 * If the file is opened successfully, the function writes the
 * students' records to the file, one student per line, in
 * the order of the linked list.
 *
 * This function must not write any empty line.
 *
 * The function closes the file and returns EXIT_SUCCESS.
 */
{
  FILE *fout = fopen(outfile, "w");
  if(fout == NULL)
  {
    return EXIT_FAILURE;
  }
  int returnvalue = writeStudentRec(fout, stu);
  

  fclose(fout);
  return returnvalue;
}

/*
 * ================================================
 */
typedef enum { BY_ID, BY_NAME } StudentField;

Student *insertByWhat(Student *head, Student *student, StudentField byWhat)
{
  if(head == NULL)
  {
    student->next = NULL;
    return student;
  }
  switch(byWhat)
  {
  case BY_ID:
    if(head->ID > student->ID)
    {
      student->next = head;
      return student;
    }
    break;
  case BY_NAME:
    if(strcmp(head->name, student->name) > 0)
    {
      student->next = head;
      return student;
    }
    break;
  }
  head->next = insertByWhat(head->next, student, byWhat);
  return head;  

}


Student *sortByWhat(Student *src, Student *dst, StudentField bywhat)
{
  if(src == NULL)
  {
    return dst;
  }
  Student *next = src->next;
  dst = insertByWhat(dst, src, bywhat);
  return sortByWhat(next, dst, bywhat);

}


Student * sortStudentbyID(Student * stu)
{
  return sortByWhat(stu, NULL, BY_ID);
}

Student * sortStudentbyName(Student * stu)
{
  return sortByWhat(stu, NULL, BY_NAME);
}

void freeStudent(Student * stu)
{
  if(stu == NULL)
  {
    return;
  }
  freeStudent(stu->next);
  Student_destroy(stu);

}

