#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

//Define the macro preprocessor OPTION_A to OPTION_D
#define OPTION_A (1 << 0)  // 0000 0001  //visibility
#define OPTION_B (1 << 1)  // 0000 0010  //sound
#define OPTION_C (1 << 2)  // 0000 0100  //play
#define OPTION_D (1 << 3)  // 0000 1000  //pause

void play_sound();
void pause_sound(int signal_num);
void playing();

int main()
{
    //WhatsApp settings
    unsigned int settings = 0;  // 0000 0000

    //Enable options A and C
    settings = settings | OPTION_A; // 0000 0000 | 0000 0001 = 0000 0001

    if (~settings & OPTION_A) // 0000 0001 & 0000 0001 = 0000 0001
    {
        printf("Visibility is enabled\n");
    }
    else
    {
        printf("Visibility is disabled\n");
    }

    //Enable Sound
    unsigned int n;
    settings = settings | OPTION_B; // 0000 0001 | 0000 0010 = 0000 0011
    if (settings & OPTION_B) // 0000 0011 & 0000 0010 = 0000 0010
    {
        printf("Sound enabled\n");

        printf("Enter the total song in your playlist: ");
        unsigned int playlist;
        scanf(" %d", &playlist);

        //clear input buffer
        while (getchar() != '\n');

        printf("\nAdd songs to your playlist\n");
        char song[playlist][100];

        for (int i = 0; i < playlist; i++)
        {
            printf("Enter song %d: ", i+1);
            fgets(song[i], sizeof(song[i]), stdin);
            song[i][strcspn(song[i], "\n")] = '\0'; //remove the trailing newline character
        }

        printf("\nDo you want to play songs in your playlist? (1 - yes | 0 - no): ");
        scanf("%d", &n);
        printf("\n");

        while (n == 1)
        {
            for (int i = 0; i < playlist; i++)
            {
                printf("%s\n", song[i]);
                playing();
                printf("**************************\n");

                if (i == playlist)
                    break;
            }
            break;
        }
    }
    else
        printf("Sound disabled\n");
    
}


void play_sound()
{
    printf("Playing sound ....\n");
    play_sound();
}

void pause_sound(int signal_num)
{
    printf("Song paused\n");
}

void playing()
{
    const char* frames[] = {
        "playing  ",
        "playing. ",
        "playing..",
        "playing..."
    };

    int sizeFrames = sizeof(frames) / sizeof(frames[0]);
    for (int i = 0; i < 500; i++)
    {
        printf("%s\r", frames[i % sizeFrames]);
        fflush(stdout);
        usleep(500000); //sleep for 0.5 seconds
    }

    printf("\n");
}