#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define NAME_LEN     50
#define PHONE_LEN    20
#define EMAIL_LEN    50

// Structure to hold individual contact information
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

// Structure of main address book
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

//Validation 
int validateName(const char *name);
int validatePhone(const AddressBook *addressBook, const char *phone);
int validateEmail(const AddressBook *addressBook, const char *email);

//Selection Helpers 
int Selected_byname_contact(int index[], AddressBook *addressBook);
int Selected_byphone_contact(int index[], AddressBook *addressBook);
int Selected_byemail_contact(int index[], AddressBook *addressBook);

/* --- File I/O & Population --- */
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);
void populateAddressBook(AddressBook *addressBook);

/* --- Input Utility --- */
void clearInputBuffer(void);
void showLoading(const char *message);

#endif /* CONTACT_H */