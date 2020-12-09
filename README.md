# Wemos udírna v0.1

## Pod stromečkem 

* Zapoj Wemos modul USB do libovolného PC
* Chvilku počkej
* Koukni na https://192.168.1.1 nebo bráchovi do mobilu

## Doma

Naklonuj tento repositář

Instaluj IDE

* https://www.microsoft.com/cs-cz/p/arduino-ide/9nblggh4rsd8?ocid=badge&rtc=1&activetab=pivot:overviewtab

Začni na

* https://blog.laskarduino.cz/zaciname-s-wemos-d1-mini-s-wifi-modulem-esp8266/

Vem do ruky pájku. 

Hardware k dispozici:

* LasKKit IoT MINI Starter Kit
* Modul převodníku pro termočlánek PT100, MAX31865, SPI
* PT100 platinový teplotní senzor 0.5m, 3 vodiče
* Wemos D1 mini 1-kanál relé shield
* WeMos D1 mini 64X48 OLED displej shield
* WeMos D1 mini dual base shield


## Hints

### GUI

Doporučuji řešení Blynk

* https://blynk.io/
* https://community.blynk.cc/t/wemos-lolin-esp8266-and-relay-misbehaving/34147/2

### Releový modul D1

Releový modul využívá pin D1, který je ale současně používaný pro I2C komunikaci s displayem. 
Řešení je buď

* Přetypovat dle https://github.com/xoseperez/espurna/issues/420
* Přepájet dle https://sharedinventions.com/?p=670

Happy Wemose :)
