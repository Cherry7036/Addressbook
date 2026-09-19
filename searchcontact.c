#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"


/* Check whether one string occurs inside another, ignoring case */
static int containsIgnoreCase(const char *text, const char *pattern)
{
    while (*text != '\0')
    {
        const char *source = text;
        const char *target = pattern;

        while (*source != '\0' && *target != '\0' && tolower((unsigned char)*source) ==
               tolower((unsigned char)*target))
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


/* Display the heading used for search results */
static void displaySearchHeader(void)
{
    printf("\n");
    printf("+------+-------------------------+----------------+----------------------------+\n");
    printf("| %-4s | %-23s | %-14s | %-26s |\n",
           "No.", "Name", "Phone", "Email");
    printf("+------+-------------------------+----------------+----------------------------+\n");
}


/* Display one matching contact */
static void displayContact(const Contact *contact, int number)
{
    printf("| %-4d | %-23s | %-14s | %-26s |\n",
           number,
           contact->name,
           contact->phone,
           contact->email);
}


void searchContact(AddressBook *addressBook)
{
    int option = 0;
    char query[30];   //used to store the search text entered by user

    while (option != 4)
    {
        printf("\n");
        printf("====================================================\n");
        printf("                 CONTACT SEARCH                     \n");
        printf("====================================================\n");
        printf("  1. Find using name\n");
        printf("  2. Find using phone number\n");
        printf("  3. Find using email address\n");
        printf("  4. Return to main menu\n");
        printf("====================================================\n");
        printf("Choose search method: ");

        if (scanf("%d", &option) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            clearInputBuffer();
            option = 0;
            continue;
        }

        clearInputBuffer();

        if (option == 1)
        {
            int matches = 0;

            printf("\nSearch by name selected.\n");
            printf("Enter name or part of the name: ");

            if (scanf("%29[^\n]", query) != 1)
            {
                clearInputBuffer();
                printf("\nNo search text was entered.\n");
                continue;
            }

            clearInputBuffer();

            displaySearchHeader();

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (containsIgnoreCase(
                        addressBook->contacts[i].name,
                        query))
                {
                    displayContact(&addressBook->contacts[i],
                                   ++matches);
                }
            }

            printf("+------+-------------------------+----------------+----------------------------+\n");

            if (matches == 0)
            {
                printf("\nNo contact matched the specified name.\n");
            }
            else
            {
                printf("\n%d matching contact(s) found.\n", matches);
            }
        }
        else if (option == 2)
        {
            int matches = 0;

            printf("\nSearch by phone number selected.\n");
            printf("Enter phone number or part of it: ");

            if (scanf("%29[^\n]", query) != 1)
            {
                clearInputBuffer();
                printf("\nNo search text was entered.\n");
                continue;
            }

            clearInputBuffer();

            displaySearchHeader();

            for (int i = 0; i < addressBook->contactCount; i++)  //traverse all the contacts in addressbook
            {
                if (strstr(addressBook->contacts[i].phone,
                           query) != NULL)
                {
                    displayContact(&addressBook->contacts[i],
                                   ++matches);
                }
            }

            printf("+------+-------------------------+----------------+----------------------------+\n");

            if (matches == 0)
            {
                printf("\nNo contact matched the specified phone number.\n");
            }
            else
            {
                printf("\n%d matching contact(s) found.\n", matches);
            }
        }
        else if (option == 3)
        {
            int matches = 0;

            printf("\nSearch by email address selected.\n");
            printf("Enter email or part of the email: ");

            if (scanf("%29[^\n]", query) != 1)
            {
                clearInputBuffer();
                printf("\nNo search text was entered.\n");
                continue;
            }

            clearInputBuffer();

            displaySearchHeader();

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (containsIgnoreCase(
                        addressBook->contacts[i].email,
                        query))
                {
                    displayContact(&addressBook->contacts[i],
                                   ++matches);
                }
            }

            printf("+------+-------------------------+----------------+----------------------------+\n");

            if (matches == 0)
            {
                printf("\nNo contact matched the specified email address.\n");
            }
            else
            {
                printf("\n%d matching contact(s) found.\n", matches);
            }
        }
        else if (option == 4)
        {
            printf("\nSearch operation closed. Returning to the main menu.\n");
        }
        else
        {
            printf("\nInvalid search option. Please choose 1, 2, 3 or 4.\n");
        }
    }
}
