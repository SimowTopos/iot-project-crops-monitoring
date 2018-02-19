import pygatt
import  binascii
import uuid
from time import sleep

import paho.mqtt.client as mqtt

import logging

logging.basicConfig()
logging.getLogger('pygatt').setLevel(logging.DEBUG)



tempTopic = "cultydata/sensor/temperature"
humTopic = "cultydata/sensor/humidity"
onboardingTopic= "cultydata/admin/humidity"


def pubMqqtLinkSession(link_id, broker_url, temp, hum, port=1883, kalive=60):
    #create connection
    client = mqtt.Client(client_id="link_id", clean_session=True, userdata=None, protocol=mqtt.MQTTv31, transport="tcp")
    client.connect(broker_url, port, kalive)
    #Define callback
    client.on_connect = on_connect
    client.on_message = on_message
    sub(client, tempTopic, humTopic)
    pub(client, tempTopic, temp)
    pub(client, humTopic, hum)
    #client.loop_forever()
    #client.loop(timeout=1.0, max_packets=1)
    #return client

def on_connect(client, object, flags, rc):
    print("Connection OK darling : " + str(object))

def on_message(client, object, flags):
    print("Message sent " + str(flags))

def sub(client, topic_1, topic_2):
    client.subscribe([(topic_1, 0), (topic_2, 2)])

def pub(client, topic, payload=None, qos=0, retain=False):
    client.publish(topic, payload, qos, retain)




def notifyBle(handle, value):
    print("START1")
    globalPayLoad = str(value)
    tabPayload = globalPayLoad.split(';')
    tempPayload = "temperature,host=192.168.1.3,deviceId=00:15:83:10:FD:8D "+tabPayload[0]
    humPayload = "humidity,host=192.168.1.3,deviceId=00:15:83:10:FD:8D "+tabPayload[1]
    print(tempPayload);
    print(humPayload);
    pubMqqtLinkSession("0000FFE1-0000-1000-8000-00805F9B34FB", "192.168.1.3", tempPayload, humPayload)
    print("END1")

adapter = pygatt.GATTToolBackend()


adapter.start()
device = adapter.connect('00:15:83:10:FD:8D')
device.subscribe("0000FFE1-0000-1000-8000-00805F9B34FB", callback=notifyBle)

while True:
    if(False):
        break;

#sleep(60)
#adapter.stop()