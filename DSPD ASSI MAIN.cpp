#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define SIZE 1000
#define DATA_SIZE 100
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
	char enrollment[11];
	struct courseData* down;
};

struct studentData
{
    char name[50];
    char enrollment_number[11];
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
    int seats_assigned[4][50];
    struct Classroom* next;
};

//Globally declared the head pointer 
struct studentData *sptr1=NULL,*sptr2=NULL;
struct course *cptr1=NULL,*cptr2=NULL;
struct Classroom *dptr=NULL;

//Adding student to the list 
void add_student(char name[],char enrollment[],int sem,char course_name[5][15])
{
	//for traversing the list
	struct studentData *ptrs=NULL;
	struct course *ptrc=NULL;
	struct courseData *cptr;
	int flag=1,i;
	//Copying student data
	struct studentData* student=(struct studentData*)malloc(sizeof(struct studentData));
	for(i=0;i<5;i++)
	{
		strcpy(student->course_name[i],course_name[i]);
	}

	student->sem=sem;

	//checking slot using hash 
	int slot=0,check=1;
	flag=1,i=0;
    int slot_count[10]={0};
    while(i<5 && flag==1)
    {
    	ptrc=cptr1;
    	while(ptrc && check && flag==1)
    	{
		
    		if(strcmp(ptrc->course_name,student->course_name[i])==0)
    		{
    			slot=ptrc->slot;
        		slot_count[slot]++;
        		//happens when previously the slot exists
        		if(slot_count[slot]>1)
        		{
            		printf("cannot be added as two courses with same slot are present\n");
            		flag=0;
        		}
        	}
        	ptrc=ptrc->next;
    	}
        i++;
    }
    //if slot are proper insert node in the list
    if(flag==1)
    {
    	strcpy(student->name,name);
		strcpy(student->enrollment_number,enrollment);
		student->next=NULL;
		student->sem=sem;
		if(student->sem==1)
		{
			if(sptr1==NULL)
			{
				sptr1=student;
			}
			else
			{
				ptrs=sptr1;
			}
		}
		else if(student->sem==2)
		{
			if(sptr2==NULL)
			{
				sptr2=student;
			}
			else
			{
				ptrs=sptr2;
			}
		}
		if(ptrs)
		{
			while(ptrs->next)
			{
				ptrs=ptrs->next;
			}
			ptrs->next=student;
		}
	}
	else
	{
		free(student);
	}
	if(flag==1)
	{
		for(int j=0;j<5;j++)
		{
			if(student->sem==1)
			{
				ptrc=cptr1;
			}
			else if(student->sem==2)
			{
				ptrc=cptr2;
			}
			flag=1;
			while(ptrc && flag)
			{
				if(strcmp(ptrc->course_name,student->course_name[j])==0)
				{
					struct courseData* temp =(struct courseData*)malloc(sizeof(struct courseData));
					strcpy(temp->name,student->name);
					strcpy(temp->enrollment,student->enrollment_number);
					temp->down=NULL;
					ptrc->count++;
					cptr=ptrc->down;
					if(cptr==NULL)
					{
						ptrc->down=temp;
					}
					else
					{
						while(cptr->down != NULL)
						{
							cptr=cptr->down;
						}
						cptr->down=temp;
					}
					flag=0;
				}
			ptrc=ptrc->next;
			}
		}
    }
}
void insertCourse(char courseName[],int slot,int nos,int all,int sem)
{
	struct course *p;
	if(sem==1)
	{
    	p=cptr1;
	}
	else if(sem==2)
	{
		p=cptr2;
	}
    struct course *temp=NULL;
    temp=(struct course*)malloc(sizeof(struct course));
    strcpy(temp->course_name,courseName);
    temp->slot=slot;
    temp->alloted_class=all;
    temp->count=nos;
    temp->next=NULL;
    temp->down=NULL;
	if(sem==1)
	{
		if(cptr1==NULL)
		{
			cptr1=temp;
		}
		else
		{
			while(p->next)
			{
				p=p->next;
			}
			p->next=temp;
		}
	}
	else if(sem==2)
	{
		if(cptr2==NULL)
		{
			cptr2=temp;
		}
		else
		{
			while(p->next)
			{
				p=p->next;
			}
			p->next=temp;
		}
	}
}
void deletecourse(char coursename[])
{
	struct course* ptrc=cptr1,*prev=NULL;
	int flag=1;
	while(ptrc && flag )
	{
		if(strcmp(ptrc->course_name,coursename)==0)
		{
			if(ptrc->down==NULL)
			{
				if(ptrc==cptr1)
				{
					cptr1=ptrc->next;
				}
				else
				{
					prev->next=ptrc->next;
				}
				free(ptrc);
				flag=0;
			}
		}
		prev=ptrc;
		ptrc=ptrc->next;
	}
	if(flag==1)
	{
		printf("Can't delete.");
	}
	
}
void add_classroom(int number, int capacity) 
{
	struct Classroom* clptr=dptr;
    struct Classroom* new_classroom = NULL;
	new_classroom=(struct Classroom*) malloc(sizeof(struct Classroom));
    new_classroom->class_name = number;
    new_classroom->capacity = capacity;
    new_classroom->next = NULL;
    //int benches=capacity/3;
    for(int i=0; i<4; i++) {
        for(int j=0; j<capacity/4; j++) {
            new_classroom->seats_assigned[i][j] = 0;
        }
    }
   
    if(clptr == NULL)
	{
        dptr = new_classroom;
    }
    else
    {
    	 while(clptr->next != NULL)
		{
        	clptr = clptr->next;
    	}
    	clptr->next = new_classroom;
	}
   
}


void allotment()
{
	struct Classroom* clptr=dptr;
	struct course* ptrc=cptr1,*ptr=cptr1;
	int assign[15]={0},flag=1;
	int loc,diff,min=INT_MAX;
    int slotc;
    
    while(ptrc)
    {
    	clptr=dptr;
		while(clptr)
		{
			if(clptr->capacity >= ptrc->count && !assign[ptrc->slot])
			{
				diff=clptr->capacity - ptrc->count;
				if(diff<min)
				{
					min=diff;
					loc=clptr->class_name;
				}
			}
			else if(assign[ptrc->slot])
			{
				ptr=cptr1;
				flag=1;
				while(ptr && flag)
				{
					if(ptr->alloted_class == clptr->class_name)
					{
						diff=clptr->capacity - ptrc->count;
						if(diff<min)
						{
							min=diff;
							loc=clptr->class_name;
						}
					}
					else
					{
						flag=0;
					}
					ptr=ptr->next;
				}
			}
			clptr=clptr->next;
		}
		slotc=ptrc->slot;
        assign[slotc]=1	;
        ptrc->alloted_class=loc;
    	ptrc=ptrc->next;
    	min=INT_MAX;
	}
	 
}
void allot_seats()
{
    struct Classroom *ccptr=dptr;
    struct studentData *s1=sptr1,*s2=sptr2;
    int i=0,j=0,flag=1;
    flag=1;
    while(ccptr)
    {
        int cols=ccptr->capacity/4;
        for(int j=1 ; j<=cols ; j++)
        {
            for(int i=1 ; i<=4 ; i++)
            {
                if(flag==1 && s1)
                {
                    //ccptr->seats_assigned[i][j]=s1->enrollment_number;
                    s1->class_name=ccptr->class_name;
                    s1->seati=i;
                    s1->seatj=j;
                    s1=s1->next;
                   
                }
                else if(flag==0 && s2)
                {
                    //ccptr->seats_assigned[i][j]=s2->enrollment_number;
                    s2->class_name=ccptr->class_name;
                    s2->seati=i;
                    s2->seatj=j;
                    s2=s2->next;
                   
                }
            }
            if(flag==1)
                flag=0;
            else
                flag=1;
        }
        ccptr=ccptr->next;
    }
}
void print()
{
    struct studentData *s1=sptr1;
    struct studentData *s2=sptr2;
    while(s1)
    {
        printf("seat alloted for %s %s in class %d is at row no. %d and bench no. %d.\n",s1->course_name,s1->enrollment_number,s1->class_name,s1->seati,s1->seatj);
        s1=s1->next;
    }
    while(s2)
    {
        printf("seat alloted for %s %s in class %d is at row no. %d and bench no. %d.\n",s2->course_name,s2->enrollment_number,s2->class_name,s2->seati,s2->seatj);
        s2=s2->next;
    }
}
void deletestudent(char enrol[])
{
	int flag=0,found=0;
	struct course* cptr;
	struct studentData* ptr=sptr1,*s;
	struct studentData* sptr=sptr1,*prevs=NULL;
		while(sptr && !flag)
		{
			if(strcmp(sptr->enrollment_number,enrol)==0)
			{
				if(prevs==NULL)
				{
					s=sptr1;
					sptr1=sptr1->next;
			    }
			    else
			    {
			    	prevs->next=sptr->next;
			    	s=sptr;
				}
				flag=1;
			}
			if(flag==0)
			{
				prevs=sptr;
				sptr=sptr->next;
			}	
		}
	int j;
	
	for (j=0;j<5;j++)
	{
		cptr=cptr1;
		flag=0;
		while(cptr && !flag)
		{
			if(strcmp(s->course_name[j],cptr->course_name)==0)
			{
				flag=1;
				struct courseData* ptr=cptr->down,*prev=NULL;
				found=0;
				while(ptr && !found)
				{
					if(strcmp(s->enrollment_number,ptr->enrollment)==0)
					{
						found=1;
						if(prev==NULL)
						{
							cptr->down=ptr->down;
							free(ptr);
						}
					    else
					    {
					    	prev->down=ptr->down;
					    	free(ptr);
						}	
					}
					prev=ptr;
					ptr=ptr->down;
				}
			}	
			cptr=cptr->next;
		}
	
	}
	
	free(s);

}
void printstudentlist(int sem)
{
	struct studentData* ptrs;
	if(sem==1)
	{
		ptrs=sptr1;	
	}
	else if(sem==2)
	{
	    ptrs=sptr2;	
	}
	else
	{
		printf("Invalid!\n");	
	}	
		
	while(ptrs)
	{
		printf("%s %s \n",ptrs->name,ptrs->enrollment_number);
		ptrs=ptrs->next;
	}
}

void printcourselist(int sem)
{
	struct course* ptrc;
	struct courseData* ptr;
	if(sem==1)
	{
		ptrc=cptr1;	
	}
	else if(sem==2)
	{
	    ptrc=cptr2;	
	}
	else
	{
		printf("Invalid!\n");	
	}
	while(ptrc)
	{
		ptr=ptrc->down;
		printf("%s\n",ptrc->course_name);
		while(ptr)
		{
			printf("%s\n",ptr->name);
			ptr=ptr->down;
		}
	
		ptrc=ptrc->next;
	}
}

void loaddata()
{
	FILE *fptrs,*fptrc;
	fptrs=fopen("student_list.txt","r");
	char name[50],enrollment[15],courses[5][15];
	int sem,i=0;
	fptrc=fopen("course_list.txt","r");
	char coursename[10];
	int slots;
	int nos,alltc;
	
	while(i<13)
	{
		
		fscanf(fptrc,"%s %d %d %d %d",coursename,&slots,&nos,&alltc,&sem);
		insertCourse(coursename,slots,nos,alltc,sem);
		i++;
	}
	i=0;
	while(i<37)
	{
		fscanf(fptrs,"%s %s %d",name,enrollment,&sem);
		for(int j=0;j<5;j++)
		{
			fscanf(fptrs,"%s",courses[j]);
		}
		add_student(name,enrollment,sem,courses);
		i++;
	}	
	FILE *fptrcl;
	fptrcl=fopen("classroom.txt","r");
	int capacity,class_name;
	i=1;
	while(i<6)
	{
		fscanf(fptrcl,"%d %d",&class_name,&capacity);
		add_classroom(class_name,capacity);
		i++;
	}
}

int main()
{
	int j,control_line;
	control_line=1;
	loaddata();
		FILE *fptrr=fopen("s_list.txt","r");
		char name[15],enrollment[11],courses[5][15];
		int sem;
	while(control_line!=0)
	{
        printf("\n____________________\n");
		printf("0 -- exit\n");
        printf("1 -- add student to student list\n");
        printf("2 -- delete a student from student list\n");
        printf("3 -- delete course to course list\n");
        printf("4 -- allotment of classrooms for lectures\n");
        printf("5 -- allotment of classrooms for exams\n");
        printf("6 -- print the list of students and exam slot allotted to each student for a given slot\n");

        printf("\nEnter the number beside the function you want to execute : ");
		scanf("%d",&control_line);
		
		switch (control_line)
		{
			case 0: //Exit
			{
				printf("User Interface exited");
				break;
			}
			case 1:
			{
				printstudentlist(1);
				printf("  \n");
				printf("After adding\n");
				fscanf(fptrr,"%s %s %d",name,enrollment,&sem);
				for(int j=0;j<5;j++)
				{
					fscanf(fptrr,"%s",courses[j]);
				}
					printf("  \n");
				add_student(name,enrollment,sem,courses);
				printstudentlist(1);
				break;
			}
			case 2: 
			 {
			 	printstudentlist(1);
				deletestudent("BT21CSE077");
				printf("after deleting\n");
				printstudentlist(1);
				printcourselist(1);
                break;
			}
			
			case 3: 
			{
				printcourselist(1);
				insertCourse("COMP",12,0,0,1);
				printcourselist(1);
				deletecourse("DSPD");
				printf("After deleting");
				printcourselist(1);
			
				break;
			}
			case 4: 
			{
			    struct course* ptrc=cptr1;
                allotment();
				while(ptrc)
				{
					printf("%s : %d\n",ptrc->course_name,ptrc->alloted_class);
					ptrc=ptrc->next;
				}
               break;
			}
			case 5:
			{
				allot_seats();
				printf("Seats alloted\n");
				break;
			}
			case 6:
			{
				print();
				break;
			}
			default:
			{
				printf("Loop exited");
				control_line=0;
				break;
			}
		}
	}
}

