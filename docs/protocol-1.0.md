# Chat

## Protocol

- Length: 2 bytes
- Protocol version: 2 bytes
- Command: 1 byte
- Rest of data

### Client->Server: Join chat room

- Command: 0x01
- nickname length: 2 byte
- nickname: nickname length bytes of ascii string

### Server->Client: Join chat room result

- Command: 0x01
- Result: 1 byte
    - 0x00: Success
    - 0x01: Nickname already taken error
    - 0x02: Illegal nickname error
    - 0xFF: Unknown error

### Client->Server: Send msg

- Command: 0x02
- length: 2 bytes
- message: length bytes ascii message

### Server->client: Send msg result

- Command: 0x02
- Result: 1 byte
    - 0x00 Success
    - 0xFF Unknown error

### Server->Client: Receive msg

- Command: 0x03
- sender nickname length: 2 bytes
- sender nickname: length bytes of ascii string
- length: 2 bytes
- message: length bytes ascii message

### Server->Client: New user entered channel

- Command: 0x04
- nickname length: 2 bytes
- nickname: length bytes of ascii string

### Client->Server: Disconnect

- Command: 0x05

### Client->Server: Ping

- Command: 0xFF

### Server->Client: Pong

Sent as response to 'ping' command

- Command: 0xFF