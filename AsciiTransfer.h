#ifndef __ASCIITRANSFER_H
#define __ASCIITRANSFER_H

/** Simple ASCII file transmission
 * Intended for use over a reliable connection
 *
 * Protocol:
 * 1a. SENDER    initiates send, wait for SOF
 * 1b. RECEIVER  sends SOF
 * 2a. SENDER    sends local filename followed by \n
 * 2b. RECEIVER  attempts to open filename sent by SENDER
 * 3a. SENDER    waits for ACK/NACK
 * 3b. RECEIVER  sends ACK if file open successful, NACK otherwise
 * 4a. SENDER    begins sending file contents, line by line
 * 4b. RECEIVER  receives and writes file contents into new filename
 * 5a. SENDER    sends EOT when done sending file contents
 * 5b. RECEIVER  closes file and terminates when EOT received.
 */

class AsciiTransfer {
public:
    /// sends the specified file
    int send(char *file);

    /// recevies a file (filename given by sender)
    int recv();
};

#endif
