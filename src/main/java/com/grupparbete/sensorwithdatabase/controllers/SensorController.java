package com.grupparbete.sensorwithdatabase.controllers;

import com.grupparbete.sensorwithdatabase.models.Jonassensor;
import com.grupparbete.sensorwithdatabase.repos.JonasSensorRepo;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("/sensor")
public class SensorController {

    private final JonasSensorRepo jonasSensRepo;


    SensorController(JonasSensorRepo jonasSensorRepo){this.jonasSensRepo = jonasSensorRepo; }

    @RequestMapping("/all")
    public String getAll(Model model) {
        List<Jonassensor> jonasSensList = jonasSensRepo.findAll();
        model.addAttribute("allSensors", jonasSensList);
        model.addAttribute("id", "ID");
        model.addAttribute("temperatur", "Temperaur" );
        model.addAttribute("tid", "Tid" );
        //model.addAttribute("DATE(tid)", "Datum" );

        model.addAttribute("temperatureTitle", "Alla temperaturer");

        return "showjonasSensors";
    }

}
