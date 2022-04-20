import paho.mqtt.client as mqtt
import random

client_id = f'python-mqtt-{random.randint(0, 1000)}'
def on_connect(client, userdata, flags, rc):
    topic_group = []
    for i in range(0, 100):
        topic_name = f"icm/test/PubTopic{i}"
        topic_group.append(topic_name)
    print(topic_group)
    for i in range(0, 100):
        client.subscribe(topic_group[i])
    print("Connected with result code: " + str(rc))

def on_message(client, userdata, msg):
    # print(msg.topic + " " + str(msg.payload))
    print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

client = mqtt.Client(client_id)
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set("admin", "password")
client.connect('127.0.0.1', 61613, 600) # 600为keepalive的时间间隔

client.loop_forever() # 保持连接