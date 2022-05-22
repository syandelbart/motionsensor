# Motion sensor
## Introduction
The light switches in my house have been getting worse and worse, to the point where the lights wouldn't turn on anymore. When trying to change those light switches, it became clear that the wiring of them was very oldskool and not documented. The fact that there are multiple switches for one single light doesn't make the situation any easier. Newer light switches generally don't use the same wiring as the models we encountered. Getting an electrician to come and clean this mess up is first of all expensive, and secondly doesn't give transparency as we still wouldn't know which wire does what. 

Since we are now in a modern age, I thought of doing things "smart". This started by buying **Philips Hue lights** and connecting them up through a Philips Hue bridge. This worked great. I set up time schemes so that the lights would power on when needed, for example at the evening and such. This was however not optimal. That's how this repo came into existance. I ordered some **PIR motion sensors** and **NodeMCUs V3 (ESP)**, mainly because the stock option was more than double the price. Then I wrote some code to interact with the Philips Hue bridge, and there is that. Now the lights only turn on when motion is detected.

## Choices
There were different choices regarding the hardware that would be used. There were three contenders:
1. Raspberri PI
2. Arduino
3. ESP

A **Raspberri PI** would've been way too overkill and expensive for such a simple application, so that wouldn't be necessary.
An **Arduino** was great for this application. However, due to the fact that the site where I ordered the parts from didn't offer the models I needed, **I went for the ESP**. I ordered the NodeMCU V3 model with Wi-Fi and Bluetooth abilities for obvious reasons.

## Interacting with Philips HUE
### Creating a user
To interact with the Philips HUE bridge, a user is needed. 
For this you need to find the IP of the bridge on your local network, make sure to update the `HUE BRIDGE IP` variable in the code accordingly
1. Navigate to `http://YOUR_BRIDGE_IP/debug/clip.html`
2. POST **URL:** `\api` with **Message Body:** `{"devicetype":"my_hue_app#motionsensor"}` (Alternate names can be used for this)
4. Press the physical bridge button 
5. POST step 2 again
This will return a username in JSON format similar to:
```
[
    {
        "success": {
            "username": "OI31xM2PlF9LwRtKLN2t0cgh9hB4ve5AyN1RS8NM"
        }
    }
]
```
This long string will be necessary for interacting with the bridge. Make sure to update the `HUE BRIDGE USER` variable in the code to the value of `username` in the above JSON text

### Getting information
Getting information from the bridge is easy once the new user has been created.
Generally you access and modify information through `http://YOUR_BRIDGE_IP/api/USERNAME/`. For a full documentation you can refer to the [Philips HUE API](https://developers.meethue.com/develop/hue-api-v2/api-reference/) site. For this application however, only the **lights** are important.

Navigating to `http://YOUR_BRIDGE_IP/api/USERNAME/lights` will output all the lights registered to the bridge in JSON format. Since the output is not very readable, it might be useful to use a JSON formatter before trying to read this. In this data, all the light ids can be found along with their relevant data. Now all that has to happen is deciding which lights you want to interact with.

### Making the code work
After you have the ids of the lights you wish to interact with, you will have to change the code accordingly.
```
int light_ids[] = {};
int light_amount = 0;

bool light_states[] = {false,false};

int light_on_times[] = {60,60}; //in seconds

int light_on_current[] = {0,0};

```
- **light_ids**           all the lights you wish to interact with (comma-seperated)
- **light_amount**        amount of lights you wish to control in total, will be automatic in future update
- **light_states**        defaults to false, makes sure the lights won't turn on when they are already on to reduce overhead
- **light_on_times**      the amount of seconds lights need to stay on individually after switching off again
- **light_on_current**    default to 0, defines the amount of seconds the light has to stay on relative to the current time

When adding more light_ids, make sure to make an entry for them in the other variables as well, otherwise errors will happen. This is something that should be improved in the future, but it is what it is for now.

##Final requirements
Make sure to enter the network SSID and password of the network your bridge is located on.
```
const char *ssid =  "SSID";  
const char *pass =  "WIFI_PASS";
```
Please note that if the network is out-of-range, there is currently no way of getting an indication of this. Make sure there is coverage before you install your sensor.

###To-do list
- [ ] Defining error messages
- [ ] Automatic determine of light_amount
- [ ] Wait with interaction until network connection is achieved after being lost
- [X] Designing a casing (bottom)
- [ ] Printing the casing


