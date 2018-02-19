package com.cultydata.service;

import org.influxdb.InfluxDB;
import org.influxdb.dto.Pong;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.support.KafkaHeaders;
import org.springframework.messaging.handler.annotation.Header;
import org.springframework.stereotype.Service;

import com.cultydata.domain.DownStreamPayload;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

@Service
public class StorageServices {
	
	@Autowired
	private InfluxDB influxDB;
	
	final GsonBuilder builder = new GsonBuilder();
	final Gson gson = builder.create();
	 
    @KafkaListener(topics = {"cultydata.sensor.temperature" , "cultydata.sensor.humidity"})
    public void onReceiving(String message, @Header(KafkaHeaders.OFFSET) Integer offset,
                            @Header(KafkaHeaders.RECEIVED_PARTITION_ID) int partition,
                            @Header(KafkaHeaders.RECEIVED_TOPIC) String topic) {
    	
	    	System.out.println("From KFKA : " + topic + "/" + partition + "/" + offset + ":" +  message);
	    	
	    	Pong response = this.influxDB.ping();
	    	if (response.getVersion().equalsIgnoreCase("unknown")) {
	    		System.out.println("Error pinging server.");
	    	}
	    	else {
	    		System.out.println(response.getVersion());	
	    	}
	    
        DownStreamPayload dsp = gson.fromJson(message, DownStreamPayload.class);
        System.out.println(dsp.toLineProtocol());
        
        influxDB.write(dsp.toLineProtocol());
    	
    }

}
    
