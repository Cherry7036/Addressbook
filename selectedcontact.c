
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"


/* Case-insensitive substring search */
static int containsIgnoreCase(const char *text, const char *pattern)
{
    if (*pattern == '\0')
        return 1;
    while (*text != '\0')
    {
        const char *source = text;
        const char *target = pattern;

        while (*source!= '\0' && *target!= '\0' && tolower((unsigned char)*source)==tolower((unsigned char)*target))
        {
            source++;
            target++;
        }

        if (*target == '\0')
            return 1;

        text++;
    }

    return 0;
}


/* Display matching contacts and return the selected serial number */
static int displayMatchingContacts(int index[],int count,AddressBook *addressBook,const char *searchText)
{
    printf("\n");
    printf("+------+-------------------------+----------------+----------------------------+\n");
    printf("| %-4s | %-23s | %-14s | %-26s |\n",
           "No.", "Name", "Phone", "Email");
    printf("+------+-------------------------+----------------+----------------------------+\n");

    for (int i = 0; i < count; i++)
    {
        int position = index[i];

        printf("| %-4d | %-23s | %-14s | %-26s |\n",
               i + 1,
               addressBook->contacts[position].name,
               addressBook->contacts[position].phone,
               addressBook->contacts[position].email);
    }

    printf("+------+-------------------------+----------------+----------------------------+\n");

    /*
     * If only one contact matched, there is no need
     * to ask the user for a serial number.
     */
    if (count == 1)
    {
        printf("\nOnly one matching contact was found for \"%s\".\n",searchText);

        return 1;
    }

    int selected;

    printf("\nEnter the serial number of the contact you want: ");

    if (scanf("%d", &selected) != 1)
    {
        clearInputBuffer();
        printf("Invalid selection.\n");
        return 0;
    }

    clearInputBuffer();

    if (selected < 1 || selected > count)
    {
        printf("The selected serial number is not valid.\n");
        return 0;
    }

    return selected;
}


/* Search contacts using their names */
int Selected_byname_contact(int index[], AddressBook *addressBook)
{
    char searchText[100];

    printf("\nEnter name to search: ");

    if (scanf(" %99[^\n]", searchText) != 1)
    {
        clearInputBuffer();
        printf("No valid name was entered.\n");
        return 0;
    }

    clearInputBuffer();

    int matches = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (containsIgnoreCase(addressBook->contacts[i].name,searchText))
        {
            index[matches] = i;
            matches++;
        }
    }

    if (matches == 0)
    {
        printf("\nNo contact was found matching \"%s\".\n",
               searchText);
        return 0;
    }

    return displayMatchingContacts(index,matches,addressBook,searchText);
}


/* Search contacts using their phone numbers */
int Selected_byphone_contact(int index[], AddressBook *addressBook)
{
    char searchText[100];

    printf("\nEnter phone number to search: ");

    if (scanf(" %99s", searchText) != 1)
    {
        clearInputBuffer();
        printf("No valid phone number was entered.\n");
        return 0;
    }

    clearInputBuffer();

    int matches = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].phone,searchText) != NULL)
        {
            index[matches] = i;
            matches++;
        }
    }

    if (matches == 0)
    {
        printf("\nNo contact was found for phone number \"%s\".\n",searchText);
        return 0;
    }

    return displayMatchingContacts(index,matches,addressBook,searchText);
}


/* Search contacts using their email addresses */
int Selected_byemail_contact(int index[], AddressBook *addressBook)
{
    char searchText[100];

    printf("\nEnter email address to search: ");

    if (scanf(" %99s", searchText) != 1)
    {
        clearInputBuffer();
        printf("No valid email address was entered.\n");
        return 0;
    }

    clearInputBuffer();

    int matches = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (containsIgnoreCase(addressBook->contacts[i].email, searchText))
        {
            index[matches] = i;
            matches++;
        }
    }

    if (matches == 0)
    {
        printf("\nNo contact was found matching email \"%s\".\n",searchText);
        return 0;
    }

    return displayMatchingContacts(index,matches,addressBook,searchText);
}
