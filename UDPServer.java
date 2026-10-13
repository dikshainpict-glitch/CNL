import java.net.*;
import java.nio.charset.StandardCharsets;

public class UDPServer {
    public static void main(String[] args) {
        int port = 6000;

        try (DatagramSocket serverSocket = new DatagramSocket(port)) {
            System.out.println("UDP Server started...");

            byte[] buffer = new byte[1024];

            while (true) {
                DatagramPacket packet =
                    new DatagramPacket(buffer, buffer.length);

                serverSocket.receive(packet);

                String msg = new String(
                    packet.getData(),
                    packet.getOffset(),
                    packet.getLength(),
                    StandardCharsets.UTF_8
                );

                System.out.println("Client: " + msg);

                if (msg.equalsIgnoreCase("exit")) {
                    break;
                }

                String reply = "Message received by server";

                byte[] response =
                    reply.getBytes(StandardCharsets.UTF_8);

                DatagramPacket responsePacket = new DatagramPacket(
                    response,
                    response.length,
                    packet.getAddress(),
                    packet.getPort()
                );

                serverSocket.send(responsePacket);
            }

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}

