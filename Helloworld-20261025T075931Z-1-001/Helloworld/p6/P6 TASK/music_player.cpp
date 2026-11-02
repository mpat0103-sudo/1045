#include "splashkit.h"
#include "utilities.h"
#include <vector>
using std::vector;

const int NO_SONG = -1;

enum main_menu_option
{
    ADD_SONG = 1,
    UPDATE_SONG = 2,
    PLAY_SONG = 3,
    PAUSE_RESUME = 4,
    PRINT_STATUS = 5,
    QUIT = 6
};

enum update_menu_option
{
    UPDATE_NAME = 1,
    UPDATE_LOVED = 2,
    RESET_PLAYS = 3,
    DELETE_SONG = 4,
    QUIT_UPDATE = 5
};

struct song_data
{
    string name;
    string id;
    string path;
    bool loved;
    int times_played;
};

struct music_player_data
{
    vector<song_data> songs;
    int next_id;
};

/**
 * Print the main menu options.
 */
void print_main_menu()
{
    write_line();
    write_line("Main Menu");
    write_line("1. Add a song");
    write_line("2. Update a song");
    write_line("3. Play a song");
    write_line("4. Pause / resume");
    write_line("5. Print status");
    write_line("6. Quit");
}

/**
 * Print the update menu options.
 */
void print_update_menu()
{
    write_line("Update Menu");
    write_line("1. Update name");
    write_line("2. Update loved");
    write_line("3. Reset times played");
    write_line("4. Delete");
    write_line("5. Quit update");
}

/**
 * Print the details of a song.
 *
 * @param song the song to print
 */
void print_song(const song_data &song)
{
    write_line("Name:         " + song.name);
    write_line("ID:           " + song.id);
    write_line("Path:         " + song.path);

    if (song.loved)
    {
        write_line("Loved:        Yes");
    }
    else
    {
        write_line("Loved:        No");
    }

    write_line("Times played: " + to_string(song.times_played));
}

/**
 * Read a new song from the user, give it a unique id, load it and add it to the player.
 *
 * @param player the music player to add the song to
 */
void add_song(music_player_data &player)
{
    song_data song;

    song.name = read_string("Enter song name: ");
    song.path = read_string("Enter song path: ");
    song.loved = read_boolean("Do you love this song? [y/n]: ");
    song.times_played = 0;

    song.id = "song-" + to_string(player.next_id);
    player.next_id++;

    load_music(song.id, song.path);

    player.songs.push_back(song);
    write_line("Added " + song.name + " as " + song.id);
}

/**
 * Search for songs by name and let the user pick one of the matches.
 *
 * @param player the music player to search
 * @returns the index of the chosen song, or NO_SONG if none was found
 */
int find_song(const music_player_data &player)
{
    int count = player.songs.size();

    if (count == 0)
    {
        write_line("There are no songs in the player.");
        return NO_SONG;
    }

    string search = to_lowercase(read_string("Enter search text: "));
    vector<int> matches;

    for (int i = 0; i < count; i++)
    {
        if (contains(to_lowercase(player.songs[i].name), search))
        {
            matches.push_back(i);
            int num = matches.size();
            write_line(to_string(num) + ". " + player.songs[i].name);
        }
    }

    int num_matches = matches.size();

    if (num_matches == 0)
    {
        write_line("No matching songs found.");
        return NO_SONG;
    }

    int choice = read_integer_range("Select a song: ", 1, num_matches);

    return matches[choice - 1];
}

/**
 * Let the user update, reset or delete a song.
 *
 * @param player the music player containing the song
 */
void update_song(music_player_data &player)
{
    int index = find_song(player);
    if (index == NO_SONG) return;

    update_menu_option option;

    do
    {
        write_line();
        print_song(player.songs[index]);
        write_line();
        print_update_menu();

        option = (update_menu_option)read_integer_range("Enter an option: ", 1, 5);

        switch (option)
        {
            case UPDATE_NAME:
                player.songs[index].name = read_string("Enter new name: ");
                write_line("Updated name.");
                break;
            case UPDATE_LOVED:
                player.songs[index].loved = !player.songs[index].loved;
                write_line("Updated loved.");
                break;
            case RESET_PLAYS:
                player.songs[index].times_played = 0;
                write_line("Reset times played.");
                break;
            case DELETE_SONG:
                write_line("Deleted " + player.songs[index].name);
                player.songs.erase(player.songs.begin() + index);
                option = QUIT_UPDATE;
                break;
            case QUIT_UPDATE:
                break;
        }
    } while (option != QUIT_UPDATE);
}

/**
 * Let the user pick a song, then play it and add one to its play count.
 *
 * @param player the music player containing the song
 */
void play_song(music_player_data &player)
{
    int index = find_song(player);
    if (index == NO_SONG) return;

    player.songs[index].times_played++;
    play_music(player.songs[index].id);

    write_line("Now playing " + player.songs[index].name);
}

/**
 * Pause the music if it is playing, otherwise resume it.
 */
void pause_resume()
{
    if (music_playing())
    {
        pause_music();
        write_line("Music paused.");
    }
    else
    {
        resume_music();
        write_line("Music resumed.");
    }
}

/**
 * Print the number of songs, total times played and number of loved songs.
 *
 * @param player the music player to report on
 */
void print_status(const music_player_data &player)
{
    int count = player.songs.size();
    int total_played = 0;
    int total_loved = 0;

    for (int i = 0; i < count; i++)
    {
        total_played += player.songs[i].times_played;

        if (player.songs[i].loved)
        {
            total_loved++;
        }
    }

    write_line("== Music Player Status ==");
    write_line("Songs:        " + to_string(count));
    write_line("Times played: " + to_string(total_played));
    write_line("Loved songs:  " + to_string(total_loved));
}

int main()
{
    music_player_data player;
    player.next_id = 0;

    main_menu_option option;

    write_line("Music Player!");

    do
    {
        print_main_menu();
        option = (main_menu_option)read_integer_range("Enter an option: ", 1, 6);

        switch (option)
        {
            case ADD_SONG:
                add_song(player);
                break;
            case UPDATE_SONG:
                update_song(player);
                break;
            case PLAY_SONG:
                play_song(player);
                break;
            case PAUSE_RESUME:
                pause_resume();
                break;
            case PRINT_STATUS:
                print_status(player);
                break;
            case QUIT:
                break;
        }
    } while (option != QUIT);

    write_line("Bye!");
    return 0;
}