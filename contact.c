#include<stdio.h>
#include<stdlib.h>
#include"contact.h"
#include <unistd.h>

void clearInputBuffer(void)
{
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}
void showLoading(const char *message)
{
    for (int i=1;i<=100;i++)
    {
        printf("\r\033[K%s..................%d%%",message,i);
        fflush(stdout);
        usleep(30000);
    }
    printf("\n");
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount=0;
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(0);
}

static const Contact dummyContacts[] = 
{
    {"Thor",       "7689764356","odinson@gmail.com"},
    {"Captain",    "8987656787","cap@gmail.com"},
    {"Charles",    "9087678458","char23@gmail.com"},
    {"Johnny",     "6578690976","john69@ac.in"},
    {"clark",      "8765435678","clarkyy@gmail.com"},
    {"Peter",      "9834213456","pet536@gmail.com"}
};

void populateAddressBook(AddressBook *addressBook) 
{
    if (addressBook == NULL) return;

    int numDummyContacts = (int)(sizeof(dummyContacts) / sizeof(dummyContacts[0]));

    for (int i = 0; i < numDummyContacts; i++) 
    {
        if (addressBook->contactCount >= MAX_CONTACTS) 
        {
            printf("Warning: Maximum contact limit (%d) reached. Stopping population.\n", MAX_CONTACTS);
            break;
        }

        addressBook->contacts[addressBook->contactCount] = dummyContacts[i];
        addressBook->contactCount++;
    }
}