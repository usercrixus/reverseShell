const net = require('net');

const PORT = 6668; // Port to listen on

const server = net.createServer((socket) => {
    // Extract the client's IP address
    const clientAddress = socket.remoteAddress.replace(/^.*:/, ''); // Extract IPv4 address if it's IPv6-mapped
    const clientPort = socket.remotePort;

    console.log(`Client connected from ${clientAddress}:${clientPort}`);

    socket.on('data', (data) => {
        console.log(`Received message from ${clientAddress}:${clientPort}: ${data.toString()}`);
    });

    socket.on('end', () => {
        console.log(`Client from ${clientAddress}:${clientPort} disconnected`);
    });

    socket.on('error', (err) => {
        console.error(`Error with client ${clientAddress}:${clientPort}: ${err.message}`);
    });
});

server.on('error', (err) => {
    console.error(`Server error: ${err.message}`);
});

server.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});

