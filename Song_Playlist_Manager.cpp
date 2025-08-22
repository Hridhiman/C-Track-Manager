// Song Playlist Manager and MP3 Tag reader
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Song_Details
{
    char language[20];
    char song_name[50];
    char artist_name[50];
    char album_name[50];
    char genre_type[50];
    char year[5];
    char comment[100];
} Song;

Song *sdetails = NULL;
int total;

void Add_Details(Song *, int);
void View_Details(Song *, int);
void Search_Details(Song *, int);
void Delete_Details(Song *, int *);
void ViewPlaylist();
void CreatePlaylist();
void DeletePlaylist();
void SearchPlaylist();
void ViewFavorites();

char username[50];
char contact_number[15];

int username_validation(char[]);
int username_validation(char username[])
{
    if (!isupper(username[0]))
    {
        return 0;
    }
    for (int i = 1; username[i] != '\0'; i++)
    {
        if (!isalpha(username[i]) && username[i] != ' ')
            return 0;
    }
    return 1;
}

int contact_validation(char[]);
int contact_validation(char contact_number[])
{
    if (contact_number[0] != '6' && contact_number[0] != '7' && contact_number[0] != '8' && contact_number[0] != '9')
    {
        return 0;
    }
    int len = strlen(contact_number);
    if (len != 10)
    {
        return 0;
    }
    for (int i = 0; contact_number[i] != '\0'; i++)
    {
        if (!isdigit(contact_number[i]))
        {
            return 0;
        }
    }
    return 1;
}

int song_namevalidation(char[]);
int song_namevalidation(char tempsong[])
{
    if (islower(tempsong[0]))
    {
        return 0;
    }
    for (int i = 1; tempsong[i] != '\0'; i++)
    {
        if (!(isalnum(tempsong[i]) || tempsong[i] == ' '))
        {
            return 0;
        }
    }
    return 1;
}

int namevalidation(char[]);
int namevalidation(char tempname[])
{
    if (!isalpha(tempname[0]))
    {
        return 0;
    }
    for (int i = 1; tempname[i] != '\0'; i++)
    {
        if (!(isalpha(tempname[i]) || tempname[i] == ' '))
        {
            return 0;
        }
    }

    return 1;
}
int loadromfile(Song *);
int loadromfile(Song *sdetails)
{
    FILE *data = fopen("Song Details.txt", "r");
    if (data == NULL)
    {
        printf("\033[0;31mFile is empty\033[0m\n");
        return -1;
    }
    int count = 0;
    while (fscanf(data, "Language: %[^\n]\nSong Name: %[^\n]\nArtist Name: %[^\n]\nAlbum Name: %[^\n]\nGenre Type: %s\nRelease Year: %s\n\n", sdetails[count].language, sdetails[count].song_name, sdetails[count].artist_name, sdetails[count].album_name, sdetails[count].genre_type, sdetails[count].year) == 6)
    {
        count++;
    }
    fclose(data);
    return count;
}

void saveddetails(Song *sdetails, int *total)
{
    FILE *data = fopen("Song Details.txt", "w");
    if (data == NULL)
    {
        perror(" ");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        fprintf(data, "Language: %s\n", sdetails[i].language);
        fprintf(data, "Song Name: %s\n", sdetails[i].song_name);
        fprintf(data, "Artist Name: %s\n", sdetails[i].artist_name);
        fprintf(data, "Album Name: %s\n", sdetails[i].album_name);
        fprintf(data, "Genre Type: %s\n", sdetails[i].genre_type);
        fprintf(data, "Release Year: %s\n\n", sdetails[i].year);
    }

    printf("\033[0;32mSong details saved successfully\033[0m\n");
    fclose(data);
}

int main()
{
    sdetails = (Song *)calloc(50, sizeof(Song));
    if (sdetails == NULL)
    {
        printf("\033[0;31mMemory allocation failed\033[0m\n");
        return -1;
    }
    total = loadromfile(sdetails);
    if (total == -1)
    {
        printf("\033[0;33mNothing loaded starting fresh\033[0m\n");
        total = 0;
    }
    printf("=========================\n");
    printf("\033[0;34mUSER LOGIN DETAILS\033[0m\n");
    printf("=========================\n");
    while (1)
    {
        printf("\033[0;33mEnter your name\033[0m\n");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
        int namevalid = username_validation(username);
        printf("\033[0;33mEnter your contact number\033[0m\n");
        fgets(contact_number, sizeof(contact_number), stdin);
        contact_number[strcspn(contact_number, "\n")] = '\0';
        int numvalid = contact_validation(contact_number);
        if (namevalid == 1 && numvalid == 1)
        {
            FILE *login = fopen("Login.txt", "a");
            if (login == NULL)
            {
                perror(" ");
                return -1;
            }
            fprintf(login, "Login Details\n\nPerson login: %s--> Contact Details: %s\n", username, contact_number);
            fclose(login);
            int open;
            printf("\n");
            printf("\033[0;34mWelcome\033[0m %s\n", username);
            printf("\n");
            printf("\033[0;33mNow you can access your\033[0m \033[44mTrack Manager\033[0m\n");
            printf("\033[0;33mLets Go press 1 to roll with your music\033[0m\n");
            scanf("%d", &open);
            if (open == 1)
            {
                int choice;
                while (1)
                {
                    printf("=======================\n");
                    printf(" \033[0;36mTRACK MANAGER\033[0m\n");
                    printf("=======================\n");
                    printf("\n");
                    printf("===========================\n");
                    printf("||\033[0;36m   MAIN MENU      \033[0m      ||\n");
                    printf("============================\n");
                    printf("||\033[44m1. ADD SONG DETAILS    \033[0m ||\n");
                    printf("----------------------------\n");
                    printf("||\033[44m2. VIEW SONG DETAILS   \033[0m ||\n");
                    printf("----------------------------\n");
                    printf("||\033[44m3. SEARCH SONG         \033[0m ||\n");
                    printf("----------------------------\n");
                    printf("||\033[44m4. DELETE SAVED SONG   \033[0m ||\n");
                    printf("----------------------------\n");
                    printf("||\033[44m5. VIEW SAVED PLAYLIST \033[0m ||\n");
                    printf("-----------------------------\n");
                    printf("||\033[44m6. CREATE NEW PLAYLIST  \033[0m||\n");
                    printf("-----------------------------\n");
                    printf("||\033[44m7. SEARCH PLAYLIST      \033[0m||\n");
                    printf("-----------------------------\n");
                    printf("||\033[44m8. VIEW FAVORITES       \033[0m||\n");
                    printf("-----------------------------\n");
                    printf("||\033[44m9. EXIT PROGRAM        \033[0m ||\n");
                    printf("============================\n");
                    printf("\n");
                    printf("\033[0;33mSelect your desired operation:\033[0m\n");
                    scanf("%d", &choice);
                    getchar();
                    switch (choice)
                    {
                    case 1:
                    {
                        int n;
                        printf("\033[0;33mPlease sepecify how many songs you want to enter:\033[0m\n");
                        scanf("%d", &n);
                        sdetails = (Song *)realloc(sdetails, (total + n) * sizeof(Song));
                        if (sdetails == NULL)
                        {
                            printf("\033[0;31mMemory allocation failed.\033[0m\n");
                            return -1;
                        }
                        for (int i = total; i < total + n; i++)
                        {
                            Add_Details(sdetails, i);
                        }
                        total += n;
                        break;
                    }
                    case 2:
                    {
                        if (total == 0)
                        {
                            printf("------------------------------------------\n");
                            printf("||      \033[0;33mNo Songs available to view.\033[0m||\n");
                            printf("------------------------------------------\n");
                        }
                        else
                        {
                            View_Details(sdetails, total);
                        }
                        break;
                    }
                    case 3:
                    {
                        if (total == 0)
                        {
                            printf("-----------------------------------------\n");
                            printf("||     \033[0;33mNo Songs available to search.\033[0m||\n");
                            printf("-----------------------------------------\n");
                        }
                        else
                        {
                            Search_Details(sdetails, total);
                        }
                        break;
                    }
                    case 4:
                    {
                        if (total == 0)
                        {
                            printf("-----------------------------------------\n");
                            printf("||     \033[0;33mNo Songs available to delete.\033[0m||\n");
                            printf("-----------------------------------------\n");
                        }
                        else
                        {
                            Delete_Details(sdetails, &total);
                        }
                        break;
                    }
                    case 5:
                    {
                        ViewPlaylist();
                        break;
                    }
                    case 6:
                    {
                        CreatePlaylist();
                        break;
                    }
                    case 7:
                    {
                        SearchPlaylist();
                    }
                    case 8:
                    {
                        ViewFavorites();
                        break;
                    }
                    case 9:
                    {
                        int exit_option;
                        while (1)
                        {
                            printf("\033[0;33mAre you sure you want to exit:\033[0m\n");
                            printf("\033[0;33m1.Yes(To Exit)\033[0m\n");
                            printf("\033[0;33m2.No(To continue)\033[0m\n");
                            scanf("%d", &exit_option);
                            getchar();
                            if (exit_option == 1)
                            {
                                printf("\033[0;31mExiting Program.\033[0m\n");
                                free(sdetails);
                                return 0;
                            }
                            else if (exit_option == 2)
                            {
                                printf("\033[0;33mReturning to main menu.\033[0m\n");
                                printf("\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mTo continue program or to exit please enter a valid option\033[0m\n");
                            }
                        }
                        break;
                    }
                    default:
                    {
                        printf("\033[0;31mInvalid option. Please try again.\033[0m\n");
                        printf("\n");
                    }
                    }
                }
            }
            break;
        }
        else if (!namevalid)
        {
            printf("\033[0;31mEnter name correctly to login\033[0m\n");
            printf("\033[0;33mA name must start with an uppercase character and must contain only alphabets\033[0m\n");
        }
        else if (!numvalid)
        {
            printf("\033[0;31Enter a valid to login\033[0m\n");
        }
    }
}

void Add_Details(Song *sdetails, int i)
{
    printf("====================================\n");
    printf("||      \033[0;34mADD SONG DETAILS\033[0m      ||\n");
    printf("====================================\n\n");
    int trackoption;
    while (1)
    {
        printf("\033[0;33mChoose your input method\033[0m\n");
        printf("\033[0;33mPress 1. for \033[0m\033[0;34mMP3 File Integration\033[0m\n");
        printf("\033[0;33mPress 2. for \033[0m\033[0;32mManual Track Organizer\033[0m\n");
        scanf("%d", &trackoption);
        getchar();
        if (trackoption == 1)
        {
            printf("========================================================\n");
            printf("||  \033[44m WELCOME TO MP3 (AUTOMATIC TAG INTEGRATION) \033[0m  ||\n");
            printf("========================================================\n");
            char filepath[200];
            printf("\033[0;33mEnter the mp3 file path\033[0m\n");
            fgets(filepath, sizeof(filepath), stdin);
            filepath[strcspn(filepath, "\n")] = '\0';
            FILE *mp3 = fopen(filepath, "rb");
            if (mp3 == NULL)
            {
                perror(" ");
                return;
            }
            fseek(mp3, -128, SEEK_END);
            char tag[128];
            fread(tag, 1, 128, mp3);
            fclose(mp3);
            if (strncmp(tag, "TAG", 3) != 0)
            {
                printf("\033[0;31mTag not founded\033[0m\n");
                return;
            }
            typedef struct SonginMP3
            {
                char song_name[31];
                char artist_name[31];
                char album_name[31];
                char genre_type[1];
                char year[4];
                char comment[31];
            } songmp3;
            songmp3 newsong;
            strncpy(newsong.song_name, tag + 3, 30);
            newsong.song_name[30] = '\0';
            strncpy(newsong.artist_name, tag + 33, 30);
            newsong.artist_name[30] = '\0';
            strncpy(newsong.album_name, tag + 63, 30);
            newsong.album_name[30] = '\0';
            strncpy(newsong.year, tag + 93, 4);
            newsong.year[4] = '\0';
            strncpy(sdetails[i].song_name, newsong.song_name, sizeof(sdetails[i].song_name) - 1);
            sdetails[i].song_name[sizeof(sdetails[i].song_name) - 1] = '\0';
            strncpy(sdetails[i].artist_name, newsong.artist_name, sizeof(sdetails[i].artist_name) - 1);
            sdetails[i].artist_name[sizeof(sdetails[i].artist_name) - 1] = '\0';
            strncpy(sdetails[i].album_name, newsong.album_name, sizeof(sdetails[i].album_name) - 1);
            sdetails[i].album_name[sizeof(sdetails[i].album_name) - 1] = '\0';
            strncpy(sdetails[i].year, newsong.year, sizeof(sdetails[i].year) - 1);
            sdetails[i].year[sizeof(sdetails[i].year) - 1] = '\0';
            strcpy(sdetails[i].genre_type, "Genre not Specified");
            strcpy(sdetails[i].comment, "No comment provided");
            int favopt;
            printf("\033[0;33mDo you want to mark this track as you favorite\033[0m\n");
            printf("\033[0;33mType 1. mark as favorite\033[0m\n");
            printf("\033[0;33mType 2. to skip\033[0m\n");
            scanf("%d", &favopt);
            getchar();
            if (favopt == 1)
            {
                FILE *favorite = fopen("Favorites.txt", "a");
                if (favorite == NULL)
                {
                    perror(" ");
                    return;
                }
                fprintf(favorite, "Song name: %s--> Artist Name: %s\n\n", sdetails[i].song_name, sdetails[i].artist_name);
                printf("Song saved to favorite successfully");
                fclose(favorite);
            }
            int optionplaylist;
            printf("\033[0;33mDo you want to save this song to a playlist\033[0m\n");
            printf("\033[0;33mType 1. save in a playlist\033[0m\n");
            printf("\033[0;33mType 2. to skip\033[0m\n");
            scanf("%d", &optionplaylist);
            getchar();
            if (optionplaylist == 1)
            {
                char filename[50];
                printf("\033[0;33mChoose a name for your playlist\033[0m\n");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                FILE *Play = fopen(filename, "a");
                if (Play == NULL)
                {
                    perror(" ");
                    return;
                }
                fprintf(Play, "Song name: %s--> Album Name: %s--> Artist Name: %s\n\n", sdetails[i].song_name, sdetails[i].album_name, sdetails[i].artist_name);
                printf("Song saved to your %s playlist successfully", filename);
                fclose(Play);
                FILE *masterfile = fopen("Playlist.txt", "a+");
                if (masterfile == NULL)
                {
                    perror(" ");
                    return;
                }
                char check[200];
                int exists = 0;
                while (fgets(check, sizeof(check), masterfile))
                {
                    check[strcspn(check, "\n")] = '\0';
                    if (strcmp(check, filename) == 0)
                    {
                        exists = 1;
                        break;
                    }
                }
                if (!exists)
                {
                    masterfile = fopen("Playlist.txt", "a");
                    if (masterfile != NULL)
                    {
                        fprintf(masterfile, "%s\n", filename);
                        fclose(masterfile);
                    }
                }
                fclose(masterfile);
            }
            break;
        }
        else if (trackoption == 2)
        {
            int langspecify;
            printf("\033[0;33mCan you specify the language of the song you are about to enter\033[0m\n");
            printf("\033[0;33mType 1. to specify the language\033[0m\n");
            printf("\033[0;33mType 2. to skip\033[0m\n");
            scanf("%d", &langspecify);
            getchar();
            if (langspecify == 1)
            {
                int choice;
                while (1)
                {
                    printf("\033[0;33mSelect the song language.\033[0m\n");
                    printf("\n");
                    printf("\033[1;36m=====================================\033[0m\n");
                    printf("          \033[1;33m LANGUAGE MENU  \033[0m\n");
                    printf("\033[1;36m=====================================\033[0m\n");

                    printf("|| \033[1;37;44m 1. ENGLISH   \033[0m ||\n");
                    printf("|| \033[1;37;42m 2. HINDI     \033[0m ||\n");
                    printf("|| \033[1;37;45m 3. BENGALI   \033[0m ||\n");
                    printf("|| \033[1;37;41m 4. PUNJABI   \033[0m ||\n");
                    printf("|| \033[1;30;43m 5. TAMIL     \033[0m ||\n");
                    printf("|| \033[1;37;46m 6. TELUGU    \033[0m ||\n");
                    printf("|| \033[1;37;100m 7. KANNADA   \033[0m ||\n");
                    printf("|| \033[1;37;42m 8. MALAYALAM \033[0m ||\n");

                    printf("\033[1;36m=====================================\033[0m\n");

                    printf("\n");
                    scanf("%d", &choice);
                    getchar();
                    if (choice == 1)
                    {
                        strcpy(sdetails[i].language, "English");
                        break;
                    }
                    else if (choice == 2)
                    {
                        strcpy(sdetails[i].language, "Hindi");
                        break;
                    }
                    else if (choice == 3)
                    {
                        strcpy(sdetails[i].language, "Bengali");
                        break;
                    }
                    else if (choice == 4)
                    {
                        strcpy(sdetails[i].language, "Punjabi");
                        break;
                    }
                    else if (choice == 5)
                    {
                        strcpy(sdetails[i].language, "Tamil");
                        break;
                    }
                    else if (choice == 6)
                    {
                        strcpy(sdetails[i].language, "Telugu");
                        break;
                    }
                    else if (choice == 7)
                    {
                        strcpy(sdetails[i].language, "Kannada");
                        break;
                    }
                    else if (choice == 8)
                    {
                        strcpy(sdetails[i].language, "Malayalam");
                        break;
                    }
                    else
                    {
                        printf("\033[0;31mSelect a valid language option from the menu.\033[0m\n");
                    }
                }
            }
            else
            {
                strcpy(sdetails[i].language, "Language not Specified");
            }

            while (1)
            {
                char tempsong[50];
                printf("\033[0;33mType the song name\033[0m\n");
                fgets(tempsong, sizeof(tempsong), stdin);
                tempsong[strcspn(tempsong, "\n")] = '\0';
                int valid = song_namevalidation(tempsong);
                if (valid == 1)
                {
                    strcpy(sdetails[i].song_name, tempsong);
                    printf("\033[0;32mSong name saved\033[0m\n");
                    break;
                }
                else
                {
                    printf("\033[0;31mEnter a valid song name\033[0m\n");
                }
            }
            while (1)
            {
                char tempname[50];
                printf("\033[0;33mType the artist name\033[0m\n");
                fgets(tempname, sizeof(tempname), stdin);
                tempname[strcspn(tempname, "\n")] = '\0';
                int valid = namevalidation(tempname);
                if (valid == 1)
                {
                    strcpy(sdetails[i].artist_name, tempname);
                    printf("\033[0;32mArtist name saved\033[0m\n");
                    break;
                }
                else
                {
                    printf("\033[0;31mEnter a valid name\033[0m\n");
                }
            }
            int info;
            printf("\033[0;33mDoes this song belong to an album?\033[0m\n");
            printf("\033[0;33mEnter 1 to provide the album name\033[0m\n");
            printf("\033[0;33mEnter 2 to skip\033[0m\n");
            scanf("%d", &info);
            getchar();
            if (info == 1)
            {
                while (1)
                {
                    char tempalbum[50];
                    printf("\033[0;33mType the album name\033[0m\n");
                    fgets(tempalbum, sizeof(tempalbum), stdin);
                    tempalbum[strcspn(tempalbum, "\n")] = '\0';
                    int valid = song_namevalidation(tempalbum);
                    if (valid == 1)
                    {
                        strcpy(sdetails[i].album_name, tempalbum);
                        printf("\033[0;32mAlbum name saved\033[0m\n");
                        break;
                    }
                    else
                    {
                        printf("\033[0;31mEnter a valid album name\033[0m\n");
                    }
                }
            }
            else
            {
                strcpy(sdetails[i].album_name, "None");
            }
            int genrespecify;
            printf("\033[0;33mCan you specify the genre of the song\033[0m\n");
            printf("\033[0;33mType 1. to specify the genre\033[0m\n");
            printf("\033[0;33mType 2. to skip\033[0m\n");
            scanf("%d", &genrespecify);
            getchar();
            if (genrespecify == 1)
            {
                int choice;
                while (1)
                {
                    printf("\033[1;36m================================================\033[0m\n");
                    printf("          \033[1;33m SELECT YOUR SONG GENRE \033[0m\n");
                    printf("\033[1;36m================================================\033[0m\n");

                    printf("|| \033[1;37;44m 1. POP         \033[0m || \033[1;37;45m 2. ROCK        \033[0m ||\n");
                    printf("|| \033[1;37;42m 3. HIPHOP      \033[0m || \033[1;37;41m 4. CLASSICAL   \033[0m ||\n");
                    printf("|| \033[1;30;43m 5. JAZZ        \033[0m || \033[1;37;46m 6. ELECTRONIC  \033[0m ||\n");
                    printf("|| \033[1;37;100m7. R&B / SOUL  \033[0m || \033[1;37;42m 8. DEVOTIONAL  \033[0m ||\n");

                    printf("\033[1;36m================================================\033[0m\n");

                    printf("\n");
                    scanf("%d", &choice);
                    getchar();
                    if (choice == 1)
                    {
                        strcpy(sdetails[i].genre_type, "Pop");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 2)
                    {
                        strcpy(sdetails[i].genre_type, "Rock");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 3)
                    {
                        strcpy(sdetails[i].genre_type, "HipHop");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 4)
                    {
                        strcpy(sdetails[i].genre_type, "Classical");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 5)
                    {
                        strcpy(sdetails[i].genre_type, "Jazz");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 6)
                    {
                        strcpy(sdetails[i].genre_type, "Electronic");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 7)
                    {
                        strcpy(sdetails[i].genre_type, "R&B/Soul");
                        printf("\033[0;32Genre type saved\033[0m\n");
                        break;
                    }
                    else if (choice == 8)
                    {
                        strcpy(sdetails[i].genre_type, "Devotional");
                        printf("\033[0;32mGenre type saved\033[0m\n");
                        break;
                    }
                    else
                    {
                        printf("\033[0;31mPlease select a valid genre type from the menu\033[0m\n");
                    }
                }
            }
            else
            {
                strcpy(sdetails[i].genre_type, "Genre not Specified");
            }
            printf("\033[0;33mEnter the Release Date\033[0m\n");
            fgets(sdetails[i].year, sizeof(sdetails[i].year), stdin);
            sdetails[i].year[strcspn(sdetails[i].year, "\n")] = '\0';
            printf("\033[0;32mRelease Date saved\033[0m\n");
            int cmntoption;
            printf("\033[0;33mYou can enter comment for this track.Press 1.to comment\033[0m\n");
            printf("\033[0;33mPress any button to skip\033[0m\n");
            scanf("%d", &cmntoption);
            getchar();
            if (cmntoption == 1)
            {
                printf("\033[0;33mType your comment\033[0m\n");
                fgets(sdetails[i].comment, sizeof(sdetails[i].comment), stdin);
                sdetails[i].comment[strcspn(sdetails[i].comment, "\n")] = '\0';
            }
            else
            {
                strcpy(sdetails[i].comment, "No comment provided");
            }
            int fav;
            printf("\033[0;33mDo you want to save this song as your 'Favorites'\033[0m\n");
            printf("\033[0;33mType 1. save as 'Favorite'\033[0m\n");
            printf("\033[0;33mType 2. to skip\033[0m\n");
            scanf("%d", &fav);
            getchar();
            if (fav == 1)
            {
                FILE *favorite = fopen("Favorites.txt", "a");
                if (favorite == NULL)
                {
                    perror(" ");
                    return;
                }
                fprintf(favorite, "Song name: %s--> Artist Name: %s\n\n", sdetails[i].song_name, sdetails[i].artist_name);
                printf("Song saved to favorite successfully\n");
                fclose(favorite);
            }
            int play;
            printf("\033[0;33mDo you want to save this song to a playlist\033[0m\n");
            printf("\033[0;33mType 1. save in a playlist\033[0m\n");
            printf("\033[0;33mType 2. to skip\033[0m\n");
            scanf("%d", &play);
            getchar();
            if (play == 1)
            {
                char filename[50];
                printf("\033[0;33mName a playlist of your choice\033[0m\n");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                FILE *Play = fopen(filename, "a");
                if (Play == NULL)
                {
                    perror(" ");
                    return;
                }
                fprintf(Play, "Song name: %s--> Album Name: %s--> Artist Name: %s\n\n", sdetails[i].song_name, sdetails[i].album_name, sdetails[i].artist_name);
                printf("Song saved to your %s playlist successfully", filename);
                fclose(Play);
                FILE *masterfile = fopen("Playlist.txt", "a+");
                if (masterfile == NULL)
                {
                    perror(" ");
                    return;
                }
                char check[200];
                int playexist = 0;
                while (fgets(check, sizeof(check), masterfile))
                {
                    check[strcspn(check, "\n")] = '\0';
                    if (strcmp(check, filename) == 0)
                    {
                        playexist = 1;
                        break;
                    }
                }
                if (!playexist)
                {
                    masterfile = fopen("Playlist.txt", "a");
                    if (masterfile != NULL)
                    {
                        fprintf(masterfile, "%s\n", filename);
                        fclose(masterfile);
                    }
                }
                fclose(masterfile);
            }
            FILE *data = fopen("Song Details.txt", "a");
            if (data == NULL)
            {
                perror(" ");
                return;
            }
            fprintf(data, "Language: %s\nSong Name: %s\nArtist Name: %s\nAlbum Name: %s\nGenre Type: %s\nRelease Year: %s\n\n", sdetails[i].language, sdetails[i].song_name, sdetails[i].artist_name, sdetails[i].album_name, sdetails[i].genre_type, sdetails[i].year);
            printf("\033[0;32mSong details saved succesfully\033[0m\n");
            fclose(data);
            break;
        }
        else
        {
            printf("\033[0;31mEnter a valid track option to continue\033[0m\n");
        }
    }
}
void View_Details(Song *sdetails, int total)
{
    printf("====================================\n");
    printf("||      \033[0;34mVIEW SONG DETAILS\033[0m      ||\n");
    printf("====================================\n\n");
    printf("\033[0;36m======================================================================================================================\033[0m\n");
    printf("\033[1;33m| %-3s | %-30s | %-20s | %-30s | %-15s | %-12s | %-5s |\033[0m\n",
           "No", "Song Name", "Artist", "Album Name", "Language", "Genre", "Year");
    printf("\033[0;36m======================================================================================================================\033[0m\n");

    for (int i = 0; i < total; i++)
    {
        printf("| %-3d | %-30s | %-20s | %-15s | %-12s | %-5s |\n",
               i + 1,
               sdetails[i].song_name,
               sdetails[i].artist_name,
               sdetails[i].album_name,
               sdetails[i].language,
               sdetails[i].genre_type,
               sdetails[i].year);
    }
    printf("======================================================================================================================\n");
}
void Search_Details(Song *sdetails, int total)
{
    printf("====================================\n");
    printf("||    \033[0;34mSEARCH SONG DETAILS\033[0m    ||\n");
    printf("====================================\n\n");
    printf("\033[0;33mNow you can search songs in multiple ways\033[0m\n");
    printf("\033[0;33mSimplify your search\033[0m\n\n");
    int choice;
    while (1)
    {
        printf("========================================\n");
        printf("||\033[0;33m            SEARCH MENU         \033[0m||\n");
        printf("========================================\n");
        printf("||\033[46m 1. SEARCH BY SONG NAME           \033[0m||\n");
        printf("----------------------------------------\n");
        printf("||\033[46m 2. SEARCH BY ARTIST NAME         \033[0m||\n");
        printf("----------------------------------------\n");
        printf("||\033[46m 3. SEARCH BY GENRE TYPE          \033[0m||\n");
        printf("----------------------------------------\n");
        printf("||\033[46m 4. SEARCH BY ALBUM NAME          \033[0m||\n");
        printf("----------------------------------------\n");
        printf("||\033[46m 5. EXIT                          \033[0m||\n");
        printf("========================================\n\n");
        printf("\033[0;33mSelect your search\033[0m\n");

        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            while (1)
            {
                char tempsong[50];
                int saved[100];
                int n = 0, found = 0;

                printf("\033[0;33mEnter the song name to search\033[0m\n");
                fgets(tempsong, sizeof(tempsong), stdin);
                tempsong[strcspn(tempsong, "\n")] = '\0';

                int valid = song_namevalidation(tempsong);
                if (valid == 1)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strstr(sdetails[i].song_name, tempsong) != NULL)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;

                            printf("\033[0;32mSong Found\033[0m\n");
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Genre Type: %s\n", sdetails[idx].genre_type);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    else
                    {
                        int option;
                        printf("\033[0;31mThe song you searched is not available in the program file\033[0m\n");
                        printf("\033[0;33mWant to add the song in the list? Press 1 to add or press 2 to skip\033[0m\n");
                        scanf("%d", &option);
                        getchar();
                        if (option == 1)
                        {
                            Add_Details(sdetails, total);
                            break;
                        }
                        else if (option == 2)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    printf("\033[0;31mEnter a valid track name to continue search\033[0m\n");
                }
            }
        }
        else if (choice == 2)
        {
            while (1)
            {
                char tempartist[50];
                int found = 0;

                printf("\033[0;33mEnter the artist name to view their songs\033[0m\n");
                fgets(tempartist, sizeof(tempartist), stdin);
                tempartist[strcspn(tempartist, "\n")] = '\0';
                int valid = namevalidation(tempartist);
                if (valid == 1)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strstr(sdetails[i].artist_name, tempartist) != NULL)
                        {
                            printf("\033[0;32mArtist match found! Displaying their songs...\033[0m\n");
                            found = 1;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", i + 1, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }

                    if (!found)
                    {
                        printf("\033[0;31mArtist with this name is not found in the file\033[0m\n");
                    }
                    break;
                }
                else
                {
                    printf("\033[0;31mEnter a valid artist name to view their songs\033[0m\n");
                }
            }
        }

        else if (choice == 3)
        {
            int genre;
            int saved[100];
            int n = 0, found = 0;
            while (1)
            {
                printf("\033[0;33mChoose your vibe! Pick a genre to explore:\033[0m\n\n");
                printf("\n");
                printf("==================================\n");
                printf("||\033[0;33mGENRE MENU\033[0m   ||\n");
                printf("==================================\n");
                printf("||\033[46m1.POP\033[0m          ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m2.ROCK\033[0m         ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m3.HIPHOP\033[0m       ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m4.CLASSICAL\033[0m    ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m5.JAZZ\033[0m         ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m6.ELECTRONIC\033[0m   ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m7.R&B/SOUL\033[0m     ||\n");
                printf("----------------------------------\n");
                printf("||\033[46m8.DEVOTIONAL\033[0m   ||\n");
                printf("==================================\n");
                printf("\n");
                scanf("%d", &genre);
                getchar();
                if (genre == 1)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "Pop") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 2)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "Rock") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 3)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "HipHop") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 4)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "Classical") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 5)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "Jazz") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 6)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "Electronic") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 7)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "R&B/Soul") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else if (genre == 8)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strcasecmp(sdetails[i].genre_type, "Devotional") == 0)
                        {
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
                else
                {
                    printf("\033[0;31mInvalid choice! Please select a valid genre to explore songs.\033[0m\n");
                    printf("\n");
                }
            }
        }
        else if (choice == 4)
        {
            while (1)
            {
                char tempalbum[50];
                int saved[100];
                int found = 0, n = 0;
                printf("\033[0;33mEnter album name\033[0m\n");
                fgets(tempalbum, sizeof(tempalbum), stdin);
                tempalbum[strcspn(tempalbum, "\n")] = '\0';
                int valid = song_namevalidation(tempalbum);
                if (valid == 1)
                {
                    for (int i = 0; i < total; i++)
                    {
                        if (strstr(sdetails[i].album_name, tempalbum) != NULL)
                        {
                            printf("\033[0;32mAlbum match found! Displaying their songs...\033[0m\n");
                            found = 1;
                            saved[n] = i;
                            n++;
                            printf("-------------------------------\n");
                            printf("%2d. %-25s\n", n, sdetails[i].song_name);
                            printf("-------------------------------\n\n");
                        }
                    }
                    if (found)
                    {
                        int sl;
                        while (1)
                        {
                            printf("Want to know more about a track? Just hit its serial number and dive into the details!\n");
                            scanf("%d", &sl);
                            getchar();

                            if (sl >= 1 && sl <= n)
                            {
                                int idx = saved[sl - 1];
                                printf("=====================\n");
                                printf("|| Song Name: %s\n", sdetails[idx].song_name);
                                printf("|| Artist Name: %s\n", sdetails[idx].artist_name);
                                printf("|| Album Name: %s\n", sdetails[idx].album_name);
                                printf("|| Release Date: %s\n", sdetails[idx].year);
                                printf("|| Song Language: %s\n", sdetails[idx].language);
                                printf("=====================\n");
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEnter a valid serial no. to view details of your right track\033[0m\n");
                            }
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            return;
        }
    }
}
void Delete_Details(Song *sdetails, int *total)
{
    printf("====================================\n");
    printf("||     \033[0;34mDELETE SONG DETAILS\033[0m     ||\n");
    printf("====================================\n\n");
    printf("\n");
    while (1)
    {
        char songname[50];
        int found = 0, artistfound = 0;
        printf("\033[0;33mTime to clean up! Enter the song name you wish to delete from your playlist:\033[0m\n");
        fgets(songname, sizeof(songname), stdin);
        songname[strcspn(songname, "\n")] = '\0';
        int valid = song_namevalidation(songname);
        if (valid == 1)
        {
            for (int i = 0; i < *total; i++)
            {
                if (strstr(sdetails[i].song_name, songname) != NULL)
                {
                    found = 1;
                    char tempartist[50];
                    printf("\033[0;33mEnter the artist name behind the track you want to delete\033[0m\n");
                    fgets(tempartist, sizeof(tempartist), stdin);
                    tempartist[strcspn(tempartist, "\n")] = '\0';
                    int valid_artist = namevalidation(tempartist);
                    if (valid_artist == 1)
                    {
                        if (strstr(sdetails[i].artist_name, tempartist) != NULL)
                        {
                            artistfound = 1;
                            for (int j = i; j < *total - 1; j++)
                            {
                                sdetails[j] = sdetails[j + 1];
                            }
                            (*total)--;
                            saveddetails(sdetails, total);
                            break;
                        }
                    }
                }
            }
            if (!artistfound)
            {
                printf("\033[0;31mThe artist name could not be found. Deletion cannot be done\033[0m\n");
            }
            if (!found)
            {
                printf("\033[0;31mThe track not found to delete\033[0m\n");
            }
            break;
        }
        else
        {
            printf("\033[0;31mEnter a valid track name to delete details\033[0m\n");
        }
    }
}
void ViewPlaylist()
{
    char name[200];
    int index = 1;

    FILE *masterfile = fopen("Playlist.txt", "r");
    if (masterfile == NULL)
    {
        int option;
        printf("\033[0;31mNo playlist is avaialble to view\033[0m\n");
        printf("\033[0;33mYou can always create a playlist to continue\033[0m\n");
        printf("\033[0;33mType 1 to create playlist. Type 2 to skip\033[0m\n");
        scanf("%d", &option);
        getchar();
        if (option == 1)
        {
            CreatePlaylist();
            return;
        }
        else
        {
            return;
        }
    }

    printf("-----------------------------------\n");
    printf("       \033[0;33mAvailable Playlists\033[0m       \n");
    printf("-----------------------------------\n");

    while (fgets(name, sizeof(name), masterfile))
    {
        name[strcspn(name, "\n")] = '\0';
        printf("----------------------------\n");
        printf("%2d. %-20s\n", index, name);
        printf("----------------------------\n");
        index++;
    }
    fclose(masterfile);

    int sl;
    printf("\033[0;33mSelect your playlist by entering its serial number:\033[0m\n");
    scanf("%d", &sl);
    getchar();

    if (sl >= 1 && sl < index)
    {
        char read[200];
        char selected[200];
        int linecount = 1;

        FILE *masterfile = fopen("Playlist.txt", "r");
        if (masterfile == NULL)
        {
            perror(" ");
            return;
        }

        while (fgets(read, sizeof(read), masterfile))
        {
            read[strcspn(read, "\n")] = '\0';
            if (linecount == sl)
            {
                strcpy(selected, read);
                break;
            }
            linecount++;
        }
        fclose(masterfile);
        FILE *Play = fopen(selected, "r");
        if (Play == NULL)
        {
            perror(" ");
            return;
        }

        printf("\n\033[0;32mContents of %s playlist:\033[0m\n", selected);
        printf("-----------------------------------\n");

        char ch;
        while ((ch = fgetc(Play)) != EOF)
        {
            putchar(ch);
        }

        printf("-----------------------------------\n");
        fclose(Play);
    }
    else
    {
        printf("\033[0;31mInvalid selection!\033[0m\n");
    }
}
void CreatePlaylist()
{
    printf("====================================\n");
    printf("||      \033[0;34mCREATE PLAYLIST\033[0m      ||\n");
    printf("====================================\n\n");

    typedef struct Playlist
    {
        char songname[50];
        char artistname[50];
    } playlist;

    char nameplay[50];
    int totalsong = 0;

    printf("\033[0;33mName a playlist of your choice:\033[0m\n");
    fgets(nameplay, sizeof(nameplay), stdin);
    nameplay[strcspn(nameplay, "\n")] = '\0';

    printf("\033[0;32mPlaylist created!\033[0m\n");
    printf("\033[0;3mHow many songs would you like to store?\033[0m\n");
    scanf("%d", &totalsong);
    getchar();

    playlist *store = (playlist *)calloc(totalsong, sizeof(playlist));
    if (store == NULL)
    {
        printf("\033[0;31mMemory allocation failed\033[0m\n");
        return;
    }

    for (int i = 0; i < totalsong; i++)
    {
        printf("\033[0;33mEnter the song name into the playlist:\033[0m\n");
        fgets(store[i].songname, sizeof(store[i].songname), stdin);
        store[i].songname[strcspn(store[i].songname, "\n")] = '\0';

        printf("\033[0;33mEnter the artist name behind the track:\033[0m\n");
        fgets(store[i].artistname, sizeof(store[i].artistname), stdin);
        store[i].artistname[strcspn(store[i].artistname, "\n")] = '\0';
    }

    FILE *Play = fopen(nameplay, "a");
    if (Play == NULL)
    {
        perror(" ");
        free(store);
        return;
    }

    for (int i = 0; i < totalsong; i++)
    {
        fprintf(Play, "Song name: %s--> Album Name: %s--> Artist Name: %s\n\n", sdetails[i].song_name, sdetails[i].album_name, sdetails[i].artist_name);
        printf("Song saved to your %s playlist successfully\n", nameplay);
    }
    fclose(Play);
    free(store);
    FILE *masterfile = fopen("Playlist.txt", "r");
    int playexist = 0;
    char check[200];

    if (masterfile != NULL)
    {
        while (fgets(check, sizeof(check), masterfile))
        {
            check[strcspn(check, "\n")] = '\0';
            if (strcmp(check, nameplay) == 0)
            {
                playexist = 1;
                break;
            }
        }
        fclose(masterfile);
    }

    if (!playexist)
    {
        masterfile = fopen("Playlist.txt", "a");
        if (masterfile != NULL)
        {
            fprintf(masterfile, "%s\n", nameplay);
            fclose(masterfile);
        }
    }
}
void SearchPlaylist()
{
    printf("====================================\n");
    printf("||      \033[0;34mSEARCH PLAYLIST\033[0m      ||\n");
    printf("====================================\n\n");

    char playlistname[50];
    printf("\033[0;33mEnter the playlist name:\033[0m\n");
    fgets(playlistname, sizeof(playlistname), stdin);
    playlistname[strcspn(playlistname, "\n")] = '\0';

    FILE *masterfile = fopen("Playlist.txt", "r");
    if (masterfile == NULL)
    {
        perror("Error opening master playlist file");
        return;
    }

    char search[100];
    int found = 0;
    while (fgets(search, sizeof(search), masterfile))
    {
        search[strcspn(search, "\n")] = '\0';
        if (strcmp(search, playlistname) == 0)
        {
            found = 1;
            printf("\033[0;32mPlaylist found!\033[0m\n\n");

            printf("------------------------\n");
            printf("||    %s    ||\n", playlistname);
            printf("------------------------\n\n");

            FILE *Play = fopen(playlistname, "r");
            if (Play == NULL)
            {
                perror("Error opening playlist file");
                fclose(masterfile);
                return;
            }

            char ch;
            printf("-----------------------------------\n");

            while ((ch = fgetc(Play)) != EOF)
            {
                putchar(ch);
            }

            printf("-----------------------------------\n");

            fclose(Play);
            break;
        }
    }

    if (!found)
    {
        printf("\033[0;31mThe playlist you are searching for is not available.\033[0m\n");
    }

    fclose(masterfile);
}
void ViewFavorites()
{
    printf("====================================\n");
    printf("||      \033[0;34mVIEW FAVORITES\033[0m      ||\n");
    printf("====================================\n\n");

    FILE *favorite = fopen("Favorites.txt", "r");
    if (favorite == NULL)
    {
        printf("\033[0;31mNo favorites found! Add some songs first.\033[0m\n");
        Add_Details(sdetails, total);
        return;
    }

    char ch;
    printf("-----------------------------------\n");

    while ((ch = fgetc(favorite)) != EOF)
    {
        putchar(ch);
    }

    printf("-----------------------------------\n");
    fclose(favorite);
}
