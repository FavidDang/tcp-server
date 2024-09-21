import socket

def send_filenames_to_server(server_host, server_port, filenames_file):
    # Create a TCP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        # Connect to the server
        client_socket.connect((server_host, server_port))
        
        try:
            # Open the file that contains the list of filenames
            with open(filenames_file, 'r') as f:
                for filename in f:
                    filename = filename.strip()  # Remove any extra whitespace/newlines
                    if filename:
                        print(filename)
                        # Send the filename over the socket
                        client_socket.sendall(filename.encode())
                        print(f"Sent filename {filename} to the server.")

                        # Wait for the server's response
                        response = client_socket.recv(1024).decode()  # Receive up to 1024 bytes
                        print(f"Response from server for {filename}: {response}")
        except Exception as e:
            print(f"An error occurred: {e}")

# Example usage
send_filenames_to_server('localhost', 8080, 'filenames.txt')
