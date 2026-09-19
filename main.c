//Documentation
/*
Name                  : A Venkata Sai Charan
student id              : 26015_253
batch id                : 26015c
start Date              : 30/07/2026
end date                : 08/08/2026

 * ================================================================
 *                     ADDRESS BOOK SYSTEM
 * ================================================================
 * Description  :
 * This file contains the main control section of the Address Book
 * application. It provides a menu-driven interface through which
 * the user can manage contact information.
 *
 * The application allows the user to:
 *
 *   1. Create new contacts
 *   2. Search for existing contacts
 *   3. Modify contact information
 *   4. Remove contacts from the address book
 *   5. Display and sort stored contacts
 *   6. Save contact information and exit the application
 *
 * Program Flow :
 * The address book is initialized when the program starts, allowing
 * previously stored contacts to be loaded from the data file.
 * The main menu is then displayed repeatedly until the user selects
 * the exit option.
 *
 * Input Handling :
 * User input is checked before processing menu selections, and the
 * input buffer is cleared whenever invalid input is detected.
 *
 * Data Management :
 * Contact records are maintained through the AddressBook structure.
 * Individual operations such as creation, searching, editing,
 * deletion, sorting, and file management are handled by their
 * respective functions.
 *
 * File Storage :
 * Contact information is stored in a CSV file so that the records
 * can be restored when the application is started again.
 
*/

#include<stdio.h>
#include<stdlib.h>
#include"contact.h"

int main(void)
{
    int choice;

    AddressBook addressBook;
    initialize(&addressBook);

    do{
        printf("\n╔═════════════════════════════════════════════════════════╗\n");
        printf("║                    ADDRESS BOOK                         ║\n");
        printf("╚═════════════════════════════════════════════════════════╝\n");
        printf("1.Create Contact\n");
        printf("2.Search Contact\n");
        printf("3.Edit Contact\n");
        printf("4.Delete Contact\n");
        printf("5.List all contacts\n");
        printf("6.Exit\n");
        printf("\n");
        printf("Enter your option : ");
        scanf("%d",&choice);
        if(!choice)
        {
            printf("Invalid option!!!! Please enter a valid option...");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        switch(choice)
        {
            case 1:
            createContact(&addressBook);
            break;

            case 2:
            searchContact(&addressBook);
            break;

            case 3:
            if(addressBook.contactCount > 0)
                editContact(&addressBook);
            else
                printf("No contacts are there !!!! Adress Book is empty !!!\n");

            break;

            case 4:
            if(addressBook.contactCount > 0)
                deleteContact(&addressBook);
            else
                printf("No contacts are there !!!! Adress Book is empty !!!\n");
            break;

            case 5:
            if(addressBook.contactCount > 0)
                listContacts(&addressBook);
            else
                printf("No contacts are there !!!! Adress Book is empty !!!\n");
            break;

            case 6:
            if (addressBook.contactCount > 0) 
            {
                printf("Saving contacts and exiting...\n");
                saveContactsToFile(&addressBook);
            } 
            else
                printf("Exiting... (Address book is empty, no file changes made).\n");
            break;

            default:
            printf("Invalid choice. Please choose an option between 1 and 6.\n");
            break;
            
        }
    }while(choice!=6);
    return 0;
}
