#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"


static void deleteSelectedContact(AddressBook *addressBook,const int index[],int contactindex)
{
    int actualIndex = index[contactindex];

    if (actualIndex < 0 || actualIndex >= addressBook->contactCount)
    {
        printf("\nError: The selected contact could not be found.\n");
        return;
    }

    printf("\n+--------------------+----------------+----------------------------+\n");
    printf("| %-18s | %-14s | %-26s |\n",
           "Name", "Phone", "Email");
    printf("+--------------------+----------------+----------------------------+\n");

    printf("| %-18s | %-14s | %-26s |\n",
           addressBook->contacts[actualIndex].name,
           addressBook->contacts[actualIndex].phone,
           addressBook->contacts[actualIndex].email);

    printf("+--------------------+----------------+----------------------------+\n");

    char ch;

    printf("\nDo you want to delete this contact? (Y/N): ");

    if (scanf(" %c", &ch) != 1)
    {
        clearInputBuffer();
        printf("Invalid confirmation. Deletion cancelled.\n");
        return;
    }

    clearInputBuffer();

    if (ch == 'y' || ch == 'Y')
    {
        for (int i = actualIndex;
             i < addressBook->contactCount - 1;
             i++)
        {
            addressBook->contacts[i] =
                addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        showLoading("Deleting contact");

        saveContactsToFile(addressBook);

        printf("\nContact deleted successfully.\n");
    }
    else
    {
        printf("\nDeletion cancelled. The contact was not removed.\n");
    }
}


static int selectContactByCriteria(int choice,int *indexList,AddressBook *addressBook)
{
    clearInputBuffer();

    switch (choice)
    {
        case 1:
            printf("\nSearching for contacts by name...\n");
            return Selected_byname_contact(indexList, addressBook);

        case 2:
            printf("\nSearching for contacts by phone number...\n");
            return Selected_byphone_contact(indexList, addressBook);

        case 3:
            printf("\nSearching for contacts by email address...\n");
            return Selected_byemail_contact(indexList, addressBook);

        default:
            printf("\nInvalid search option.\n");
            return 0;
    }
}


void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts are available to delete.\n");
        return;
    }

    int index[addressBook->contactCount];
    int deleteChoice;

    do
    {
        printf("\n");
        printf("===============================================\n");
        printf("              DELETE CONTACT MENU             \n");
        printf("===============================================\n");
        printf("  1. Find contact using name\n");
        printf("  2. Find contact using phone number\n");
        printf("  3. Find contact using email address\n");
        printf("  4. Exit deletion menu\n");
        printf("===============================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &deleteChoice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        if (deleteChoice >= 1 && deleteChoice <= 3)
        {
            int selectedIndex =
                selectContactByCriteria(deleteChoice,index,addressBook);

            if (selectedIndex > 0)
            {
                deleteSelectedContact(addressBook,index,selectedIndex - 1);
            }
        }
        else if (deleteChoice == 4)
        {
            printf("\nLeaving the delete contact menu...\n");
            clearInputBuffer();
        }
        else
        {
            printf("\nInvalid option. Please select a number from 1 to 4.\n");
            clearInputBuffer();
        }

    } while (deleteChoice != 4);
}

