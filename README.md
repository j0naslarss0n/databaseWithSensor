 
# DatabaseWithSensor
### Multiple remote sensor monitoring through Hibernate backend &amp; Thymeleaf frontend


This was a group-project at Nackademin to learn more about System Integration.
We were four in the group and each one of us used either a Raspberry pi or an arduino
to setup a temperature sensor and send the data to a remote Mariadb-database.
The data from that database was then retrived and handled by a spring boot/Hibernate program
and presented with html/thymeleaf templates in a browser.

<p><br></p>

## The Setup

![setup](/arkitektur.png)

<p><br></p>

#### All four in the group used different solutions to gather and upload the data.
#### I choose to write a program in C that ran with crontab on Raspbian.

```
if (mysql_real_connect(conn, server, username, password,database, port, NULL, 0) == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    printf("Unable to connect with MySQL server\n");
    finish_with_error(conn); // error handler

```
#### And to push up data to the server.

```
snprintf(buffern, sizeof buffern, "INSERT INTO jonassensor (temperatur) VALUES('%f');",value);
if(mysql_query(conn, buffern)){
    printf("value added to table\n");
    finish_with_error(conn);

```
##### To complile mariaDB-flags are needed.
```
gcc uploadData -o uploadData.c  `mariaDB_config --cflags --libs`
```
<p><br></p>

#### With Spring boot/Hibernate you need to create and map models to tables in the database with the same name and attribute:
```
@Entity
@Data
@Table(name="Jonassensor")
@NoArgsConstructor
public class Jonassensor {

    @Id
    @GeneratedValue
    private Long id;
    private float temperatur;
    //private String date;
    private LocalDateTime tid;

    public Jonassensor(float temperatur, LocalDateTime tid) {
        this.temperatur = temperatur;
        //this.date = date;
        this.tid = tid;
    }
```
<p><br></p>

#### You then create an interface with JpaRepositories to get generated repository implemenations, such as getTemperatureById()
```
public interface JonasSensorRepo extends JpaRepository<Jonassensor,Long> {}
```


<p><br></p>

### The frontend will display several buttons representing functions

![frontend](/frontend.png)

#### Functions included in TempController
* Show Everyones Data
* Show individual Data
* Find/show Latest
* Find/Show top-5 Highest Temperature
* Find/Show top-5 Lowest Temperature


## Thanks to the rest of the team: Frej, Björn and Alexander
