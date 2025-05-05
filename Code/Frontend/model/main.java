package model;

import view.InfoCanvas;

public class main
{
    public static final int motorCount = 6;
    public static final int servoCount = 6;
    public final int numComponents = motorCount + servoCount;
    int motors[] = {0, 0, 0, 0, 0, 0};
    int servos[] = {90, 90, 90, 90, 90, 90};
    int MotorNum = 0;
    int ServoNum = 0;
    public int speed = 0;

    public void keyW()
    {
        for(int i = 0; i < motorCount; i++)
            motors[i] = speed;
    }
    public void keyA()
    {
        for(int i = 0; i < motorCount-3; i++)
            motors[i] = speed;
        for(int i = 3; i < motorCount; i++)
            motors[i] = -1 * speed;
    }
    public void keyS()
    {
        for(int i = 0; i < motorCount; i++)
            motors[i] = -1 * speed;
    }
    public void keyD()
    {
        for(int i = 0; i < motorCount-3; i++)
            motors[i] = -1 * speed;
        for(int i = 3; i < motorCount; i++)
            motors[i] = speed;
    }

    public void keyWA()
    {
        for(int i = 0; i < motorCount-3; i++)
            motors[i] = speed;
        for(int i = 3; i < motorCount; i++)
            motors[i] = speed/2;
    }

    public void keyWD()
    {
        for(int i = 0; i < motorCount-3; i++)
            motors[i] = speed/2;
        for(int i = 3; i < motorCount; i++)
            motors[i] = speed;
    }
    
    public void keySKA()
    {
        for(int i = 0; i < motorCount-3; i++)
            motors[i] = -1 * speed/2;
        for(int i = 3; i < motorCount; i++)
            motors[i] = -1 * speed;
    }

    public void keySD()
    {
        for(int i = 0; i < motorCount-3; i++)
            motors[i] = -1 * speed;
        for(int i = 3; i < motorCount; i++)
            motors[i] = -1 * speed/2;
    }

    public void SpeedUp()
    {
        if(speed < 250)
            speed+=1;
    }
    public void SlowDown()
    {
        if(speed > 0)
            speed-=1;
    }
    public void releaseKey(int k, int t)
    {
        System.out.println(t);
        if(t == 0)
            for(int i = 0; i < motorCount; i++)
                motors[i] = 0;
        if(t == 1)
        {
            for(int i = 0; i < motorCount; i++)
                motors[i] = speed;
        }
        else if(t == 2)
            for(int i = 0; i < motorCount; i++)
                motors[i] = -1 * speed;
    }
    public int getSpeed()
    {
        return speed;
    }
    public void ServoLeft()
    {
        for(int i = 0; i < servoCount; i++)
        {   
            if(servos[i] > 0)
                servos[i] = servos[i] - 1;
        }
    }
    public void ServoRight()
    {
        for(int i = 0; i < servoCount; i++)
        {   
            if(servos[i] < 360)
                servos[i] = servos[i] + 1;
        }
    }
    public void Mode()
    {
        switch(InfoCanvas.canvasMode)
        {
            case "dark":
                InfoCanvas.canvasMode = "gray";
                break;
            case "gray":
                InfoCanvas.canvasMode = "light";
                break;
            case "light":
                InfoCanvas.canvasMode = "dark";
                break;
        }
    }
    

    public int getMotorPower(int x)
    {
        if(x < 0 || x > 6)
        {
            return 0;
        }
        else
            return motors[x];
    }

    public int getServoAngle(int x)
    {
        if(x < 0 || x > 6)
        {
            return 0;
        }
        else
            return servos[x];
    }

    
}
