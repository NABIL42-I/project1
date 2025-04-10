#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Function to show a random motivational quote
void showMotivationalQuote() {

    const char* quotes[] = {

        " A room without books is like a body without a soul. -> Marcus Tullius Cicero\n",
        " There is no friend as loyal as a book. -> Ernest Hemingway\n",
        " Books are a uniquely portable magic. -> Stephen King\n",
        " Reading is to the mind what exercise is to the body.  -> Joseph Addison\n",
        " A book is a dream that you hold in your hand. -> Neil Gaiman\n"

    };

    int randomIndex = rand() % 5;
    printf("✨ %s\n", quotes[randomIndex]);

}

// Function to greet the user based on time of day
void greetUser() {
    time_t t;
    struct tm *tm_info;
    char timeStr[5];

    time(&t);
    tm_info = localtime(&t);
    strftime(timeStr, sizeof(timeStr), "%H", tm_info); // Get the current hour

    int hour = atoi(timeStr);

    // Display greeting based on the time of day
    if (hour >= 5 && hour < 12) {
        printf("   Good Morning! Welcome to the Online Book Shop.\n");
    } else if (hour >= 12 && hour < 17) {
        printf("   Good Afternoon! Welcome to the Online Book Shop.\n");
    } else if (hour >= 17 && hour < 21) {
        printf("   Good Evening! Welcome to the Online Book Shop.\n");
    } else {
        printf("   Good Night! Welcome to the Online Book Shop.\n");
    }
}

// Function to add a book
void addBook() {
     
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full!\n");
        return;
    }

    Book newBook;
    newBook.id = nextBookId++;

    printf("Enter book title: ");
    getchar(); // To consume leftover newline
    fgets(newBook.title, MAX_TITLE_LENGTH, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;  // Remove newline

    printf("Enter book author: ");
    fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;

    printf("Enter book price: ");
    scanf("%f", &newBook.price);

    printf("Enter book quantity: ");
    scanf("%d", &newBook.quantity);

    books[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

// Function to display all books
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Price: $%.2f, Quantity: %d\n",
            books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
    }
}

// Function to search for a book by title
void searchBook() {
    char title[MAX_TITLE_LENGTH];
    printf("Enter book title to search: ");
    getchar(); // To consume leftover newline
    fgets(title, MAX_TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0;  // Remove newline

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Book found! ID: %d, Title: %s, Author: %s, Price: $%.2f, Quantity: %d\n",
                books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to buy a book by ID
void buyBook() {
    int id, qty;
    printf("Enter book ID to buy: ");
    scanf("%d", &id);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            if (books[i].quantity >= qty) {
                books[i].quantity -= qty;
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

// Function to delete a book by ID
void deleteBook() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book ID not found.\n");
}

// Function to update book information
void updateBook() {
    int id;
    printf("Enter book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Enter new book title: ");
            getchar(); 
            // To consume leftover newline

            fgets(books[i].title, MAX_TITLE_LENGTH, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;

            printf("Enter new book author: ");

            fgets(books[i].author, MAX_AUTHOR_LENGTH, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;

            printf("Enter new book price: ");
            scanf("%f", &books[i].price);

            printf("Enter new book quantity: ");
            scanf("%d", &books[i].quantity);

            printf("Book updated successfully!\n");

            return;
        }
    }

    printf("Book ID not found.\n");
}

// Function to register a new user

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("User storage is full!\n");
        return;
    }

    User newUser;
    newUser.id = nextUserId++;

    printf("Enter user name: ");
    getchar(); 
    // To consume leftover newline
    fgets(newUser.name, MAX_NAME_LENGTH, stdin);

    newUser.name[strcspn(newUser.name, "\n")] = 0;  
    // Remove newline

    printf("Enter user email: ");
    fgets(newUser.email, MAX_EMAIL_LENGTH, stdin);

    newUser.email[strcspn(newUser.email, "\n")] = 0;
   // now user will enter phone number

    printf("Enter user phone: ");
    fgets(newUser.phone, MAX_PHONE_LENGTH, stdin);

    newUser.phone[strcspn(newUser.phone, "\n")] = 0;

    printf("Enter password: ");
    // now user will enter password
    fgets(newUser.password, MAX_PASSWORD_LENGTH, stdin);

    newUser.password[strcspn(newUser.password, "\n")] = 0;  // Remove newline

    // count the total user 
    // add new user in usercount;
    users[userCount++] = newUser;
    printf("User registered successfully!\n");
}

void welcome() 
{
    system("cls"); // For Windows; use "clear" if on Linux

    printf("\n\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t|         Welcome To           |\n");
    printf("\t\t\t|     Online Book Shop!        |\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\n\t\tPress Enter to continue...");

    getchar(); // Wait for user to press Enter
}

// Function to login a user
// Only valid user are allow!!!!!!!!!!!!!!!

void loginUser() {
   
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter email: ");

    getchar(); // To consume leftover newline
    fgets(email, MAX_EMAIL_LENGTH, stdin);

    email[strcspn(email, "\n")] = 0;  // Remove newline

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;  // Remove newline
   
          int r = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            // printf("Login successful! Welcome, %s!\n", users[i].name);
            // greetUser(); // Display greeting after login
                r=1;
            // showMotivationalQuote();

            // Display motivational quote after login
            // return;
        }
    }

    if(r){ 
    welcome(); 
    // printf("Login successful! Welcome, %s!\n", users[i].name);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful! Welcome, %s!\n", users[i].name);
            // greetUser(); // Display greeting after login
                // r=1;
            // showMotivationalQuote()
            // Display motivational quote after login
            // return;
        }
    }
    return ;
    }

    // if user enter wrong password................
    printf("Login failed. Incorrect email or password.\n");
}

//        books categoryMenu function
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

void showNonFictionBooks() {
    system("cls");

    printf("\n\n\t\t\t     NON-FICTION CATEGORY BOOK LIST\n");
    printf("\t\t========================================================\n\n");

    printf("\t\t  - The Diary of a Young Girl\t\t\t★★★★★\n");
    printf("\t\t  - The Power of Habit\t\t\t\t★★★★☆\n");
    printf("\t\t  - Thinking, Fast and Slow\t\t\t★★★★★\n");
    printf("\t\t  - Meditations\t\t\t\t\t★★★★☆\n");
    printf("\t\t  - The Body Keeps the Score\t\t\t★★★★★\n");
    printf("\t\t  - In Cold Blood\t\t\t\t★★★★☆\n");
    printf("\t\t  - Into the Wild\t\t\t\t★★★★☆\n");
    printf("\t\t  - SALT, FAT, ACID, HEAT\t\t\t★★★★☆\n");
    printf("\t\t  - The Lean Startup\t\t\t\t★★★★☆\n");
    printf("\t\t  - Sapiens: A Brief History of Humankind\t★★★★★\n");
    printf("\t\t  - The Audacity of Hope\t\t\t★★★★☆\n");

    printf("\n\t\t========================================================\n");
    printf("\t\t     Find the truth, learn the stories, live the lessons\n");

    printf("\n\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume leftover newline
    getchar(); // wait for user to press Enter
}

// #include <stdio.h>
// #include <stdlib.h>

void showNonFictionBooks1() {
    system("cls");

    printf("\n\n\t\t\t📘🌍 Explore Non-Fiction Realms 🌍📘\n");
    printf("\t\t------------------------------------------------------\n\n");

    printf("\t\t  🔹 The Diary of a Young Girl\t\t⭐️⭐️⭐️⭐️⭐️\n");
    printf("\t\t  🔹 The Power of Habit\t\t\t⭐️⭐️⭐️⭐️☆\n");
    printf("\t\t  🔹 Thinking, Fast and Slow\t\t⭐️⭐️⭐️⭐️⭐️\n");
    printf("\t\t  🔹 Meditations\t\t\t⭐️⭐️⭐️⭐️☆\n");
    printf("\t\t  🔹 The Body Keeps the Score\t\t⭐️⭐️⭐️⭐️⭐️\n");
    printf("\t\t  🔹 In Cold Blood\t\t\t⭐️⭐️⭐️⭐️☆\n");
    printf("\t\t  🔹 Into the Wild\t\t\t⭐️⭐️⭐️⭐️☆\n");
    printf("\t\t  🔹 SALT, FAT, ACID, HEAT\t\t⭐️⭐️⭐️⭐️☆\n");
    printf("\t\t  🔹 The Lean Startup\t\t\t⭐️⭐️⭐️⭐️☆\n");
    printf("\t\t  🔹 Sapiens: A Brief History...\t\t⭐️⭐️⭐️⭐️⭐️\n");
    printf("\t\t  🔹 The Audacity of Hope\t\t⭐️⭐️⭐️⭐️☆\n");

    printf("\n\t\t------------------------------------------------------\n");
    printf("\t\t   💡 Discover wisdom from the minds of legends 💡\n");

    printf("\n\n\t\t\tPress Enter to return to the main menu...");
    getchar(); // consume newline if needed
    getchar(); // wait for user input
}



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


void showNonfictionStorytelling() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Nonfiction Storytelling books
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


void showHistoricalFantasyBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Historical Fantasy books
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

void showHumorBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Humor books
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


void showPhilosophicalFiction() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Philosophical Fiction books
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

void showDystopianScienceFiction() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Dystopian Science Fiction books
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


void showEpistolaryNovels() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Epistolary Novels
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

void showCyberpunkBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Cyberpunk books
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

void showMagicalRealismBooks() {
    // Clear screen using 'cls' for Windows
    system("cls");

    // Display the list of Magical Realism books
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

// Main menu
int main() {
    
    int choice;

    // Seed the random number generator
    srand(time(NULL));

    // Greet the user when the program starts
    greetUser();
    
    showMotivationalQuote();
    do
    {
        printf("\n--- Online Book Shop Menu ---\n");
        
        printf("1. Add Book\n");

        printf("2. Display Books\n");
        printf("3. Search Book\n");

        printf("4. Buy Book\n");

        printf("5. Delete Book\n");
        printf("6. Update Book Info\n");
        printf("7. Register New User\n");

        printf("8. Login as User\n");
        printf("9. Suggest Books\n");

        printf("10.Others\n");
        // printf("Enter your choice: ");
        // scanf("%d", &choice);
        printf("11.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            
            case 1: addBook(); 
                    break;
                    
            case 2: displayBooks();
                    break;
                    
            case 3: searchBook(); 
                    break;
                    
            case 4: buyBook(); 
                    break;
                    
            case 5: deleteBook();
                   break;
                   
            case 6: updateBook(); 
                break;
                
            case 7: addUser(); 
                    break;
                    
            case 8: loginUser(); 
                    break;
                    
            case 9: Suggest_Book();
                    break;
             case 10: printf("Others\n");
                    break;
           //  user can exit from this system          
            case 11: 
            printf("Exiting...\n");  
            // Goodbye massage to user for using our system
               goodbyeMessage();
               printf("Exiting...\n");  
                break;
                // return;
          
            // user dial wrong input!!!  
            default: 
             printf("Invalid choice.\n");
        }

    } 
    while (choice != 11);
    
     return 0;
}

