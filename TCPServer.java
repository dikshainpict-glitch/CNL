import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String[] args) {
        int port = 5000;

        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("TCP Server is waiting for client...");

            try (
                Socket socket = serverSocket.accept();
                BufferedReader in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
                PrintWriter out = new PrintWriter(
                    socket.getOutputStream(), true);
                BufferedReader keyboard = new BufferedReader(
                    new InputStreamReader(System.in))
            ) {
                System.out.println("Client connected!");

                Thread receiver = new Thread(() -> {
                    try {
                        String msg;
                        while ((msg = in.readLine()) != null) {
                            System.out.println("\nClient: " + msg);

                            if (msg.equalsIgnoreCase("exit")) {
                                break;
                            }

                            System.out.print("Server: ");
                        }
                    } catch (IOException e) {
                        System.out.println("Client disconnected.");
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
            }

        } catch (IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }
}