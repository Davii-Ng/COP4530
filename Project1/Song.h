#ifndef SONG_H
#define SONG_H

#include <string>

using namespace std;

class Song {
public:
    Song();
    Song(const string& title, const string& artist, int seconds);

    const string& getTitle()  const;
    const string& getArtist() const;
    int           getSeconds() const;

    string formattedLength() const;   // 241 -> "4:01"
    string toFileLine()      const;   // "Title | Artist | 241"

    // Parses one line of playlist.txt. Returns false if the line is malformed.
    static bool fromFileLine(const string& line, Song& out);

private:
    string title;
    string artist;
    int    seconds;
};

#endif