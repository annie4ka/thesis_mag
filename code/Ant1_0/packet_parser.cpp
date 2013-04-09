#include <packet_parser.h>
#include <stdio.h>



int  equal (struct timeval t1, struct timeval t2)
{
    return ((t1.tv_sec==t2.tv_sec)&&(t1.tv_usec==t2.tv_usec));
}

int less_ (struct timeval t1, struct timeval t2)
{
    return ((t1.tv_sec<t2.tv_sec)||((t1.tv_sec==t2.tv_sec)&&(t1.tv_usec<t2.tv_usec)));
}


int greater( struct timeval t1, struct timeval t2)
{
    return !(less_(t1,t2)||equal(t1,t2));
}

double  sub(struct timeval t1, struct timeval t2)
{
    double d;
    int sign;
    struct timeval dif;
    if (less_(t1,t2))
    {
        sign=-1;
        dif=t1;
        t1=t2;
        t2=dif;
    }
    else
        sign=1;
    if (t1.tv_usec<t2.tv_usec)
    {
        dif.tv_usec=1000000-t2.tv_usec+t1.tv_usec;
        ++t2.tv_sec;
    }
    else
        dif.tv_usec=t1.tv_usec-t2.tv_usec;
    dif.tv_sec=t1.tv_sec-t2.tv_sec;
        d=dif.tv_sec+0.000001*dif.tv_usec;
    return (d*sign);
}


void new_IP_pac(FILE* qFile, struct timeval ts,PEVENT pEvent, uint32_t len )
{
    static struct timeval prev_ts;
    static int count = 0;
    static double sum =0;
    if (pEvent->ip.protocol==6)//tcp
    {

        if (((count>=8000)&&(count<=12000))||((count>=15000)&&(count<=18000)))
        {
            fprintf (qFile, "%f %d %d %d %d %d %d %d !\n", sub(ts,prev_ts),len,
                     (bool)(pEvent->tcp.flags&SYN),(bool)(pEvent->tcp.flags&FIN),(bool)(pEvent->tcp.flags&ACK),
                     (bool)(pEvent->tcp.flags&PSH),(bool)(pEvent->tcp.flags&URG),(bool)(pEvent->tcp.flags&RST));
                    ///time_dif, length, syn,fin,ack,psh,urg,rst
        }
        else
            if (count>0)
        {
            fprintf (qFile, "%f %d %d %d %d %d %d %d *\n", sub(ts,prev_ts),len,
                     (bool)(pEvent->tcp.flags&SYN),(bool)(pEvent->tcp.flags&FIN),(bool)(pEvent->tcp.flags&ACK),
                     (bool)(pEvent->tcp.flags&PSH),(bool)(pEvent->tcp.flags&URG),(bool)(pEvent->tcp.flags&RST));
                    ///time_dif, length, syn,fin,ack,psh,urg,rst
        }
        sum+=sub(ts,prev_ts);
        ++ count;
        prev_ts=ts;

    }
    return ;
}

int parse (string read_file, string out_file)
{
    PCAPPKTHDR pkthdr;
    uint32_t SIZE_LINK_HEADER;
    uint8_t buffer[128];
    EVENT event;
    PCAPFILEHDR *pfilehdr;

    FILE* pFile=fopen(read_file.c_str(),"rb");
    if (!pFile)
        cout<<"fail..."<<endl;
    FILE* qFile=fopen(out_file.c_str(),"wb");
    if (!qFile)
        cout<<"fail..."<<endl;


    fread(buffer,sizeof(PCAPFILEHDR),1,pFile);
    pfilehdr=(PCAPFILEHDR*)buffer;
    if(pfilehdr->magic!=0xa1b2c3d4)
    {
        fclose(pFile);
        return 1;
    }
    switch(pfilehdr->linktype)
    {
        case 1:/* Ethernet (10Mb) */
            {SIZE_LINK_HEADER=14;
            }
            break;
        case 113:/* Linuz cooked sockets */
            SIZE_LINK_HEADER=16;
                break;
        default:
            fclose(pFile);
            return 2;
    }
    int All_count = 0;
    while ((!feof(pFile))/*&&(All_count<20000)*/)
    {
        ++All_count;
        fread (&pkthdr, sizeof (PCAPPKTHDR), 1, pFile);
        fread (&buffer, SIZE_LINK_HEADER, 1, pFile);
        fread (&event, pkthdr.caplen - SIZE_LINK_HEADER,1, pFile);
        if (ntohs (*(uint16_t*)(buffer+SIZE_LINK_HEADER-2)) == 0x0800) // ip
        {
          new_IP_pac(qFile,pkthdr.ts,&event,pkthdr.len );
        }
    }


    cout<<"reading from "<<read_file<<"..."<<endl;
    cout<<"writing to "<<out_file<<"..."<<endl;
    cout<< All_count;
    fclose(pFile);
    fclose (qFile);
    return 0;
}
