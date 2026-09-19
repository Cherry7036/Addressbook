
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"


int validateName(const char *name)
{
    int length;
    int i = 0;

    if (name[0] == ' ')
    {
        printf("\nName cannot begin with a blank space.\n");
        return 0;
    }

    length = strlen(name);

    if (length < 4)
    {
        printf("\nName should contain at least 4 characters.\n");
        return 0;
    }

    while (i < length)
    {
        unsigned char ch = (unsigned char)name[i];
        if (!isalpha(ch) && ch != ' ')
        {
            printf("\nInvalid name. Use alphabets and spaces only.\n");
            return 0;
        }
        if (ch == ' ' && name[i + 1] == ' ')
        {
            printf("\nMultiple consecutive spaces are not allowed in a name.\n");
            return 0;
        }
        i++;
    }
    return 1;
}

int validatePhone(const AddressBook *addressBook, const char *phone)
{
    int length = strlen(phone);
    int i = 0;

    if (length != 10)
    {
        printf("\nPhone number should contain exactly 10 digits.\n");
        return 0;
    }
    if (phone[0] < '6' || phone[0] > '9')
    {
        printf("\nPhone number must begin with a digit from 6 to 9.\n");
        return 0;
    }
    while (i < length)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            printf("\nInvalid phone number. Digits only are accepted.\n");
            return 0;
        }
        i++;
    }
    i = 0;
    //checking for duplicate numbers
    while (i < addressBook->contactCount)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\nThis phone number is already registered.\n");
            return 0;
        }
        i++;
    }
    return 1;
}

int validateEmail(const AddressBook *addressBook, const char *email)
{
    int atCount = 0;
    int dotCount = 0;
    int atIndex = -1;
    int dotIndex = -1;
    int length = strlen(email);
    int i;

    /* Check for an empty email */
    if (length == 0)
    {
        printf("\nEmail address cannot be left blank.\n");
        return 0;
    }

    /* First character must be lowercase */
    if (!islower((unsigned char)email[0]))
    {
        printf("\nEmail must begin with a lowercase alphabet.\n");
        return 0;
    }

    /* Locate '@' and '.' */
    i = 0;
    while (i < length)
    {
        if (email[i] == '@')
        {
            atCount++;
            atIndex = i;
        }
        if (email[i] == '.')
        {
            dotCount++;
            dotIndex = i;
        }
        i++;
    }

    /* There should be exactly one '@' */
    if (atCount != 1)
    {
        printf("\nEmail should contain one '@' symbol only.\n");
        return 0;
    }

    /* There should be exactly one '.' */
    if (dotCount != 1)
    {
        printf("\nEmail should contain one dot (.) only.\n");
        return 0;
    }

    /* Dot should appear after '@' */
    if (dotIndex <= atIndex)
    {
        printf("\nThe '.' must appear after the '@' symbol.\n");
        return 0;
    }

    /* Validate the username portion */
    i = 0;

    while (i < atIndex)
    {
        unsigned char ch = (unsigned char)email[i];

        if (!islower(ch) && !isdigit(ch))
        {
            printf("\nEmail username may contain lowercase letters and digits only.\n");
            return 0;
        }

        i++;
    }
    /* Character immediately before '@' must be alphanumeric */
    if (!isalnum((unsigned char)email[atIndex - 1]))
    {
        printf("\nThe username must end with a letter or number before '@'.\n");
        return 0;
    }


    /* Something must exist between '@' and '.' */
    if (dotIndex == atIndex + 1)
    {
        printf("\nA domain name is required between '@' and '.'.\n");
        return 0;
    }

    /* Validate the domain section */
    i = atIndex + 1;

    while (i < length)
    {
        if (email[i] == '.')
        {
            i++;
            continue;
        }

        if (!islower((unsigned char)email[i]))
        {
            printf("\nThe domain can contain lowercase letters only.\n");
            return 0;
        }

        i++;
    }
    /* Check supported email extensions */
    const char *extension = email + dotIndex;

    if (strcmp(extension, ".com") != 0 && strcmp(extension, ".in") != 0)
    {
        printf("\nUnsupported email extension. Use .com or .in.\n");
        return 0;
    }
    /* Check whether the email already exists */
    i = 0;

    while(i<addressBook->contactCount)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("\nThis email address is already in use.\n");
            return 0;
        }

        i++;
    }

    return 1;
}
