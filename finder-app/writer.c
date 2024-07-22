#include <stdio.h>
#include <string.h>
#include <syslog.h>

static const int EXIT_ERROR = 1;

/// @brief @c main() excluding the resource clean-up.
/// @param argv Command-line arguments.
/// @param file @c FILE pointer to the text.
/// @return The return value for @c main()
static int RunMain(const char *argv[], FILE *file)
{
    const char *writefile = argv[1];
    const char *writestr = argv[2];
    const size_t writestr_len = strlen(writestr);

    file = fopen(writefile, "w");
    if (!file)
    {
        syslog(LOG_USER, "Failed to open the file '%s'", writefile);
        return EXIT_ERROR;
    }
    if (fwrite(writestr, sizeof(char), writestr_len, file) != writestr_len)
    {
        syslog(LOG_USER, "Failed to write the string '%s' to the file '%s'", writestr, writefile);
        return EXIT_ERROR;
    }
    return 0;
}

int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        syslog(LOG_USER, "Invalid number of command-line arguments");
        return EXIT_ERROR;
    }

    FILE *file = NULL;

    int return_value = RunMain(argv, file);

    // Clean-up
    if (file && fclose(file))
    {
        syslog(LOG_USER, "Failed to close the file");
        return_value = EXIT_ERROR;
    }

    return return_value;
}
