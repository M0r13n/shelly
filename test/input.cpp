#include "gtest/gtest.h"

extern "C" {
#include "input.h"
#include <limits.h>
}


TEST(input, get_current_folder)
{
    ASSERT_FALSE(strcmp(cur_folder(), "test"));
}

TEST(input, change_folder)
{
    char folder_name[30] = "A_FOLDER_WITH_A_NAME";
    set_folder(folder_name);
    ASSERT_FALSE(strcmp(cur_folder(), folder_name));
}

TEST(input, change_folder_path_max)
{
    /* Check for buffer overflow */
    int siz = PATH_MAX + 20;
    char folder_name[siz];
    for (int i = 0; i < siz; i++)
    {
        folder_name[i] = 'A';
    }
    set_folder(folder_name);
    ASSERT_EQ(strlen(cur_folder()), PATH_MAX - 1);
}

TEST(input, empty_folder)
{
    set_folder((char *) "");
    ASSERT_FALSE(strcmp(cur_folder(), "~"));
}

TEST(input, cd_relative)
{
    set_folder((char *) "..");
    ASSERT_FALSE(strstr(cur_folder(), ".."));
}


TEST(input, get_folder)
{
    int buf_siz = 30;
    char folder[buf_siz];
    get_folder(folder, 30);
    set_folder(folder);
    ASSERT_FALSE(strcmp(cur_folder(), folder));
    ASSERT_FALSE(strcmp(cur_folder(), "test"));
    ASSERT_TRUE(strcmp(cur_folder(), "FOLDER"));
}