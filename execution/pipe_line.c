/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:14:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/04 13:56:36 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int no_input_commands(char *command)
{
    if (!strcmp(command,"ls"))
    {
        return(1);
    }
    return(0);
        
}
static void error_handling(int return_value,char *failed_function)
{
    if(return_value==-1)
    {
        if(!strcmp(failed_function, "close"))
            perror("close failed\n");
        if(!strcmp(failed_function, "dup2"))
            perror("dup2 failed\n");
        if(!strcmp(failed_function, "fork"))
            perror("fork failed\n");
        exit(1);
    }
} 
static void pipe_line(t_tree *tree, char **PWD, char **OLDPWD)
{
    int fd[2];
    int pid[2];
    
    (1 && pipe(fd), (pid[0] = fork()), error_handling(pid[0], "fork"));
    if (pid[0] == 0)
    {
        error_handling(close(fd[0]), "close");
        error_handling(dup2(fd[1], STDOUT_FILENO), "dup2");
        recursion(tree->data.pipe.rtree, PWD,OLDPWD);
        error_handling(close(fd[1]), "close");
        exit(0);
    }
    (1 && (pid[1] = fork()), error_handling(pid[1], "fork"));
    if (pid[1] == 0) 
    {
        error_handling(close(fd[1]), "close");
        error_handling(dup2(fd[0], STDIN_FILENO), "dup2");
        recursion(tree->data.pipe.ltree, PWD,OLDPWD);
        error_handling(close(fd[0]), "close");
        exit(0);
    }
    error_handling(close(fd[0]), "close");
    error_handling(close(fd[1]), "close");
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
}
void recursion(t_tree *tree, char **PWD, char **OLDPWD)
{
   
    int pid;
    static int flag;
    int fd;
    int original_in;
    int original_out;

    if (!tree) 
        return;
    if (tree->type == 0) 
    {
        if(flag == 0)
        {
            pid =fork();
            if(pid == 0)
            {
                execution_entery(tree->data.argv, PWD, OLDPWD);
                exit(0);
            }
            waitpid(pid,NULL,0);
        }
        else
        {
            execution_entery(tree->data.argv, PWD, OLDPWD);
            exit(0);
        }
    }
    else if (tree->type == 1)
    {
        flag = 1;
        pipe_line(tree, PWD, OLDPWD);
        flag = 0;
    }
    else if (tree->type == 2)
    {
        if(access((tree->data.red.file.name), F_OK) == 0)
        {
            original_in=dup(STDIN_FILENO);
            fd = open(tree->data.red.file.name, O_RDONLY);
            dup2(fd,STDIN_FILENO);
            recursion(tree->data.red.ntree, PWD, OLDPWD);
            close(fd);
            dup2(original_in,STDIN_FILENO);
            close(original_in);
        }
        else
            printf("error file not found\n");
    }
    else if (tree->type == 3)
    {
        if(access((tree->data.red.file.name), F_OK) == 0)
        {
            fd = open(tree->data.red.file.name,O_WRONLY);
        }
        else
        {
            fd = open(tree->data.red.file.name, O_CREAT | O_RDWR);
            if(fd <0)
                printf("error\n");
        }
        original_out=dup(STDOUT_FILENO);
        dup2(fd,STDOUT_FILENO);
        close(fd);
        recursion(tree->data.red.ntree, PWD, OLDPWD);
        dup2(original_out,STDOUT_FILENO);
        close(original_out);
    }

    else if (tree->type == 4)
    {
        original_in=dup(STDIN_FILENO);
        dup2(tree->data.red.file.fd, STDIN_FILENO);
        recursion(tree->data.red.ntree, PWD, OLDPWD);
        close(tree->data.red.file.fd);
        dup2(original_in, STDIN_FILENO);
        close(original_in);
    }
    else if(tree->type == 5)
    {
        original_out=dup(STDOUT_FILENO);
        if(access(tree->data.red.file.name, F_OK)==0)
            fd = open(tree->data.red.file.name, O_WRONLY|O_APPEND);
        else
            fd = open(tree->data.red.file.name, O_CREAT|O_WRONLY|O_APPEND);
        dup2(fd,STDOUT_FILENO);
        recursion(tree->data.red.ntree, PWD, OLDPWD);
        close(fd);
        dup2(original_out,STDOUT_FILENO);
        close(original_out);
    }
}

// #include "../minishell.h"

// static int no_input_commands(char *command) {
//     if (!strcmp(command, "ls")) {
//         printf("l9inaha\n");
//         return (1);
//     }
//     return (0);
// }

// static void pipe_line(t_tree *tree, char **PWD, char **OLDPWD) {
//     int fd[2];
//     int pid[2];
    
//     pipe(fd);
    
//     // Right side of pipe (writes to pipe) - your rtree is the producer
//     pid[0] = fork();
//     if (pid[0] == 0) {
//         close(fd[0]);  // Close read end
//         dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to write end
//         close(fd[1]);
//         recursion(tree->data.pipe.rtree, PWD, OLDPWD);  // Execute RIGHT side (producer)
//         exit(0);  // Important: exit after execution
//     }
    
//     // Left side of pipe (reads from pipe) - your ltree is the consumer
//     pid[1] = fork();
//     if (pid[1] == 0) {
//         close(fd[1]);  // Close write end
//         dup2(fd[0], STDIN_FILENO);   // Redirect stdin to read end
//         close(fd[0]);
//         recursion(tree->data.pipe.ltree, PWD, OLDPWD);  // Execute LEFT side (consumer)
//         exit(0);  // Important: exit after execution
//     }
    
//     // Parent process closes both ends and waits
//     close(fd[0]);
//     close(fd[1]);
//     waitpid(pid[0], NULL, 0);
//     waitpid(pid[1], NULL, 0);
// }

// void recursion(t_tree *tree, char **PWD, char **OLDPWD) {
//     int pid;
    
//     if (!tree)
//         return;
    
//     if (tree->type == 0) {  // Command node
//         // Always fork for commands to maintain proper process isolation
//         pid = fork();
//         if (pid == 0) {
//             execution_entery(tree->data.argv, PWD, OLDPWD);
//             exit(0);  // Make sure child exits
//         }
//         waitpid(pid, NULL, 0);
//     }
//     else if (tree->type == 1) {  // Pipe node
//         pipe_line(tree, PWD, OLDPWD);
//     }
// }