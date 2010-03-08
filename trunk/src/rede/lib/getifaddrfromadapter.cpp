#include "getifaddrfromadapter.h"

#include <stdio.h>

#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

#include <arpa/inet.h>

QString
getIfaddrFromAdapter( const QString _adapter )
{
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    /* I want IP address attached to "eth0" */
    strncpy(ifr.ifr_name, _adapter.toAscii(), IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    QString ret = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

    return ret;
}
