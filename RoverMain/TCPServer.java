import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String args[]) throws Exception {
        String clientSentence;
        String capitalizedSentence;
        ServerSocket welcomeSocket = new ServerSocket(23);
		System.out.println("Waiting for connect");
        while(true) {
            Socket connectionSocket = welcomeSocket.accept();
			System.out.println("Connected!");
            BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            clientSentence = inFromClient.readLine();
			System.out.println(clientSentence);
			float tarLat = 28.582183f;
			String lat = "" + tarLat + '\n';
			float tarLon = -81.202770f;
			String lon = "" + tarLon + '\n';
            capitalizedSentence = clientSentence.toUpperCase() + '\n';
            //outToClient.writeBytes(capitalizedSentence);
			outToClient.writeBytes(lat);
			outToClient.writeBytes(lon);
			
			while(true)
			{
				clientSentence = inFromClient.readLine();
				System.out.println(clientSentence);
			}
        }
    }
}