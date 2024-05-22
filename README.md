# Variable
In main.cpp change :  
SERVER_PORT  
DISCOVERY_SERVER_IP  
DISCOVERY_SERVER_PORT  

SERVER_PORT is the port the reverse shell will use (the target)  
DISCOVERY_SERVER_IP is the ip (or domain name) your discovery server will be host  
the discovery server is the node server.js program. He is used to keep ip information  
of the target.  
DISCOVERY_SERVER_PORT is the port your discovery server is linked to.  

# server.js
This is the discovery server. It is used to keep trace of the target ip.  
You should host it on a server and launch it with node server.js > ip.txt  
or something like nohup.