/*
 * ============================================
 *   MUSIC PLAYLIST MANAGER - Terminal UI
 *   DSA Project - Linked Lists Application
 *   Language: C++
 * ============================================
 *
 * Features:
 *  - Colored terminal output (ANSI codes)
 *  - Doubly Linked List for playlist
 *  - Animated loading bar
 *  - Clean bordered menus
 *  - Windows terminal compatible (no emojis)
 */

#include <iostream>
#include <string>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BRED        "\033[91m"
#define BGREEN      "\033[92m"
#define BYELLOW     "\033[93m"
#define BBLUE       "\033[94m"
#define BMAGENTA    "\033[95m"
#define BCYAN       "\033[96m"
#define BWHITE      "\033[97m"
#define BG_BLACK    "\033[40m"
#define BG_GREEN    "\033[42m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"

void waitMs(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ─────────────────────────────────────────
//  NODE STRUCTURE
// ─────────────────────────────────────────
struct Node {
    string title;
    string artist;
    Node* prev;
    Node* next;

    Node(string t, string a) {
        title = t;
        artist = a;
        prev = NULL;
        next = NULL;
    }
};

// ─────────────────────────────────────────
//  PLAYLIST CLASS
// ─────────────────────────────────────────
class Playlist {
private:
    Node* head;
    Node* tail;
    Node* current;
    int   size;

public:
    Playlist() { head = NULL; tail = NULL; current = NULL; size = 0; }

    void addSong(string title, string artist) {
        Node* newNode = new Node(title, artist);
        if (head == NULL) {
            head = tail = current = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    bool removeSong(string title) {
        if (!head) return false;
        Node* temp = head;
        while (temp && temp->title != title) temp = temp->next;
        if (!temp) return false;

        if (temp == current) {
            if (current->next)      current = current->next;
            else if (current->prev) current = current->prev;
            else                    current = NULL;
        }
        if (temp->prev) temp->prev->next = temp->next;
        else            head = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        else            tail = temp->prev;

        delete temp;
        size--;
        return true;
    }

    bool playNext() {
        if (!current || !current->next) return false;
        current = current->next;
        return true;
    }

    bool playPrev() {
        if (!current || !current->prev) return false;
        current = current->prev;
        return true;
    }

    bool playSong(string title) {
        Node* temp = head;
        while (temp) {
            if (temp->title == title) { current = temp; return true; }
            temp = temp->next;
        }
        return false;
    }

    int searchSong(string title) {
        Node* temp = head;
        int pos = 1;
        while (temp) {
            if (temp->title == title) return pos;
            temp = temp->next;
            pos++;
        }
        return -1;
    }

    Node* getHead() { return head; }
    Node* getCurrent() { return current; }
    int   getSize() { return size; }

    ~Playlist() {
        Node* temp = head;
        while (temp) { Node* n = temp->next; delete temp; temp = n; }
    }
};

// ─────────────────────────────────────────
//  UI FUNCTIONS
// ─────────────────────────────────────────
void printLine(int width, string color = WHITE) {
    cout << color;
    for (int i = 0; i < width; i++) cout << "-";
    cout << RESET << "\n";
}

void printCentered(string text, int width, string color = WHITE) {
    int p = (width - (int)text.length()) / 2;
    if (p < 0) p = 0;
    cout << color << string(p, ' ') << text << RESET << "\n";
}

void animateLoading(string msg) {
    string frames[] = { "[=       ]","[==      ]","[===     ]","[====    ]",
                       "[=====   ]","[======  ]","[======= ]","[========]" };
    for (int i = 0; i < 8; i++) {
        cout << "\r  " << CYAN << msg << " " << BGREEN << frames[i] << RESET << flush;
        waitMs(80);
    }
    cout << "\r  " << CYAN << msg << " " << BGREEN << "[========] Done!" << RESET << "\n";
    waitMs(300);
}

void showNowPlaying(Node* current) {
    if (!current) {
        cout << "\n  " << YELLOW << ">>  No song is currently playing.\n" << RESET;
        return;
    }
    cout << "\n";
    cout << "  " << BG_MAGENTA << BWHITE << BOLD << "  >>  NOW PLAYING                         " << RESET << "\n";
    cout << "  " << MAGENTA << "+------------------------------------------+" << RESET << "\n";
    cout << "  " << MAGENTA << "| " << RESET;
    cout << BWHITE << BOLD << " [*] " << left << setw(36) << current->title.substr(0, 36) << RESET;
    cout << MAGENTA << "|" << RESET << "\n";
    cout << "  " << MAGENTA << "| " << RESET;
    cout << CYAN << "     " << left << setw(36) << current->artist.substr(0, 36) << RESET;
    cout << MAGENTA << "|" << RESET << "\n";
    cout << "  " << MAGENTA << "| " << RESET;
    cout << "  " << BGREEN << "[====================]" << RESET;
    cout << YELLOW << "  1:24 / 3:47   " << RESET;
    cout << MAGENTA << " |" << RESET << "\n";
    cout << "  " << MAGENTA << "|" << RESET;
    cout << "        " << BWHITE << " |<<    " << BGREEN << ">>    " << RESET << BWHITE << ">>|" << RESET;
    cout << "                 ";
    cout << MAGENTA << "|" << RESET << "\n";
    cout << "  " << MAGENTA << "+------------------------------------------+" << RESET << "\n";
}

void showPlaylist(Playlist& pl) {
    clearScreen();
    cout << "\n";
    cout << "  " << BG_BLUE << BWHITE << BOLD << "  >>  YOUR PLAYLIST                       " << RESET << "\n";
    printLine(46, BLUE);

    Node* temp = pl.getHead();
    int   num = 1;

    if (!temp) {
        cout << "\n  " << YELLOW << "  Playlist is empty! Add some songs.\n" << RESET;
    }

    while (temp) {
        if (temp == pl.getCurrent()) {
            cout << "  " << BG_GREEN << BWHITE << BOLD;
            cout << "  " << num << ". >> "
                << left << setw(22) << temp->title.substr(0, 22)
                << setw(14) << temp->artist.substr(0, 14)
                << RESET << "\n";
        }
        else {
            cout << "  " << CYAN << num << ". " << RESET;
            cout << BWHITE << left << setw(24) << temp->title.substr(0, 24) << RESET;
            cout << YELLOW << left << setw(16) << temp->artist.substr(0, 16) << RESET << "\n";
        }
        temp = temp->next;
        num++;
    }

    printLine(46, BLUE);
    cout << "  " << BBLUE << "Total: " << BWHITE << pl.getSize() << " songs" << RESET << "\n";
}

void showMenu() {
    cout << "\n";
    cout << "  " << BG_BLACK << BMAGENTA << BOLD << "  +====================================+   " << RESET << "\n";
    cout << "  " << BG_BLACK << BMAGENTA << BOLD << "  |      -- PLAYLIST MANAGER --        |   " << RESET << "\n";
    cout << "  " << BG_BLACK << BMAGENTA << BOLD << "  +====================================+   " << RESET << "\n";

    string opts[][2] = {
        {"1","Add Song"},
        {"2","Remove Song"},
        {"3","Play Next  >>"},
        {"4","Play Previous  <<"},
        {"5","Show Current Song"},
        {"6","Display Full Playlist"},
        {"7","Search Song"},
        {"8","Play Specific Song"},
        {"0","Exit"}
    };

    for (auto& o : opts) {
        cout << "  " << BG_BLACK << MAGENTA << "  |  " << RESET;
        cout << BG_BLACK << BGREEN << " " << o[0] << ". " << RESET;
        cout << BG_BLACK << BWHITE << left << setw(30) << o[1] << RESET;
        cout << BG_BLACK << MAGENTA << "|   " << RESET << "\n";
    }

    cout << "  " << BG_BLACK << BMAGENTA << BOLD << "  +====================================+   " << RESET << "\n";
    cout << "\n  " << BGREEN << "Enter choice ->  " << RESET;
}

void msgSuccess(string msg) {
    cout << "\n  " << BGREEN << "[OK]  " << msg << RESET << "\n";
    waitMs(700);
}

void msgError(string msg) {
    cout << "\n  " << BRED << "[X]   " << msg << RESET << "\n";
    waitMs(700);
}

void splashScreen() {
    clearScreen();
    cout << "\n\n";
    cout << BMAGENTA << BOLD;
    cout << "        ##    ##  ##   ##  #####  ####  ####\n";
    cout << "        ###  ###  ##   ##  ##     ##  ##  ##\n";
    cout << "        ## ## ##  ##   ##  #####  ####    ##\n";
    cout << "        ##    ##  ##   ##     ##  ##  ##  ##\n";
    cout << "        ##    ##   #####   #####  ##  ## ####\n";
    cout << RESET << "\n";
    printCentered("P L A Y L I S T   M A N A G E R", 56, BCYAN);
    printCentered("DSA Project  |  Doubly Linked List", 56, YELLOW);
    cout << "\n";
    animateLoading("  Loading");
    waitMs(400);
}

// ─────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────
int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    splashScreen();

    Playlist pl;
    pl.addSong("Blinding Lights", "The Weeknd");
    pl.addSong("Shape of You", "Ed Sheeran");
    pl.addSong("Stay", "Justin Bieber");
    pl.addSong("Levitating", "Dua Lipa");
    pl.addSong("As It Was", "Harry Styles");

    int    choice;
    string title, artist;

    do {
        clearScreen();
        showNowPlaying(pl.getCurrent());
        showMenu();

        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1:
            clearScreen();
            cout << "\n  " << BCYAN << BOLD << "  ADD NEW SONG\n" << RESET;
            printLine(40, CYAN);
            cout << "  " << BWHITE << "Song Title  : " << RESET;
            getline(cin, title);
            cout << "  " << BWHITE << "Artist Name : " << RESET;
            getline(cin, artist);
            pl.addSong(title, artist);
            animateLoading("  Adding to playlist");
            msgSuccess("\"" + title + "\" added!");
            break;

        case 2:
            clearScreen();
            showPlaylist(pl);
            cout << "\n  " << BYELLOW << "  REMOVE SONG\n" << RESET;
            cout << "  " << BWHITE << "Enter song title : " << RESET;
            getline(cin, title);
            if (pl.removeSong(title))
                msgSuccess("\"" + title + "\" removed.");
            else
                msgError("Song \"" + title + "\" not found!");
            break;

        case 3:
            if (pl.playNext()) {
                animateLoading("  Skipping");
                msgSuccess("Playing next song!");
            }
            else {
                msgError("You are at the LAST song!");
            }
            break;

        case 4:
            if (pl.playPrev()) {
                animateLoading("  Going back");
                msgSuccess("Playing previous song!");
            }
            else {
                msgError("You are at the FIRST song!");
            }
            break;

        case 5:
            clearScreen();
            showNowPlaying(pl.getCurrent());
            cout << "\n  Press Enter to continue...";
            cin.get();
            break;

        case 6:
            showPlaylist(pl);
            cout << "\n  Press Enter to continue...";
            cin.get();
            break;

        case 7:
            clearScreen();
            cout << "\n  " << BCYAN << "  SEARCH SONG\n" << RESET;
            printLine(40, CYAN);
            cout << "  " << BWHITE << "Enter song title : " << RESET;
            getline(cin, title);
            {
                int pos = pl.searchSong(title);
                if (pos != -1)
                    msgSuccess("Found \"" + title + "\" at position " + to_string(pos));
                else
                    msgError("\"" + title + "\" not found in playlist.");
            }
            break;

        case 8:
            clearScreen();
            showPlaylist(pl);
            cout << "\n  " << BCYAN << "  PLAY SONG\n" << RESET;
            cout << "  " << BWHITE << "Enter song title : " << RESET;
            getline(cin, title);
            if (pl.playSong(title)) {
                animateLoading("  Loading song");
                msgSuccess("Now playing: \"" + title + "\"");
            }
            else {
                msgError("Song \"" + title + "\" not found!");
            }
            break;

        case 0:
            clearScreen();
            cout << "\n\n";
            printCentered("Thanks for using Playlist Manager!", 56, BMAGENTA);
            printCentered("Goodbye! Keep listening to music!", 56, BCYAN);
            cout << "\n\n";
            break;

        default:
            msgError("Invalid choice! Please enter 0-8.");
        }

    } while (choice != 0);

    return 0;
}