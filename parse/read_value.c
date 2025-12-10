#include "../header/object.h"
#include "../readline/cm_readline.h"
#include <fcntl.h>
#include <unistd.h>

static int ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' || 
        c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

t_scene *object_parsing(t_scene *scene, char *str)
{
    char **split;
    while (ft_isspace(*str))
        str++;
    if (str[0] == '\n' || str[0] == '\0')
        return (scene);
    split = ft_split(str, ' ');
    if(!split || !split[0])
        return scene;
    if(ft_strncmp(split[0],"A",1) == 0)
        scene->ambient = parse_ambient(split);
    else if(ft_strncmp(split[0],"C",1) == 0)
        scene->camera = parse_camera(split);
    else if(ft_strncmp(split[0],"L",1) == 0)
        scene->light = parse_light(split);
    else if(ft_strncmp(split[0],"sp",2) == 0)
        add_object(&(scene->object),new_object(SPHERE, parse_sphere(split)));
    else if(ft_strncmp(split[0],"pl",2) == 0)
        add_object(&(scene->object),new_object(PLANE, parse_plane(split)));
    else if(ft_strncmp(split[0],"cy",2) == 0)
        add_object(&(scene->object),new_object(CYLINDER, parse_cylinder(split)));
    else
        printf_error("invalid object");
    free_split(split);
    return scene;
}

t_scene *read_value(char **argv)
{
    t_scene *scene;
    char *str;
    int fd;

    fd = -1;
    if(ft_strlen(argv[1]) > 3 &&
        ft_strncmp(argv[1] + ft_strlen(argv[1]) -3,".rt",3) == 0)
        fd = open(argv[1],O_RDONLY);
    if(fd < 0)
        printf_error("invalid file");
    str = cm_readline(fd);
    scene = malloc(sizeof(t_scene));
    if(!scene)
        return (NULL);
    scene->object = NULL;
    while(str)
    {            
        scene = object_parsing(scene,str);
        free(str);
        str = cm_readline(fd);
    }
    close(fd);
    return scene;
}