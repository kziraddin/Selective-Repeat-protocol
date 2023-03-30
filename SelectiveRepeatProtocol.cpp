#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cstring>
using namespace std;

const int WINDOW_SIZE = 4;
const int TIMEOUT = 5;

struct packet {
    int seq_num;
    bool ack_received;
    string data;
};

int main() {
    srand(time(NULL));

    // Create a list of packets to send
    string message;
    cout << "Enter your message:\n";
    std::getline(std::cin, message);
    cout<< "\n";
    int num_packets = message.size();
    packet packets[num_packets];
    for (int i = 0; i < num_packets; i++) {
        packets[i].seq_num = i;
        packets[i].ack_received = false;
        packets[i].data = message[i];
    }

    // Send packets using GBN protocol
    int base = 0;
    int next_seq_num = 0;
    int i;

    while (base < num_packets) {
        // Send packets in window
        for (int i = base; i < min(base + WINDOW_SIZE, num_packets); i++) {
            if(packets[i].ack_received == false){
                std::cout << "Sending packet: " << packets[i].seq_num << " \"" << message[i]<< "\"" << endl;
            }
        }

        // Wait for ACKs
        int num_acks_received = 0;
        int timeout_count = 0;
        while (num_acks_received < WINDOW_SIZE && timeout_count < TIMEOUT) {
            usleep(1000000); // Wait 1 second
            for (int i = base; i < min(base + WINDOW_SIZE, num_packets); i++) {
                if (packets[i].ack_received == false && rand() % 2 == 1) {
                    cout << "\t\t\tReceived ACK for packet: " << packets[i].seq_num << " \"" << message[i]<< "\""<< endl;
                    packets[i].ack_received = true;
                    num_acks_received++;
                }
            }
            timeout_count++;
        }

        // Resend packets that did not receive an ACK
        for (int i = base; i < min(base + WINDOW_SIZE, num_packets); i++){
            if (packets[i].ack_received == false) {
                    cout << "Timeout occurred, resending packet: " << packets[i].seq_num << " \""<< message[i]<< "\""<< endl;
            }
        }
        // Slide the window
        while (packets[base].ack_received == true) {
            base++;
            next_seq_num++;
        }
    }
    cout<< "\nAll packets has been sent succesfully!"<<endl;
    return 0;
}


/*Selective Repeat protocol is a type of error-control protocol used in computer networks to ensure reliable data transmission 
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
Overall, Selective Repeat is a widely used and effective error-control protocol in modern computer networks. */