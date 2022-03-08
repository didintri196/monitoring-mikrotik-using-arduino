
# Monitoring Mikrotik using Arduino + LCD TFT

Monitoring mikrotik using Arduino + LCD TFT dengan menggunakan interface LAN
## Demo

Insert gif or link to demo


## Materials

 - Mikrotik
 - Arduino UNO
 - Arduino Ethernet Shield W5100
 - LAN Cable

## Library Arduino
- [Ethernet](https://github.com/embeddist/WIZ_Ethernet_Library-IDE1.0.5)
- [LCD TFT](https://github.com/JoaoLopesF/SPFD5408)
- [aWOT](https://github.com/lasselukkari/aWOT)

## Installation Arduino

- Plug ethernet shield to Arduino
- Plug TFT LCD to ethernet shield
- Connect Cable Arduino to your port USB Laptop
- Install [Software Arduino](https://www.arduino.cc/en/software) on your PC/Laptop
- Open Software Arduino
- Build Script Monitor-Arduino.ino 
- 
```bash
  npm install my-project
  cd my-project
```
    
## API Reference

#### Get all items

```http
  GET /api/items
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `api_key` | `string` | **Required**. Your API key |

#### Get item

```http
  GET /api/items/${id}
```

| Parameter | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `id`      | `string` | **Required**. Id of item to fetch |
