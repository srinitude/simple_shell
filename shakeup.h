#ifndef SHAKEUP
#define SHAKEUP
#define HSHPATH "PATH"
#define ENVSIZE 4000

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * struct list_s - singly linked list
 * @data: address to malloc'ed memory
 * @next: points to the next node in linked list
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	void *data;
	struct list_s *next;
} list_t;

/**
 * struct _builtins_s - struct for matching command lines with functions
 * @command: builtin command
 * @f: associated function
 */
typedef struct _builtins_s
{
	char *command;
	void (*f)();
} _builtins_t;

/**
 * struct general_s - struct for shell
 * @isInteractive: flag for interactive mode
 * @_env: environment var
 * @builtins: table of builtins
 * @nCommands: number of commands run by user
 * @head: head of linked list of malloc'ed memory
 */
typedef struct general_s
{
	unsigned int isInteractive;
	char **_env;
	_builtins_t *builtins;
	unsigned int nCommands;
	list_t *head;
} general_t;

_builtins_t *initBuiltins(general_t *genHead);
general_t *initStruct(char **env, general_t *genHead);
int addMemAddress(general_t *genHead, void *ptr);
list_t *addNodeEnd(list_t **head, void *ptr);
list_t *addNode(list_t **head, void *ptr);
size_t printList(general_t *genHead);
char *mallocBuffer(size_t length, general_t *genHead);

int interactiveShell(general_t *genHead);
int nonInteractiveShell(char *buffer, general_t *genHead);
char **tokenize(char *str, char delim[], general_t *genHead);
unsigned int _strlen(const char *str);
char *_strdup(const char *s, general_t *genHead);
char *__strcat(char *dest, char *source);
int _strcmp(char *s1, char *s2);
char *_itoa(unsigned int num);

char *getUserInput(char *buffer, size_t *length, general_t *genHead);
int checkEOF(char *buffer);
char **parseBuffer(char *buffer, general_t *genHead);

void printPrompt(char *prompt);
size_t correctAbsPath(char *token);
char *findCmd(char *b, general_t *genHead);
int createFork(char **bufferTokens, general_t *genHead);
char *createCWDFile(char *file);

char *_getenv(char *name);
void findBuiltin(general_t *vars, char *cmd);
void runEnv(general_t *genHead);
void runExit(general_t *genHead);
void runSetenv(void);
void runUnsetenv(void);
void freeEnv(general_t *genHead);
void freeList(general_t *genHead);
void freeStruct(general_t *genHead);

#endif
