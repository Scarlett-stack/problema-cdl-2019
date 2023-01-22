#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_CODE "/exit"

int main(int argc, char *argv[])
{
    char **text = NULL;                 // array of strings
    char line[BUFSIZ];                  // line buffer while reading from stdin
    char *p;                            // temporal pointer on the input line
    int n = 0;                          // line counter of stdin
    int i;                              // general index
    FILE **fp;                          // array of file pointers

    if (NULL == (fp = (FILE **)malloc((argc - 1) * sizeof(FILE *)))) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    for (i = 1; i < argc; i++) {        // open files in the arguments
        printf("%s\n", argv[i]);
        if (NULL == (fp[i - 1] = fopen(argv[i], "rb"))) {
            perror(argv[i]);
            return EXIT_FAILURE;
        }
    }

    while (fgets(line, BUFSIZ, stdin)) {
        if ((p = strrchr(line, '\n'))) *p = '\0';       // remove trailing newline, if any
        if ((p = strrchr(line, '\r'))) *p = '\0';       // remove trailing cr character, if any
        if (NULL == (text =(char **) realloc(text, (n + 1) * sizeof(char **)))) {
            perror("realloc");
            return EXIT_FAILURE;
        }
        if (NULL == (text[n] = (char *)malloc(strlen(line) + 1))) {
                                                        // allocate memory for the input line
            perror("malloc");
            return EXIT_FAILURE;
        }
        strcpy(text[n], line);
        n++;                                            // increment the line counter
        if (strncmp(line, EXIT_CODE, strlen(EXIT_CODE)) == 0) break;
    }

    // show the input from stdin
    for (i = 0; i < n; i++)
        printf("%s\n", text[i]);

    /*
     * do your processings of the input files here
     */

    // free memory after usage
    for (i = 1; i < argc; i++)
        fclose(fp[i - 1]);
    free(fp);
    for (i = 0; i < n; i++)
        free(text[i]);
    free(text);

    return EXIT_SUCCESS;
}
/*#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    vector<string> filenames;

    // adauga numele de fisiere din linia de comanda
    for (int i = 1; i < argc; i++) {
        filenames.push_back(argv[i]);
    }

    string word_beginning;
    while (true) {
        cout << "Enter the beginning of a word (or '/exit' to quit):" << endl;
        cin >> word_beginning;

        // verifica daca s-a introdus /exit
        if (word_beginning == "/exit") {
            break;
        }

        // parcurge toate fisierele si cauta cuvintele
        for (string filename : filenames) {
            ifstream file(filename);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    // cauta cuvintele care incep cu word_beginning
                    if (line.find(word_beginning) == 0) {
                        cout << line << endl;
                    }
                }
                file.close();
            } else {
                cout << "Failed to open file " << filename << endl;
            }
        }
    }

    return 0;
}
*/
