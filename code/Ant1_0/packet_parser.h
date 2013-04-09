#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <winsock.h>


#define FIN 0x01
#define SYN 0x02
#define RST 0x04
#define PSH 0x08
#define ACK 0x10
#define URG 0x20
#define FREE 0x00

typedef struct tagIPHDR
{
    uint8_t ihl:4,
    version:4;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
} IPHDR, *PIPHDR;

typedef struct tagTCPHDR
{
    uint16_t sport;
    uint16_t dport;
    uint32_t seq;
    uint32_t ack;
    uint8_t res;
    uint8_t flags;
    uint16_t win;
    uint16_t check;
    uint16_t urg_ptr;
} TCPHDR, *PTCPHDR;

typedef struct tagUDPHDR
{
    uint16_t sport;
    uint16_t dport;
    uint16_t len;
    uint16_t check;

} UDPHDR,*PUDPHDR;

typedef struct tagEVENT
{
    IPHDR ip;
    union
    {
        //ICMPHDR icmp;
        TCPHDR	tcp;
        //UDPHDR	udp;
    };
    uint8_t rezerved[1024];
}EVENT, *PEVENT;

typedef struct tagPCAPPKTHDR
{
    struct timeval ts;//время захвата
    uint32_t caplen;//сколько байт без этого заголовка записано в файл
    uint32_t len;// размер пакета
} PCAPPKTHDR;


typedef struct tagPCAPFILEHDR
{
    uint32_t magic;//сигнатура 0х1a2b3c4d
    uint16_t version_major;//# версии
    uint16_t version_minor;
    uint32_t thiszone;//отличие от UTC в секундах
    uint32_t sigfigs;//==0
    uint32_t snap_len;//(=68) размер захватываемойчасти пакета ||==MTU
    uint32_t linktype;//# протокола канального уровня
} PCAPFILEHDR;


#endif // PACKET_PARSER_H
