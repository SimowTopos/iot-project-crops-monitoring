package com.cultydata.controller;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class Hello {

    @RequestMapping("/index")
    public String index() {
        return "Greetings from Spring Boot!";
    }
    
    
    

}
