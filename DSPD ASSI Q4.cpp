

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
					if(ptr->alloted_class != clptr->class_name)
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
				}
			}
			clptr=clptr->next;
		}
		slotc=ptrc->slot;
        assign[slotc]=1;
        ptrc->alloted_class=loc;
    	ptrc=ptrc->next;
    	min=INT_MAX;
	}
	 
}
