

void deletion(struct studentData* s)
{
	int i=0,flag=0,found=0;
	struct course* cptr;
	struct studentData* ptr=sptr1;
	for(i=0;i<5;i++)
	{
		cptr=cptr1;
		flag=0;
		while(cptr && !flag)
		{
			if(strcmp(s->course_name[i],cptr->course_name))
			{
				flag=1;
				struct courseData* ptr=cptr->down,*prev=NULL;
				found=0;
				while(ptr && !found)
				{
					if(strcmp(s->enrollment_number,ptr->enrollment))
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
		struct studentData* sptr=sptr1,*prevs=NULL;
		while(sptr)
		{
			if(strcmp(sptr->enrollment_number,s->enrollment_number))
			{
				if(prevs==NULL)
				{
					sptr1=sptr1->next;
					free(sptr);
			    }
			    else
			    {
			    	prevs->next=sptr->next;
			    	free(sptr);
				}
			}
			prevs=sptr;
			sptr=sptr->next;
		}
	}

}
