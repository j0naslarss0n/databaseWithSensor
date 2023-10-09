package com.grupparbete.sensorwithdatabase.repos;

import com.grupparbete.sensorwithdatabase.models.Jonassensor;
import org.springframework.data.jpa.repository.JpaRepository;

public interface JonasSensorRepo extends JpaRepository<Jonassensor, Long> {
}
