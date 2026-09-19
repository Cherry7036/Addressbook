
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"


/* Compare two strings without considering uppercase/lowercase */
static int compareIgnoreCase(const char *first, const char *second)
{
    while (*first != '\0' && *second != '\0')
    {
        char ch1 = (char)tolower((unsigned char)*first);
        char ch2 = (char)tolower((unsigned char)*second);

        if (ch1 != ch2)
        {
            return ch1 - ch2;
        }

        first++;
        second++;
    }

    return tolower((unsigned char)*first) - tolower((unsigned char)*second);
}


/* Return the field which should be used for sorting */
static const char *getContactField(const Contact *contact,int criteria)
{
    switch (criteria)
    {
        case 1:
            return contact->name;

        case 2:
            return contact->phone;

        case 3:
            return contact->email;

        default:
            return NULL;
    }
}


void listContacts(AddressBook *addressBook)
{
    if (addressBook == NULL)
    {
        printf("\nUnable to display contacts: invalid address book.\n");
        return;
    }

    if (addressBook->contactCount <= 0)
    {
        printf("\nThe address book currently has no contacts.\n");
        return;
    }

    int sortChoice = 0;

    printf("\n");
    printf("+------------------------------------------------+\n");
    printf("|              CONTACT SORT OPTIONS              |\n");
    printf("+------------------------------------------------+\n");
    printf("|  1. Arrange contacts by name                   |\n");
    printf("|  2. Arrange contacts by phone number          |\n");
    printf("|  3. Arrange contacts by email                  |\n");
    printf("+------------------------------------------------+\n");
    printf("Enter sorting option: ");

    if (scanf("%d", &sortChoice) != 1)
    {
        printf("\nInvalid input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (sortChoice < 1 || sortChoice > 3)
    {
        printf("\nInvalid option. Select a value from 1 to 3.\n");
        return;
    }


    /*
     * Insertion sort
     *
     * Each contact is picked and inserted into its
     * correct position among the contacts already sorted.
     */
    for (int current = 1;
         current < addressBook->contactCount;
         current++)
    {
        Contact selected = addressBook->contacts[current];

        const char *selectedField =
            getContactField(&selected, sortChoice);

        int position = current - 1;

        while (position >= 0)
        {
            const char *previousField =getContactField(&addressBook->contacts[position],sortChoice);

            if (compareIgnoreCase(previousField, selectedField) <= 0)
            {
                break;
            }

            addressBook->contacts[position + 1] =
                addressBook->contacts[position];

            position--;
        }

        addressBook->contacts[position + 1] = selected;
    }
    const char *title;
    if (sortChoice == 1)
        title = "NAME";
    else if (sortChoice == 2)
        title = "PHONE";
    else
        title = "EMAIL";


    printf("\n");
    printf("==============================================================\n");
    printf("              CONTACTS SORTED USING %s\n", title);
    printf("==============================================================\n");

    printf("+------+--------------------+----------------+----------------------------+\n");
    printf("| %-4s | %-18s | %-14s | %-26s |\n",
           "No.", "Name", "Phone", "Email");
    printf("+------+--------------------+----------------+----------------------------+\n");


    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-4d | %-18s | %-14s | %-26s |\n",i + 1,addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }


    printf("+------+--------------------+----------------+----------------------------+\n");
    printf("Number of contacts: %d\n",
           addressBook->contactCount);
}

