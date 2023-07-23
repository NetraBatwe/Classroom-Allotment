void insertCourse(char courseName[],char slot,int nos,int all)
{
    struct course *p=cptr1;
    struct course *temp=NULL;
    temp=(struct course*)malloc(sizeof(struct course));
    strcpy(temp->course_name,courseName);
    temp->slot=slot;
    temp->alloted_class=all;
    temp->count=nos;
    temp->next=NULL;
    temp->down=NULL;
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

void deletecourse(char coursename[])
{
	struct course* ptrc=cptr1,*prev=NULL;
	
	while(ptrc)
	{
		if(strcmp(ptrc->course_name,coursename))
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
			}
			else
			{
				printf("Cant delete as students have taken the course");
			}
		}
		prev=ptrc;
		ptrc=ptrc->next;
	}
	
}
