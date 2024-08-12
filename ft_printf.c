/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nal-haki <nal-haki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:24:49 by nal-haki          #+#    #+#             */
/*   Updated: 2024/08/12 13:36:35 by nal-haki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void putchar(char *str , int *len){
len =0;
    if (!str)
        return ;
    
    while (*str)
        len+=write(1,str++,1);
    
}

void putdigit(int nbr, int base ,int *len){
    char* hexa = "0123456789abcdef";
    len =0;
    
    if (nbr<0)
    {
     nbr=-nbr;
      len+=write(1,"-",1);
    }   
    if (nbr>= base)
        putdigit(nbr/base);

         len+=write(1,hexa[nbr%base],1);  
    
}

int main(void){
    int len=0;
    char *str= "Hello World";
    
    putchar(str,&len);
}