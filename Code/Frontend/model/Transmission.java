package model;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import controller.App;

public class Transmission 
{
    public static String MessageSend = "";
    public static ServerSocket serverSocket;
    public static Socket clientSocket;
    public static DataOutputStream transmit;
    public static DataInputStream receive;
    public static String PiStatus = "Disconnected";    
    public static String Message = "";
    public static String previousMessage = "1/1/000.1/2/000.1/3/000.1/4/000.1/5/000.1/6/000.2/1/090.2/2/090.2/3/090.2/4/090.2/5/090.2/6/090.";
    public static String currentMessage = "";

    public static void Connect() throws IOException
    {
        try 
        {
            clientSocket = new Socket(App.address, App.port);
            receive = new DataInputStream(System.in);
            transmit = new DataOutputStream(clientSocket.getOutputStream());
            serverSocket = new ServerSocket(App.port);
            clientSocket = serverSocket.accept();
        }
        catch (UnknownHostException u) 
        {
            System.out.print("Connection unsuccsessful: ");
            System.out.println(u);
            //System.exit(0);
        }
        catch (IOException i) 
        {
            System.out.print("Connection unsuccsessful: ");
            System.out.println(i);
            // System.exit(0);
        }
        PiStatus = "Connected";
    }

    public static void Disconnect() throws IOException 
    {
        try 
        {
            clientSocket.close();
            serverSocket.close();
        }
        catch (IOException i) {
            System.out.println(i);
        }
    }

    public static void sendMessage(String message) throws IOException
    {
        try
        {
            transmit.writeUTF(message);
        }
        catch(IOException i)
        {
            System.out.print("Message failed to send");
            System.out.println(i);
        }
    }

    public static String findNew()
    {
        Message = "";
        currentMessage = "";
        for(int i = 0; i < App.Main.numComponents; i++)
        {
            if(i < main.motorCount)
                currentMessage += "1/" + String.format("%s", i+1) + "/" + String.format("%3s", App.Main.getMotorPower(i)).replace(' ', '0') + ".";
                
            else
                currentMessage += "2/" + String.format("%s", i-main.motorCount+1) + "/" + String.format("%3s", App.Main.getServoAngle(i-main.motorCount)).replace(' ', '0') + ".";
        }

        if(currentMessage != previousMessage)
        {
            for(int j = 0; j < App.Main.numComponents * 8; j += 8)
            {
                if(!currentMessage.substring(j, j+8).equals(previousMessage.substring(j, j+8)))
                {
                    Message += currentMessage.substring(j, j+8);
                }
            }
        }
        previousMessage = currentMessage;
        return Message;
    }
    
    public static String getMessageSend()
    {
        return MessageSend;
    }

    public static void updateMessage()
    {
        MessageSend = Transmission.findNew();
    }
}