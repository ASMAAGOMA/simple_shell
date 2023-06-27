#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3
#define LOWERCASE_CONVERTER 1
#define UNSIGNED_CONVERTER 2
#define USING_GETLINE 0
#define USING_STRTOK 0
#define HISTORY_FILE "simple_shell_history"
#define HISTORY_MAXIMUM 4096

extern char **environ;

/**
 * struct liststring - linked list
 * @number: numder
 * @string: string
 * @next: pointer that pointd to the next node
 */

typedef struct liststring
{
	int number;
	char *string;
	struct liststring *next;
} list_t;

/**
 * struct passing_information - containing arguments to pass into a function
 * @arg :string from getline
 * @argv: array of strings
 * @path: path for the command
 * @argc: arg count
 * @line_counter: err count
 * @fname: file name
 * @environment: copy of environ
 * @history: his node
 * @alias: aliasnode
 * @env_changed: chases the environment change
 * @status: return status
 * @command_buffer: command_buffer
 * @command_buffer_type: command_buffer_type
 * @read_file_discriptor: file discriptor to read input
 * @history_count: history number line counter
 * @error_number: error code for the exit
 * @line_count_flag: count current line
 * @environ: copy of environ
 */

typedef struct passing_information
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_counter;
	int error_number;
	int line_count_flag;
	char *fname;
	list_t *environment;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **command_buffer;
	int command_buffer_type;
	int read_file_discriptor;
	int history_count;
} information_t;

#define INFORMATION_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtinpart - have builtin string
 * @type: builtin flag
 * @function: function
 */

typedef struct builtinpart
{
	char *type;
	int (*function)(information_t *);
} builtins_taple;

/*strings.c_file*/
int string_length(char *string);
int string_cmp(char *string1, char *string2);
char *string_cat(char *dest, char *src);
char *starting(const char *hay, const char *need);

/*strings_2.c_file*/
char *string_copy(char *dest, char *src);
char *string_duplication(const char *string);

/*_putchar.c_file*/
int _putchar(char c);
void _puts(char *string);

/*strings_3.c_file*/
char *string_n_copy(char *dest, char *src, int m);
char *string_n_cat(char *dest, char *src, int m);
char *string_char(char *string, char c);

/*strings_4.c_file*/
char **string_split(char *string, char *delimeter);
char **string_split2(char *string, char delimeter);

/*all_about_memory_file*/
int pointer_free(void **pointer);
void *memory_reallocation(void *pointer, unsigned int old, unsigned int new);
char *memory_setting(char *m, char byte, unsigned int amount);
void string_free(char **ss);

/*interactive_mode_file*/
int is_interact(information_t *information);
int is_delimeter(char s, char *delimeter);
int alphabetic(int s);
int my_atoi(char *string);

/*interactive_mode_2_file*/
int print_decimal(int in, int file_descriptor);
void error_printer(information_t *information, char *error_message);
int rev_atoi(char *string);
char *number_converter(long int number, int b, int f);
void comments_remover(char *buffer);

/*error_funcs_file*/
void error_puts(char *string);
int error_putchar (char c);
int puts_file_descriptor(char *string, int file_descriptor);
int put_file_descriptor(char ch, int file_descriptor);

/*linked_lists_file*/
list_t *add_node_start(list_t **h, const char *string, int n);
list_t *add_node_at_end(list_t **h, const char *string, int n);
void list_free(list_t **h_pointer);
int delete_node_index(list_t **h, unsigned int i);
int print_string_list(const list_t *head);

/*linked_lists_2_file*/
ssize_t getting_index(list_t *h, list_t *n);
list_t *starts_the_node(list_t *n, char *pre, char next_c);
size_t list_printer(const list_t *head);
char **list_strings(list_t *h);
size_t list_length(const list_t *head);

/*main_function*/
int main(int ac, char **av);

/*information_file*/
void freedom(information_t *information, int e);
void information_setting(information_t *information, char **av);
void information_clearing(information_t *information);

/**environmet_file*/
int the_environment(information_t *information);
int environ_population(information_t *information);
int unsetting_environ(information_t *information);
int setting_environ(information_t *information);
char *getting_environment(information_t *information, char *na);

/*environmet_2_file*/
int my_unsetting_environ(information_t *information, char *variable);
char **environment_getting(information_t *information);
int setting_the_environ(information_t *information, char *variable, char *v);

/*input_output_file*/
char *his_file(information_t *information);
int his_write(information_t *information);
int his_read(information_t *information);
int building_list(information_t *information, char *buffer, int lc);
int renumbering(information_t *information);

/*shell_exit*/
int exit_shell(information_t *information);
int change_directory(information_t *i);
int the_h(information_t *information);

/*shell_exit_2*/
int history_display(information_t *information);
int alias_unsetting(information_t *information, char *string);
int alias_printer(list_t *node);
int alias_setting(information_t *information, char *string);
int mimic_alias(information_t *information);

/*command_file*/
int executable_command(information_t *information, char *p);
char *chars_duplication(char *p, int s, int e);
char *p_finder(information_t *information, char *ps, char *command);

/*check_file*/
int have_ch(information_t *information, char *buffer, size_t *possition);
void ch_checker(information_t *information, char *buffer,
	size_t *possition, size_t t, size_t l);
int alias_replacement(information_t *information);
int variable_replacement(information_t *information);
int string_replacement(char **o, char *n);

/**shell_g_l*/
ssize_t buf_in(information_t *information, char **buffer, size_t *l);
void s_h(__attribute__((unused))int s_n);
ssize_t in_getting(information_t *information);
ssize_t buffer_r(information_t *information, char *buffer, size_t *t);
int g_t(information_t *information, char **pointer, size_t *l);

/**the_e_file*/
int my_hsh(information_t *information, char **vector);
int bi_finder(information_t *information);
void command_f(information_t *information);
void command_finder(information_t *information);

#endif
