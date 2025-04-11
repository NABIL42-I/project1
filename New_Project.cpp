#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>  
#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_PHONE_LENGTH 15
#define MAX_PASSWORD_LENGTH 50

// Struct for Book
typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    float price;
    int quantity;
} Book;

// *********
bool isLoggedIn =0;

// Struct for User
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Global arrays to hold books and users
Book books[MAX_BOOKS];
User users[MAX_USERS];
int nextBookId = 1;
int nextUserId = 1;
int bookCount = 0;
int userCount = 0;
//                                                                     Function Prototypes
void saveBooksToFile();
void loadBooksFromFile();

//                                                                  Function to show a random motivational quote
void showMotivationalQuote() {

    const char* quotes[] = {

        " A room without books is like a body without a soul. -> Marcus Tullius Cicero\n",
        " There is no friend as loyal as a book. -> Ernest Hemingway\n",
        " Books are a uniquely portable magic. -> Stephen King\n",
        " Reading is to the mind what exercise is to the body.  -> Joseph Addison\n",
        " A book is a dream that you hold in your hand. -> Neil Gaiman\n"

    };

    int randomIndex = rand() % 5;
    printf("~>%s\n", quotes[randomIndex]);

}
// *********************
//                                                                                Save books to file
void saveBooksToFile() {
    FILE *fp = fopen("books.txt", "w");
    if (!fp) {
        printf("Error saving books to file!\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%d|%s|%s|%.2f|%d\n", books[i].id, books[i].title,
                books[i].author, books[i].price, books[i].quantity);
    }

    fclose(fp);
}

// **********************************
//                                                                                 Load books from file
void loadBooksFromFile() {
    FILE *fp = fopen("books.txt", "r");
    if (!fp) return;

    while (fscanf(fp, "%d|%[^|]|%[^|]|%f|%d\n", &books[bookCount].id,
                  books[bookCount].title, books[bookCount].author,
                  &books[bookCount].price, &books[bookCount].quantity) == 5) {
        if (books[bookCount].id >= nextBookId) {
            nextBookId = books[bookCount].id + 1;
        }
        bookCount++;
    }

    fclose(fp);
}

//                                                                    Function to greet the user based on time of day
void greetUser() {
    time_t t;
    struct tm *tm_info;
    char timeStr[5];

    time(&t);
    tm_info = localtime(&t);
    strftime(timeStr, sizeof(timeStr), "%H", tm_info); // Get the current hour

    int hour = atoi(timeStr);

    //                                                                   Display greeting based on the time of day
    printf("\n");
    if (hour >= 5 && hour < 12) {
        printf("~~~~~~~~~~~~~~~~~~~Good Morning! Welcome to the Online Book Shop.~~~~~~~~~~~~~~~~~~~\n");
    } else if (hour >= 12 && hour < 17) {
        printf("~~~~~~~~~~~~~~~~~~~Good Afternoon! Welcome to the Online Book Shop.~~~~~~~~~~~~~~~~\n");
    } else if (hour >= 17 && hour < 21) {
        printf("~~~~~~~~~~~~~~~~~~Good Evening! Welcome to the Online Book Shop.~~~~~~~~~~~~~~~~~~\n");
    } else {
        printf("~~~~~~~~~~~~~~~~~~Good Night! Welcome to the Online Book Shop.~~~~~~~~~~~~~~~~~~~\n");
    }
}


// Function to add a book
// Function to add a book (protected by admin password)
// Needed for getch()

//                                                                          Function to take password input and mask it with '*'
void getPassword(char* password, int maxLength) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();  // Read a single character without showing it

        if (ch == 13) { // Enter key pressed
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8) { // Backspace pressed
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < maxLength - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
}

//                                                                     Function to add a book (protected by password with masked input)
void addBook() {
    char password[50];

    // Ask for admin password with '*' masking
    printf("Enter admin password to add a book: ");
    getPassword(password, sizeof(password));

    // Check if password is correct
    if (strcmp(password, "111") != 0) {
        printf("Incorrect password! Access denied.\n");
        return;
    }

    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full!\n");
        return;
    }

    Book newBook;
    newBook.id = nextBookId++;

    printf("Enter book title: ");
    getchar();  // Clear leftover newline
    fgets(newBook.title, MAX_TITLE_LENGTH, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;

    printf("Enter book author: ");
    fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;

    printf("Enter book price: ");
    scanf("%f", &newBook.price);

    printf("Enter book quantity: ");
    scanf("%d", &newBook.quantity);

    books[bookCount++] = newBook;
    saveBooksToFile();
    printf("Book added successfully!\n");
}


//                                                                                   Function to display all books
// Display all books
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }
   system("cls");
    printf("\nAvailable Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d | Title: %s | Author: %s | Price: $%.2f | Quantity: %d\n",
            books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
    }
    printf("\n\t\t\tPress any key to return to the previous menu...");
    getchar(); // To consume newline if previous input used scanf
    getchar(); // Wait for user to press a key
}

//                                                                                  Function to search for a book by title
// Search book
void searchBook() {
    char title[MAX_TITLE_LENGTH];
    printf("Enter book title to search: ");
    getchar();
    fgets(title, MAX_TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0;

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Book Found - ID: %d, Author: %s, Price: $%.2f, Quantity: %d\n",
                books[i].id, books[i].author, books[i].price, books[i].quantity);
            return;
        }
    }
    printf("Book not found.\n");
}

//                                                                                  Function to buy a book by ID
// Buy a book
void buyBook() {
     
    if (!isLoggedIn) {
        system("cls");
        printf("\t\t-----You must log in first to buy books-----\n");
        printf("\n\t\tPress Enter to continue...");
        getchar(); // Wait for user to press Enter
        getchar();
        return;
    }
    int id, qty;
    printf("Enter book ID to buy: ");
    scanf("%d", &id);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            if (books[i].quantity >= qty) {
                books[i].quantity -= qty;
                saveBooksToFile();
                printf("Purchase successful! Total: $%.2f\n", books[i].price * qty);
                return;
            } else {
                printf("Not enough stock available.\n");
                return;
            }
        }
    }
    printf("Book ID not found.\n");
}


//                                                                                       Function to delete a book by ID
// Delete book
void deleteBook() {
    char password[50];

    // Ask for admin password with '*' masking
    printf("Enter admin password to update a book: ");
    getPassword(password, sizeof(password));

    // Check if password is correct
    if (strcmp(password, "111") != 0) {
        printf("Incorrect password! Access denied.\n");
        return;
    }
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            saveBooksToFile();
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book ID not found.\n");
}


//                                                                                Function to update book information
// Update book
void updateBook() {
    char password[50];

    // Ask for admin password with '*' masking
    printf("Enter admin password to update a book: ");
    getPassword(password, sizeof(password));

    // Check if password is correct
    if (strcmp(password, "111") != 0) {
        printf("Incorrect password! Access denied.\n");
        return;
    }
    int id;
    printf("Enter book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Enter new title: ");
            getchar();
            fgets(books[i].title, MAX_TITLE_LENGTH, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;

            printf("Enter new author: ");
            fgets(books[i].author, MAX_AUTHOR_LENGTH, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;

            printf("Enter new price: ");
            scanf("%f", &books[i].price);

            printf("Enter new quantity: ");
            scanf("%d", &books[i].quantity);

            saveBooksToFile();
            printf("Book updated successfully!\n");
            return;
        }
    }
    printf("Book ID not found.\n");
}


//                                                                              Function to register a new user

// Register user
// Save users to file
void saveUsersToFile() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing users!\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s\n",
                users[i].id,
                users[i].name,
                users[i].email,
                users[i].phone,
                users[i].password);
    }

    fclose(fp);
}

//                                                                              Load users from file
void loadUsersFromFile() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        // File might not exist yet
        return;
    }

    userCount = 0;

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^\n]\n",
                  &users[userCount].id,
                  users[userCount].name,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].password) == 5) {
        if (users[userCount].id >= nextUserId) {
            nextUserId = users[userCount].id + 1;
        }
        userCount++;
    }

    fclose(fp);
}

//                                                                                Welcome screen after login
void welcome() {
    system("cls"); // Use "clear" if on Linux
    printf("\n\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t|         Welcome To           |\n");
    printf("\t\t\t|     Online Book Shop!        |\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\n\t\tPress Enter to continue...");
    getchar(); // Wait for Enter
}

//                                                                                    Add/register a user
void addUser() {
    if (userCount >= MAX_USERS) {
        printf("User storage is full!\n");
        return;
    }

    User newUser;
    newUser.id = nextUserId++;

    printf("Enter user name: ");
    getchar();
    fgets(newUser.name, MAX_NAME_LENGTH, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;

    printf("Enter user email: ");
    fgets(newUser.email, MAX_EMAIL_LENGTH, stdin);
    newUser.email[strcspn(newUser.email, "\n")] = 0;

    printf("Enter user phone: ");
    fgets(newUser.phone, MAX_PHONE_LENGTH, stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = 0;

    printf("Enter password: ");
    fgets(newUser.password, MAX_PASSWORD_LENGTH, stdin);
    newUser.password[strcspn(newUser.password, "\n")] = 0;

    users[userCount++] = newUser;
    saveUsersToFile(); // Save after registration
    printf("User registered successfully!\n");
}

//                                                                                          Login a user
void loginUser() {
    loadUsersFromFile(); // Load users before login

    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter email: ");
    getchar(); // clear buffer
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            isLoggedIn = 1;
            found = 1;
            welcome();
            printf("Login successful! Welcome, %s!\n", users[i].name);
            return;
        }
    }

    if (!found) {
        printf("Login failed. Incorrect email or password.\n");
    }
}
//                                                                                books categoryMenu function
int categoryMenu() {
    system("cls");
    printf("\n\t\t\t|===========================================|\n");
    printf("\t\t\t|          SELECT A BOOK CATEGORY           |\n");
    printf("\t\t\t|===========================================|\n");
    printf("\t\t\t|  1.  Fiction                              |\n");
    printf("\t\t\t|  2.  Non-Fiction                          |\n");
    printf("\t\t\t|  3.  Poetry                               |\n");
    printf("\t\t\t|  4.  Drama                                |\n");
    printf("\t\t\t|  5.  Educational                          |\n");
    printf("\t\t\t|  6.  Children's Books                     |\n");
    printf("\t\t\t|  7.  Art & Design                         |\n");
    printf("\t\t\t|  8.  Religious & Spiritual                |\n");
    printf("\t\t\t|  9.  Comics & Graphic Novel               |\n");
    printf("\t\t\t| 10.  Cookbooks                            |\n");
    printf("\t\t\t| 11.  Reference                            |\n");
    printf("\t\t\t| 12.  Humor                                |\n");
    printf("\t\t\t| 13.  Philosophical Fiction                |\n");
    printf("\t\t\t| 14.  Cyberpunk                            |\n");
    printf("\t\t\t| 15.  Magical Realism                      |\n");
    printf("\t\t\t| 16.  Epistolary Novels                    |\n");
    printf("\t\t\t| 17.  Dystopian Science Fiction            |\n");
    printf("\t\t\t| 18.  Historical Fantasy                   |\n");
    printf("\t\t\t| 19.  Nonfiction Storytelling              |\n");
    printf("\t\t\t| 20.  Surrealist Literature                |\n");
    printf("\t\t\t| 21.  Satirical Novels                     |\n");
    printf("\t\t\t|===========================================|\n");

    printf("\n\t\t\tEnter your choice (1-21): ");
    int com;// Take  commands from user
    scanf("%d", &com);
// if(com>21){
//     printf("Invalid Choice, Kindly enter Correct Keyword!\n");
//     // )
// }
// else{         
    // Optionally handle input
    printf("\n\t\t\tYou selected category %d.\n", com);
// }
return com;
}
 //                                                      Books in the Fiction Category  function
void showFictionBooks() {
    system("cls");
    printf("\n\t\t\t=============================================\n");
    printf("\t\t\t|        Books in the Fiction Category       |\n");
    printf("\t\t\t=============================================\n");
    printf("\t\t\t- The Great Gatsby by F. Scott Fitzgerald\n");
    printf("\t\t\t- The Book Thief by Markus Zusak\n");
    printf("\t\t\t- Dune by Frank Herbert\n");
    printf("\t\t\t- The Lord of the Rings by J.R.R. Tolkien\n");
    printf("\t\t\t- Gone Girl by Gillian Flynn\n");
    printf("\t\t\t- It by Stephen King\n");
    printf("\t\t\t- Pride and Prejudice by Jane Austen\n");
    printf("\t\t\t- Treasure Island by Robert Louis Stevenson\n");
    printf("\t\t\t- The Hunger Games by Suzanne Collins\n");
    printf("\t\t\t- 1984 by George Orwell\n");
    printf("\t\t\t=============================================\n");

    printf("\n\t\t\tPress any key to return to the previous menu...");
    getchar(); // To consume newline if previous input used scanf
    getchar(); // Wait for user to press a key
}

//                                                     NON-FICTION CATEGORY BOOK LIST 
void showNonFictionBooks() {
    system("cls");

    printf("\n\n\t\t\t     NON-FICTION CATEGORY BOOK LIST\n");
    printf("\t\t========================================================\n\n");

    printf("\t\t  - The Diary of a Young Girl\t\t\t\n");
    printf("\t\t  - The Power of Habit\t\t\t\t\n");
    printf("\t\t  - Thinking, Fast and Slow\t\t\t\n");
    printf("\t\t  - Meditations\t\t\t\t\t\n");
    printf("\t\t  - The Body Keeps the Score\t\t\t\n");
    printf("\t\t  - In Cold Blood\t\t\t\t\n");
    printf("\t\t  - Into the Wild\t\t\t\t\n");
    printf("\t\t  - SALT, FAT, ACID, HEAT\t\t\t\n");
    printf("\t\t  - The Lean Startup\t\t\t\t\n");
    printf("\t\t  - Sapiens: A Brief History of Humankind\t\n");
    printf("\t\t  - The Audacity of Hope\t\t\t\n");

    printf("\n\t\t========================================================\n");
    printf("\t\t     Find the truth, learn the stories, live the lessons\n");

    printf("\n\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user to press Enter
}
//                                                     POETRY CATEGORY BOOKS
void showPoetryBooks() {
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t     POETRY CATEGORY BOOKS");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Waste Land by T.S. Eliot");
    printf("\n\t\t\t  2. Milk and Honey by Rupi Kaur");
    printf("\n\t\t\t  3. The Essential Haiku by Robert Hass");
    printf("\n\t\t\t  4. The 100 Best Limericks by Thomas H. Upton");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Immerse yourself in rhythm and rhyme.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume newline
    getchar(); // wait for user
}

//                                                   DRAMA CATEGORY BOOKS
void showDramaBooks() {
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t     DRAMA CATEGORY BOOKS");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Hamlet by William Shakespeare");
    printf("\n\t\t\t  2. Death of a Salesman by Arthur Miller");
    printf("\n\t\t\t  3. Oedipus Rex by Sophocles");
    printf("\n\t\t\t  4. A Midsummer Night's Dream by William Shakespeare");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Witness emotion unfold on stage.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                      EDUCATIONAL CATEGORY BOOKS                
void showEducationalBooks() {
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  EDUCATIONAL CATEGORY BOOKS");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Introduction to Algorithms by Thomas H. Cormen");
    printf("\n\t\t\t  2. On the Origin of Species by Charles Darwin");
    printf("\n\t\t\t  3. Oxford English Dictionary");
    printf("\n\t\t\t  4. Cracking the Coding Interview by Gayle Laakmann McDowell");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Expand your mind, explore knowledge.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}


//                                                            CHILDREN'S BOOKS CATEGORY function
void showChildrensBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of children's books
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  CHILDREN'S BOOKS CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Where the Wild Things Are by Maurice Sendak");
    printf("\n\t\t\t  2. Green Eggs and Ham by Dr. Seuss");
    printf("\n\t\t\t  3. Harry Potter and the Sorcerer's Stone by J.K. Rowling");
    printf("\n\t\t\t  4. Amulet by Kazu Kibuishi");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  A world of adventure and imagination.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}


//                                                                ART & DESIGN CATEGORY BOOKS function
void showArtAndDesignBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Art & Design books
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  ART & DESIGN CATEGORY BOOKS");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Story of Art by E.H. Gombrich");
    printf("\n\t\t\t  2. On Photography by Susan Sontag");
    printf("\n\t\t\t  3. Thinking with Type by Ellen Lupton");
    printf("\n\t\t\t  4. The Architecture of Happiness by Alain de Botton");
    printf("\n\t\t\t  5. The Fashion System by Roland Barthes");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Explore creativity and design.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                RELIGIOUS & SPIRITUAL CATEGORY Function
void showReligiousAndSpiritualBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Religious & Spiritual books
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  RELIGIOUS & SPIRITUAL CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Bible");
    printf("\n\t\t\t  2. The Quran");
    printf("\n\t\t\t  3. The Heart of the Buddha's Teaching by Thich Nhat Hanh");
    printf("\n\t\t\t  4. The Bhagavad Gita by Eknath Easwaran");
    printf("\n\t\t\t  5. Mythology by Edith Hamilton");
    printf("\n\t\t\t  6. The Power of Now by Eckhart Tolle");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Explore wisdom and spirituality.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                                  COMICS & GRAPHIC NOVELS CATEGORY Function
void showComicsAndGraphicNovelsBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Comics & Graphic Novels books
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  COMICS & GRAPHIC NOVELS CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Naruto by Masashi Kishimoto");
    printf("\n\t\t\t  2. Watchmen by Alan Moore");
    printf("\n\t\t\t  3. Sarah's Scribbles by Sarah Andersen");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Dive into the world of graphic storytelling.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                                COOKBOOKS CATEGORY Function
void showCookbooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Cookbooks
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  COOKBOOKS CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Bread Baker's Apprentice by Peter Reinhart");
    printf("\n\t\t\t  2. Jerusalem: A Cookbook by Yotam Ottolenghi");
    printf("\n\t\t\t  3. The Oh She Glows Cookbook by Angela Liddon");
    printf("\n\t\t\t  4. 30-Minute Meals by Rachael Ray");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Discover delicious recipes and cooking tips.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                           REFERENCE CATEGORY BOOKS Function
void showReferenceBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Reference books
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  REFERENCE CATEGORY BOOKS");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Merriam-Webster's Collegiate Dictionary");
    printf("\n\t\t\t  2. Encyclopedia Britannica");
    printf("\n\t\t\t  3. The Old Farmer's Almanac");
    printf("\n\t\t\t  4. National Geographic Atlas of the World");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Your source of knowledge and information.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}
//
//                                                               SATIRICAL NOVELS CATEGORY Function 

void showSatiricalNovels() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Satirical Novels
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  SATIRICAL NOVELS CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Catch-22 by Joseph Heller");
    printf("\n\t\t\t  2. Slaughterhouse-Five by Kurt Vonnegut");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Satire at its finest.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                                  SURREALIST LITERATURE CATEGORY Function
void showSurrealistLiterature() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Surrealist Literature books
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  SURREALIST LITERATURE CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Metamorphosis by Franz Kafka");
    printf("\n\t\t\t  2. The Trial by Franz Kafka");
    printf("\n\t\t\t  3. Invisible Cities by Italo Calvino");
    printf("\n\t\t\t  4. The Obscene Bird of Night by José Donoso");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Explore the surreal and the fantastic.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                                 Display the list of Nonfiction Storytelling books
void showNonfictionStorytelling() {
    // Clear screen using 'cls' for Windows
    system("cls");
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  NONFICTION STORYTELLING CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Sapiens: A Brief History of Humankind by Yuval Noah Harari");
    printf("\n\t\t\t  2. Educated by Tara Westover");
    printf("\n\t\t\t  3. Into the Wild by Jon Krakauer");
    printf("\n\t\t\t  4. The Immortal Life of Henrietta Lacks by Rebecca Skloot");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Stories that captivate and enlighten.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                                               Display the list of Historical Fantasy books
void showHistoricalFantasyBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  HISTORICAL FANTASY CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Jonathan Strange & Mr Norrell by Susanna Clarke");
    printf("\n\t\t\t  2. The Night Watch by Sergei Lukyanenko");
    printf("\n\t\t\t  3. The Lions of Al-Rassan by Guy Gavriel Kay");
    printf("\n\t\t\t  4. The Golem and the Jinni by Helene Wecker");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  A blend of history and fantasy.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                       // Display the list of Humor books
void showHumorBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  HUMOR CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Hitchhiker's Guide to the Galaxy by Douglas Adams");
    printf("\n\t\t\t  2. Pride and Prejudice and Zombies by Seth Grahame-Smith");
    printf("\n\t\t\t  3. Born a Crime by Trevor Noah");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Laugh out loud with these witty books!");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                            // Display the list of Philosophical Fiction books

void showPhilosophicalFiction() {
    // Clear screen using 'cls' for Windows
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  PHILOSOPHICAL FICTION CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Sophie's World by Jostein Gaarder");
    printf("\n\t\t\t  2. The Stranger by Albert Camus");
    printf("\n\t\t\t  3. The Myth of Sisyphus by Albert Camus");
    printf("\n\t\t\t  4. The Story of SIUUU by Abir");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Deep thoughts, deep stories.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

    //                                                 Display the list of Dystopian Science Fiction books

void showDystopianScienceFiction() {
    // Clear screen using 'cls' for Windows
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  DYSTOPIAN SCIENCE FICTION CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. The Handmaid's Tale by Margaret Atwood");
    printf("\n\t\t\t  2. Fahrenheit 451 by Ray Bradbury");
    printf("\n\t\t\t  3. Brave New World by Aldous Huxley");
    printf("\n\t\t\t  4. The Dispossessed by Ursula K. Le Guin");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  A glimpse into dystopian futures.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                           // Display the list of Epistolary Novels

void showEpistolaryNovels() {
    // Clear screen using 'cls' for Windows
    system("cls");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  EPISTOLARY NOVELS CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Dracula by Bram Stoker");
    printf("\n\t\t\t  2. The Perks of Being a Wallflower by Stephen Chbosky");
    printf("\n\t\t\t  3. 84, Charing Cross Road by Helene Hanff");
    printf("\n\t\t\t  4. Frankenstein by Mary Shelley");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Stories told through letters.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                        // Display the list of Cyberpunk books
void showCyberpunkBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  CYBERPUNK CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. Neuromancer by William Gibson");
    printf("\n\t\t\t  2. Snow Crash by Neal Stephenson");
    printf("\n\t\t\t  3. Altered Carbon by Richard K. Morgan");
    printf("\n\t\t\t  4. Do Androids Dream of Electric Sheep? by Philip K. Dick");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Dive into a high-tech, low-life world.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                                    Display the list of Magical Realism books

void showMagicalRealismBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");
    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  MAGICAL REALISM CATEGORY");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n\t\t\t  1. One Hundred Years of Solitude by Gabriel García Márquez");
    printf("\n\t\t\t  2. The House of the Spirits by Isabel Allende");
    printf("\n\t\t\t  3. The Night Circus by Erin Morgenstern");
    printf("\n\t\t\t  4. 100 Types of Vondami by Dr. Maruf Mridha");

    printf("\n\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t  Where the ordinary meets the extraordinary.");
    printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // Prompt user to return to the main menu
    printf("\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user input
}

//                                         Selected by user , user can choose any catagory and then search those books in search option if it's available now in book store!!       
void Suggest_Book()
{
    printf("Kindly, Enter a book category :\n");
    
  
  int com =  categoryMenu() ;
  if(com>21){
    printf("Invalid Choice, Kindly enter Correct Keyword!\n");
    // when com is greater than 21;
    return; 
    // if user enter wrong keyword then program execution will stop automatically
}

       if (com==1) 
       {

        showFictionBooks();
    }
    else if (com == 2) 
    {
        showNonFictionBooks();
    }
else if (com == 3)
{
        // printf("\nBooks in the Poetry category:\n");

        showPoetryBooks();
    }
    else if (com == 4) 
    {
        // printf("\nBooks in the Drama category:\n");
     
        showDramaBooks();
     
    }
    else if (com == 5)
    {
        // printf("\nBooks in the Educational category:\n");
        showEducationalBooks();
    }
    else if (com == 6) 
    {
        // printf("\nBooks in the Children's Books category:\n");
        showChildrensBooks();
    }
 else if (com == 7) 
 {
        // printf("\nBooks in the Art & Design category:\n");
  
        showArtAndDesignBooks();
    }
    else if (com == 8) 
    {
        // printf("\nBooks in the Religious & Spiritual category:\n");
        showReligiousAndSpiritualBooks();
    }
    else if (com == 9)
    {
        // printf("\nBooks in the Comics & Graphic Novels category:\n");
        showComicsAndGraphicNovelsBooks();
    }
    else if(com == 10)
    {
        // printf("\nBooks in the Cookbooks category:\n");
        showCookbooks();
    }
else if (com == 11)
{
        // printf("\nBooks in the Reference category:\n");
        showReferenceBooks();
    }
    else if (com == 12) 
    {
        // printf("\nBooks in the Humor category:\n");
    
        showHumorBooks();
    }
     else if (com == 13) 
     {
    //     printf("\nBooks in the  Philosophical Fiction :\n");
    showPhilosophicalFiction();
     }
     else if (com == 14)
     {
        // printf("\nBooks in the  Cyberpunk :\n");
        showCyberpunkBooks();
     }
else if (com == 15) {
        // printf("\nBooks in the  Magical Realism:\n");
        showMagicalRealismBooks();

      }
       else if (com == 16) {
        // printf("\nBooks in the Epistolary Novels category:\n");   
        showEpistolaryNovels();
      }
       else if (com == 17) {
        // printf("\nBooks in the Dystopian Science Fiction category:\n");
        showDystopianScienceFiction();
    }
    else if (com == 18) {
        // printf("\nBook in the Historical Fantasy category:\n");
        showHistoricalFantasyBooks();
    }
else if (com == 19) {
        // printf("\nBooks in the  Nonfiction Storytelling category:\n");
        showNonfictionStorytelling();
    }

else if (com == 20) {
        // printf("\nBooks in the Surrealist Literature category:\n");
        showSurrealistLiterature();
    }
    else if (com == 21) {
        // printf("\nBooks in the Satirical Novels category:\n");
        showSatiricalNovels();
    }
        
    else {
        printf("Invalid!!!!!!!!!!\n");
    }


}

//                                                                      Give goodbye message to user
void goodbyeMessage() {
    // system("cls") for clear the terminal
    system("cls");

    printf("\n\n");
    printf("\t\t\t*******************************\n");
    printf("\t\t\t*    Thanks For Using Our     *\n");
    printf("\t\t\t*     Online Book System      *\n");
    printf("\t\t\t*         Stay Happy!         *\n");
    printf("\t\t\t*******************************\n");
    printf("\n\n");
}

//                                                   Day of Week Calculation using Zeller's Congruence-like formula for Jan 1"
// or more informally
// "Mod 7 Year-Day Offset Formula"
int First_Day_of_Year(int yrrrear){
    int day = (yrrrear * 365 + (yrrrear - 1) / 4 - (yrrrear - 1) / 100 + (yrrrear - 1) / 400) % 7;
    return day; // Sunday = 0
}

//                                                                          Calender Fuction 
int  calender(){
    system("cls");
    int i,j,TotalDays,weekdays ,spaceCounter = 0,year;
    printf("Enter your Year : ");
    scanf("%d",&year);
    printf("\n");

    char month[12][20]={"January", "February","March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int DaysInMonth[]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("\n*********************** WELCOME TO %d ******************************\n",year);

    // check if it is a leap year
    if ((year%4 == 0 && year%100!= 0) || (year%400==0)){
        DaysInMonth[1] = 29;
    }

    weekdays = First_Day_of_Year(year);

    for(i=0;i<12;i++){
        printf("\n\n-------------------- %s ----------------------\n\n",month[i]);
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n\n");

        for(spaceCounter = 0; spaceCounter < weekdays; spaceCounter++)
            printf("     ");

        TotalDays = DaysInMonth[i];

        for(j=1; j<=TotalDays; j++){
            printf("%5d",j);
            weekdays++;
            if(weekdays > 6){
                weekdays = 0;
                printf("\n");
            }
        }
      
    }
    return year;
}
//                                                    Store Owner 
void Credits(){
        char names[5][20] = {"SHAWON", "MARUF", "ABIR", "ANTU", "NABIL"};
    
        printf("=================================================\n");
        printf("               🎓 Our Team Members 🎓           \n");
        printf("=================================================\n");
    
        for (int i = 0; i < 5; i++) {
        printf("🔹                     %-10s\n", names[i]);  // Left-aligned with bullet
        }
    
        printf("=================================================\n");
    }
  
    //                                                           Customer Feedback function 
void customer_feedback() {
    system("cls");
    char name[50];
    char feedback[500];
    FILE *file;

    // Open file in append mode
    file = fopen("feedback.txt", "a");

    if (file == NULL) {
        printf("Error opening feedback file!\n");
        return;
    }

    printf("\n============================================\n");
    printf("          Customer Feedback Form          \n");
    printf("============================================\n");
    getchar();
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // remove newline
    printf("Enter your feedback: ");
    fgets(feedback, sizeof(feedback), stdin);
    feedback[strcspn(feedback, "\n")] = 0;

    // Write to file
    fprintf(file, "Name     : %s\n", name);
    fprintf(file, "Feedback : %s\n", feedback);
    fprintf(file, "--------------------------------------------\n");

    fclose(file);  // Close file

    // Display confirmation
    printf("\n============================================\n");
    printf("        Thank You for Your Feedback!       \n");
    printf("============================================\n");
    printf("Name     : %s\n", name);
    printf("Feedback : %s\n", feedback);
    printf("============================================\n");
    printf("\n============================================\n");
printf("       Thank You for Your Feedback!       \n");
printf("Your feedback helps us improve our service.   \n");
printf("We truly appreciate your time and thoughts.    \n");
printf("============================================\n");
 // Prompt user to return to the main menu
 printf("\n\t\t\tPress Enter to return to the main menu...");
 getchar(); // consume leftover newline
 getchar(); // wait for user input
}

//                                                 ShowcurrentDatetime to user
void showCurrentDateTime() {
    time_t t;
    struct tm *tm_info;
    char buffer[100];

    // Get the current time
    time(&t);
    tm_info = localtime(&t);

    printf("\n");
    printf("====================================================\n");

    // Print the current date and time in a formal style
    strftime(buffer, sizeof(buffer), "%A", tm_info);  // Weekday name
    printf("Day of the Week: %s\n", buffer);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);  // Date
    printf("Current Date: %s\n", buffer);

    strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);  // Time
    printf("Current Time: %s\n", buffer);

    printf("====================================================\n");
}

//                                                                          Function to show previously submitted customer feedback
void showCustomerFeedback() {
    system("cls"); // Clear the screen

    FILE *file;           // File pointer for reading feedback
    char line[512];       // Buffer to hold each line from the file

    // Open feedback file in read mode
    file = fopen("feedback.txt", "r");

    // Check if file opening failed
    if (file == NULL) {
        printf("No feedback available or error opening file!\n");
        printf("\n\t\tPress Enter to return to the main menu...");
        getchar(); // Consume leftover newline
        getchar(); // Wait for Enter key
        return;
    }

    // Print feedback section header
    printf("\n============================================\n");
    printf("         All Customer Feedbacks            \n");
    printf("============================================\n");

    int feedbackFound = 0; // Flag to check if feedback exists

    // Read each line from the file and display it
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Print the line
        feedbackFound = 1;  // Feedback was found
    }

    fclose(file); // Close the file after reading

    // If no feedback was found, display a message
    if (!feedbackFound) {
        printf("No feedback has been submitted yet.\n");
    }

    // Footer and return prompt
    printf("============================================\n");
    printf("\n\t\tPress Enter to return to the main menu...");
    getchar(); // Consume leftover newline
    getchar(); // Wait for user input
}

//                                                 user have many option to choose
// This function displays the "Others" menu where the user can choose additional features 
// such as viewing a calendar, team members, giving feedback, viewing feedback, or checking the current time.

void Others() {
    system("cls");
    int com;
    // Displaying the "Others" menu options to the user
    printf("What's on your mind to do?\n\n");
    printf("\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n\t\t\t| (1) Calender                 |");
    printf("\n\t\t\t| (2) Team Member              |");
    printf("\n\t\t\t| (3) Customer Feedback        |");
    printf("\n\t\t\t| (4) Show Previous Feedback   |");
    printf("\n\t\t\t| (5) Time                     |");  // Fixed the duplicate (4) to (5)
    printf("\n\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n");

    // Asking the user to select an option
    printf("Please, Select !!\n");
    printf("Enter : ");
    scanf("%d", &com);  // Reading user input

    // Option 1: Show calendar for a given year
    if (com == 1) {
        int year = calender();  // Call calendar function and store returned year

        // Display confirmation message
        printf("\n\n");
        printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\t\t\t   Correctly generates the calendar for the year %d  \n", year);
        printf("\n\t\t\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        // Prompt user to return to the main menu
        printf("\n\t\t\tPress Enter to return to the main menu...");
        getchar(); // Consume leftover newline character
        getchar(); // Wait for user to press Enter
    }
    // Option 2: Show credits (team members)
    else if (com == 2) {
        Credits();  // Display team member information
    }
    // Option 3: Collect customer feedback
    else if (com == 3) {
        customer_feedback();  // Collect and save customer feedback
    }
    // Option 4: Show previously collected customer feedback
    else if (com == 4) {
        showCustomerFeedback();  // Display stored feedback
    }
    // Option 5: Show current date and time
    else if (com == 5) {
        showCurrentDateTime();  // Display system date and time
    }
    // Invalid option
    else {
        printf("-------------Invalid Try Once more!!!!----------------\n");
    }
}


//                                                       DecorativeLIne Function
void printDecorativeLine() {
    printf("\n=============================================================\n");
}

//                                                            Main Function
int main() {
    int choice;

    // Seed the random number generator
    srand(time(NULL));

    loadBooksFromFile();

    // showMotivationalQuote();
    // Greet the user when the program starts
    greetUser();
    
    showMotivationalQuote();

    do{
//                                                                 Main Menu
        printDecorativeLine();
        printf("\t~~~~~~Online Book Shop Menu~~~~~~");
        printDecorativeLine();

        printf("\n\t1. Add Book\n");
        printf("\t2. Display Books\n");
        printf("\t3. Search Book\n");
        printf("\t4. Buy Book\n");
        printf("\t5. Delete Book\n");
        printf("\t6. Update Book Info\n");
        printf("\t7. Register New User\n");
        printf("\t8. Login as User\n");
        printf("\t9. Suggest Books\n");
        printf("\t10. Others & Customer's Feedback\n");
        printf("\t11. Exit\n");

        printDecorativeLine();
        
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);

        printf("\n");

        switch (choice)
        {
            case 1: 
                printf("\tAdding a new book...\n");
                addBook(); 
                break;
                    
            case 2: 
                printf("\tDisplaying books...\n");
                displayBooks();
                break;
                    
            case 3: 
                printf("\tSearching for a book...\n");
                searchBook(); 
                break;
                    
            case 4: 
                printf("\tProceeding with book purchase...\n");
                buyBook(); 
                break;
                    
            case 5: 
                printf("\tDeleting a book...\n");
                deleteBook();
                break;
            
            case 6: 
                printf("\tUpdating book information...\n");
                updateBook(); 
                break;
                
            case 7: 
                printf("\tRegistering a new user...\n");
                addUser(); 
                break;
                    
            case 8: 
                printf("\tLogging in as a user...\n");
                loginUser(); 
                break;
                    
            case 9: 
                printf("\tSuggesting books...\n");
                Suggest_Book();
                break;

            case 10: 
                printf("\tHandling other tasks...\n");
                Others();
                break;

            case 11: 
                printf("\tExiting the system...\n");  
                goodbyeMessage();
                break;

            default: 
                printf("\tInvalid choice. Please try again.\n");
        }

        printDecorativeLine();
        
    } while (choice != 11);

    return 0;
}