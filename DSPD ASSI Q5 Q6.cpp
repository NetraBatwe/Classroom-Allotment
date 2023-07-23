void allot_seats()
{
    struct Classroom *ccptr=dptr;
    struct studentData *s1=sptr1,*s2=sptr2;
    int i=0,j=0,flag=1;
    flag=1;
    while(ccptr)
    {
        int benches_per_row=ccptr->capacity/12;
        for(int j=0 ; j<benches_per_row*3 ; j++)
        {
            for(int i=0 ; i<4 ; i++)
            {
                if(flag==1)
                {
                    strcpy(ccptr->seats_assigned[i][j],s1->enrollment_number);
                    s1->class_name=ccptr->class_name;
                    s1->seati=i;
                    s1->seatj=j;
                    s1=s1->next;
                }
                else if(flag==0)
                {
                    strcpy(ccptr->seats_assigned[i][j],s2->enrollment_number);
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
        printf("seat alloted for %s in class %d is at row no. %d and bench no. %d.",s1->enrollment_number,s1->class,s1->seati,s1->seatj);
        s1=s1->next;
    }
    while(s2)
    {
        printf("seat alloted for %s in class %d is at row no. %d and bench no. %d.",s2->enrollment_number,s2->class,s2->seati,s2->seatj);
        s2=s2->next;
    }
}
