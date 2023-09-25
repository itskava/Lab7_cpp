#define _CRT_SECURE_NO_WARNINGS

#define SONGS_LIMIT 100
typedef struct {
	char* name;
	char* artist;
	unsigned int durationInSeconds;
} Song;

typedef struct {
	char* name;
	int songAmount;
	Song* songs;
} Playlist;

typedef struct {
	char* name;
	char* email;
	int age;
} Bio;

typedef struct {
	Bio bio;
	Playlist playlists[SONGS_LIMIT];
} User;
