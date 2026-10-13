import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) {
        String host = "localhost";
        int port = 5000;

        try (
            Socket socket = new Socket(host, port);
            BufferedReader in = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(
                socket.getOutputStream(), true);
            BufferedReader keyboard = new BufferedReader(
                new InputStreamReader(System.in))
        ) {
            System.out.println("Connected to TCP Server!");

            Thread receiver = new Thread(() -> {
                try {
                    String msg;
                    while ((msg = in.readLine()) != null) {
                        System.out.println("\nServer: " + msg);

                        if (msg.equalsIgnoreCase("exit")) {
                            break;
                        }

                        System.out.print("Client: ");
                    }
                } catch (IOException e) {
                    System.out.println("Connection closed.");
                }
            });

            receiver.setDaemon(true);
            receiver.start();

            String msg;
            while ((msg = keyboard.readLine()) != null) {
                out.println(msg);

                if (msg.equalsIgnoreCase("exit")) {
                    break;
                }
            }

        } catch (IOException e) {
            System.out.println("Client error: " + e.getMessage());
        }
    }
}