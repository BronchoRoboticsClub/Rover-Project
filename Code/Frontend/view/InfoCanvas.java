package view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;

import controller.App;
import model.Transmission;
import model.main;

public class InfoCanvas extends JPanel
{    
    public static final int WIDTH = 1536;
    public static final int HEIGHT = 864;

    public static String canvasMode = "dark";

    public int motorSection = 20;
    public int servoSection = 250;
    public int connectionSection = 700;
    public InfoCanvas()
    {
        setPreferredSize(new Dimension(WIDTH, HEIGHT));
    }

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;  
        if(canvasMode == "gray")
        {
            setBackground(Color.GRAY);
            g2.setColor(Color.BLACK);
        }
        else if(canvasMode == "light")
        {
            setBackground(Color.white);
            g2.setColor(Color.black);
        }
        else if(canvasMode == "dark")
        {
            setBackground(Color.black);
            g2.setColor(Color.white);
        }  
        drawInfoBox(g2);
        drawInfo(g2);
    }

    public void drawInfoBox(Graphics2D g2)
    {
        g2.setFont(new Font("Courier New", Font.BOLD, 14));
        g2.drawLine(260, 0, 260 , HEIGHT);
        g2.drawLine(0, servoSection, 260, servoSection);
        g2.drawLine(0, connectionSection, 260, connectionSection);
    }
    public void drawInfo(Graphics2D g2)
    {
        g2.setFont(new Font("Courier New", Font.BOLD, 14));
        g2.drawString("Motors:", 10 , motorSection);
        g2.drawString("Speed: " + App.Main.getSpeed(), 20, motorSection+20);
        for(int i = 0; i < main.motorCount; i++)
        {
            g2.drawString("Motor " + (i+1) + ": ", 20, motorSection+25+(i+1)*25);
            g2.drawString(App.Main.getMotorPower(i) + "", 170, motorSection+25+(i+1)*25);
            // g2.drawString(App.enc.getMotorValue(i), 300, motorSection+25+(i+1)*25);

        }

        g2.drawString("Servos:", 10 , servoSection + 30);
        for(int i = 0; i < main.servoCount; i++)
        {
            g2.drawString("Servo " + (i+1) + ": ", 20, (servoSection+30)+(i+1)*25);
            g2.drawString(App.Main.getServoAngle(i) + "", 170, (servoSection+30)+(i+1)*25);
            // g2.drawString(App.enc.getServoValue(i), 300, (servoSection+30)+(i+1)*25);
        }

        g2.drawString("Connections:", 10, connectionSection+30);
        g2.drawString("Raspberry Pi:  " + Transmission.PiStatus, 10, connectionSection+60);
        
        g2.drawString("Message: " + Transmission.getMessageSend(), 300, 300);
       }
}
