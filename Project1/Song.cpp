/*
 * Authored by Ngoc Viet Nguyen - U14177860
 * Implements Song construction, formatting, and playlist-file parsing.
 */

#include "Song.h"
using namespace std;

Song::Song() : title(""), artist(""), seconds(0) {}

Song::Song(const string& title, const string& artist, int seconds)
    : title(title), artist(artist), seconds(seconds) {}

const string& Song::getTitle() const { return title; }
const string& Song::getArtist() const { return artist; }
int Song::getSeconds() const { return seconds; }

// Converts seconds into "m:ss", padding seconds with a leading zero.
string Song::formattedLength() const {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    string secsStr = to_string(secs);
    if (secs < 10) secsStr = "0" + secsStr;
    return to_string(minutes) + ":" + secsStr;
}

string Song::toFileLine() const {
    return title + " | " + artist + " | " + to_string(seconds);
}

// Strips leading/trailing spaces.
static string trim(const string& s) {
    size_t start = s.find_first_not_of(' ');
    size_t end = s.find_last_not_of(' ');
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Expects "Title | Artist | Seconds". Fails on missing fields or non-numeric length.
bool Song::fromFileLine(const string& line, Song& out) {
    size_t firstPipe = line.find('|');
    if (firstPipe == string::npos) return false;

    size_t secondPipe = line.find('|', firstPipe + 1);
    if (secondPipe == string::npos) return false;

    string titlePart = trim(line.substr(0, firstPipe));
    string artistPart = trim(line.substr(firstPipe + 1, secondPipe - firstPipe - 1));
    string secondsPart = trim(line.substr(secondPipe + 1));

    if (titlePart.empty() || artistPart.empty() || secondsPart.empty()) return false;

    // Manual digit check, no <cctype> needed.
    for (size_t i = 0; i < secondsPart.size(); i++) {
        if (secondsPart[i] < '0' || secondsPart[i] > '9') return false;
    }

    int secondsValue = stoi(secondsPart);
    out = Song(titlePart, artistPart, secondsValue);
    return true;
}