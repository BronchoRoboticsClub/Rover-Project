package controller;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.IOException;

import model.Transmission;

public class KeyPressListener implements KeyListener
{
    int W = KeyEvent.VK_W, A = KeyEvent.VK_A, S = KeyEvent.VK_S, D = KeyEvent.VK_D;
    int Left = KeyEvent.VK_LEFT, Right = KeyEvent.VK_RIGHT;
    boolean pressed = true, w = false, a = false, s = false, d = false;

    @Override
    public void keyTyped(KeyEvent e) 
    {
        
    }

    @Override
    public void keyPressed(KeyEvent e) 
    {
        int key = e.getKeyCode();
        if(key != W && key != A && key != S && key != D)
        {
            switch(key)
            {
                case KeyEvent.VK_LEFT:
                    App.Main.ServoLeft();
                    Transmission.updateMessage();
                    App.win.updateCanvas();
                    break;
                case KeyEvent.VK_RIGHT:
                    App.Main.ServoRight();
                    Transmission.updateMessage();
                    App.win.updateCanvas();
                    break;
                case KeyEvent.VK_UP:
                    App.Main.SpeedUp();
                    App.win.updateCanvas();
                    break;
                case KeyEvent.VK_DOWN:
                    App.Main.SlowDown();
                    App.win.updateCanvas();
                    break;
                case KeyEvent.VK_M:
                    App.Main.Mode();
                    App.win.updateCanvas();
                    break;
                case KeyEvent.VK_ESCAPE:
                    System.exit(0);
                    break;
            }
        }
            
        else if(key == W || w == pressed)
        {
            if(w != pressed)
            {
                w = pressed;
                App.Main.keyW();
            }
            else if(key == A && a != pressed)
            {
                a = pressed;
                App.Main.keyWA();
            }
            else if(key == D && d != pressed)
            {  
                d = pressed;
                App.Main.keyWD();
            }
        }

        else if(key == S || s == pressed)
        {
            if(s != pressed)
            {
                s = pressed;
                App.Main.keyS();
            }
            else if(key == A && a != pressed)
            {
                a = pressed;
                App.Main.keySKA();
            }
            else if(key == D && d != pressed)
            {  
                d = pressed;
                App.Main.keySD();
            }
        }

        else if(key == A && w != pressed && s != pressed && a != pressed && d != pressed)
        {
            a = pressed;
            App.Main.keyA();
        }

        else if(key == D && w != pressed && s != pressed && d != pressed && a != pressed)
        {
            d = pressed;
            App.Main.keyD();
        }

        if(key == W || key == A || key == S || key == D || key == Left || key == Right)
        {
            Transmission.updateMessage();
            try 
            {
                Transmission.sendMessage(Transmission.getMessageSend());
            }
            catch (IOException i)
            {
                System.out.println(i);
            }
        }
        App.win.updateCanvas();
    }

    @Override
    public void keyReleased(KeyEvent e) 
    {
        int key = e.getKeyCode();
        if((key == W && s != pressed) || (key == S && w != pressed))
        {
            App.Main.releaseKey(key, 0);
            if(key == W)
                w = false;
            else
                s = false;
        }
        a = false;
        d = false;
        
        if(key == A || key == D)
        {
            if(w == pressed)
                App.Main.releaseKey(key, 1);
            else if(s == pressed)
                App.Main.releaseKey(key, 2);
            else
                App.Main.releaseKey(key, 0);
        }
        
        if(key == W || key == A || key == S ||  key == D)
        {
            Transmission.updateMessage();
            try 
            {
                Transmission.sendMessage(Transmission.getMessageSend());
            }
            catch (IOException i)
            {
                System.out.println(i);
            }
        }
        App.win.updateCanvas();
    }
}