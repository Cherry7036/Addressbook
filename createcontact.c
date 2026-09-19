#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

void createContact(AddressBook *addressBook)
{
    char answer[10];

    do
    {
        /* Check whether address book is full */
        if (addressBook->contactCount == MAX_CONTACTS)
        {
            printf("\nError: Address book is full (Maximum %d contacts allowed).\n",MAX_CONTACTS);
            return;
        }

        /* Point to the next empty contact */
        Contact *newContact =&addressBook->contacts[addressBook->contactCount];

        /* Read and validate name */
        do
        {
            printf("\n%-20s: ", "Enter name");
            scanf(" %[^\n]", newContact->name);
            clearInputBuffer();

            if (!validateName(newContact->name))
                printf("%-20s: ", "Enter name again");

        } while (!validateName(newContact->name));


        /* Read and validate phone number */
        do
        {
            printf("%-20s: ", "Enter phone number");
            scanf(" %[^\n]", newContact->phone);
            clearInputBuffer();

            if (!validatePhone(addressBook, newContact->phone))
                printf("%-20s: ", "Enter phone number again");

        } while (!validatePhone(addressBook, newContact->phone));


        /* Read and validate email */
        do
        {
            printf("%-20s: ", "Enter email ID");
            scanf(" %[^\n]", newContact->email);
            clearInputBuffer();

            if (!validateEmail(addressBook, newContact->email))
                printf("%-20s: ", "Enter email again");

        } while (!validateEmail(addressBook, newContact->email));

        /* Increase contact count */
        addressBook->contactCount++;

        showLoading("Saving contacts");

        saveContactsToFile(addressBook);

        printf("\n-------- Contact no %d successfully created ---------\n",addressBook->contactCount);


        /* Ask whether another contact should be created */
        do
        {
            printf("\nCreate another contact? (yes/no): ");

            scanf("%9s", answer);
            clearInputBuffer();

            if (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0)
            {
                printf("Invalid response. Please enter 'yes' or 'no'.\n");
            }

        } while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0);

    } while (strcmp(answer, "yes") == 0);
}