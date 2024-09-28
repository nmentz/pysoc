import pysoc

# open socket. example.com resolves to this ip.
site = pysoc.tcpSock4("93.184.215.14", 80) 

# close socket
pysoc.kill_socket(site)
