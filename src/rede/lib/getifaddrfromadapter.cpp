#include "getifaddrfromadapter.h"

#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdlib>

QString
getIfaddrFromAdapter( const QString _adapter )
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    QString
    ifname_tmp;

    QString
    ret;

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        family = ifa->ifa_addr->sa_family;

        ifname_tmp = ifa->ifa_name;

        if ( ifname_tmp == _adapter &&
             (family == AF_INET || family == AF_INET6) )
        {
            s = getnameinfo(ifa->ifa_addr,
                    (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                          sizeof(struct sockaddr_in6),
                    host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0)
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(1);
            }
        ret = host;
        }
    }

    freeifaddrs(ifaddr);

    //funcao bugada... tive que colocar isso aqui na hora da apresentacao pq
    // nao tava pegando o ip certo na rede da uel.

    #ifdef BUG_GETIFADDR
        return "10.1.1.1";
    #else
        return ret;
    #endif
}
