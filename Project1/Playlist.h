#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "circular-linked-list.h"
#include "Song.h"

using namespace std;

enum class RepeatMode { All, One };

class Playlist {
public:
    Playlist(const string& name);

    bool loadFromFile(const string& path);
    bool saveToFile(const string& path) const;

    void next();
    void previous();
    void jumpTo(int trackNumber);

    void addSong(const Song& song);
    void queueSong(const Song& song);
    void removeCurrent();

    void shuffle(unsigned seed);
    void toggleRepeat();

    const Song& nowPlaying() const;
    int         nowPlayingNumber() const;
    vector<Song> allSongs() const;
    int         totalSeconds() const;
    RepeatMode  getMode() const;
    const vector<string>& recentlyPlayed() const;

private:
    string          name;
    CircularList<Song>   songs;
    CircularList<string> history;
    RepeatMode           mode;
    vector<string>       recentCache;

    void recordPlayed(const Song& song);
};

#endif