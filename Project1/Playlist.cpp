/*
 * Authored by Ngoc Viet Nguyen - U14177860
 * Implements Playlist operations: file I/O, playback navigation, song management, shuffle, repeat, and history.
 */

#include "Playlist.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

Playlist::Playlist(const string& name)
    : name(name), mode(RepeatMode::All) {}

bool Playlist::loadFromFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        Song song;
        if (Song::fromFileLine(line, song)) {
            addSong(song);
        } else {
            cout << "Warning: skipped malformed line: " << line << endl;
        }
    }
    return true;
}

bool Playlist::saveToFile(const string& path) const {
    ofstream file(path);
    if (!file.is_open()) return false;

    file << "# title | artist | length in seconds\n";
    vector<Song> all = songs.toVector();
    for (size_t i = 0; i < all.size(); i++) {
        file << all[i].toFileLine() << "\n";
    }
    return true;
}

// Repeat-one skips the advance entirely.
void Playlist::next() {
    if (songs.isEmpty()) return;

    if (mode != RepeatMode::One) {
        songs.advance(1);
    }
    recordPlayed(songs.current());
}

void Playlist::previous() {
    if (songs.isEmpty()) return;

    songs.advance(-1);
    recordPlayed(songs.current());
}

void Playlist::jumpTo(int trackNumber) {
    if (songs.isEmpty()) return;

    int index = trackNumber - 1;
    if (index < 0 || index >= songs.size()) return;

    songs.jumpTo(index);
    recordPlayed(songs.current());
}

void Playlist::addSong(const Song& song) {
    songs.add(song);
}

void Playlist::queueSong(const Song& song) {
    songs.insertAfterCurrent(song);
}

void Playlist::removeCurrent() {
    songs.removeCurrent();
}

// Manual shuffle using rand()
void Playlist::shuffle(unsigned seed) {
    vector<Song> values = songs.toVector();
    srand(seed);

    for (int i = static_cast<int>(values.size()) - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Song temp = values[i];
        values[i] = values[j];
        values[j] = temp;
    }

    songs.reorder(values);
}

void Playlist::toggleRepeat() {
    mode = (mode == RepeatMode::All) ? RepeatMode::One : RepeatMode::All;
}

int Playlist::nowPlayingNumber() const {
    return songs.currentIndex() + 1;
}

vector<Song> Playlist::allSongs() const {
    return songs.toVector();
}

int Playlist::totalSeconds() const {
    int total = 0;
    vector<Song> all = songs.toVector();
    for (size_t i = 0; i < all.size(); i++) {
        total += all[i].getSeconds();
    }
    return total;
}

RepeatMode Playlist::getMode() const {
    return mode;
}

const vector<string>& Playlist::recentlyPlayed() const {
    return recentCache;
}

// Fixed-size ring buffer: once full, oldest title is overwritten in place
void Playlist::recordPlayed(const Song& song) {
    if (history.size() < 5) {
        history.add(song.getTitle());
    } else {
        history.advance(1);
        history.current() = song.getTitle();
    }
    recentCache = history.toVector();
}