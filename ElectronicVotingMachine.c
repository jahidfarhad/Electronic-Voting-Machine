#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<string.h>

char name[100][100],symbol[100];
char voterID[100],ID[100][100],matchID[100];
int count[100]= {0},candidate,i,j=0,co=0;

void centerMessage(const char *message)
{
    int len=30;
    int pos=0;
    printf("\t\t\t");
    for(pos=0; pos<len; pos++)
    {
        printf(" ");
    }
    printf("%s",message);
}

void headMessage(const char *message)
{
    system("cls");
    printf("\n\t\t\t############################################################################");
    printf("\n\t\t\t############                                                    ############");
    printf("\n\t\t\t############\t\t\tVoting Machine\t\t\t############");
    printf("\n\t\t\t############                                                    ############");
    printf("\n\t\t\t############################################################################");
    printf("\n\t\t\t----------------------------------------------------------------------------\n");
    centerMessage(message);
    printf("\n\t\t\t----------------------------------------------------------------------------\n");
}

void welcomeMessage()
{
    headMessage("Welcome To The Election");
    printf("\n\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =            ELECTRONIC VOTING              =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\n\n\tPress any key to continue......");
    getch();
}

int mainMenu()
{
    headMessage("Main Menu");
    int option;
    printf("\n\t\t\t\t\t\tChoose An Option:\n");
    printf("\n\t\t\t\t\t\t1. Registration\n");
    printf("\t\t\t\t\t\t2. Candidates\n");
    printf("\t\t\t\t\t\t3. Vote Casting\n");
    printf("\t\t\t\t\t\t4. Result Menu\n");
    printf("\t\t\t\t\t\t5. Exit\n");
    printf("\n\t\t\t\t\t\tEnter Your Option: ");
    scanf("%d",&option);
    switch(option)
    {

    case 1:
        registration();
        break;
    case 2:
        candidates();
        break;
    case 3:
        voterLogin();
        break;
    case 4:
        finishVoting();
        break;
    case 5:
        Exit();
        break;
    default:
        printf("\n\t\aWrong Input...Try Again...");
        getch();
        mainMenu();

    }
}

int registration()
{
    int j,temp,option;
    char sym,fileName[10];
    headMessage("Registration For Candidates");
    printf("\n\tEnter The Number Of Candidates Participating In The Election:\n\t");
    scanf("%d",&candidate);
    for(i=0; i<candidate; i++)
    {

        printf("\n\t========== For %d Candidate =========\n",(i+1));
        printf("\n\tEnter Candidate's Name:\n\t");
        fscanf(stdin, " ");
        gets(name[i]);

        sprintf(fileName,"Final Results %d.txt",(i+1));
        FILE *file;
        file=fopen(fileName,"w");
        fprintf(file,"Candidate: %s\n",name[i]);

start:
        temp=0;
        printf("\n\tEnter Candidate's Symbol(special characters only):\n\t");
        scanf(" %c",&sym);
        for(j=0; j<i; j++)
        {

            if(symbol[j]==sym)
            {

                printf("\n\n\t\aThis Symbol Is Already Taken.\n\n");
                temp=1;
                goto start;
            }
        }
        if(temp==0)
        {

            symbol[i]=sym;
            fprintf(file,"Symbol: %c\n",symbol[i]);
        }
        fprintf(file,"Votes: %d\n",count[i]);
        fclose(file);
    }
Start:
    printf("\n\n\t1. Goto Next Page\n");
    printf("\t2. Goto Main Menu\n");
    printf("\n\tChoose Option 1 or 2:\n\t");
    scanf("%d",&option);
    switch(option)
    {

    case 1:
        printf("\n\n\n\tPress any key to continue......");
        getch();
        voterLogin();
        break;
    case 2:
        mainMenu();
        break;
    default:
        printf("\n\t\aWrong Input...Try Again...");
        getch();
        goto Start;
    }
}

int candidates()
{
    headMessage("Candidates Details");
    for(i=0; i<candidate; i++)
    {

        printf("\n\t========== For %d Candidate =========\n",(i+1));
        printf("\n\tCandidate's Name: %s",name[i]);
        printf("\n\tCandidate's Symbol: %c\n",symbol[i]);
    }
    printf("\n\n\n\tPress any key to continue......");
    getch();
    mainMenu();
}

int voterLogin()
{
    headMessage("Voter Details");
    int flag,temp=0;
    printf("\tEnter Your Voter ID:\n\t");
    scanf("%s",&voterID);

    strcpy(ID[j],voterID);
    j++;
    if(strcmp(matchID,voterID)==0)
        co=1;
    for(i=0; i<=j; i++)
    {
        if(strcmp(voterID,ID[i])==0)
            co++;
    }
    if(co==1)
        flag=0;
    else
        flag=1;
    co=0;

    if(flag==0)
    {
        FILE *file=fopen("Voters.csv","r");
        if (!file)
        {

            printf("\n\t\aCan't Open File\n");
            return 0;
        }
        char buf[1024];
        int field_count=0;
        int entries=0;
        fgets(buf,1024,file);
        char *field=strtok(buf,",");
        while(fgets(buf,1024,file))
        {

            field_count=0;
            field=strtok(buf,",");
            if(strcmp(field,voterID)==0)
            {

                printf("\n\n\tLogin Successful.....\n\n");
                while(field)
                {
                    if (field_count==0)
                    {
                        printf("\n\tVoter ID : ");
                    }
                    if (field_count==1)
                    {
                        printf("\tName : ");
                    }
                    if (field_count==2)
                    {
                        printf("\tAge : ");
                    }

                    printf("%s\n",field);
                    field=strtok(NULL,",");
                    field_count++;
                }
                printf("\n");
                strcpy(matchID,voterID);
                temp=0;
                break;
            }
            else
            {

                temp=1;
            }
        }
        if(temp==1)
        {

            printf("\n\n\t\aVoter ID Doesn't Match...Try Again...");
            getch();
            voterLogin();
        }
        fclose(file);
    }
    else
    {

        printf("\n\n\t\a\aError! You Already Casted Your Vote.");
        printf("\n\n\n\tPress any key to continue......");
        getch();
        mainMenu();
    }
    printf("\n\n\n\tPress any key to continue......");
    getch();
    givingVote();
}

int givingVote()
{
    headMessage("Casting The Votes");
    char sym,fileName[10];
    int temp=0;
    for(i=0; i<candidate; i++)
    {

        printf("\t%d. %s (%c)\n",(i+1),name[i],symbol[i]);
    }
    printf("\n\tEnter The Symbol Of Your Representative:\n\t");
    scanf(" %c",&sym);
    for(i=0; i<candidate; i++)
    {

        if(sym==symbol[i])
        {
            count[i]++;
            temp=0;

            sprintf(fileName,"Final Results %d.txt",(i+1));
            FILE *file;
            file=fopen(fileName,"w");
            fprintf(file,"Candidate: %s\n",name[i]);
            fprintf(file,"Symbol: %c\n",symbol[i]);
            fprintf(file,"Votes: %d\n",count[i]);
            fclose(file);
            break;
        }
        else
        {

            temp=1;

        }
    }
    if(temp==1)
    {

        printf("\n\n\t\aWrong Symbol...Try Again...");
        getch();
        givingVote();
    }
    printf("\n\n\t\aThank You! Your Vote Has Been Casted.\n");

    int option;
Start:
    printf("\n\n\t1. Goto Next Page\n");
    printf("\t2. Goto Main Menu\n");
    printf("\n\tChoose Option 1 or 2:\n\t");
    scanf("%d",&option);
    switch(option)
    {

    case 1:
        printf("\n\n\n\tPress any key to continue......");
        getch();
        choice();
        break;
    case 2:
        mainMenu();
        break;
    default:
        printf("\n\t\aWrong Input...Try Again...");
        getch();
        goto Start;
    }
}

int choice()
{
    headMessage("Voting Options");
    int option;
    printf("\n\t1. Finish Voting\n");
    printf("\t2. Another Voter Login\n");
    printf("\n\tChoose Option 1 or 2:\n\t");
    scanf("%d",&option);
    switch(option)
    {

    case 1:
        printf("\n\t\aVoting Process Has Been Finished.\n");
        printf("\n\n\n\tPress any key to continue......");
        getch();
        finishVoting();
        break;
    case 2:
        voterLogin();
        givingVote();
        choice();
        break;
    default:
        printf("\n\t\aWrong Input...Try Again...");
        getch();
        choice();
    }
}

int finishVoting()
{
    headMessage("Result Menu");
    printf("\n\tChoose an Option:\n");
    printf("\t1. Vote Difference Between Two Participants\n");
    printf("\t2. Final Results\n");
    printf("\t3. Main Menu\n");
    printf("\t4. Exit\n");
    printf("\n\tEnter Your Choice:\n\t");
    int option;
    scanf("%d",&option);
    switch(option)
    {

    case 1:
        printf("\n\n\n\tPress any key to continue......");
        getch();
        voteDifference();
        break;
    case 2:
        printf("\n\n\n\tPress any key to continue......");
        getch();
        results();
        break;
    case 3:
        printf("\n\n\n\tPress any key to continue......");
        getch();
        mainMenu();
        break;
    case 4:
        Exit();
        break;
    default:
        printf("\n\t\aWrong Input...Try Again...");
        getch();
        finishVoting();
    }
}

int voteDifference()
{
    headMessage("Vote Difference");
    int s1,s2;
    for(i=0; i<candidate; i++)
    {

        printf("\t%d. %s (%c)\n",(i+1),name[i],symbol[i]);
    }
    printf("\n\tEnter The Serial Numbers:\n\t");
    scanf("%d%d",&s1,&s2);
    if(count[s1-1]==count[s2-1])
    {
        printf("\n\tIt's a Tie Between Both The Candidates\n");
    }
    printf("\n\tThe Difference Between %s And %s Is: %d\n",name[s1-1],name[s2-1],abs(count[s1-1]-count[s2-1]));
    printf("\n\n\n\tPress any key to continue......");
    getch();
    finishVoting();

}

int results()
{
    headMessage("Final Results");
    printf("\n\tFinal Results Are:\n\n");

    for(i=0; i<candidate; i++)
    {

        printf("\n\t========== For %d Candidate =========\n\n",(i+1));
        printf("\tCandidate: %s\n",name[i]);
        printf("\tSymbol: %c\n",symbol[i]);
        printf("\tVotes: %d\n\n",count[i]);

    }

    printf("\n\n\n\tPress any key to continue......");
    getch();
    finishVoting();
}

int Exit()
{
    headMessage("Exit Options");
    int option;
    char fileName[10];
    printf("\n\t1. Save & Exit\n");
    printf("\t2. Exit Without Saving\n");
    printf("\n\tChoose Option 1 or 2:\n\t");
    scanf("%d",&option);
    switch(option)
    {
    case 1:
        printf("\n\n\tData Saved Successfully...Press Any Key To Exit...");
        getch();
        printf("\n");
        exit(0);
    case 2:
        for(i=0; i<candidate; i++)
        {

            sprintf(fileName,"Final Results %d.txt",(i+1));
            remove(fileName);
        }
        exit(0);
    default:
        printf("\n\t\aWrong Input...Try Again...");
        getch();
        Exit();
    }
}

int main()
{
    welcomeMessage();
    mainMenu();

    return 0;
}
