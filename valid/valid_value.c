#include "../header/object.h"
#include "../readline/cm_readline.h"
#include <unistd.h>
#include <fcntl.h>

int	is_valid_double(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
		{
			if (str[i] != '\n')
				return (0);
		}
		i++;
	}
	return (1);
}

int check_duplicate(t_scene *scene, char **split)
{
    if (ft_strncmp(split[0], "A", 1) == 0 && scene->amb_count >= 1)
    {
        return 1;
    }
    if (ft_strncmp(split[0], "C", 1) == 0 && scene->cam_count >= 1)
    {
        return 1;
    }
    if (ft_strncmp(split[0], "L", 1) == 0 && scene->light_count >= 1)
    {
        return 1;
    }
    return 0;
}

int check_object(char *str)
{
    while (ft_isspace(*str))
        str++;
    if (*str == '\0' || *str == '\n')
        return (0);
    if (ft_strncmp(str, "A", 1) == 0 && ft_isspace(str[1]))
        return (0);
    else if (ft_strncmp(str, "C", 1) == 0 && ft_isspace(str[1]))
        return (0);
    else if (ft_strncmp(str, "L", 1) == 0 && ft_isspace(str[1]))
        return (0);
    else if (ft_strncmp(str, "sp", 2) == 0 && ft_isspace(str[2]))
        return (0);
    else if (ft_strncmp(str, "pl", 2) == 0 && ft_isspace(str[2]))
        return (0);
    else if (ft_strncmp(str, "cy", 2) == 0 && ft_isspace(str[2]))
        return (0);
    return (1);
}

int valid_vec(char *str)
{
    char **split;
    int i;

    split = ft_split(str, ',');
    if (!split || split_count(split) != 3)
    {
        free_split(split);
        return (0);
    }
    i = 0;
    while (i < 3)
    {
        if (!is_valid_double(split[i]))
        {
            free_split(split);
            return (0);
        }
        i++;
    }
    free_split(split);
    return (1);
}

int valid_unit_vec(char *str)
{
    char **split;
    double val;
    int i;

    split = ft_split(str, ',');
    if (!split || split_count(split) != 3)
    {
        free_split(split);
        return (0);
    }
    i = 0;
    while (i < 3)
    {
        if (!is_valid_double(split[i]))
        {
            free_split(split);
            return (0);
        }
        val = ft_atod(split[i]);
        if (val < -1.0 || val > 1.0)
        {
            free_split(split);
            return (0);
        }
        i++;
    }
    free_split(split);
    return (1);
}

int valid_color(char *str)
{
    char **split;
    double val;
    int i;

    split = ft_split(str, ',');
    if (!split || split_count(split) != 3)
    {
        free_split(split);
        return (0);
    }
    i = 0;
    while (i < 3)
    {
        if (!is_valid_double(split[i]))
        {
            free_split(split);
            return (0);
        }
        val = ft_atod(split[i]);
        if (val < 0.0 || val > 255.0)
        {
            free_split(split);
            return (0);
        }
        i++;
    }
    free_split(split);
    return (1);
}

int valid_ambient(char **split)
{
    int result;
    result = 1;    
    if (split_count(split) != 3)
        return (0);
    if (!is_valid_double(split[1]))
        return (0);
    if (!valid_color(split[2]))
        return (0);
    return (1);
}

int valid_camera(char **split)
{
    int result;
    result = 1;
    if (split_count(split) != 4)
        result = 0;
    if (!valid_vec(split[1]))
        result =0;
    if (!valid_unit_vec(split[2]))
        result = 0;
    if (!is_valid_double(split[3]))
        result = 0;
    return (result);
}

int valid_light(char **split)
{
    if (split_count(split) != 4)
        return (0);
    if (!valid_vec(split[1]))
        return (0);
    if (!is_valid_double(split[2]))
        return (0);
    if (!valid_color(split[3]))
        return (0);
    return (1);
}

int valid_sphere(char **split)
{
    if (split_count(split) != 4)
        return (0);
    if (!valid_vec(split[1]))
        return (0);
    if (!is_valid_double(split[2]))
        return (0);
    if (!valid_color(split[3]))
        return (0);
    return (1);
}

int valid_plane(char **split)
{
    if (split_count(split) != 4)
        return (0);
    if (!valid_vec(split[1]))
        return (0);
    if (!valid_unit_vec(split[2]))
        return (0);
    if (!valid_color(split[3]))
        return (0);
    return (1);
}

int valid_cylinder(char **split)
{
    if (split_count(split) != 6)
        return (0);
    if (!valid_vec(split[1]))
        return (0);
    if (!valid_unit_vec(split[2]))
        return (0);
    if (!is_valid_double(split[3]))
        return (0);
    if (!is_valid_double(split[4]))
        return (0);
    if (!valid_color(split[5]))
        return (0);
    return (1);
}

int valid_element(char **split)
{
    int result;

    result = 0;
    if (ft_strncmp(split[0], "A", 1) == 0)
        result = valid_ambient(split);
    else if (ft_strncmp(split[0], "C", 1) == 0)
        result = valid_camera(split);
    else if (ft_strncmp(split[0], "L", 1) == 0)
        result = valid_light(split);
    else if (ft_strncmp(split[0], "sp", 2) == 0)
        result = valid_sphere(split);
    else if (ft_strncmp(split[0], "pl", 2) == 0)
        result = valid_plane(split);
    else if (ft_strncmp(split[0], "cy", 2) == 0)
        result = valid_cylinder(split);
    return (result);
}

int object_check_parsing(t_scene *scene, char *str)
{
    char **split;
    int result;

    while (ft_isspace(*str))
        str++;
    if (str[0] == '\n' || str[0] == '\0')
        return (0);
    split = ft_split(str, ' ');
    if (!split)
        return (1);
    result = check_duplicate(scene, split);
    result = !valid_element(split);
    if (!result)
    {
        if (ft_strncmp(split[0], "A", 1) == 0)
            scene->amb_count++;
        else if (ft_strncmp(split[0], "C", 1) == 0)
            scene->cam_count++;
        else if (ft_strncmp(split[0], "L", 1) == 0)
            scene->light_count++;
    }
    free_split(split);
    return (result);
}

int valid_value(char **argv)
{
    t_scene *scene;
    char *str;
    int fd;
    int error;

    scene = scene_init();
    fd = open_file(argv);
    if (fd < 0)
    {
        free_scene(scene);
        printf("Error: invalid file\n");
        return (1);
    }
    str = cm_readline(fd);
    error = 0;
    while (str)
    {
        if (check_object(str))
            error = 1;
        if (object_check_parsing(scene, str))
            error = 1;
        free(str);
        if (error)
        {
            while ((str = cm_readline(fd)))
                free(str);
            break;
        }        
        str = cm_readline(fd);
    }
    close(fd);
    if (!error && (scene->amb_count != 1 || scene->cam_count != 1 || scene->light_count != 1))
    {
        printf("Error: missing required elements (A, C, L)\n");
        error = 1;
    }
	fd = open("/dev/null", O_RDONLY);
	if (fd >= 0)
	{
		str = cm_readline(fd);
		if (str)
			free(str);
		close(fd);
	}
    free_scene(scene);
    return (error);
}