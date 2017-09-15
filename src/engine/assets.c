/// Assets (source)
/// (c) 2017 Jani Nykänen

#include "assets.h"

#include "SDL2/SDL.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/// Word type
typedef struct
{
    char data [256]; /// Word characters
    Uint8 len; /// Word length
}
WORD;

/// Asset type enum
enum
{
    T_BITMAP = 0,
};

/// Asset type
typedef struct
{
    void* data; /// Asset data
    char* name; /// Asset name
    int type; /// Asset type
}
ASSET;

/// An array of words
static WORD words [65536]; // No more words supported

/// Amount of words
static unsigned int wordCount;

/// Word parse count index
static unsigned int wordIndex;
/// Path
static char* path;
/// Name
static char* name;
/// Asset type
static int assType;
/// Assets array
static ASSET assets[1024];
/// Asset count
static unsigned int assCount;

/// Parse file
/// path File path
/// Returns 0 if success, 1 if error
static int parse_file(const char* path)
{
    // Open file
    FILE* f = fopen(path,"r");
    if(f == NULL)
    {
        printf("Failed to open a file in %s!\n",path);
        return 1;
    }

    // Initialize the first word
    words[0].len = 0;

    // Go through characters
    char ch;
    bool ignore = false;
    while ( (ch = fgetc(f)) != EOF)
    {
        // If comment, ignore until newline
        if(ch == '#')
        {
            ignore = true;
        }

        if(!ignore)
        {
            // If newline or space, move to the next word (if the word length is not 0)
            if(words[wordCount].len != 0 && (ch == '\n' || ch == ' '))
            {
                wordCount ++;
                words[wordCount].len = 0;
            }
            else
            {
                words[wordCount].data[words[wordCount].len] = ch;
                words[wordCount].len ++;
            }
        }
        // If newline and comment, comment ends
        else if(ignore && ch == '\n')
        {
            ignore = false;
        }

        
    }
    
    return 0;
}

/// Load assets from list
/// > 0 on success, 1 on error
static int load_from_list()
{
    wordIndex = 0;
    assCount = 0;
    int i = 0;
    for(; i <= wordCount; i++)
    {
        if(wordIndex == 0)
        {
            char* s = words[i].data;
            if(strcmp(s,"bitmap") == 0)
            {
                assType = T_BITMAP;
                wordIndex = 2;
            }
            
        }
        else
        {
            if(wordIndex == 2)
            {
                name = words[i].data;
            }
            else if(wordIndex == 1)
            {
                path = words[i].data;
                // LOAD!

                if(assType == T_BITMAP)
                {
                    printf("Loading a bitmap called %s ",path);
                    printf("in %s.\n",path);

                    BITMAP* b = load_bitmap(path);
                    if(b == NULL)
                    {
                        return 1;
                    }
                    assets[assCount].data = (void*)b;
                    assets[assCount].type = T_BITMAP;
                    assets[assCount].name = name;
                }

                assCount ++;
            }

            wordIndex --;
        }
    }

    return 0;
}

/// Load assets
int load_assets(const char* path)
{
    // Parse file
    if(parse_file(path) != 0 || load_from_list() != 0)
    {
        return 1;
    }

    return 0;
}

/// Get bitmap by name
BITMAP* get_bitmap(const char* name)
{
    int i = 0;
    for(; i < assCount; i++)
    {
        if(assets[i].type == T_BITMAP && strcmp(assets[i].name,name) == 0)
        {
            return (BITMAP*)assets[i].data;
        }
    }

    return NULL;
}