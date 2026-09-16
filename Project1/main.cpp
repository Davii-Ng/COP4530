/*
 * Authored by Ngoc Viet Nguyen - U14177860
 * Runs the console music player interface and handles user input.
 */

#include <iostream>
#include <ctime>
#include "Playlist.h"
using namespace std;

// Pads a string with spaces on the right to reach a fixed width.
string padRight(const string& s, int width) {
    string result = s;
    while (static_cast<int>(result.size()) < width) result += ' ';
    return result;
}

void printMenu(const Playlist& playlist) {
    vector<Song> allSongs = playlist.allSongs();
    int totalSecs = playlist.totalSeconds();
    string secsStr = to_string(totalSecs % 60);
    if (totalSecs % 60 < 10) secsStr = "0" + secsStr;

    cout << "\n  MUSIC PLAYER -- \"Road Trip\", " << allSongs.size()
         << " tracks, " << totalSecs / 60 << ":" << secsStr
         << " total      repeat: "
         << (playlist.getMode() == RepeatMode::All ? "all" : "one") << "\n\n";

    int currentNum = allSongs.empty() ? -1 : playlist.nowPlayingNumber();

    for (size_t i = 0; i < allSongs.size(); i++) {
        bool isCurrent = (static_cast<int>(i) + 1 == currentNum);
        cout << (isCurrent ? "   >   " : "       ")
             << (i + 1) << "   "
             << padRight(allSongs[i].getTitle(), 22)
             << padRight(allSongs[i].getArtist(), 18)
             << allSongs[i].formattedLength()
             << (isCurrent ? "    now playing" : "") << "\n";
    }

    cout << "\n  recently played: ";
    const vector<string>& recent = playlist.recentlyPlayed();
    for (size_t i = 0; i < recent.size(); i++) {
        cout << recent[i];
        if (i + 1 < recent.size()) cout << ", ";
    }
    cout << "\n\n";

    cout << "  [n] next      [p] previous   [g] go to track   [r] repeat mode\n";
    cout << "  [a] add song  [q] queue next [x] remove current [s] shuffle\n";
    cout << "  [w] save      [e] exit\n\n";
}

int readInt(const string& prompt) {
    cout << prompt;
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  Invalid number, try again: ";
    }
    cin.ignore(1000, '\n');
    return value;
}

string readLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int main() {
    Playlist playlist("Road Trip");

    if (!playlist.loadFromFile("playlist.txt")) {
        cout << "Could not open playlist.txt, starting empty.\n";
    }

    char choice;
    bool running = true;

    while (running) {
        printMenu(playlist);
        cout << "  choice> ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
            case 'n':
                playlist.next();
                break;
            case 'p':
                playlist.previous();
                break;
            case 'g': {
                int track = readInt("  track number> ");
                playlist.jumpTo(track);
                break;
            }
            case 'r':
                playlist.toggleRepeat();
                break;
            case 'a': {
                string title = readLine("  title> ");
                string artist = readLine("  artist> ");
                int secs = readInt("  duration (seconds)> ");
                playlist.addSong(Song(title, artist, secs));
                break;
            }
            case 'q': {
                string title = readLine("  title> ");
                string artist = readLine("  artist> ");
                int secs = readInt("  duration (seconds)> ");
                playlist.queueSong(Song(title, artist, secs));
                break;
            }
            case 'x':
                playlist.removeCurrent();
                break;
            case 's':
                playlist.shuffle(static_cast<unsigned>(time(nullptr)));
                break;
            case 'w':
                cout << (playlist.saveToFile("playlist.txt") ? "  Saved.\n" : "  Save failed.\n");
                break;
            case 'e':
                running = false;
                break;
            default:
                cout << "  Unknown command.\n";
        }
    }

    return 0;
}