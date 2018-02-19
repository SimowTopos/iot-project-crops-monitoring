package com.cultydata.domain;

import java.util.concurrent.TimeUnit;

public class DownStreamPayload {
	
	private String payload;
	
	private String timestamp;
	
	 @Override
	 public String toString() {
		 return payload + " - " + timestamp;
	 }
	 
	 private String milliToNano() {
		 return String.valueOf(TimeUnit.MILLISECONDS.toNanos(Long.valueOf(timestamp))); 
	 }
	 
	 public String toLineProtocol() {
		 return payload + " " + milliToNano();
	 }

}
