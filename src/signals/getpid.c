/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:13:31 by nal-haki          #+#    #+#             */
/*   Updated: 2024/09/30 17:34:21 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../minishell.h" 

pid_t fetch_current_pid() {
    // Open the /proc/self/stat file to read process information
    FILE *stat_file = fopen("/proc/self/stat", "r");
    if (stat_file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    // The first field in /proc/self/stat is the PID
    fscanf(stat_file, "%d", &pid);
    fclose(stat_file);

    return pid;
}

