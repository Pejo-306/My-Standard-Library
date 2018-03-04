#define REPLACES 4

void strsub(char *str, char *search, char *replace)
{
    char *buffer = (char *)malloc(sizeof(char) *
        (strlen(str)+1 + REPLACES * strlen(replace)));
    strcpy(buffer, "");
    int replaces = 0;
    int offset = 0;
    for (int i = 0, j; i < strlen(str); ++i) {
        for (j = 0; j < strlen(search) && str[i+j] == search[j]; ++j);
        
        if (j == strlen(search)) { // match found
            for (j = 0; j < strlen(replace); ++j)
                buffer[offset+i+j] = replace[j];
            offset += strlen(replace)-1;
            replaces++;
        } else {
            buffer[offset+i] = str[i];
        }

        if (replaces == REPLACES) {
            // allocate more memory
            buffer = (char *)realloc(buffer, sizeof(char) *
                (strlen(str)+strlen(buffer)+1 + REPLACES * strlen(replace)));
            replaces = 0;
        }
    }
    buffer[offset + strlen(str)] = '\0';

    str = (char *)realloc(str, sizeof(char) * (strlen(buffer)+1));
    strcpy(str, buffer);
    free(buffer);
}

