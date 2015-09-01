#include <dht.h>
dht DHT;
#include <Console.h>
#include <Process.h>


#define DHT11_PIN 5

const unsigned long postingInterval = 10000;  //delay between updates to xively.com
unsigned long lastRequest = 0;      // when you last made a request
String dataString = "";

static char tbuffer[6];
static char hbuffer[6];

void setup()
{
    Bridge.begin(115200);
    Console.begin(); 

 // while (!Console) {
    ; // wait for Console port to connect.]
   
 // }

}

void updateData() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
     DHT.read11(DHT11_PIN);
    float h = DHT.humidity;
    float t = DHT.temperature;

    if (isnan(t) || isnan(h))
    {
      ;//  Console.println("Failed to read from DHT");
    }
    else
    {
        //print the sensor data in serial monitor
      Console.print("Humidity: ");
       Console.print(h);
     Console.print(" %\t");
       Console.print("Temperature: ");
       Console.print(t);
      
      
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      Console.println(" *C");

       //convert the sensor data from float to string
    dtostrf(t,5, 2, tbuffer);
    dtostrf(h,5, 2, hbuffer);
      
      // convert the readings to a String to send it:
        dataString = "Temperature,";
        
        dataString += tbuffer;
      //add Humidity:
        dataString += "\nHumidity,";
        dataString += hbuffer;
    }
}

// this method makes a HTTP connection to the server:
void sendData() {
 // Console.print("test");
  Process p;
  p.begin(",set_value");
  p.addParameter(tbuffer);
  p.addParameter(hbuffer);
  p.run();
  // If there's incoming data from the net connection,
  // send it out the Serial:
  while (p.available()>0) {
    char c = p.read();
   // Console.write(c);
  }
}

void loop()
{
  // get a timestamp so you can calculate reading and sending intervals:
  long now = millis();
  // if the sending interval has passed since your
  // last connection, then connect again and send data:
  if (now - lastRequest >= postingInterval) {
    updateData();
    sendData();
    lastRequest = now;
  }

}
