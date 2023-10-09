 
/************************************************
 * Uppgift i Systemintegration IoT				
 * vid Nackademin 2023							
 * Ett litet program i C som skickar upp		
 * data mot en mySQL/mariaDB datatbas			
 *												
 ************************************************/
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

// tömmer buffern
void flush(){
        while(getchar() !='\n');
        }

// Avslutar och ger feedback om error.
void finish_with_error(MYSQL *conn){
	fprintf(stderr, "%s\n", mysql_error(conn)); // TODO en logg där det skrivs
	mysql_close(conn);
	flush();
	return 0;
	}


int main(int argc, char **argv)
{


	// Värden/credentials till servern.
        char server [64] = "exampledb.exampledns.org";
    	char username [16] = "name";
    	char password [16] = "password";
    	int port = 3306;
    	char database[16] = "tempDb";
    	char buffern[128];
    	int id;
		char path[50] = "/sys/bus/w1/devices/";
    	char rom[20];
    	char buf[100];
    	DIR *dirp;
    	struct dirent *direntp;
    	int fd =-1;
    	char *temp;
    	float value;
		float temperatur;

	   // Monterar sensor
    system("modprobe w1-gpio");
    system("modprobe w1-therm");

	// Kollar om  /sys/bus/w1/devices/ enheten finns.
    if((dirp = opendir(path)) == NULL)
    {
        printf("opendir error\n");
        return 1;
    }
    // Läser om sensors finns
    while((direntp = readdir(dirp)) != NULL)
    {

        // Kopierar modulens seriernummer
        if(strstr(direntp->d_name,"28-xxxxxxxxx"))
        {
            strcpy(rom,direntp->d_name);

        }
    }
    closedir(dirp);
    // Lägger till strängen om "/w1_slave"
    // och blir "/sys/bus/w1/devices/28-xxxxxxxxx/w1_slave"
    strcat(path,rom);
    strcat(path,"/w1_slave");

	//while(1)		Istället för en loop så körs/skickas data via crontab
    //{
        // Öppna path med read only.
        if((fd = open(path,O_RDONLY)) < 0)
        {
            fprintf(stderr, "Error");
            printf("open error\n");
            return 1;
        }
        // Läser filen
        if(read(fd,buf,sizeof(buf)) < 0)
        {
            printf("read error\n");
            return 1;
        }
        // Läser ut 't'.
        temp = strchr(buf,'t');
        // Läser påföljande efter "t=".
        sscanf(temp,"t=%s",temp);
        // atof: gör om sträng till en float.
        value = atof(temp)/1000;
        printf(" temp : %.2f °C\n",value);

		// Skapar en anslutning till MySQL
    	MYSQL* conn = mysql_init(NULL);

		// Kontrollerar om det är anslutet
    	if (conn == NULL) {
        	printf("MySQL initialization failed");
			finish_with_error();
        	return 1;
    	}

		// Ansluter mot servern
    	if (mysql_real_connect(conn, server, username, password,database, port, NULL, 0) == NULL) {
        	fprintf(stderr, "%s\n", mysql_error(conn));
        	printf("Unable to connect with MySQL server\n");
			finish_with_error(conn);
        	return 1;
    	}
    	// Skriver in värdet i databasen
		snprintf(buffern, sizeof buffern, "INSERT INTO jonassensor (temperatur) VALUES('%f');",value);
    	if(mysql_query(conn, buffern)){
        	printf("value added to table\n");
			finish_with_error(conn);

        }

mysql_close(conn);


return 0;
