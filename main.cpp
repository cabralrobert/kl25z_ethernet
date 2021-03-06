#include <mbed.h>
#include <WIZnetInterface.h>
#include <Glucometer.h>

#define ECHO_SERVER_PORT   80

SPI spi(PTD2, PTD3, PTD1); // mosi, miso, sclk
WIZnetInterface eth(&spi, PTD0, PTA4); // spi, cs, reset
Serial pc(PTA2,PTA1,115200);
DigitalOut led(PTB0);
Glucometer gluc(D5);

void f_ethernet_init(void);


const char * IP_Addr    = "192.168.0.2";
const char * IP_Subnet  = "255.255.255.0";
const char * IP_Gateway = "192.168.0.1";
int ret,dummy;
int lv=1;


char a[]={"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"};
char b[]={"<html>\r\n<body>\r\n"};
char c[]={"<title>Tele Diabetes</title>\r\n"};
char d[]={"<h2>Tele Diabetes </h2>\r\n"};
char e[]={"<br /><hr>\r\n"};
char f[]={"<FONT FACE=\"Arial\" SIZE=\"2\" COLOR=\"FF0000\">"};

char paq_en[32];



int main()
{
    f_ethernet_init();
    TCPSocketServer server;
    server.bind(ECHO_SERVER_PORT);
    server.listen();
    pc.printf("\nEsperando conexion con cliente...\n");
    TCPSocketConnection client;
    while(lv)
    {
        lv=server.accept(client);
        if(!lv)
        {
           pc.printf("Cliente conectado: %s\n", client.get_address());

        }
        else
        {
           wait(10);
        }
    }


           client.send(a,sizeof(a));
           client.send(b,sizeof(b));
           client.send(c,sizeof(c));
           client.send(d,sizeof(d));
           client.send(e,sizeof(e));
           client.send(f,sizeof(f));




    while(1)
    {
      dummy++;
      sprintf(paq_en,"<FONT><br>Contador=%d</FONT>",dummy);
      client.send(paq_en,sizeof(paq_en));
      wait(1);
    }
}

void f_ethernet_init()
{
     uint8_t mac[]={0x00,0x08,0xDC,0x1C,0xAA,0xCA};
   // mbed_mac_address((char *)mac);
    pc.printf("\tIniciando Servidor Ethernet...\n\r");
    wait(1);
    ret = eth.init(mac, IP_Addr, IP_Subnet, IP_Gateway);
    if(!ret)
    {
        pc.printf("Inicializado, MAC= %s\n\r",eth.getMACAddress());
    }
    else
    {
        pc.printf("Fallo comunicacion... Reinicie dispositivos...\n\r");
    }
    pc.printf("Conectando.");
    wait(2);
    pc.printf(".");
    wait(2);
    pc.printf(".\n\r");
    wait(1);
    ret = eth.connect();
    if(!ret)
    {
        pc.printf("Conexion Establecida!\n\n\r");
        wait(1);
        pc.printf("IP=%s\n\rMASK=%s\n\rGW=%s\n\r",eth.getIPAddress(), eth.getNetworkMask(), eth.getGateway());
    }
    else
    {
        pc.printf("Fallo conexion... Reinicie dispositivos...\n\r");
    }
}
