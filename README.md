# 🎵 Music Playlist Manager
> A terminal-based Music Playlist Manager built in C++ using a **Doubly Linked List** data structure.

---

## 📌 About the Project

This is a DSA (Data Structures and Algorithms) project that simulates a music playlist manager.
It demonstrates the practical application of **Doubly Linked Lists** through a colorful, interactive terminal UI.

---

## 🧠 Data Structure Used

**Doubly Linked List**

```
NULL <-- [Song1] <--> [Song2] <--> [Song3] --> NULL
```

Each node in the list stores:
- Song Title
- Artist Name
- Pointer to the **next** song
- Pointer to the **previous** song

---

## ✨ Features

| Feature | Description |
|---|---|
| Add Song | Insert a new song at the end of the playlist |
| Remove Song | Delete a song by title |
| Play Next | Move to the next song |
| Play Previous | Move to the previous song |
| Show Current Song | Display the currently playing song |
| Display Playlist | Show all songs with the current one highlighted |
| Search Song | Find a song and show its position |
| Play Specific Song | Jump directly to any song by title |

---

## 🎨 UI Features

- Colored terminal output using ANSI escape codes
- Animated loading bar
- Now Playing banner with progress bar
- Color-highlighted currently playing song
- Clean bordered menus
- Windows terminal compatible

---

## 🛠️ How to Compile & Run

### Using Visual Studio (Windows)
1. Open Visual Studio
2. Create a new **Console App (C++)** project
3. Paste the code into the main `.cpp` file
4. Press `Ctrl + F5` to build and run

### Using g++ (Linux / Mac)
```bash
g++ playlist_manager_ui.cpp -o playlist
./playlist
```

### Using Developer PowerShell (Visual Studio)
```bash
cl playlist_manager_ui.cpp /Fe:playlist.exe
playlist.exe
```

---

## 📁 Project Structure

```
Playlist-Manager/
│
├── playlist_manager.cpp        # Basic version (no UI)
├── playlist_manager_ui.cpp     # Full Terminal UI version
└── README.md                   # Project documentation
```

---

## 📊 Linked List Operations & Time Complexity

| Operation | Time Complexity |
|---|---|
| Add Song (at end) | O(1) |
| Remove Song | O(n) |
| Play Next / Previous | O(1) |
| Search Song | O(n) |
| Display Playlist | O(n) |

---

## 🖥️ Screenshots

### Main Menu
```
  +====================================+
  |      -- PLAYLIST MANAGER --        |
  +====================================+
  |   1. Add Song                      |
  |   2. Remove Song                   |
  |   3. Play Next  >>                 |
  |   4. Play Previous  <<             |
  |   5. Show Current Song             |
  |   6. Display Full Playlist         |
  |   7. Search Song                   |
  |   8. Play Specific Song            |
  |   0. Exit                          |
  +====================================+
```

### Now Playing
```
  >>  NOW PLAYING
  +------------------------------------------+
  | [*] Blinding Lights                       |
  |       The Weeknd                          |
  |   [====================]  1:24 / 3:47    |
  |           |<<    >>    >>|                |
  +------------------------------------------+
```

---

## 👩‍💻 Author

**Upeksha Wijerathe**
- GitHub: [@UpekshaWijerathe](https://github.com/UpekshaWijerathe)

---

## 📚 Course

Data Structures and Algorithms (DSA)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
