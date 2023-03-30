# Selective Repeat Protocol implementation in C++

Selective Repeat protocol is a type of error-control protocol used in computer networks to ensure reliable data transmission 
over unreliable networks. It is a variant of the Go-Back-N protocol.
In the Selective Repeat protocol, the sender can transmit multiple packets without waiting for an acknowledgment for each packet. 
The receiver buffers out-of-order packets until a missing packet is received, at which point it sends a selective acknowledgment 
(SACK) to the sender indicating which packets have been received successfully.
The sender maintains a window of packets that have been transmitted but not yet acknowledged. 
If a packet is not acknowledged within a certain time period, the sender retransmits the packet.
One of the advantages of Selective Repeat over Go-Back-N is that it allows for more efficient use of network bandwidth. 
In Go-Back-N, if a packet is lost or damaged, all subsequent packets in the window are also retransmitted, 
even if they have already been successfully received by the receiver. In Selective Repeat, only the missing packet is retransmitted, 
reducing unnecessary retransmissions and improving network efficiency.However, Selective Repeat requires more complex buffering 
and processing at the receiver compared to Go-Back-N. It is also more susceptible to errors caused by packet duplication, 
as the receiver may erroneously accept a duplicated packet as a missing packet and send a SACK that triggers unnecessary retransmissions.
Overall, Selective Repeat is a widely used and effective error-control protocol in modern computer networks.
