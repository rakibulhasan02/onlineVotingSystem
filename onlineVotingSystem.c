#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>

#define MAX_CANDIDATES 5
#define MAX_VOTERS 5

typedef struct
{
    char name[50];
    int votes;
} Candidate;

typedef struct
{
    char nid[20];
    int hasVoted;
} Voter;

Candidate candidates[MAX_CANDIDATES] =
{
    {"Dr Younus", 0},
    {"Khaleda Zia", 0},
    {"Ershad Uddin", 0}
};

Voter voters[MAX_VOTERS] =
{
    {"1111111111", 0},
    {"2222222222", 0},
    {"3333333333", 0},
    {"4444444444", 0},
    {"5555555555", 0}
};

// Function prototypes
void voterLogin();
void adminLogin();
int loginVoter(char *nid);
void castVote(int voterIndex);
int isVotingAllowed();
int canViewResults();
int checkAdmin(char *username, char *password);
void votesCount();
void displayLeadingCandidate();

int main()
{
    int choice;
    do
    {
        printf("\nOnline Voting System\n");
        printf("1. Voter Login\n");
        printf("2. Admin Login\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if (isVotingAllowed())
            {
                voterLogin();
            }
            else
            {
                printf("Voting is only allowed between 10 AM and 4 PM.\n");
            }
            break;
        case 2:
            adminLogin();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 0);
    return 0;
}

// Check if current time is between 10 AM and 4 PM
int isVotingAllowed()
{
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    int hour = localTime->tm_hour;

    if (hour >= 10 && hour < 16)
    {
        return 1; // Voting is allowed between 10 AM and 4 PM
    }
    return 0; // Voting is not allowed outside this window
}

// Check if results can be viewed (after 4 PM)
int canViewResults()
{
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    int hour = localTime->tm_hour;

    if (hour >= 16)
    {
        return 1; // Results can be viewed after 4 PM
    }
    return 0; // Cannot view results before 4 PM
}

// Voter login and voting process
void voterLogin()
{
    char nid[20];
    printf("\nEnter your National ID (NID): ");
    scanf("%s", nid);

    int voterIndex = loginVoter(nid);
    if (voterIndex != -1 && voters[voterIndex].hasVoted == 0)
    {
        castVote(voterIndex);
    }
    else if (voterIndex != -1 && voters[voterIndex].hasVoted == 1)
    {
        printf("You have already voted.\n");
    }
    else
    {
        printf("Invalid NID or voter not found.\n");
    }
}

// Voter authentication
int loginVoter(char *nid)
{
    for (int i = 0; i < MAX_VOTERS; i++)
    {
        if (strcmp(voters[i].nid, nid) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Cast the vote
void castVote(int voterIndex)
{
    int voteChoice;
    printf("\nCandidates:\n");
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
    printf("Enter the number of the candidate you want to vote for: ");
    scanf("%d", &voteChoice);

    if (voteChoice >= 1 && voteChoice <= MAX_CANDIDATES)
    {
        candidates[voteChoice - 1].votes++;
        voters[voterIndex].hasVoted = 1;
        printf("Your vote has been cast successfully!\n");
    }
    else
    {
        printf("Invalid choice. Try again.\n");
    }
}

// Admin login
void adminLogin()
{
    char adminUser[50], adminPass[50];

    printf("Enter Admin Username: ");
    scanf("%s", adminUser);
    printf("Enter Admin Password: ");
    scanf("%s", adminPass);

    if (checkAdmin(adminUser, adminPass))
    {
        int adminChoice;
        do
        {
            printf("\n1. View vote count\n");
            printf("2. View leading candidate\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &adminChoice);
            switch (adminChoice)
            {
            case 1:
                if (canViewResults())
                {
                    votesCount();
                }
                else
                {
                    printf("Results can only be viewed after 4 PM.\n");
                }
                break;
            case 2:
                if (canViewResults())
                {
                    displayLeadingCandidate();
                }
                else
                {
                    printf("Results can only be viewed after 4 PM.\n");
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        while (adminChoice != 0);
    }
    else
    {
        printf("Invalid Admin Credentials!\n");
    }
}

// View vote count
void votesCount()
{
    printf("\nVote Count:\n");
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
}

// Display the leading candidate
void displayLeadingCandidate()
{
    int maxVotes = 0;
    char leadingCandidate[50];

    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        if (candidates[i].votes > maxVotes)
        {
            maxVotes = candidates[i].votes;
            strcpy(leadingCandidate, candidates[i].name);
        }
    }

    if (maxVotes > 0)
    {
        printf("\nThe leading candidate is %s with %d votes.\n", leadingCandidate, maxVotes);
    }
    else
    {
        printf("\nNo votes have been cast yet.\n");
    }
}

// Check Admin credentials
int checkAdmin(char *username, char *password)
{
    return(strcmp(username,"admin")==0&& strcmp(password,"admin123")==0);
}