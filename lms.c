#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for Book and Member
typedef struct 
{
    int book_id;
    char book_name[100];
    char book_author[100];
    int IsBorrowed; // 0 for available, 1 for borrowed
} Book;

typedef struct 
{
    int member_id;
    char member_name[100];
    int BorrowedBookID; // -1 if no book is borrowed
} Member;

// Global variables for book and member arrays
Book *books = NULL;
Member *members = NULL;
int BookCount = 0;
int MemberCount = 0;

// Function declarations
void LoadBooks();
void SaveBooks();
void LoadMembers();
void SaveMembers();
void AddBook();
void DisplayBooks();
void SearchBook();
void AddMember();
void DisplayMembers();
void BorrowBook();
void ReturnBook();

int main()
{
    int choice;
    // Load data from files
    LoadBooks();
    LoadMembers();

    do {
        printf("\n============ LIBRARY MANAGEMENT SYSTEM ============\n");
        printf("1: ADD A NEW BOOK\n");
        printf("2: DISPLAY ALL BOOKS\n");
        printf("3: SEARCH BOOK BY ID\n");
        printf("4: ADD A NEW MEMBER\n");
        printf("5: DISPLAY ALL MEMBERS\n");
        printf("6: BORROW A BOOK\n");
        printf("7: RETURN A BOOK\n");
        printf("8: EXIT\n");
        printf("ENTER YOUR CHOICE (1-8): ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            AddBook();
            break;
        case 2:
            DisplayBooks();
            break;
        case 3:
            SearchBook();
            break;
        case 4:
            AddMember();
            break;
        case 5:
            DisplayMembers();
            break;
        case 6:
            BorrowBook();
            break;
        case 7:
            ReturnBook();
            break;
        case 8:
            SaveBooks();
            SaveMembers();
            printf("Exiting the system. Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);

    // Free allocated memory
    free(books);
    free(members);

    return 0;
}

// Function to load books from file
void LoadBooks()
{
    FILE *file = fopen("books.dat", "r");
    if (file == NULL) return; // No books saved yet
    fscanf(file, "%d", &BookCount);
    books = malloc(BookCount * sizeof(Book));
    for (int i = 0; i < BookCount; i++) 
    {
        fscanf(file, "%d %[^\n] %[^\n] %d", &books[i].book_id, books[i].book_name, books[i].book_author, &books[i].IsBorrowed);
    }
    fclose(file);
}

// Function to save books to file
void SaveBooks()
{
    FILE *file = fopen("books.dat", "w");
    if (file == NULL) 
    {
        printf("Error saving books!\n");
        return;
    }
    fprintf(file, "%d\n", BookCount);
    for (int i = 0; i < BookCount; i++) 
    {
        fprintf(file, "%d\n%s\n%s\n%d\n", books[i].book_id, books[i].book_name, books[i].book_author, books[i].IsBorrowed);
    }
    fclose(file);
}

// Function to load members from file
void LoadMembers()
{
    FILE *file = fopen("members.dat", "r");
    if (file == NULL) return; // No members saved yet
    fscanf(file, "%d", &MemberCount);
    members = malloc(MemberCount * sizeof(Member));
    for (int i = 0; i < MemberCount; i++) 
    {
        fscanf(file, "%d %[^\n] %d", &members[i].member_id, members[i].member_name, &members[i].BorrowedBookID);
    }
    fclose(file);
}

// Function to save members to file
void SaveMembers()
{
    FILE *file = fopen("members.dat", "w");
    if (file == NULL) 
    {
        printf("Error saving members!\n");
        return;
    }
    fprintf(file, "%d\n", MemberCount);
    for (int i = 0; i < MemberCount; i++) 
    {
        fprintf(file, "%d\n%s\n%d\n", members[i].member_id, members[i].member_name, members[i].BorrowedBookID);
    }
    fclose(file);
}

// Function to add a new book
void AddBook()
{
    BookCount++;
    books = realloc(books, BookCount * sizeof(Book));
    printf("Enter Book ID: ");
    scanf("%d", &books[BookCount - 1].book_id);
    printf("Enter Book Name: ");
    scanf(" %[^\n]", books[BookCount - 1].book_name);
    printf("Enter Author Name: ");
    scanf(" %[^\n]", books[BookCount - 1].book_author);
    books[BookCount - 1].IsBorrowed = 0; // Book is available by default
    printf("Book added successfully!\n");
}

// Function to display all books
void DisplayBooks()
{
    if (BookCount == 0) {
        printf("No books available.\n");
        return;
    }
    for (int i = 0; i < BookCount; i++) 
    {
        printf("Book ID: %d\nName: %s\nAuthor: %s\nStatus: %s\n",
               books[i].book_id, books[i].book_name, books[i].book_author,
               books[i].IsBorrowed ? "Borrowed" : "Available");
        printf("-------------------------------------\n");
    }
}

// search a book by id
void SearchBook()
{
    int id, found = 0;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < BookCount; i++) 
    {
        if (books[i].book_id == id) 
        {
            printf("Book ID: %d\nName: %s\nAuthor: %s\nStatus: %s\n",
                   books[i].book_id, books[i].book_name, books[i].book_author,
                   books[i].IsBorrowed ? "Borrowed" : "Available");
            found = 1;
            break;
        }
    }
    if (!found) 
    {
        printf("Book with ID %d not found.\n", id);
    }
}

// Function to add a new member
void AddMember()
{
    MemberCount++;
    members = realloc(members, MemberCount * sizeof(Member));
    printf("Enter Member ID: ");
    scanf("%d", &members[MemberCount - 1].member_id);
    printf("Enter Member Name: ");
    scanf(" %[^\n]", members[MemberCount - 1].member_name);
    members[MemberCount - 1].BorrowedBookID = -1; // No book borrowed initially
    printf("Member added successfully!\n");
}

// Function to display all members
void DisplayMembers()
{
    if (MemberCount == 0) {
        printf("No members available.\n");
        return;
    }
    for (int i = 0; i < MemberCount; i++) 
    {
        printf("Member ID: %d\nName: %s\nBorrowed Book ID: %d\n",
               members[i].member_id, members[i].member_name,
               members[i].BorrowedBookID == -1 ? 0 : members[i].BorrowedBookID);
        printf("-------------------------------------\n");
    }
}

// Function to borrow a book
void BorrowBook()
{
    int MId, BId, FoundMember = 0, FoundBook = 0;
    printf("Enter Member ID: ");
    scanf("%d", &MId);
    printf("Enter Book ID: ");
    scanf("%d", &BId);

    for (int i = 0; i < MemberCount; i++) 
    {
        if (members[i].member_id == MId) 
        {
            FoundMember = 1;
            if (members[i].BorrowedBookID != -1) 
            {
                printf("Member has already borrowed a book.\n");
                return;
            }
            for (int j = 0; j < BookCount; j++) 
            {
                if (books[j].book_id == BId && books[j].IsBorrowed == 0) 
                {
                    books[j].IsBorrowed = 1;
                    members[i].BorrowedBookID = BId;
                    printf("Book borrowed successfully!\n");
                    return;
                } else if (books[j].book_id == BId && books[j].IsBorrowed == 1) 
                {
                    printf("Book is already borrowed.\n");
                    return;
                }
            }
            FoundBook = 1;
        }
    }

    if (!FoundMember) printf("Member not found.\n");
    if (!FoundBook) printf("Book not found.\n");
}

// Function to return a book
void ReturnBook()
{
    int MId, found = 0;
    printf("Enter Member ID: ");
    scanf("%d", &MId);

    for (int i = 0; i < MemberCount; i++) 
    {
        if (members[i].member_id == MId) 
        {
            found = 1;
            if (members[i].BorrowedBookID == -1) 
            {
                printf("Member has not borrowed any book.\n");
                return;
            }
            for (int j = 0; j < BookCount; j++) {
                if (books[j].book_id == members[i].BorrowedBookID)
                {
                    books[j].IsBorrowed = 0;
                    members[i].BorrowedBookID = -1;
                    printf("Book returned successfully!\n");
                    return;
                }
            }
        }
    }

    if (!found) printf("Member not found.\n");
}
