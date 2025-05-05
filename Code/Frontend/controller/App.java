package controller;

import java.io.IOException;

import javax.swing.JFrame;
import view.AppWindow;
import model.main;
import model.Transmission;

public class App
{
    public static final String address = "10.0.0.3";
    public static final int port = 65432;

    public static AppWindow win = new AppWindow();
    public static main Main = new main();
    public static Transmission server = new Transmission();

    public static void main(String[] args) throws IOException
    {
        win.init();
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        win.setUndecorated(true);
        win.setLocation(0,0);
        win.pack();
        win.setVisible(true);
        Transmission.Connect();
        Transmission.getMessageSend();
    }
}