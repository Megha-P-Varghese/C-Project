#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>//for the random number generation
#include <windows.h>//for the delay or Sleep
//After each major operations i have introduces a sleep function just to isolate it from the next Menun invocation3
struct Candidate {
	int id;
    char name[50];
    char party[50];
    char description[200];
    int votes;
    struct Candidate* next;
};

struct Voter {
	int id;
    char name[50];
    int age;
    char address[100];
    int hasVoted;
    struct Voter* next;
};

struct Candidate* candidateList = NULL;
struct Voter* voterList = NULL;

void registerCandidate() {
    struct Candidate* newCandidate = (struct Candidate*)malloc(sizeof(struct Candidate));

    if (newCandidate == NULL) {
        printf("\n*****************************\nMemory allocation failed. Unable to register candidate.\n*****************************\n");
        return;
    }

    printf("Enter candidate name: ");
    scanf("%s", newCandidate->name);
    printf("Enter candidate party: ");
    scanf("%s", newCandidate->party);
    printf("Enter candidate description: ");
    scanf(" %[^\n]", newCandidate->description);
    newCandidate->votes = 0;
    // Seed the random number generator with the current time ,but the numbers are between 1 and 10 for test purpose
    //the same is used in voters but the random is taken between 11 and 30
    srand(time(NULL));
    newCandidate->id= (rand() % 10) + 1;
    newCandidate->next = candidateList;
    candidateList = newCandidate;
 printf("\n****************************************************\n");
	printf("Candidate registered successfully with Unique ID : %d",newCandidate->id);
	printf("\n****************************************************\n");
	Sleep(2000);
}

void registerVoter() {
    struct Voter* newVoter = (struct Voter*)malloc(sizeof(struct Voter));

    if (newVoter == NULL) {
        printf("\n*****************************\nMemory allocation failed. Unable to register voter.\n*****************************\n");
        return;
    }
	printf("Enter voter age: ");
    scanf("%d", &newVoter->age);
    if(newVoter->age<18){
    	printf("\n************\nGrow Up Kid!\n************\n");
    	Sleep(2000);
    	return;
    }
    printf("Enter voter name: ");
    scanf("%s", newVoter->name);
    printf("Enter voter address: ");
    scanf(" %[^\n]", newVoter->address);
    newVoter->hasVoted = 0;
    srand(time(NULL));
    newVoter->id= (rand() % 20) + 11;
    newVoter->next = voterList;
    voterList = newVoter;

    printf("\n****************************************************\n");
	printf("Voter registered successfully with Unique Voter ID : %d",newVoter->id);
	printf("\n****************************************************\n");
	Sleep(2000);
}

void castVote() {
    int voterId, candidateId;
	if(candidateList==NULL)
	{
		printf("\n***********************************************\n");
		printf("Please add Atleast one candidate to Cast a vote.");
		printf("\n***********************************************\n");
		Sleep(2000);
		return;
	}
    printf("Enter voter ID: ");
    scanf("%d", &voterId);

    struct Voter* currentVoter = voterList;
    
    while (currentVoter != NULL && currentVoter->id!=voterId) {
    	
        currentVoter = currentVoter->next;
    }
    if (currentVoter == NULL) 
	{
		printf("\n*****************\nInvalid Voter ID.\n*****************\n");
		Sleep(2000);
        return;
	}
	else if(currentVoter->hasVoted!=0)
	{
		printf("\n**************************\nVoter has already cast a vote.\n**************************\n");
		Sleep(2000);
		return;	
	}
    printf("\n*********************\nAvailable candidates:\n*********************\n");
    struct Candidate* currentCandidate = candidateList;
    printf("ID\tNAME\tPARTY\n");
    while (currentCandidate != NULL) {
        printf("%d. %s - %s\n", currentCandidate->id, currentCandidate->name, currentCandidate->party);
        currentCandidate = currentCandidate->next;
    }

    printf("Enter candidate ID: ");
    scanf("%d", &candidateId);

    struct Candidate* selectedCandidate = candidateList;
    while (selectedCandidate != NULL && candidateId!=selectedCandidate->id) {
        selectedCandidate = selectedCandidate->next;
    }

    if (selectedCandidate == NULL) {
    	printf("\n*****************************\nInvalid Candidate ID, Please try Again!\n*****************************\n");
    	Sleep(2000);
    	return;
    }
    	selectedCandidate->votes++;
        currentVoter->hasVoted = 1;
        printf("\n************************\nVote cast successfully!\n************************\n");
        Sleep(2000);
}

void tallyVotes() {
    int maxVotes = -1,top=1;
    struct Candidate* winner = NULL; 

    struct Candidate* currentCandidate = candidateList;
    while (currentCandidate != NULL) {
    	if(currentCandidate->votes == maxVotes)
        {
        	top=1;
        }
        else if (currentCandidate->votes > maxVotes) {
            maxVotes = currentCandidate->votes;
            winner = currentCandidate;
            top=0;
        }
        
        currentCandidate = currentCandidate->next;
    }
    if(top)
    {
    	 printf("\n***********\nIts a draw.\n***********\n");
    	 Sleep(3000);
    	 return;
    	 
    }

    if (winner != NULL) {
        printf("\n*************\nWINNER:\n*************\nID : %d\nName : %s\nParty : %s\nVotes : %d\n*************\n",winner->id, winner->name, winner->party, maxVotes);
    } else {
        printf("\n*********************\nNo votes have been cast.\n*********************\n");
    }
    Sleep(5000);
}

void verifyVote() {
    int voterId;
    printf("Enter voter ID: ");
    scanf("%d", &voterId);

    struct Voter* currentVoter = voterList;
    while (currentVoter != NULL && currentVoter->id!=voterId) {
    	
        currentVoter = currentVoter->next;
    }
    if (currentVoter == NULL) 
	{
		printf("\n*****************\nInvalid Voter ID.\n*****************\n");

	}
	else if(currentVoter->hasVoted==1)
	{
		printf("\n***************************\nVoter has already cast a vote.\n***************************\n");
	}
	else
	{
		printf("\n***************************\nVoter yet to cast a vote.\n***************************\n");

	}
	Sleep(2000);
}

int main() {
    int choice;

    do {
        printf("\nCANDIDATE ELECTION MANAGEMENT SYSTEM\n");
        printf("_____________________________________\nWhat would you like to do?\n_____________________________________\n\n");
        printf("* Register Candidate - 1\n");
        printf("* Register Voter - 2\n");
        printf("* Cast Vote - 3\n");
        printf("* Vote Verification - 4\n");
        printf("* Tally Votes - 5\n");
        printf("* Exit - 6\n");
        printf("_____________________________________\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerCandidate();
                break;
            case 2:
                registerVoter();
                break;
            case 3:
                castVote();
                break;
            case 4:
                verifyVote();
                break;
            case 5:
                tallyVotes();
                break;
            case 6:
                printf("Exiting the application...\n");
                break;
            default:
                printf("\n!!!!!!!!!!!!!!!!!!!!!!!\nInvalid choice. Please try again.\n!!!!!!!!!!!!!!!!!!!!!!!\n");
                Sleep(1000);
        }
    } while (choice != 6);

    // Free allocated memory for candidates
    struct Candidate* currentCandidate = candidateList;
    while (currentCandidate != NULL) {
        struct Candidate* temp = currentCandidate;
        currentCandidate = currentCandidate->next;
        free(temp);
    }

    // Free allocated memory for voters
    struct Voter* currentVoter = voterList;
    while (currentVoter != NULL) {
        struct Voter* temp = currentVoter;
        currentVoter = currentVoter->next;
        free(temp);
    }

    return 0;
}

