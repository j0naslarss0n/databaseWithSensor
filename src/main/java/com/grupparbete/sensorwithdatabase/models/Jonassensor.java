package com.grupparbete.sensorwithdatabase.models;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.sql.Timestamp;
import java.time.LocalDateTime;


@Entity
@Data
@Table(name="Jonassensor") // Blev probelem
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
}
