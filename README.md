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
