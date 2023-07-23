#define DATA_SIZE 50
void add_student(char name[],char enrollment[],int sem,char course_name[5][15])
{
	//for traversing the list
	struct studentData *ptrs;
	struct course *ptrc;
	struct courseData *cptr;
	int flag=1,i;
	//Copying student data
	struct studentData *student=(struct studentData*)malloc(sizeof(struct studentData));
	for(i=0;i<5;i++)
	{
		strcpy(student->course_name[i],course_name[i]);
	}
	//checking slot
	int slot=0,check=1;
	flag=1;
    int slot_count[26]={0};
    while(student->course_name[i]!=NULL && flag==1)
    {
    	ptrc=cptr1;
    	while(ptrc && check && flag==1)
    	{
		
    		if(strcmp(ptrc->course_name,student->course_name[i]))
    		{
    			slot=(int)ptrc->slot;
    			check=0;
			}
        	slot_count[slot-65]++;
        	if(slot_count[slot]>1)
        	{
            	printf("cannot be added as two courses with same slot are present");
            	flag=0;
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
		if(sptr1==NULL)
		{
			sptr1=student;
		}
		else
		{
			ptrs=sptr1;
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
		ptrc=cptr1;
		flag=1;
		while(ptrc && flag)
		{
			if(strcmp(ptrc->course_name,student->course_name[j]))
			{
				struct courseData* temp =(struct courseData*)malloc(sizeof(struct courseData));
				strcpy(student->name,temp->name);
				strcpy(student->enrollment_number,temp->enrollment);
				ptrc->count++;
				cptr=ptrc->down;
				if(cptr==NULL)
				{
					cptr=temp;
				}
				else
				{
					while(cptr->down)
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

