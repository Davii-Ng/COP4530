#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
public:
    Song();
    Song(const std::string& title, const std::string& artist, int seconds);

    const std::string& getTitle()  const;
    const std::string& getArtist() const;
    int                getSeconds() const;

    std::string formattedLength() const;   // 241 -> "4:01"
    std::string toFileLine()      const;   // "Title | Artist | 241"

    // Parses one line of playlist.txt. Returns false if the line is malformed.
    static bool fromFileLine(const std::string& line, Song& out);

private:
    std::string title;
    std::string artist;
    int         seconds;
};

#endif