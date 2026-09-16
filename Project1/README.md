# Music Carousel

A console-based music playlist manager built on a custom circular doubly linked list.

## Features

- Load/Save playlist
- Next/Previous track
- Add/Remove song
- Display playlist with track numbers, durations, and a now-playing marker
- Jump to a track by number
- Queue song to play next
- Shuffle 
- Repeat modes: all/one
- Recently-played history (last 5 tracks)
- Total playlist duration (mm:ss)

## File Structure

```
.
├── circular-linked-list.h    # template for main feature
├── Song.h / Song.cpp         # song data: title, artist, duration
├── Playlist.h / Playlist.cpp # the ring, cursor, repeat modes, history
├── main.cpp                  # menu, display, input handling
└── playlist.txt              # sample playlist
```

## Build & Run

Requires a C++17 compiler.

```
g++ -std=c++17 -Wall -Wextra main.cpp Song.cpp Playlist.cpp -o player
./player
```

`playlist.txt` must be in the same directory as the `.exe` file.

## Controls

| Key | Action |
|-----|--------|
| n   | next track |
| p   | previous track |
| g   | go to track number |
| r   | toggle repeat mode |
| a   | add song to end |
| q   | queue song to play next |
| x   | remove current song |
| s   | shuffle |
| w   | save playlist to file |
| e   | exit |

## Design Notes

- **Circular playlist**: the playlist doesn't stop when it reaches the end, instead, it loops back to the start.
- **Doubly linked**: going to the previous song is just as fast as going to the next one, no matter how long the playlist is, as the complexity is only O(1).
- **Two pointers**: the playlist keeps track of both its display order and what's currently playing separately, so the list itself never appears to shuffle around as you play.
- **Reusable structure**: the same underlying design is used both for the playlist and for keeping a short history of recently played songs.

## Group Members

- Minh Duong Nguyen
- Ngoc Viet Nguyen
