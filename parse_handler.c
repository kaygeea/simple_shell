#include "simshell.h"

/**
 * is_cmd - a function that determines whether a file is an executable command
 * @info: incoming argument representing the struct list
 * @path: incoming argument for path to file
 *
 * Return: 1 if true, or 0 if otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - a function that duplicates characters
 * @pathstr: incoming argument for the PATH string
 * @start: incoming argument for starting index
 * @stop: incoming argument for stopping index
 *
 * Return: pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start, i < stop; i++)
		if (pathstr[i] != ';')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - a function that searches PATH string for inputed command
 * @info: incoming argument for struct list
 * @pathstr: incoming argument for the PATH string
 * @cmd: incoming argument for the command to be searched for in pathstr
 *
 * Return: full PATH of cmd if found, or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2 && starts_with(cmd, "./")))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++
	}
	return (NULL);
}