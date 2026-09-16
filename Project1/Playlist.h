#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "CircularList.h"
#include "Song.h"

enum class RepeatMode { All, One };

class Playlist {
public:
    Playlist(const std::string& name);

    bool loadFromFile(const std::string& path);
    bool saveToFile(const std::string& path) const;

    void next();
    void previous();
    void jumpTo(int trackNumber);          // 1-based, as shown on screen

    void addSong(const Song& song);        // to the end
    void queueSong(const Song& song);      // to play immediately next
    void removeCurrent();

    void shuffle(unsigned seed);
    void toggleRepeat();

    const Song& nowPlaying() const;
    int         nowPlayingNumber() const;  // 1-based
    std::vector<Song> allSongs() const;
    int         totalSeconds() const;
    RepeatMode  getMode() const;
    const std::vector<std::string>& recentlyPlayed() const;

private:
    std::string          name;
    CircularList<Song>   songs;
    CircularList<std::string> history;   // fixed-size ring buffer, last 5 titles
    RepeatMode           mode;

    void recordPlayed(const Song& song);
};

#endif