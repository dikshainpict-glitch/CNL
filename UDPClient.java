import java.net.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class UDPClient {
    public static void main(String[] args) {
        String host = "localhost";
        int port = 6000;

        try (
            DatagramSocket clientSocket = new DatagramSocket();
            BufferedReader keyboard = new BufferedReader(
                new InputStreamReader(System.in))
        ) {
            clientSocket.setSoTimeout(3000);

            InetAddress address = InetAddress.getByName(host);

            System.out.println("UDP Client started!");

            while (true) {
                System.out.print("Enter message: ");
                String msg = keyboard.readLine();

                if (msg == null) {
                    break;
                }

                byte[] data = msg.getBytes(StandardCharsets.UTF_8);

                DatagramPacket packet = new DatagramPacket(
                    data, data.length, address, port
                );

                clientSocket.send(packet);

                if (msg.equalsIgnoreCase("exit")) {
                    break;
                }

                byte[] buffer = new byte[1024];
                DatagramPacket response = new DatagramPacket(
                    buffer, buffer.length
                );

                try {
                    clientSocket.receive(response);

                    String reply = new String(
                        response.getData(),
                        response.getOffset(),
                        response.getLength(),
                        StandardCharsets.UTF_8
                    );

                    System.out.println("Server: " + reply);

                } catch (SocketTimeoutException e) {
                    System.out.println("No response from server.");
                }
            }

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}