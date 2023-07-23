#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define SIZE 1000

struct course
{
    char course_name[10];
    int slot;
    int count;
    int alloted_class;
    struct course* next;
    struct courseData* down;
};

struct courseData 
{
	char name[50];
	char enrollment[10];
	struct courseData* down;
};

struct studentData
{
    char name[50];
    char enrollment_number[10];
    int sem;
    int seati;
    int seatj;
    int class_name;
	char course_name[5][15];
 	struct studentData* next;
};

struct Classroom
{
    int capacity;
    int class_name;
    int seats_assigned[4][5];
    struct Classroom* next;
};

struct studentData *sptr1=NULL,*sptr2=NULL; 
struct course *cptr1=NULL,*cptr2=NULL;
struct Classroom *dptr=NULL;

