#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void display_month_row(int *m_cday, int *m_cdate, int no_days_month)
{
    for (int space = 1; space < (*m_cday); space++)
        printf(1,"    ");
    while (((*m_cday) != 8) && ((*m_cdate) <= no_days_month))
    {
    	if((*m_cdate) < 10)
    		printf(1," %d", (*m_cdate));
    	else
        	printf(1,"%d", (*m_cdate));
        (*m_cdate)++;
        (*m_cday)++;
        if ((*m_cday) < 8)
            printf(1,"  ");
    }
    if ((*m_cday) == 8)
        (*m_cday) = 1;
    else if ((*m_cdate) == (no_days_month + 1))
    {
        while ((*m_cday) < 8)
        {
            printf(1,"  ");
            (*m_cday)++;
            if ((*m_cday) < 8)
                printf(1,"  ");
        }
        (*m_cday) = 1;
    }
}

int no_days_month(int month, int year)
{
    switch(month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            if(((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) !=0)))
                return 29;
            else
                return 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
    }
    return 0;
}

int day1_mm_yyyy(int mm, int yyyy)
{
    int day1;

    day1 = ((yyyy % 100)/4)+1;

    switch (mm)
    {
        case 1:
        case 10:
            day1 += 1;
            break;
        case 2:
        case 3:
        case 11:
            day1 += 4;
            break;
        case 5:
            day1 += 2;
            break;
        case 6:
            day1 += 5;
            break;
        case 8:
            day1 += 3;
            break;
        case 9:
        case 12:
            day1 += 6;
            break;
    }

    if(((yyyy % 400) == 0) || (((yyyy % 4) == 0) && ((yyyy % 100) !=0)))
    {
        if((mm == 1) || (mm == 2))
            day1 -= 1;
    }

    int temp_yy = yyyy;
    if(temp_yy < 1700)
        while(temp_yy < 1700)
            temp_yy += 400;
    else if(temp_yy > 2099)
        while(temp_yy > 2099)
            temp_yy -= 400;

    if(temp_yy < 1800)
        day1 += 4;
    else if(temp_yy < 1900)
        day1 += 2;
    else if(temp_yy >= 2000)
        day1 += 6;
    
    day1 += (yyyy % 100);
    day1 %= 7;

    switch (day1)
    {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        case 5:
            return 5;
            break;
        case 6:
            return 6;
            break;
        case 0:
            return 7;
            break;
    }
    return 0;
}

void display_yyyy_cal(int yyyy)
{
    for(int month = 1; month < 12;)
    {
        //display month names
        switch(month)
        {
            case 1:
                printf(1,"         JANUARY          ");
                printf(1,"    ");
                printf(1,"         FEBRUARY         ");
                printf(1,"    ");
                printf(1,"          MARCH           ");
                printf(1,"\n");
                break;
            case 4:
                printf(1,"          APRIL           ");
                printf(1,"    ");
                printf(1,"           MAY            ");
                printf(1,"    ");
                printf(1,"           JUNE           ");
                printf(1,"\n");
                break;
            case 7:
                printf(1,"           JULY           ");
                printf(1,"    ");
                printf(1,"          AUGUST          ");
                printf(1,"    ");
                printf(1,"        SEPTEMBER         ");
                printf(1,"\n");
                break;
            case 10:
                printf(1,"         OCTOBER          ");
                printf(1,"    ");
                printf(1,"         NOVEMBER         ");
                printf(1,"    ");
                printf(1,"         DECEMBER         ");
                printf(1,"\n");
                break;
        }

        //underline month names
        printf(1,"--------------------------");
        printf(1,"    ");
        printf(1,"--------------------------");
        printf(1,"    ");
        printf(1,"--------------------------");
        printf(1,"\n");
        
        //display day names
        printf(1,"SU  MO  TU  WE  TH  FR  SA");
        printf(1,"    ");
        printf(1,"SU  MO  TU  WE  TH  FR  SA");
        printf(1,"    ");
        printf(1,"SU  MO  TU  WE  TH  FR  SA");
        printf(1,"\n\n");

        //display dates
        int mc1_date = 1, mc2_date = 1 , mc3_date = 1;
        int mc1_cday = day1_mm_yyyy(month, yyyy);
        int mc2_cday = mc1_cday + ((no_days_month(month, yyyy)) % 7);
        if(mc2_cday > 7)
            mc2_cday %= 7;
        int mc3_cday = mc2_cday + ((no_days_month(month + 1, yyyy)) % 7);
        if(mc3_cday > 7)
            mc3_cday %= 7;

        while ((mc1_date <= (no_days_month(month, yyyy))) || (mc2_date <= (no_days_month(month + 1, yyyy))) || (mc3_date <= (no_days_month(month +2, yyyy))))
        {
            if (mc1_date <= (no_days_month(month, yyyy)))
            {
                display_month_row(&mc1_cday, &mc1_date, (no_days_month(month, yyyy)));
                printf(1,"    ");

                if (mc2_date <= (no_days_month(month + 1, yyyy)))
                {
                    display_month_row(&mc2_cday, &mc2_date, (no_days_month(month + 1, yyyy)));
                    printf(1,"    ");

                    if (mc3_date <= (no_days_month(month +2, yyyy)))
                    {
                        display_month_row(&mc3_cday, &mc3_date, (no_days_month(month +2, yyyy)));
                        printf(1,"\n");
                    }
                    else // if m3 is complete
                    {
                        printf(1,"                          "); // 26
                        printf(1,"\n");
                    }
                }
                else // if m2 is complete
                {
                    printf(1,"                          "); // 26
                    printf(1,"    ");

                    if (mc3_date <= (no_days_month(month +2, yyyy)))
                    {
                        display_month_row(&mc3_cday, &mc3_date, (no_days_month(month +2, yyyy)));
                        printf(1,"\n");
                    }
                    else // if m3 is complete
                    {
                        printf(1,"                          "); // 26
                        printf(1,"\n");
                    }
                }
            }
            else // if m1 is complete
            {
                printf(1,"                          "); // 26
                printf(1,"    ");

                if (mc2_date <= (no_days_month(month + 1, yyyy)))
                {
                    display_month_row(&mc2_cday, &mc2_date, (no_days_month(month + 1, yyyy)));
                    printf(1,"    ");

                    if (mc3_date <= (no_days_month(month +2, yyyy)))
                    {
                        display_month_row(&mc3_cday, &mc3_date, (no_days_month(month +2, yyyy)));
                        printf(1,"\n");
                    }
                    else // if m3 is complete
                    {
                        printf(1,"                          "); // 26
                        printf(1,"\n");
                    }
                }
                else // if m2 is complete
                {
                    printf(1,"                          "); // 26
                    printf(1,"    ");

                    if (mc3_date <= (no_days_month(month +2, yyyy)))
                    {
                        display_month_row(&mc3_cday, &mc3_date, (no_days_month(month +2, yyyy)));
                        printf(1,"\n");
                    }
                    else // if m3 is complete
                    {
                        printf(1,"                          "); // 26
                        printf(1,"\n");
                    }
                }
            }
        }

        month += 3;
        printf(1,"\n\n");
    }
}

void display_cal_mm_yyyy(int month, int year)
{
    //display month name
    switch (month)
    {
        case 1:
            printf(1,"       JANUARY %d       ", year);
            break;
        case 2:
            printf(1,"       FEBRUARY %d      ", year);
            break;
        case 3:
            printf(1,"        MARCH %d        ", year);
            break;
        case 4:
            printf(1,"        APRIL %d        ", year);
            break;
        case 5:
            printf(1,"         MAY %d         ", year);
            break;
        case 6:
            printf(1,"         JUNE %d        ", year);
            break;
        case 7:
            printf(1,"         JULY %d        ", year);
            break;
        case 8:
            printf(1,"        AUGUST %d       ", year);
            break;
        case 9:
            printf(1,"      SEPTEMBER %d      ", year);
            break;
        case 10:
            printf(1,"       OCTOBER %d       ", year);
            break;
        case 11:
            printf(1,"       NOVEMBER %d      ", year);
            break;
        case 12:
            printf(1,"       DECEMBER %d      ", year);
            break;
    }
    printf(1,"\n--------------------------\n");
    printf(1,"SU  MO  TU  WE  TH  FR  SA");
    printf(1,"\n\n");

    //display dates
    int day1 = day1_mm_yyyy(month, year);
    int date = 1;

    for (int space = 1; space < day1; space++)
        printf(1,"    ");
    for (date = 1; date <= no_days_month(month, year); date++)
    {
        if ((date + day1 - 1) % 7 != 0)
        {
        	if(date < 10)
            		printf(1," %d  ", date);
            	else
            		printf(1,"%d  ", date);
        }
        else
        {
        	if(date < 10)
            		printf(1," %d\n", date);
            	else
            		printf(1,"%d\n", date);
        }
    }
    printf(1,"\n");
}

int return_year(char arg[])
{
    int year = 0;
    for(int i=0; i<4; i++)
    {
    	if(arg[i] == '0')
            year = (year * 10);
        else if((arg[i]) == '1')
            year = (year *10) + 1;
        else if((arg[i]) == '2')
            year = (year *10) + 2;
        else if((arg[i]) == '3')
            year = (year *10) + 3;
        else if((arg[i]) == '4')
            year = (year *10) + 4;
        else if((arg[i]) == '5')
            year = (year *10) + 5;
        else if((arg[i]) == '6')
            year = (year *10) + 6;
        else if((arg[i]) == '7')
            year = (year *10) + 7;
        else if((arg[i]) == '8')
            year = (year *10) + 8;
        else if((arg[i]) == '9')
            year = (year *10) + 9;
    }

    return year;
}

int return_month(char *arg)
{
    int month = 0;
    for(int i=0; i<2; i++)
    {
    	if(arg[i] == '0')
            month = (month * 10);
        else if(arg[i] == '1')
            month = (month *10) + 1;
        else if(arg[i] == '2')
            month = (month *10) + 2;
        else if(arg[i] == '3')
            month = (month *10) + 3;
        else if(arg[i] == '4')
            month = (month *10) + 4;
        else if(arg[i] == '5')
            month = (month *10) + 5;
        else if(arg[i] == '6')
            month = (month *10) + 6;
        else if(arg[i] == '7')
            month = (month *10) + 7;
        else if(arg[i] == '8')
            month = (month *10) + 8;
        else if(arg[i] == '9')
            month = (month *10) + 9;
    }

    return month;
}

int main(int argc,char* argv[])
{
	int yyyy = 2022;
	int mm = 1;
	
	if(argc == 1)
	{
		printf(1,"\n--------Default calendar of year %d--------\n\n", yyyy);
		display_yyyy_cal(2022);
	}
	else if(argc == 2)
	{
		yyyy = return_year((argv[1]));
		printf(1,"\n--------Calendar of year %d--------\n\n", yyyy);
		display_yyyy_cal(yyyy);
	}
	else if(argc == 3)
	{
		mm = return_month(argv[1]);
		yyyy = return_year(argv[2]);
		printf(1,"\n--------Calendar of %d %d--------\n\n", mm, yyyy);
		display_cal_mm_yyyy(mm, yyyy);
	}
	else
	{
		printf(1,"\nInvalid Command\n", mm, yyyy);
	}
	exit();
	return 0;
    	
}