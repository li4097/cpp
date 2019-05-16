/*
 * net.h
 * Copyright (C) 2019 LQ <LQ@localhost.localdomain>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NET_H
#define NET_H


void tcpServer(int port);
void tcpClient(const char* ip,int port);


#endif /* !NET_H */
