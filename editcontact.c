#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"


static void selectededitcontact(AddressBook *addressBook,const int index[],int selectedcontact)
{
    int actualIndex = index[selectedcontact];
    int choice = 0;
    char temp[NAME_LEN];

    /* Verify that the selected index is valid */
    if (actualIndex < 0 || actualIndex >= addressBook->contactCount)
    {
        printf("\nUnable to open the selected contact.\n");
        return;
    }

    while (choice != 4)
    {
        printf("\n");
        printf("--------------------------------------------------\n");
        printf(" Currently editing : %s\n",
               addressBook->contacts[actualIndex].name);
        printf("--------------------------------------------------\n");
        printf("  1 -> Change name\n");
        printf("  2 -> Change phone number\n");
        printf("  3 -> Change email address\n");
        printf("  4 -> Save and return\n");
        printf("--------------------------------------------------\n");
        printf("Choose an action: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nPlease enter a valid numeric option.\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }

        clearInputBuffer();

        if (choice == 1)
        {
            printf("\nNew name: ");
            scanf(" %[^\n]", temp);
            clearInputBuffer();

            if (validateName(temp))
            {
                strcpy(addressBook->contacts[actualIndex].name, temp);

                showLoading("Updating contact");

                saveContactsToFile(addressBook);

                printf("\nName changed successfully.\n");
            }
        }
        else if (choice == 2)
        {
            printf("\nNew phone number: ");
            scanf(" %[^\n]", temp);
            clearInputBuffer();

            if (validatePhone(addressBook, temp))
            {
                strcpy(addressBook->contacts[actualIndex].phone, temp);

                showLoading("Updating contact");

                saveContactsToFile(addressBook);

                printf("\nPhone number changed successfully.\n");

            }
        }
        else if (choice == 3)
        {
            printf("\nNew email address: ");
            scanf(" %[^\n]", temp);
            clearInputBuffer();

            if (validateEmail(addressBook, temp))
            {

                strcpy(addressBook->contacts[actualIndex].email, temp);

                showLoading("Updating contact");

                saveContactsToFile(addressBook);

                printf("\nEmail address changed successfully.\n");
            }
        }
        else if (choice == 4)
        {
            printf("\nLeaving contact editor...\n");
        }
        else
        {
            printf("\nThat option does not exist. Select 1 to 4.\n");
        }
    }
}


static int selectContactByCriteria(int choice,int *indexList,AddressBook *addressBook)
{
    clearInputBuffer();

    if (choice == 1)
    {
        printf("\nSearching contacts using the name...\n");
        return Selected_byname_contact(indexList, addressBook);
    }
    else if (choice == 2)
    {
        printf("\nSearching contacts using the phone number...\n");
        return Selected_byphone_contact(indexList, addressBook);
    }
    else if (choice == 3)
    {
        printf("\nSearching contacts using the email address...\n");
        return Selected_byemail_contact(indexList, addressBook);
    }

    printf("\nInvalid search selection.\n");
    return 0;
}


void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nThere are no contacts available for editing.\n");
        return;
    }

    int index[addressBook->contactCount];
    int editChoice = 0;

    while (editChoice != 4)
    {
        printf("\n");
        printf("====================================================\n");
        printf("                 EDIT CONTACT MENU                  \n");
        printf("====================================================\n");
        printf("  1. Locate contact by name\n");
        printf("  2. Locate contact by phone\n");
        printf("  3. Locate contact by email\n");
        printf("  4. Return to previous menu\n");
        printf("====================================================\n");
        printf("Select an option: ");

        if (scanf("%d", &editChoice) != 1)
        {
            printf("\nInvalid input. Enter a number from 1 to 4.\n");
            clearInputBuffer();
            editChoice = 0;
            continue;
        }

        if (editChoice >= 1 && editChoice <= 3)
        {
            int selectedIndex =
                selectContactByCriteria(editChoice,index,addressBook);

            if (selectedIndex > 0)
            {
                selectededitcontact(addressBook,index,selectedIndex - 1);
            }
        }
        else if (editChoice == 4)
        {
            printf("\nReturning to the Address Book menu...\n");
            clearInputBuffer();
        }
        else
        {
            printf("\nInvalid option. Please choose between 1 and 4.\n");
            clearInputBuffer();
        }
    }
}
