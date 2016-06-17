/**
*SOCKET°°¥¶¿Ì
*/
#ifndef _SOCKET_UTILS_H_
#define _SOCKET_UTILS_H_

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "Log.h"


int Accept(int fd, struct sockaddr *addr, socklen_t *salenptr);

void Bind(int fd, const struct sockaddr *sa, socklen_t salen);

void Connect(int fd, const struct sockaddr *sa, socklen_t salen);

void Listen(int fd, int backlog);

int Socket(int family, int type, int protocol);

ssize_t Read(int fd, void *ptr, size_t nbytes);

ssize_t Write(int fd, const void *ptr, size_t nbytes);

void Close(int fd);


#endif