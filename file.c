#include <stdio.h>
#include <string.h>
#include "contact.h"


void saveContactsToFile(AddressBook *addressBook)
{
    if (addressBook == NULL)
    {
        printf("\nUnable to save contacts: invalid address book.\n");
        return;
    }

    FILE *file = fopen("contact.csv", "w");

    if (file == NULL)
    {
        printf("\nCould not create or open the contact file.\n");
        return;
    }

    int i = 0;

    while (i < addressBook->contactCount)
    {
        fprintf(file,
                "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);

        i++;
    }

    fclose(file);

    printf("\nAll contacts have been stored successfully.\n");
}


void loadContactsFromFile(AddressBook *addressBook)
{
    if (addressBook == NULL)
    {
        printf("\nUnable to load contacts: invalid address book.\n");
        return;
    }

    FILE *file = fopen("contact.csv", "r");

    if (file == NULL)
    {
        addressBook->contactCount = 0;

        printf("\nNo previous contact file was found.\n");
        printf("Starting with a new empty address book.\n");

        return;
    }

    addressBook->contactCount = 0;

    while (addressBook->contactCount < MAX_CONTACTS)
    {
        Contact *current =
            &addressBook->contacts[addressBook->contactCount];

        int result = fscanf(file,
                            " %49[^,],%49[^,],%49[^\n]",
                            current->name,
                            current->phone,
                            current->email);

        if (result != 3)
        {
            break;
        }

        addressBook->contactCount++;
    }

    fclose(file);

    printf("\nContact information loaded successfully.\n");
}
