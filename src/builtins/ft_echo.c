#include "../../minishell.h"

// Helper function to check if the argument is a valid '-n' option
int	check_option(char *option)
{
	int	i;

	i = 1;
	// Start at 1 to skip the first '-' and check for 'n' characters
	while (option[i] && option[i] == 'n')
		i++;
	// Return 1 only if all characters after '-' are 'n'
	return (option[i] == '\0');
}

// Function to check if the string is an option starting with '-'
int	check_if_option(char *exec)
{
	if (exec[0] == '-')
		return (check_option(exec));
	return (0);
}

// Function to replace all instances of $$ in a string with the provided PID
char	*replace_dollar_dollar(char *str, pid_t pid)
{
	char	*result;
	int		i;
	int		j;
	int		pid_len;
	char	pid_str[16]; // Buffer to store the PID as a string

	// Convert the PID to a string
	sprintf(pid_str, "%d", pid);
	pid_len = ft_strlen(pid_str);

	// Allocate memory for the result (maximum possible size)
	result = (char *)malloc(ft_strlen(str) * pid_len + 1);
	if (!result)
		return (NULL);

	i = 0;
	j = 0;
	while (str[i])
	{
		// Replace every instance of $$ with the PID
		if (str[i] == '$' && str[i + 1] == '$')
		{
			ft_strlcpy(&result[j], pid_str, pid_len + 1);
			j += pid_len;
			i += 2; // Skip the second $
		}
		// Handle a single $
		else if (str[i] == '$')
		{
			result[j++] = '$';
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	ft_echo(char **exec)
{
	int	n_flag;
	int	i;
	char	*processed_str;
	pid_t pid; // Add a variable to hold the PID

	// Get the current process ID using fork()
	pid = fork();

	// If fork fails
	if (pid < 0)
	{
		perror("fork");
		return -1; // Return an error code
	}

	// If in the child process
	if (pid == 0)
	{
		// You can perform the echo operation here
		i = 1;
		n_flag = 0;

		// Check if there are any '-n' options and skip them
		while (exec && exec[i] && check_if_option(exec[i]))
		{
			n_flag = 1;
			i++;
		}

		// Print the remaining arguments, replacing $$ with PID
		while (exec && exec[i])
		{
			processed_str = replace_dollar_dollar(exec[i], getppid()); // Handle $$ replacement
			printf("%s", processed_str);
			free(processed_str); // Free the dynamically allocated string

			if (exec[i + 1])  // Print space between arguments except after the last one
				printf(" ");
			i++;
		}

		// If the '-n' option was not present, print a newline
		if (!n_flag)
			printf("\n");

		exit(0); // Exit child process
	}

	// Parent process can wait for the child if necessary
	wait(NULL); // Wait for the child process to finish



	return (0);
}
